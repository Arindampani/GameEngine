#include "Collision.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Matrix4.h"
#include "../GameObject/GameObject.h"
#include "../Containers/Pointers.h"
#include <Windows.h>
#include <vector>
#include "../GameObject/World.h"
#include "../Init/Engine.h"

namespace Engine {
	namespace Collision {


		struct AABB
		{
			Vector3 m_Center;
			Vector3 m_Extents;

			AABB(const Vector3& i_Center, const Vector3& i_Extents):
			m_Center(i_Center),
			m_Extents(i_Extents){

			}
		};

		struct Collideable
		{
			WeakPointer<GameObject>		m_GameObject;
			AABB						m_BoundingBox;
			Matrix4						m_ObjectToWorld;
			Matrix4						m_OrientationInWorld;
			Vector3						m_BBCenterInWorld;

			Collideable(
				const SmartPointer<GameObject>& i_GameObject,
				const AABB& i_CollisionData,
				const Matrix4& i_ObjectToWorld,
				const Matrix4& i_OrientationInWorld,
				const Vector3& i_BBCenterInWorld):
			m_GameObject(i_GameObject),
			m_BoundingBox(i_CollisionData),
			m_ObjectToWorld(i_ObjectToWorld),
			m_OrientationInWorld(i_OrientationInWorld),
			m_BBCenterInWorld(i_BBCenterInWorld){

			}
		};


		struct CollisionPair
		{
			Collideable* m_CollisionObjects[2];
			float						m_CollisionTime;
			Vector3						m_CollisionNormal;
			CollisionPair(
				Collideable* i_CollisionObject1,
				Collideable* i_CollisionObject2,
				const float& i_collisionTime,
				const Vector3& i_CollisionNormal):
				m_CollisionObjects{i_CollisionObject1,i_CollisionObject2},
				m_CollisionTime(i_collisionTime),
				m_CollisionNormal(i_CollisionNormal)
			{



			}
		};

		std::vector<Collideable*> AllCollideables;

		void AddCollidable(const SmartPointer<GameObject>& i_GameObject, const Vector3& i_Center, const Vector3& i_extents) {
			AABB collisionData(i_Center,i_extents);

			SmartPointer<GameObject> GameObject = i_GameObject;
			Matrix4 ObjectToWorld = Matrix4::CreateTranslation(GameObject->GetPosition()) * Matrix4::CreateZRotation(GameObject->GetRotation().z());
			Matrix4 Orientation = Matrix4::CreateZRotation(GameObject->GetRotation().z());
			Vector4 NewCenter = ObjectToWorld * Vector4(i_Center, 1.0);
			AllCollideables.push_back(new Collideable(i_GameObject,collisionData,ObjectToWorld,Orientation, Vector3(NewCenter.x(), NewCenter.y(), NewCenter.z())));

		}

		void Init() {


		}

		void ShutDown() {

			AllCollideables.clear();
			AllCollideables.shrink_to_fit();
		}


