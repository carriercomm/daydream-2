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

#include <iostream>
#include "Core/Util/Logging.h"

#include "Core/Component.h"
#include "Core/Util/Factory.h"
#include "Core/Util/FileWatcher.h"

using namespace dd;

struct TestComponent : public Component
{
	int Int = 5;
	float Float = 1.33333f;
	double Double = 1.33333;
	std::string String = "Hello World";
};

int main(int argc, char* argv[])
{
	FileWatcher fw("test");

	fw.Watch("test.txt", [](std::string path, FileWatcher::FileEventFlags flags)
	{ 
		if (flags & FileWatcher::FileEventFlags::SizeChanged) {
			std::cout << path << " says size changed!" << std::endl;
		}
		
		if (flags & FileWatcher::FileEventFlags::DateChanged) {
			std::cout << path << " says date changed!" << std::endl;
		}
	
		if (flags & FileWatcher::FileEventFlags::Created) {
			std::cout << path << " says created!" << std::endl;
		}

		if (flags & FileWatcher::FileEventFlags::Deleted) {
			std::cout << path << " says deleted!" << std::endl;
		}
	});
	std::cin.get();
	fw.Watch("test2.txt", nullptr);

	while (true)
	{

	}
	return 0;

	auto componentFactory = new Factory<Component>();
	componentFactory->Register<TestComponent>();

	auto component1 = static_cast<TestComponent*>(componentFactory->Create<TestComponent>());
	std::cout << "component1->Int = " << component1->Int << std::endl;
	std::cout << "component1->Float = " << component1->Float << std::endl;
	std::cout << "component1->Double = " << component1->Double << std::endl;
	std::cout << "component1->String = " << component1->String.c_str() << std::endl;

	auto component2 = static_cast<TestComponent*>(componentFactory->Copy<TestComponent>(component1));
	std::cout << "component2->Int = " << component2->Int << std::endl;
	std::cout << "component2->Float = " << component2->Float << std::endl;
	std::cout << "component2->Double = " << component2->Double << std::endl;
	std::cout << "component2->String = " << component2->String.c_str() << std::endl;


}