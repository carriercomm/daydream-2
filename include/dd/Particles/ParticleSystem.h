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

#ifndef ParticleSystem_h__
#define ParticleSystem_h__

#include "Core/System.h"
#include "Core/EventBroker.h"
#include "Core/Color.h"
#include "Core/CTransform.h"
#include "Core/EKeyUp.h"
#include "Rendering/CPointLight.h"
#include "Rendering/CSprite.h"
#include "Transform/TransformSystem.h"
#include "CParticle.h"
#include "CParticleEmitter.h"

namespace dd
{

namespace Systems
{

class ParticleSystem : public System
{
public:
	ParticleSystem(World* world, std::shared_ptr<dd::EventBroker> eventBroker)
		: System(world, eventBroker)
	{ }

	void RegisterComponents(ComponentFactory* cf) override;
	void Update(double dt) override;
	void UpdateEntity(double dt, EntityID entity, EntityID parent) override;
	void Initialize() override;

	//void CreateExplosion(glm::vec3 _pos, double _lifeTime, int _particlesToSpawn, std::string _spritePath, glm::quat _relativeUpOri, float _speed, float _spreadAngle, float _particleScale);

	virtual bool OnCommand(const Events::KeyUp &event) { return false; }

private:
	void SpawnParticles(EntityID emitterID);
	float RandomizeAngle(float spreadAngle);
	//void ScaleInterpolation(double timeProgress, std::vector<float> spectrum, glm::vec3 &scale);
	void VectorInterpolation(double timeProgress, std::vector<glm::vec3> spectrum, glm::vec3 &velocity);
	void ScalarInterpolation(double timeProgress, std::vector<float> spectrum, float &alpha);
	void Billboard();
	//std::map<EntityID, std::list<ParticleData>> m_ParticleEmitter;
	
	std::shared_ptr<Systems::TransformSystem> m_TransformSystem;

	bool tempSpawnedExplosions;
	
	std::map<EntityID, double> m_ExplosionEmitters;
	std::map<EntityID, EntityID> m_ParticlesToEmitter;
};

}


}

#endif // !ParticleSystem_h__