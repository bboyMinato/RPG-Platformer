#pragma once
#include <map>
#include <string>
#include <memory>
#include <functional>
#include "GameObject.h"

class ObjectFactory
{
public:
	GameObject* CreateObject(std::string type, Properties* props);
	void RegisterType(std::string className, std::function<GameObject* (Properties* props)>type); 
	static ObjectFactory* GetInstance() { return _instance = (_instance != nullptr) ? _instance : new ObjectFactory(); }

private:
	static ObjectFactory* _instance;
};

