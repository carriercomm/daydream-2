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
#include "Core/ResourceManager.h"

std::unordered_map<std::string, std::function<dd::Resource*(std::string)>> dd::ResourceManager::m_FactoryFunctions; // type -> factory function
std::unordered_map<std::pair<std::string, std::string>, dd::Resource*> dd::ResourceManager::m_ResourceCache; // (type, name) -> resource
unsigned int dd::ResourceManager::m_CurrentResourceTypeID = 0;
std::unordered_map<std::string, unsigned int> dd::ResourceManager::m_ResourceTypeIDs;
std::unordered_map<unsigned int, unsigned int> dd::ResourceManager::m_ResourceCount;
bool dd::ResourceManager::m_Preloading = false;

unsigned int dd::ResourceManager::GetTypeID(std::string resourceType)
{
	if (m_ResourceTypeIDs.find(resourceType) == m_ResourceTypeIDs.end())
	{
		m_ResourceTypeIDs[resourceType] = m_CurrentResourceTypeID++;
	}
	return m_ResourceTypeIDs[resourceType];
}

unsigned int dd::ResourceManager::GetNewResourceID(unsigned int typeID)
{
	return m_ResourceCount[typeID]++;
}

bool dd::ResourceManager::IsResourceLoaded(std::string resourceType, std::string resourceName)
{
	return m_ResourceCache.find(std::make_pair(resourceType, resourceName)) != m_ResourceCache.end();
}