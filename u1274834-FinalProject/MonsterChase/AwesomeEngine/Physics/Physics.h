#pragma once
#include "../Math/Point2D.h"
#include "../GameObject/GameObject.h"

namespace Engine {
	namespace Physics
	{

		void Run(const int& dir, const float& dt);

		void Update();
		void AddMovable(const SmartPointer<GameObject>& i_GameObject, const float& i_Mass, const float& i_Kd, const bool& i_hasGravity, const bool& i_isControllable);
		void ShutDown();
		//void AddForceToGameObject(GameObject& io_Object, Point2D i_Forces, float dt);
	};
}