		bool CheckSeperatingAxis(const Vector4& i_CollisionAxis, Collideable& i_Obj1, const Vector4& i_Obj1CenterInWorld ,Collideable i_Obj2, const Vector4& i_Obj2CenterInWorld, const float& i_dt, float& o_taxisEnter, float& o_taxisExit) {
			//if (i_Obj1.m_GameObject.Acquire()->GetName() == "Arindam") {
			//	if ((i_Obj1.m_GameObject.Acquire()->GetPosition().x() + 44.0) > (i_Obj2.m_GameObject.Acquire()->GetPosition().x() - 160.0f)) {
			//	//	LPCSTR lpOutputString = "Collided\n";
			//	//	OutputDebugStringA(lpOutputString);
			//	}
			//}
			
			Vector3 Obj2RelVel = i_Obj2.m_GameObject.Acquire()->GetVelocity() - i_Obj1.m_GameObject.Acquire()->GetVelocity();
			Vector3 Obj2Travel = Obj2RelVel * i_dt;

			float Obj2TravelAlongAxis = dot(Vector4(Obj2Travel,0.0), i_CollisionAxis);

			float Obj1CenterOnAxis = dot(Vector4(i_Obj1.m_BBCenterInWorld, 0.0f), i_CollisionAxis);
			float Obj2CenterOnAxis = dot(Vector4(i_Obj2.m_BBCenterInWorld,0.0f), i_CollisionAxis);

			//Vector4 Obj1ExtentsInWorld = i_Obj1.m_ObjectToWorld * Vector4(i_Obj1.m_BoundingBox.m_Extents, 1.0f);
			//Vector4 Obj2ExtentsInWorld = i_Obj2.m_ObjectToWorld * Vector4(i_Obj2.m_BoundingBox.m_Extents, 1.0f);

			//float Obj2VelAlongAxis = dot(Vector4(i_Obj2.m_GameObject.Acquire()->GetVelocity(),1.0f), i_CollisionAxis);

			//Vector4 Obj1XExtentInWorld = i_Obj1.m_OrientationInWorld * Vector4(1.0, 0.0, 0.0, 0.0);
			//Obj1XExtentInWorld = Obj1XExtentInWorld.Normalized() * i_Obj1.m_BoundingBox.m_Extents.x();
			//Vector4 Obj1YExtentInWorld = i_Obj1.m_OrientationInWorld * Vector4(0.0, 1.0, 0.0, 0.0);
			//Obj1YExtentInWorld = Obj1YExtentInWorld.Normalized() * i_Obj1.m_BoundingBox.m_Extents.y();
			//Vector4 Obj1ZExtentInWorld = i_Obj1.m_OrientationInWorld * Vector4(0.0, 0.0, 1.0, 0.0);
			//Obj1ZExtentInWorld = Obj1ZExtentInWorld.Normalized() * i_Obj1.m_BoundingBox.m_Extents.z();

			//float Obj1ProjectedExtents =
			//	fabs(dot(i_CollisionAxis, Obj1XExtentInWorld)) +
			//	fabs(dot(i_CollisionAxis, Obj1YExtentInWorld)) +
			//	fabs(dot(i_CollisionAxis, Obj1ZExtentInWorld));


			Vector4 Obj2XExtentInWorld = i_Obj2.m_OrientationInWorld * Vector4(1.0, 0.0, 0.0, 0.0);
			Obj2XExtentInWorld = Obj2XExtentInWorld.Normalized() * i_Obj2.m_BoundingBox.m_Extents.x();
			Vector4 Obj2YExtentInWorld = i_Obj2.m_OrientationInWorld * Vector4(0.0, 1.0, 0.0, 0.0);
			Obj2YExtentInWorld = Obj2YExtentInWorld.Normalized() * i_Obj2.m_BoundingBox.m_Extents.y();
			Vector4 Obj2ZExtentInWorld = i_Obj2.m_OrientationInWorld * Vector4(0.0, 0.0, 1.0, 0.0);
			Obj2ZExtentInWorld = Obj2ZExtentInWorld.Normalized() * i_Obj2.m_BoundingBox.m_Extents.z();



			float Obj2ProjectedExtents =
				fabs(dot(i_CollisionAxis, Obj2XExtentInWorld)) +
				fabs(dot(i_CollisionAxis, Obj2YExtentInWorld)) +
				fabs(dot(i_CollisionAxis, Obj2ZExtentInWorld));


			float Obj2ExtentsAlongAxis = dot(Vector4 (i_Obj1.m_BoundingBox.m_Extents, 0.0),i_CollisionAxis) + Obj2ProjectedExtents;

			float Bleft = Obj1CenterOnAxis - Obj2ExtentsAlongAxis;
			float BRight = Obj1CenterOnAxis + Obj2ExtentsAlongAxis;


			if (IsZero(Obj2TravelAlongAxis))
			{
				if ((Obj2CenterOnAxis < Bleft) || (Obj2CenterOnAxis > BRight))
					return true;
				else
				{
					o_taxisEnter = 0.0f;
					o_taxisExit = 1.0f;
					return false;
				}
			}

			float DClose = Bleft - Obj2CenterOnAxis;
			float DOpen = BRight - Obj2CenterOnAxis;

			o_taxisEnter = DClose / Obj2TravelAlongAxis;
			o_taxisExit = DOpen / Obj2TravelAlongAxis;

			if (o_taxisEnter > o_taxisExit) {
				float temp = o_taxisEnter;
				o_taxisEnter = o_taxisExit;
				o_taxisExit = temp;
			}

			if (!((o_taxisEnter >= 1.0f) || (o_taxisExit <= 0.0f)))
				return false;



			return true;
		}

