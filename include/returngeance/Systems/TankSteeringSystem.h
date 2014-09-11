#include <array>
#include "System.h"
#include "Events/TankSteer.h"
#include "Events/SetVelocity.h"
#include "Events/ApplyForce.h"
#include "Events/ApplyPointImpulse.h"
#include "Events/CreateExplosion.h"
#include "Events/Collision.h"
#include "Components/Transform.h"
#include "Components/TankSteering.h"
#include "Components/TowerSteering.h"
#include "Components/BarrelSteering.h"
#include "Components/Physics.h"
#include "Components/Vehicle.h"
#include "Components/Player.h"
#include "Components/Model.h"
#include "Components/Team.h"
#include "Systems/TransformSystem.h"
#include "Systems/ParticleSystem.h"
#include "InputController.h"

#include "Components/Health.h"
#include "Components/TankShell.h"
#include "Components/SphereShape.h"
#include "Components/Listener.h"
#include "Components/SoundEmitter.h"

#include "Events/EnableCollisions.h"
#include "Events/DisableCollisions.h"
#include "Components/Trigger.h"
#include "Components/TriggerExplosion.h"
#include "Components/FrameTimer.h"

#include "Events/PlaySFX.h"
#include "Events/PlayBGM.h"
#include "Events/Dead.h"

#include "Events/Damage.h"
#include "Components/Vehicle.h"
#include "Components/Player.h"

#include "Events/SpawnVehicle.h"
#include "Components/SpawnPoint.h"

#include "Components/Wheel.h"
#include "Components/MeshShape.h"
#include "Components/Camera.h"
#include "Components/BoxShape.h"
#include "Components/WheelPair.h"
#include "Components/Input.h"

#include "Events/SetViewportCamera.h"
#include "Events/GameOver.h"

namespace Systems
{

	class TankSteeringSystem : public System
	{
	public:
		TankSteeringSystem(World* world, std::shared_ptr<::EventBroker> eventBroker, std::shared_ptr<::ResourceManager> resourceManager)
			: System(world, eventBroker, resourceManager)
		{ }

		void RegisterComponents(ComponentFactory* cf) override;
		void Initialize() override;

		void Update(double dt) override;
		void UpdateEntity(double dt, EntityID entity, EntityID parent) override;

	private:
		std::map<EntityID, double> m_TimeSinceLastShot;

		EventRelay<TankSteeringSystem, Events::Collision> m_ECollision;
		bool OnCollision(const Events::Collision &e);
		EventRelay<TankSteeringSystem, Events::SpawnVehicle> m_ESpawnVehicle;
		bool OnSpawnVehicle(const Events::SpawnVehicle &e);

		class TankSteeringInputController;
		std::array<std::shared_ptr<TankSteeringInputController>, 4> m_TankInputControllers;

		EntityID CreateTank(int playerID);
		void AddTankWheelPair(EntityID tankEntity, glm::vec3 position, int axleID, bool front);
	};

	class TankSteeringSystem::TankSteeringInputController : InputController<TankSteeringSystem>
	{
	public:
		TankSteeringInputController(std::shared_ptr<::EventBroker> eventBroker, int playerID)
			: InputController(eventBroker)
		{
			PlayerID = playerID;

			m_Horizontal = 0.f;
			m_Vertical = 0.f;
			PositionX = 0;
			PositionY = 0;
			Handbrake = false;

			m_TowerDirection = 0.f;
			m_BarrelDirection = 0.f;
			TowerDirection = 0.f;
			BarrelDirection = 0.f;

			m_Shoot = false;
		}

		int PlayerID;

		float PositionY;
		float PositionX;
		bool Handbrake;

		float TowerDirection;
		float BarrelDirection;
		bool Shoot;

		void Update(double dt);
	protected:
		virtual bool OnCommand(const Events::InputCommand &event);
		//virtual bool OnMouseMove(const Events::MouseMove &event);

	private:
		float m_Horizontal;
		float m_Vertical;

		float m_TowerDirection;
		float m_BarrelDirection;

		bool m_Shoot;
	};
}