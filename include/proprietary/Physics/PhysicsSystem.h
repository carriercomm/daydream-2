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

#ifndef PhysicsSystem_h__
#define PhysicsSystem_h__

#define HKVECTOR4_TO_GLMVEC3(hkvec) \
	glm::vec3(hkvec(0), hkvec(1), hkvec(2))
#define GLMVEC3_TO_HKVECTOR4(glmvec) \
	hkVector4(glmvec.x, glmvec.y, glmvec.z)

#define HKQUATERNION_TO_GLMQUAT(gkquat) \
	glm::quat(gkquat(3), gkquat(0), gkquat(1), gkquat(2))
#define GLMQUAT_TO_HKQUATERNION(glmquat) \
	hkQuaternion(glmquat.x, glmquat.y, glmquat.z, glmquat.w)

#include "Core/System.h"
#include "Core/OBJ.h"
#include "Core/CTransform.h"
#include "Trigger/ELeaveTrigger.h"
#include "Transform/TransformSystem.h"
#include "CPhysics.h"
#include "CBoxShape.h"
#include "CSphereShape.h"
#include "CVehicle.h"
#include "CMeshShape.h"
#include "CHingeConstraint.h"
#include "CWheelPair.h"
//#include "CPlayer.h"
#include "ESetVelocity.h"
#include "EApplyForce.h"
#include "EApplyPointImpulse.h"
#include "ECollision.h"
#include "Trigger/CTrigger.h"
#include "Core/CTemplate.h"
#include "Trigger/EEnterTrigger.h"

// Math and base include
#include <Common/Base/hkBase.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/System/Error/hkDefaultError.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/Config/hkConfigVersion.h>
#include <Common/Base/Memory/System/hkMemorySystem.h>
#include <Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>
#include <Common/Base/Container/String/hkStringBuf.h>

// Dynamics includes
#include <Physics2012/Collide/hkpCollide.h>
#include <Physics2012/Collide/Agent/ConvexAgent/SphereBox/hkpSphereBoxAgent.h>
#include <Physics2012/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics2012/Collide/Shape/Convex/Sphere/hkpSphereShape.h>
#include <Physics2012/Collide/Dispatch/hkpAgentRegisterUtil.h>

#include <Physics2012/Dynamics/World/hkpWorld.h>
#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Physics2012/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>

// Visual Debugger includes
#include <Common/Visualize/hkVisualDebugger.h>
#include <Physics2012/Utilities/VisualDebugger/hkpPhysicsContext.h>

#include <Physics2012/Collide/Shape/Compound/Collection/ExtendedMeshShape/hkpExtendedMeshShape.h>
#include <Physics2012/Collide/Shape/Compound/Tree/Mopp/hkpMoppBvTreeShape.h>
#include <Physics2012/Collide/Shape/Compound/Tree/Mopp/hkpMoppUtility.h>

#include <Common/Base/Thread/JobQueue/hkJobQueue.h>
#include <Common/Base/Thread/Job/ThreadPool/Cpu/hkCpuJobThreadPool.h>
#include <Common/Base/DebugUtil/MultiThreadCheck/hkMultiThreadCheck.h>
#include <Physics/Constraint/Data/Hinge/hkpHingeConstraintData.h>
#include <Physics/Constraint/Data/LimitedHinge/hkpLimitedHingeConstraintData.h>

#include <Physics2012/Collide/Shape/Compound/Collection/List/hkpListShape.h>
#include <Physics2012/Internal/Collide/StaticCompound/hkpStaticCompoundShape.h>
#include <Physics2012/Collide/Util/ShapeShrinker/hkpShapeShrinker.h>
#include <Physics2012/Collide/Shape/Misc/Bv/hkpBvShape.h>

#include <unordered_map>

#include <Physics2012/Dynamics/Collide/ContactListener/hkpContactListener.h>

#include <Physics2012/Collide/Agent/CompoundAgent/BvTree/hkpBvTreeAgent.h>

#include <Physics2012/Collide/Shape/Misc/PhantomCallback/hkpPhantomCallbackShape.h>
#include "EEnableCollisions.h"
#include "EDisableCollisions.h"
#include "VehicleSetup.h"


namespace Systems
{
class PhysicsSystem : public System
{
public:
	class MyCollisionResolution: public hkReferencedObject, public hkpContactListener
	{
	public:

		MyCollisionResolution(Systems::PhysicsSystem* physicsSystem)
			: m_PhysicsSystem(physicsSystem) { }

		virtual void contactPointCallback( const hkpContactPointEvent& event ) 
		{
			EntityID entity1 = m_PhysicsSystem->m_RigidBodyEntities[event.getBody(0)];
			EntityID entity2 = m_PhysicsSystem->m_RigidBodyEntities[event.getBody(1)];

			Events::Collision e;
			e.Entity1 = entity1;
			e.Entity2 = entity2;
			m_PhysicsSystem->EventBroker->Publish(e);
		}
		
	private:
		Systems::PhysicsSystem* m_PhysicsSystem;
	};
	friend class MyCollisionResolution;

	class PhantomCallbackShape: public hkpPhantomCallbackShape
	{
	public:

		PhantomCallbackShape(Systems::PhysicsSystem* physicsSystem)
			: m_PhysicsSystem(physicsSystem) { }