		bool CheckCollision(Collideable& i_Collideable1,Collideable& i_Collideable2, float i_dt, float& o_tCollision, Vector3 & o_CollisionNormal) {
			if (i_Collideable1.m_GameObject.Acquire()->GetName() == "Monster") {
				if ((i_Collideable1.m_GameObject.Acquire()->GetPosition().y()) < (i_Collideable2.m_GameObject.Acquire()->GetPosition().y() + 4.0)) {
					//LPCSTR lpOutputString = "Collided\n";
					//OutputDebugStringA(lpOutputString);
				}
			}
			float tEnter = 0.0f;
			float tExit = 0.1f;
			Vector4 CollisionAxis = i_Collideable1.m_OrientationInWorld * Vector4(1.0, 0.0, 0.0, 0.0);
			CollisionAxis = CollisionAxis.Normalized();
			
			Vector4 Obj1CenterInWorld = Vector4(i_Collideable1.m_BBCenterInWorld, 1.0f);
			Vector4 Obj2CenterInWorld = Vector4(i_Collideable2.m_BBCenterInWorld, 1.0f);


			float axisEnter = 0.0f;
			float axisExit = 0.1f;
			///obj1 x axis against obj2 x axis
			if (CheckSeperatingAxis(CollisionAxis, i_Collideable1, Obj1CenterInWorld, i_Collideable2, Obj2CenterInWorld, i_dt, axisEnter, axisExit)) {
				//seperate axis detected
				return false;
			}
			else {
				if (axisEnter > tEnter)
				{

					tEnter = axisEnter;
					o_CollisionNormal = Vector3(CollisionAxis.x(), CollisionAxis.y(), CollisionAxis.z());
				}
				if (axisExit < tExit)
					tExit = axisExit;
				//LPCSTR lpOutputString = "Collided - obj1 x axis against obj2 x axis\n";
				//OutputDebugStringA(lpOutputString);
			}
			CollisionAxis = i_Collideable1.m_OrientationInWorld * Vector4(0.0, 1.0, 0.0, 0.0);
			CollisionAxis = CollisionAxis.Normalized();

			axisEnter = 0.0f;
			axisExit = 0.1f;
			///obj1 y axis against obj2 y axis
			if (CheckSeperatingAxis(CollisionAxis, i_Collideable1, Obj1CenterInWorld, i_Collideable2, Obj2CenterInWorld, i_dt, axisEnter, axisExit)) {
				//seperate axis detected
				return false;
			}
			else {
				if (axisEnter > tEnter)
				{
					tEnter = axisEnter;
					o_CollisionNormal = Vector3(CollisionAxis.x(), CollisionAxis.y(), CollisionAxis.z());
				}
				if (axisExit < tExit)
					tExit = axisExit;
				//LPCSTR lpOutputString = "Collided - obj1 y axis against obj2 y axis\n";
				//OutputDebugStringA(lpOutputString);
			}

			CollisionAxis = i_Collideable2.m_OrientationInWorld * Vector4(1.0, 0.0, 0.0, 0.0);
			CollisionAxis = CollisionAxis.Normalized();

			axisEnter = 0.0f;
			axisExit = 0.1f;
			///obj2 x axis against obj1 x axis
			if (CheckSeperatingAxis(CollisionAxis, i_Collideable2, Obj2CenterInWorld, i_Collideable1, Obj1CenterInWorld, i_dt, axisEnter, axisExit)) {
				//seperate axis detected
				return false;
			}
			else {
				if (axisEnter > tEnter) {
					tEnter = axisEnter;
					o_CollisionNormal = Vector3(CollisionAxis.x(), CollisionAxis.y(), CollisionAxis.z());
				}
				if (axisExit < tExit)
					tExit = axisExit;
				//LPCSTR lpOutputString = "Collided - obj2 x axis against obj1 x axis\n";
				//OutputDebugStringA(lpOutputString);
			}

			CollisionAxis = i_Collideable2.m_OrientationInWorld * Vector4(0.0, 1.0, 0.0, 0.0);
			CollisionAxis = CollisionAxis.Normalized();

			axisEnter = 0.0f;
			axisExit = 0.1f;
			///obj2 y axis against obj1 y axis
			if (CheckSeperatingAxis(CollisionAxis, i_Collideable2, Obj2CenterInWorld, i_Collideable1, Obj1CenterInWorld, i_dt, axisEnter, axisExit)) {
				//seperate axis detected
				return false;
			}
			else {
				if (axisEnter > tEnter) {
					tEnter = axisEnter;
					o_CollisionNormal = Vector3(CollisionAxis.x(), CollisionAxis.y(), CollisionAxis.z());
				}
				if (axisExit < tExit)
					tExit = axisExit;
				//LPCSTR lpOutputString = "Collided - obj2 y axis against obj1 y axis\n";
				//OutputDebugStringA(lpOutputString);
			}



			o_tCollision = tEnter;
			o_CollisionNormal = Vector3(CollisionAxis.x(), CollisionAxis.y(), CollisionAxis.z());

			return tEnter < tExit;
		}

