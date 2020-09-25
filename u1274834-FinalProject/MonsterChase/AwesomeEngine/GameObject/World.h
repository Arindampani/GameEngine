#pragma once
#include <vector>
#include "GameObject.h"
#include "../Containers/Pointers.h"

namespace Engine {

	void AddGameObjectToWorld(const SmartPointer<GameObject> & i_NewGameObject);
	void RemoveGameObjectFromWorld(WeakPointer<GameObject>& i_NewGameObject);
	std::vector<SmartPointer<GameObject>> GetWorldObjects();

	namespace World {
		void Shutdown();
	}
}



