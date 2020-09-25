#pragma once
#include "../Math/Vector3.h"
#include "../Containers/Pointers.h"
#include <string>

namespace Engine {


	class GameObject
	{
	public:
		GameObject(const Vector3& i_InitialPosition, const Vector3& i_InitialVelocity, const Vector3& i_InitialRotation, const float& i_Mass, const std::string i_Name) :
			m_Position(i_InitialPosition),
			m_Velocity(i_InitialVelocity),
			m_Rotation(i_InitialRotation),
			m_Mass(i_Mass),
			m_Name(i_Name)
		{}

		Vector3 GetPosition() const { return m_Position; }
		void SetPosition(const Vector3& i_Position) { m_Position = i_Position; }//Position in feet

		Vector3 GetVelocity() const { return m_Velocity; }
		void SetVelocity(const Vector3& i_Velocity) { m_Velocity = i_Velocity; }

		Vector3 GetRotation() const { return m_Rotation; }
		void SetRotation(const Vector3& i_Rotation) { m_Rotation = i_Rotation; }

		float GetMass() const { return m_Mass; }
		void SetMass(const float& i_Mass) { m_Mass = i_Mass; }

		std::string GetName() const { return m_Name; }
		void SetName(const float& i_Name) { m_Name = i_Name; }

	private:

		float m_Mass;
		Vector3 m_Position;
		Vector3 m_Velocity;
		Vector3 m_Rotation;

		std::string m_Name;
	};
}