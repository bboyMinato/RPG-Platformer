#pragma once
#include <map>
#include <string>
#include <memory>
#include <functional>
#include "GameObject.h"

class ObjectManager
{
public:
	static ObjectManager* GetInstance() { return _instance = (_instance != nullptr) ? _instance : new ObjectManager(); }

	GameObject* CreateObject(std::string type, Properties* props);
	void RegisterType(std::string className, std::function<GameObject* (Properties* props)> type); 	

private:
	static ObjectManager* _instance;
	ObjectManager() {}
	std::map<std::string, std::function<GameObject* (Properties* props)>> _typeRegistry;
};

template<class Type>
class RegisterObject
{
public:
	RegisterObject(std::string className)
	{
		ObjectManager::GetInstance()->RegisterType(className, [](Properties* props)->GameObject* {return new Type(props);});
	}
};