#include "Physics.h" 
#include "../GameObject/GameObject.h"
#include <vector>
#include"../Math/Utilities.h"
#include "../GameObject/World.h"
#include <Windows.h>
namespace Engine {
	namespace Physics {

		struct Movable
		{
			WeakPointer<GameObject>	m_movableObject;
			//Vector3* m_acceleration;
			//Vector3* m_forces;
			float m_mass;
			float m_Kd;
			bool m_hasGravity;
			bool m_isControllable;

			Movable(const SmartPointer<GameObject>& i_GameObject,
				const float& i_Mass, const float& i_Kd,
				const bool& i_hasGravity,
				const bool& i_isControllable) :
				m_movableObject(i_GameObject),
				//m_acceleration(new Vector3(0.0f, 0.0f, 0.0f)),
				//m_forces(new Vector3(0.0f, 0.0f, 0.0f)),
				m_mass(i_Mass),
				m_Kd(i_Kd),
				m_hasGravity(i_hasGravity),
				m_isControllable(i_isControllable)
			{
			}
		};

		std::vector<Movable*> AllMovables;

		void AddMovable(const SmartPointer<GameObject>& i_GameObject, const float& i_Mass, const float& i_Kd, const bool& i_hasGravity, const bool& i_isControllable) {
			AllMovables.push_back(new Movable(i_GameObject, i_Mass, i_Kd, i_hasGravity,i_isControllable));
		}
		void AddForceToGameObject(SmartPointer<GameObject> & io_Object, Vector3 i_Force, float i_dt) {
				Vector3 Acceleration = i_Force / io_Object->GetMass();

			Vector3 InitialVelocity = io_Object->GetVelocity();
			Vector3 NewVelocity = io_Object->GetVelocity() + (Acceleration * i_dt );
			Vector3 AverageVelocity = (InitialVelocity + NewVelocity) / 2.0f;
			Vector3 NewPosition = io_Object->GetPosition() + (AverageVelocity * i_dt);
			io_Object->SetVelocity(NewVelocity);
			io_Object->SetPosition(NewPosition);


		}

		void Run(const int& i_dir, const float& i_dt) {
			

			for (auto& Ob : AllMovables)
			{
	
					Vector3 force(0.0f, 0.0f, 0.0f);
					Vector3 gravity(0.0f, 0.0f, 0.0f);

					if(Ob->m_hasGravity)
						gravity = Vector3(0, -9.8f/10, 0.0f) * Ob->m_mass;
						
						Vector3 drag(0.0f, 0.0f, 0.0f);
						if (Ob->m_isControllable) {
							if (i_dir == 0) {

								force = Vector3(0.0f, 0.0f, 0.0f);
								drag = Vector3(0.0f, 0.0f, 0.0f);

							}
							else if (i_dir == 1) {

								force = Vector3(0.0f, 500.0f, 0.0f);
								drag = Vector3(0.0f, -100.0f, 0.0f);

							}
							else if (i_dir == 2) {

								force = Vector3(-500.0, 0.0f, 0.0f);
								drag = Vector3(100.0f, 0.0f, 0.0f);

							}
							else if (i_dir == 3) {

								force = Vector3(0.0f, -500.0f, 0.0f);
								drag = Vector3(0.0f, 100.0f, 0.0f);

							}
							else if (i_dir == 4) {

								force = Vector3(500.0f, 0.0f, 0.0f);
								drag = Vector3(-100.0f, 0.0f, 0.0f);

							}
						}
							Vector3 TotalForce = force + gravity + drag;
							SmartPointer<GameObject> ob = Ob->m_movableObject.Acquire();
							AddForceToGameObject(ob, TotalForce, i_dt);

			
			}
		}


		void Update() {

		}

		void ShutDown() {
			AllMovables.clear();
			AllMovables.shrink_to_fit();
		}

		
	}
}