		void UpdateCollisionData(size_t count) {
			
			if (count > 1) {
				for (size_t i = 0; i <= (count - 1); i++) {

					Collideable* c = AllCollideables[i];
					c->m_ObjectToWorld = Matrix4::CreateTranslation(c->m_GameObject.Acquire()->GetPosition()) * Matrix4::CreateZRotation(c->m_GameObject.Acquire()->GetRotation().z());
					c->m_OrientationInWorld = Matrix4::CreateZRotation(c->m_GameObject.Acquire()->GetRotation().z());
					c->m_BBCenterInWorld = c->m_ObjectToWorld.TransformPoint(c->m_BoundingBox.m_Center);

				}
			}
		}
		CollisionPair ProcessCollision(const float& i_dt) {
			const size_t count = AllCollideables.size();
			//std::vector<CollisionInfo> collisions = std::vector<CollisionInfo>();
			CollisionPair EarliestCollision = CollisionPair(nullptr,nullptr,i_dt,Vector3::Zero);


			UpdateCollisionData(count);

			if (count > 1) {
				
				for (size_t i = 0; i <= (count - 1); i++) {

					for (size_t j = 0; j <= (count - 1); j++) {
						float TimeOfCollision = 0.0f;
						Vector3 CollisionNormal = Vector3::Zero;
						if (AllCollideables[i]->m_GameObject.Acquire()->GetName().compare(AllCollideables[j]->m_GameObject.Acquire()->GetName()) != 0) {


							if (CheckCollision(*AllCollideables[i], *AllCollideables[j], i_dt, TimeOfCollision, CollisionNormal)) {
								LPCSTR lpOutputString = "Collision Found";
								OutputDebugStringA(lpOutputString);
							if (TimeOfCollision < EarliestCollision.m_CollisionTime) {
									EarliestCollision.m_CollisionTime = TimeOfCollision;
									EarliestCollision.m_CollisionNormal = CollisionNormal;
									EarliestCollision.m_CollisionObjects[0] = AllCollideables[i];
									EarliestCollision.m_CollisionObjects[1] = AllCollideables[j];
								}
							}
						}
					}

				}

			}

			return EarliestCollision;

		}
		Vector3 PostCollisionVelocity(const float &m1, const float &m2, Vector3 &v1, Vector3 &v2) {

			Vector3 vel_final(0.0f, 0.0f, 0.0f);

			vel_final = v1 * ((m1 - m2) / (m1 + m2)) + v2 * ((2 * m2) / (m1 + m2));

			return vel_final;
		}

