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

#ifndef SoundEmitter_h__
#define SoundEmitter_h__

#include <vector>

#include <fmod.hpp>
#include <fmod_errors.h>

#include "Core/System.h"
#include "Core/CTransform.h"
#include "Core/EComponentCreated.h"
#include "Transform/TransformSystem.h"

#include "Sound.h"
#include "CSoundEmitter.h"
#include "CListener.h"
#include "EPlaySFX.h"
#include "EPlayBGM.h"
#include "EStopSound.h"

namespace Systems
{

class SoundSystem : public System
{
public:
	SoundSystem(World* world, std::shared_ptr<::EventBroker> eventBroker, std::shared_ptr<::ResourceManager> resourceManager)
		: System(world, eventBroker, resourceManager)
	{ }
	~SoundSystem();
	void RegisterComponents(ComponentFactory* cf) override;
	void RegisterResourceTypes(std::shared_ptr<::ResourceManager> rm) override;
	void Initialize() override;
	void Update(double dt) override;
	void UpdateEntity(double dt, EntityID entity, EntityID parent) override;
	void OnComponentRemoved(EntityID entity, std::string type, Component* component) override;
	FMOD_SYSTEM* GetFMODSystem() const { return m_System; }
private:
	// Events
	EventRelay<SoundSystem, Events::ComponentCreated> m_EComponentCreated;
	bool OnComponentCreated(const Events::ComponentCreated &event);
	EventRelay<SoundSystem, Events::PlaySFX> m_EPlaySFX;
	bool PlaySFX(const Events::PlaySFX &event);
	EventRelay<SoundSystem, Events::PlayBGM> m_EPlayBGM;
	bool PlayBGM(const Events::PlayBGM &event);
	EventRelay<SoundSystem, Events::StopSound> m_EStopSound;
	bool StopSound(const Events::StopSound &event);

	void LoadSound(FMOD_SOUND*&, std::string, float, float);
	void PlaySound(FMOD_CHANNEL**, FMOD_SOUND*, float volume, bool loop);
	
	FMOD_SYSTEM* m_System;
	FMOD_BOOL m_isPlaying;
	FMOD_CHANNEL* m_BGMChannel;
	std::vector<EntityID> m_Listeners;
	std::map<EntityID, FMOD_CHANNEL*> m_Channels;
	std::map<EntityID, FMOD_CHANNEL*> m_DeleteChannels;
	std::map<EntityID, FMOD_SOUND*> m_DeleteSounds;	
	std::map<EntityID, FMOD_SOUND*> m_Sounds;	
	std::shared_ptr<Systems::TransformSystem> m_TransformSystem;
	
};

}
#endif // !SoundEmitter_h__

