#pragma once
#include "../Containers/Pointers.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/World.h"

#include <functional>

namespace Engine {
	namespace Collision {

		void Init();
		void Run(const float& i_dt);
		void ShutDown();
		void AddCollidable(const SmartPointer<GameObject>& i_GameObject, const Vector3& i_Center, const Vector3& i_Extents);
	}

}