		virtual void phantomEnterEvent( const hkpCollidable* collidableA, const hkpCollidable* collidableB, const hkpCollisionInput& env )
		{
			EntityID entity1 = m_PhysicsSystem->m_RigidBodyEntities[hkpGetRigidBody(collidableA)];
			EntityID entity2 = m_PhysicsSystem->m_RigidBodyEntities[hkpGetRigidBody(collidableB)];

			if(m_PhysicsSystem->m_World->ValidEntity(entity1) && m_PhysicsSystem->m_World->ValidEntity(entity2))
			{
				Events::EnterTrigger e;
				e.Trigger = entity1;
				e.Entity = entity2;
				m_PhysicsSystem->EventBroker->Publish(e);
			}
		}

		virtual void phantomLeaveEvent( const hkpCollidable* collidableA, const hkpCollidable* collidableB )
		{
			EntityID entity1 = m_PhysicsSystem->m_RigidBodyEntities[hkpGetRigidBody(collidableA)];
			EntityID entity2 = m_PhysicsSystem->m_RigidBodyEntities[hkpGetRigidBody(collidableB)];

			if(m_PhysicsSystem->m_World->ValidEntity(entity1) && m_PhysicsSystem->m_World->ValidEntity(entity2))
			{
				Events::LeaveTrigger e;
				e.Trigger = entity1;
				e.Entity = entity2;
				m_PhysicsSystem->EventBroker->Publish(e);
			}
		}

	private:
		Systems::PhysicsSystem* m_PhysicsSystem;
	};
	friend class PhantomCallbackShape;
	
	PhysicsSystem(World* world, std::shared_ptr<::EventBroker> eventBroker, std::shared_ptr<::ResourceManager> resourceManager)
		: System(world, eventBroker, resourceManager) { }

	void RegisterComponents(ComponentFactory* cf) override;
	void Initialize() override;

	void Update(double dt) override;
	void UpdateEntity(double dt, EntityID entity, EntityID parent) override;
	void OnComponentRemoved(EntityID entity, std::string type, Component* component) override;
	void OnEntityCommit(EntityID entity) override;
	void OnEntityRemoved(EntityID entity) override;
	
private:
	double m_Accumulator;
	hkpWorld* m_PhysicsWorld;
	hkpGroupFilter* m_CollisionFilter;

	// Events
	EventRelay<PhysicsSystem, Events::TankSteer> m_ETankSteer;
	bool OnTankSteer(const Events::TankSteer &event);
	EventRelay<PhysicsSystem, Events::JeepSteer> m_EJeepSteer;
	bool OnJeepSteer(const Events::JeepSteer &event);
	EventRelay<PhysicsSystem, Events::SetVelocity> m_ESetVelocity;
	bool OnSetVelocity(const Events::SetVelocity &event);
	EventRelay<PhysicsSystem, Events::ApplyForce> m_EApplyForce;
	bool OnApplyForce(const Events::ApplyForce &event);
	EventRelay<PhysicsSystem, Events::ApplyPointImpulse> m_EApplyPointImpulse;
	bool OnApplyPointImpulse(const Events::ApplyPointImpulse &event);

	EventRelay<PhysicsSystem, Events::EnableCollisions> m_EEnableCollisions;
	bool OnEnableCollisions(const Events::EnableCollisions &e);
	EventRelay<PhysicsSystem, Events::DisableCollisions> m_EDisableCollisions;
	bool OnDisableCollisions(const Events::DisableCollisions &e);
	EventRelay<PhysicsSystem, Events::Dead> m_EDead;
	bool OnDead(const Events::Dead &e);


	void SetUpPhysicsState(EntityID entity, EntityID parent);
	void TearDownPhysicsState(EntityID entity, EntityID parent);

	hkVisualDebugger* m_VisualDebugger;
	void SetupVisualDebugger(hkpPhysicsContext* worlds);
	void StepVisualDebugger();
	static void HK_CALL HavokErrorReport(const char* msg, void*);
	void SetupPhysics(hkpWorld* physicsWorld);
	
	std::unordered_map<EntityID, hkpRigidBody*> m_RigidBodies;
	std::unordered_map<hkpRigidBody*, EntityID> m_RigidBodyEntities;
	
	hkJobThreadPool* m_ThreadPool;
	hkJobQueue* m_JobQueue;
	int m_TotalNumThreadsUsed;
	hkpPhysicsContext* m_Context;

	std::unordered_map<EntityID, hkpVehicleInstance*> m_Vehicles;
	std::vector<EntityID> m_Wheels;

	hkpVehicleInstance* Systems::PhysicsSystem::createVehicle(VehicleSetup& vehicleSetup, hkpRigidBody* chassis);


	struct ShapeArrayData
	{
		ShapeArrayData(EntityID entity, hkpConvexShape* convexShape, hkpShape* shape)
		{
			Entity = entity;
			ConvexShape = convexShape;
			Shape = shape;
		}
		EntityID Entity;
		hkpConvexShape* ConvexShape;
		hkpShape* Shape;
	};
	std::unordered_map<EntityID, std::list<ShapeArrayData>> m_Shapes;
	std::unordered_map<EntityID, hkpListShape*> m_ListShapes;



	struct  ExtendedShapeData
	{
		hkpExtendedMeshShape* ExtendedMeshShape;
		std::vector<hkReal>* Vertices;
		std::vector<hkUint16>* VertexIndices;
		hkpMoppCode* Code;
		hkpMoppBvTreeShape* MoppShape;
	};
	std::unordered_map<EntityID, ExtendedShapeData > m_ExtendedMeshShapes;

	MyCollisionResolution* m_collisionResolution;
};

}
#endif // PhysicsSystem_h__
