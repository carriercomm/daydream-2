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

#ifndef Physics_Vehicle_h__
#define Physics_Vehicle_h__

//#include "PrecompiledHeader.h"

#include <Common/Base/hkBase.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/System/Error/hkDefaultError.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/Config/hkConfigVersion.h>
#include <Common/Base/Memory/System/hkMemorySystem.h>
#include <Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>
#include <Common/Base/Container/String/hkStringBuf.h>

// Vehicle page 425 in documentation
#include <Physics2012/Vehicle/hkpVehicleInstance.h>

#include <Physics2012/Vehicle/AeroDynamics/Default/hkpVehicleDefaultAerodynamics.h>
#include <Physics2012/Vehicle/DriverInput/Default/hkpVehicleDefaultAnalogDriverInput.h>
#include <Physics2012/Vehicle/Brake/Default/hkpVehicleDefaultBrake.h>
#include <Physics2012/Vehicle/Engine/Default/hkpVehicleDefaultEngine.h>
#include <Physics2012/Vehicle/VelocityDamper/Default/hkpVehicleDefaultVelocityDamper.h>
#include <Physics2012/Vehicle/Steering/Default/hkpVehicleDefaultSteering.h>
#include <Physics2012/Vehicle/Steering/hkpVehicleSteering.h>
#include <Physics2012/Vehicle/Suspension/Default/hkpVehicleDefaultSuspension.h>
#include <Physics2012/Vehicle/Transmission/Default/hkpVehicleDefaultTransmission.h>
#include <Physics2012/Vehicle/WheelCollide/RayCast/hkpVehicleRayCastWheelCollide.h>
#include <Physics2012/Vehicle/WheelCollide/RayCast/hkpVehicleRayCastWheelCollide.h>
#include <Physics2012/Collide/Filter/Group/hkpGroupFilter.h>

#include "Core/World.h"
#include "Core/CTransform.h"
#include "CVehicle.h"
#include "CWheel.h"

/// Tank specific steering implementation. Rear wheels steer in opposite direction
/// to front wheels.
class TankSteering: public hkpVehicleDefaultSteering
{
public:
	virtual void calcSteering(const hkReal deltaTime, const hkpVehicleInstance* vehicle, const hkpVehicleDriverInput::FilteredDriverInputOutput& filteredInfoOutput, SteeringAnglesOutput& steeringOutput )
	{
		hkpVehicleDefaultSteering::calcMainSteeringAngle( deltaTime, vehicle, filteredInfoOutput, steeringOutput );

		// Wheels.
		for (int w_it = 0; w_it < m_doesWheelSteer.getSize(); w_it++)
		{
			if ( m_doesWheelSteer[w_it] )
			{
				steeringOutput.m_wheelsSteeringAngle [w_it] = steeringOutput.m_mainSteeringAngle;
			}
			else
			{
				// Steer with front and back wheels to simulate a tank.
				steeringOutput.m_wheelsSteeringAngle [w_it] = -steeringOutput.m_mainSteeringAngle;
			}
		}
	}
};

class VehicleSetup
{
public:
	virtual void VehicleSetup::buildVehicle(World *world, const hkpWorld* physicsWorld, hkpVehicleInstance& vehicle, EntityID vehicleEntity, std::vector<EntityID> wheelEntities);

public:
	struct WheelData
	{
		Components::Wheel* WheelComponent;
		Components::Transform* TransformComponent;

	};
	
	std::vector<WheelData> m_Wheels;

	virtual void setupVehicleData(const hkpWorld* world, hkpVehicleData& data);
	virtual void setupComponent(const hkpVehicleData& data, hkpVehicleDefaultAnalogDriverInput& driverInput);
	virtual void setupComponent(const hkpVehicleData& data, hkpVehicleDefaultEngine& engine, Components::Vehicle vehicleComponent);
	virtual void setupComponent(const hkpVehicleData& data, hkpVehicleDefaultSteering& steering, Components::Vehicle vehicleComponent);
	
	virtual void setupComponent(const hkpVehicleData& data, hkpVehicleDefaultTransmission& transmission, Components::Vehicle vehicleComponent);
	virtual void setupComponent(const hkpVehicleData& data, hkpVehicleDefaultBrake& brake, Components::Vehicle vehicleComponent );
	virtual void setupComponent(const hkpVehicleData& data, hkpVehicleDefaultSuspension& suspension, Components::Vehicle vehicleComponent);
	virtual void setupComponent(const hkpVehicleData& data, hkpVehicleDefaultAerodynamics& aerodynamics, Components::Vehicle vehicleComponent );
	virtual void setupComponent(const hkpVehicleData& data, hkpVehicleDefaultVelocityDamper& velocityDamper, Components::Vehicle vehicleComponent);

	virtual void setupWheelCollide(const hkpWorld* world, const hkpVehicleInstance& vehicle, hkpVehicleRayCastWheelCollide& wheelCollide);

};

#endif // Physics_Vehicle_h__
