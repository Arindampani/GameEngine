#pragma once
#include "../GameObject/GameObject.h"
#include "../Math/Point2D.h"
namespace Engine {
	class IGameObjectController
	{
	public:
		virtual void SetGameObject(GameObject* i_pObject) = 0;
		virtual void UpdateGameObject() = 0;
	};
}