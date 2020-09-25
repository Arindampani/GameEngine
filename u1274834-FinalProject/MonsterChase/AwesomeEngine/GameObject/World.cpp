#include "GameObject.h"
#include "../Containers/Pointers.h"
#include "World.h"

#include <future>

static std::mutex WorldObjectsMutex;
namespace Engine {
	//static std::mutex s_WorldMutex;
	std::vector<SmartPointer<GameObject>> WorldObjects;
	
	void AddGameObjectToWorld(const SmartPointer<GameObject> & i_NewGameObject)
	{
		//std::lock_guard<std::mutex> lock(s_WorldMutex);
		WorldObjects.push_back(i_NewGameObject);
	}

	void RemoveGameObjectFromWorld(WeakPointer<GameObject>& i_NewGameObject) {
		SmartPointer<GameObject> GameObject = i_NewGameObject.Acquire();

		//std::lock_guard<std::mutex> lock(WorldObjectsMutex);

		for (auto& iter : WorldObjects)
		{
			if (iter == i_NewGameObject)
			{
				if (iter != WorldObjects.back())
					std::swap(iter, WorldObjects.back());

				WorldObjects.pop_back();
				return;
			}
		}
	}

	std::vector<SmartPointer<GameObject>> GetWorldObjects() {
		return WorldObjects;
	}

	namespace World {
		void Shutdown() {
			WorldObjects.clear();
			WorldObjects.shrink_to_fit();
		}
	}
}