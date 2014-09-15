#ifndef ComponentFactory_h__
#define ComponentFactory_h__

#include <string>
#include <memory>
#include <functional>
#include <map>

template <typename T>
class Factory
{
public:
	/*void Register(std::string name, std::function<T(void)> factoryFunction)
	{
		m_FactoryFunctions[name] = factoryFunction;
	}*/

	template <typename T2>
	void Register(std::function<T*(void)> factoryFunction)
	{
		m_FactoryFunctions[typeid(T2).name()] = factoryFunction;
	}

	template <typename T2>
	void Register()
	{
		m_FactoryFunctions[typeid(T2).name()] = []() { return new T2(); };
		m_CopyFunctions[typeid(T2).name()] = [](const T* t) { return new T2(*static_cast<const T2*>(t)); };
	}

	T* Create(std::string name)
	{
		auto it = m_FactoryFunctions.find(name);
		if (it != m_FactoryFunctions.end())
		{
			return it->second();
		}
		else
		{
			return nullptr;
		}
	}

	template <typename T2>
	T* Create()
	{
		auto it = m_FactoryFunctions.find(typeid(T2).name());
		if (it != m_FactoryFunctions.end())
		{
			return it->second();
		}
		else
		{
			return nullptr;
		}
	}

	T* Copy(std::string name, const T* toCopy)
	{
		auto it = m_CopyFunctions.find(name);
		if (it != m_CopyFunctions.end())
		{
			return it->second(toCopy);
		} 
		else
		{
			return nullptr;
		}
	}

	template <typename T2>
	T* Copy(const T* toCopy)
	{
		auto it = m_CopyFunctions.find(typeid(T2).name());
		if (it != m_CopyFunctions.end())
		{
			return it->second(toCopy);
		} else
		{
			return nullptr;
		}
	}

private:
	std::map<std::string, std::function<T*(void)>> m_FactoryFunctions;
	std::map<std::string, std::function<T*(const T*)>> m_CopyFunctions;
};

#endif // ComponentFactory_h__