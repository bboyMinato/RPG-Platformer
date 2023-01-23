#include "../include/ObjectManager.h"
ObjectManager* ObjectManager::_instance = nullptr;

GameObject* ObjectManager::CreateObject(std::string type, Properties* props)
{
	GameObject* object = nullptr;
	auto it = _typeRegistry.find(type);

	if (it != _typeRegistry.end())
		object = it->second(props);

	return object;
}

void ObjectManager::RegisterType(std::string className, std::function<GameObject* (Properties* props)> type)
{
	_typeRegistry[className] = type;
}
