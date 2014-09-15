/*
	This file is part of Daydream Engine.
	Copyright 2014 Adam Byléhn, Tobias Dahl, Simon Holmberg, Viktor Ljung
	
	Daydream Engine is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	Daydream Engine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.
	
	You should have received a copy of the GNU Lesser General Public License
	along with Daydream Engine.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "PrecompiledHeader.h"
#include "Sound/SoundSystem.h"
#include "Core/World.h"

Systems::SoundSystem::~SoundSystem()
{
	FMOD_System_Release(m_System);
}

void Systems::SoundSystem::Initialize()
{
	EVENT_SUBSCRIBE_MEMBER(m_EComponentCreated, &SoundSystem::OnComponentCreated);
	EVENT_SUBSCRIBE_MEMBER(m_EPlaySFX, &SoundSystem::PlaySFX);
	EVENT_SUBSCRIBE_MEMBER(m_EPlayBGM, &SoundSystem::PlayBGM);
	EVENT_SUBSCRIBE_MEMBER(m_EStopSound, &SoundSystem::StopSound);
	m_isPlaying = false;
	m_TransformSystem = m_World->GetSystem<Systems::TransformSystem>();
	FMOD_System_Create(&m_System);
	FMOD_RESULT result = FMOD_System_Init(m_System, 32, FMOD_INIT_3D_RIGHTHANDED | FMOD_INIT_ENABLE_PROFILE, 0);
	if(result != FMOD_OK)
	{
		LOG_ERROR("Did initialized load FMOD correctly");
	}
	else
	{
		LOG_INFO("FMOD initialized successfully");
	}
	FMOD_System_Set3DSettings(m_System, 0.f, 1.f, 1.f); //dopplerScale, distancefactor, rolloffscale
	
}

void Systems::SoundSystem::RegisterComponents(ComponentFactory* cf)
{
	cf->Register<Components::SoundEmitter>([]() { return new Components::SoundEmitter(); });
	cf->Register<Components::Listener>([]() { return new Components::Listener(); });
}

void Systems::SoundSystem::RegisterResourceTypes(std::shared_ptr<::ResourceManager> rm)
{
	rm->RegisterType("Sound3D", [this](std::string resourceName) { return new Sound(resourceName, this->m_System, Components::SoundEmitter::SoundType::SOUND_3D); });
	rm->RegisterType("Sound2D", [this](std::string resourceName) { return new Sound(resourceName, this->m_System, Components::SoundEmitter::SoundType::SOUND_2D); });
}

void Systems::SoundSystem::Update(double dt)
{
	FMOD_System_Update(m_System);
	
	//Delete sounds. Not until it's done playing
	std::map<EntityID, FMOD_CHANNEL*>::iterator it;
	for(it = m_DeleteChannels.begin(); it != m_DeleteChannels.end();)
	{
		FMOD_Channel_IsPlaying(it->second, &m_isPlaying);
		if(m_isPlaying)
		{
			it++;
		}
		else
		{
// 			FMOD_Sound_Release(m_DeleteSounds[it->first]);
 			m_DeleteSounds.erase(it->first);
			it = m_DeleteChannels.erase(it);
		}

	}
	//LOG_INFO("Antal emitters i listan: %i", m_Channels.size());

	for(it = m_Channels.begin(); it != m_Channels.end();)
	{
		FMOD_Channel_IsPlaying(it->second, &m_isPlaying);
		if(!m_isPlaying)
		{
			it = m_Channels.erase(it);			
		}
		else
		{
			it++;
		}
	}
}

void Systems::SoundSystem::UpdateEntity(double dt, EntityID entity, EntityID parent)
{
	auto listener = m_World->GetComponent<Components::Listener>(entity);
	if(listener)
	{
		int lID = std::find(m_Listeners.begin(), m_Listeners.end(), entity) - m_Listeners.begin();
		auto lTransform = m_World->GetComponent<Components::Transform>(entity);
		
		glm::vec3 tPos = m_TransformSystem->AbsolutePosition(entity);
		FMOD_VECTOR lPos = {tPos.x, tPos.y, tPos.z}; 

		glm::vec3 tVel = (lTransform->Velocity * 1000.f) / (float)dt;
		FMOD_VECTOR lVel = {tVel.x, tVel.y, tVel.z};

		glm::vec3 tUp = glm::normalize(lTransform->Orientation * glm::vec3(0,1,0));
		FMOD_VECTOR lUp = {tUp.x, tUp.y, tUp.z}; 
		glm::vec3 tForward = glm::normalize(lTransform->Orientation * glm::vec3(0,0,-1));
		FMOD_VECTOR lForward = {tForward.x, tForward.y, tForward.z};

		FMOD_System_Set3DListenerAttributes(m_System, lID, (const FMOD_VECTOR*)&lPos, (const FMOD_VECTOR*)&lVel, (const FMOD_VECTOR*)&lForward, (const FMOD_VECTOR*)&lUp);
	}

	auto emitter = m_World->GetComponent<Components::SoundEmitter>(entity);
	if(emitter)
	{
		FMOD_CHANNEL* channel = m_Channels[entity];
		FMOD_SOUND* sound = m_Sounds[entity];
		auto eTransform = m_World->GetComponent<Components::Transform>(entity);
		
		glm::vec3 tPos = m_TransformSystem->AbsolutePosition(entity);
		FMOD_VECTOR ePos = {tPos.x, tPos.y, tPos.z};

		glm::vec3 tVel = (eTransform->Velocity * 1000.f) / float(dt);
		FMOD_VECTOR eVel = {tVel.x, tVel.y, tVel.z};
		
		FMOD_Channel_Set3DAttributes(channel, &ePos, &eVel);
	}
}

bool Systems::SoundSystem::OnComponentCreated(const Events::ComponentCreated &event)
{
	auto listener = std::dynamic_pointer_cast<Components::Listener>(event.Component);
	if(listener)
	{
		m_Listeners.push_back(listener->Entity);
	}

	auto emitter = std::dynamic_pointer_cast<Components::SoundEmitter>(event.Component);
	if(emitter)
	{
		FMOD_CHANNEL* channel;
		FMOD_SOUND* sound;

		std::string path = emitter->Path;
		float volume = emitter->Gain;
		bool loop = emitter->Loop;
		float maxDist = emitter->MaxDistance;
		float minDist = emitter->MinDistance;
		float pitch = emitter->Pitch;
		LoadSound(sound, path, maxDist, minDist);
		m_Channels.insert(std::make_pair(emitter->Entity, channel));
		m_Sounds.insert(std::make_pair(emitter->Entity, sound));
	}
	return true;
}

bool Systems::SoundSystem::PlaySFX(const Events::PlaySFX &event)
{
	auto eEntity = m_World->CreateEntity();
	auto eTransform = m_World->AddComponent<Components::Transform>(eEntity);
	eTransform->Position = event.Position;
	auto eComponent = m_World->AddComponent<Components::SoundEmitter>(eEntity);
	eComponent->MinDistance = event.MinDistance;
	eComponent->MaxDistance= event.MaxDistance;
	eComponent->Loop = event.Loop;
	eComponent->Gain = event.Volume;
	
	eComponent->type = Components::SoundEmitter::SoundType::SOUND_3D;
	Sound* sound = ResourceManager->Load<Sound>("Sound3D", event.Resource);
	m_Sounds[eEntity] = *sound;
	FMOD_Sound_Set3DMinMaxDistance(*sound, eComponent->MinDistance, eComponent->MaxDistance);

	PlaySound(&m_Channels[eEntity], *sound, 1.0, eComponent->Loop);
	return true;
}

bool Systems::SoundSystem::PlayBGM(const Events::PlayBGM &event)
{
	FMOD_RESULT result;
	result = FMOD_Channel_Stop(m_BGMChannel);
	if(result != FMOD_OK)	
		LOG_INFO("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	Sound* sound = ResourceManager->Load<Sound>("Sound2D", event.Resource);

	result = FMOD_System_PlaySound(m_System, FMOD_CHANNEL_FREE, *sound, false, &m_BGMChannel);
	if(result != FMOD_OK)	
		LOG_INFO("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	FMOD_Channel_SetMode(m_BGMChannel, FMOD_LOOP_NORMAL);
	FMOD_Sound_SetLoopCount(*sound, -1);

	return true;
}



bool Systems::SoundSystem::StopSound(const Events::StopSound &event)
{
	auto eComp = m_World->GetComponent<Components::SoundEmitter>(event.Emitter);
	if(eComp)
	{
		FMOD_Channel_Stop(m_Channels[event.Emitter]);
	}
	else
	{
		FMOD_Channel_Stop(m_BGMChannel);
	}
	return true;
}

void Systems::SoundSystem::LoadSound(FMOD_SOUND* &sound, std::string filePath, float maxDist, float minDist)
{
	FMOD_RESULT result = FMOD_System_CreateSound(m_System, filePath.c_str(), FMOD_3D | FMOD_HARDWARE , 0, &sound);
	if (result != FMOD_OK)
	{
		LOG_ERROR("FMOD did not load file: %s", filePath.c_str());
	}
	FMOD_Sound_Set3DMinMaxDistance(sound, minDist, maxDist);
}

void Systems::SoundSystem::PlaySound(FMOD_CHANNEL** channel, FMOD_SOUND* sound, float volume, bool loop)
{
	FMOD_System_PlaySound(m_System, FMOD_CHANNEL_FREE, sound, false, channel);
	FMOD_Channel_SetVolume(*channel, volume);
	if(loop)
	{
		FMOD_Channel_SetMode(*channel, FMOD_LOOP_NORMAL);
		FMOD_Sound_SetLoopCount(sound, -1);
	}
}

void Systems::SoundSystem::OnComponentRemoved(EntityID entity, std::string type, Component* component)
{
	auto emitter = dynamic_cast<Components::SoundEmitter*>(component);
	if(emitter)
	{
		m_DeleteChannels.insert(std::make_pair(entity, m_Channels[entity]));
		m_DeleteSounds.insert(std::make_pair(entity, m_Sounds[entity]));
		m_Channels.erase(entity);
		m_Sounds.erase(entity);
	}
}