		void CalculatePostVelocities(WeakPointer<GameObject>& A, WeakPointer<GameObject>& B, const Vector3& CollisionNormal) {

			SmartPointer<GameObject> ObjectA = A.Acquire();
			SmartPointer<GameObject> ObjectB = B.Acquire();
			float m1 = ObjectA->GetMass();
			float m2 = ObjectB->GetMass();
			Vector3 v1 = ObjectA->GetVelocity();
			Vector3 v2 = ObjectB->GetVelocity();
			if (ObjectA->GetName() == "OOBLeft" || ObjectA->GetName() == "OOBRight" || ObjectA->GetName() == "OOBUpper" || ObjectA->GetName() == "OOBleft") {
				
				Vector3 c = CollisionNormal.Normalized();
				Vector3 NewVelocity = v2 - 2 * (dot(v2, c)) * c;
				ObjectB->SetVelocity(NewVelocity);
			}
			else if (ObjectB->GetName() == "OOBLeft" || ObjectB->GetName() == "OOBRight" || ObjectB->GetName() == "OOBUpper" || ObjectB->GetName() == "OOBleft") {
				
				Vector3 c = CollisionNormal.Normalized();
				Vector3 NewVelocity = v1 - 2 * (dot(v1, c)) * c;
				ObjectA->SetVelocity(NewVelocity);
			}
			else {
				ObjectA->SetVelocity(PostCollisionVelocity(m1, m2, v1, v2));
				ObjectB->SetVelocity(PostCollisionVelocity(m2, m1, v2, v1));
			}


			return;
		}
		void CollisionRespond(CollisionPair CollidedPair) {
			CalculatePostVelocities(CollidedPair.m_CollisionObjects[0]->m_GameObject, CollidedPair.m_CollisionObjects[1]->m_GameObject,CollidedPair.m_CollisionNormal);

			return;
		}

		void Run(const float& i_dt) {
			
			CollisionPair CollisionToProcess = ProcessCollision(i_dt);
			if (CollisionToProcess.m_CollisionObjects[0]) {
				
				SmartPointer<GameObject> ObjectA = CollisionToProcess.m_CollisionObjects[0]->m_GameObject.Acquire();
				SmartPointer<GameObject> ObjectB = CollisionToProcess.m_CollisionObjects[1]->m_GameObject.Acquire();

				if (ObjectA->GetName() == "Monster10" && ObjectB->GetName() == "OOB-Bottom")
				{
					//RemoveGameObjectFromWorld(CollisionToProcess.m_CollisionObjects[0]->m_GameObject);
					Engine::RequestShutdown();
					LPCSTR lpOutputString = "You Win";
					OutputDebugStringA(lpOutputString);
				}
				else if (ObjectB->GetName() == "Monster10" && ObjectA->GetName() == "OOB-Bottom") {
					//RemoveGameObjectFromWorld(CollisionToProcess.m_CollisionObjects[1]->m_GameObject);
					LPCSTR lpOutputString = "You Win";
					OutputDebugStringA(lpOutputString);
					Engine::RequestShutdown();
				}
				else if(ObjectA->GetName() == "Monster" && ObjectB->GetName() == "Player") {
					Engine::RequestShutdown();
					LPCSTR lpOutputString = "You Loose";
					OutputDebugStringA(lpOutputString);
					//CollisionRespond(CollisionToProcess);
				}
				else if (ObjectB->GetName() == "Monster" && ObjectA->GetName() == "Player") {
					LPCSTR lpOutputString = "You Loose";
					OutputDebugStringA(lpOutputString);
					Engine::RequestShutdown();
					//CollisionRespond(CollisionToProcess);
				}
				
			}
		}


	}
}
