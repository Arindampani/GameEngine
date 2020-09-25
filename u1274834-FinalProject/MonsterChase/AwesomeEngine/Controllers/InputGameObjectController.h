#pragma once
#include <iostream>
#include "IGameObjectController.h"
namespace Engine {
	class InputGameObjectController : public IGameObjectController
	{
	public:
		void SetGameObject(GameObject* i_pGameObject) override { m_pGameObject = i_pGameObject; }

		void UpdateGameObject() override {
			if (m_pGameObject) {
				Vector3 Direction = getMovementDirectionFromUser();
				Vector3 newPosition = Direction + m_pGameObject->GetPosition();
				m_pGameObject->SetPosition(newPosition);
			}
		}

		Vector3 getMovementDirectionFromUser();
	private:

		GameObject* m_pGameObject;
	};
}

