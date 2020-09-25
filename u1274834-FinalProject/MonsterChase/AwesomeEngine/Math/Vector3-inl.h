#pragma once
#include "Utilities.h"
namespace Engine {
	inline Vector3::Vector3(float i_x, float i_y, float i_z) :
		m_x(i_x),
		m_y(i_y),
		m_z(i_z)
	{
		//check for float validity later
		assert(!IsNAN(i_x));
		assert(!IsNAN(i_y));
		assert(!IsNAN(i_z));
	}

	inline Vector3::Vector3(float i_vec[3]) :
		m_x(i_vec[0]),
		m_y(i_vec[1]),
		m_z(i_vec[2])
	{
		//check for float validity later
		assert(!IsNAN(i_vec[0]));
		assert(!IsNAN(i_vec[1]));
		assert(!IsNAN(i_vec[2]));
	}

	inline Vector3::Vector3(const Vector3& i_rhs) :
		m_x(i_rhs.m_x),
		m_y(i_rhs.m_y),
		m_z(i_rhs.m_z)
	{
		//check for float validity later
		assert(!IsNAN(i_rhs.m_x));
		assert(!IsNAN(i_rhs.m_y));
		assert(!IsNAN(i_rhs.m_z));
	}

	inline Vector3& Vector3::operator=(const Vector3& i_rhs)
	{
		//check for float validity later
		assert(!IsNAN(i_rhs.m_x));
		assert(!IsNAN(i_rhs.m_y));
		assert(!IsNAN(i_rhs.m_z));

		m_x = i_rhs.m_x;
		m_y = i_rhs.m_y;
		m_z = i_rhs.m_z;

		return *this;
	}

	inline float Vector3::x(void) const
	{

		return m_x;

	}

	inline float Vector3::y(void) const
	{

		return m_y;

	}

	inline float Vector3::z(void) const
	{

		return m_z;

	}

	inline void Vector3::x(float i_x)
	{
		//check for float validity later
		assert(!IsNAN(i_x));
		m_x = i_x;

	}

	inline void Vector3::y(float i_y)
	{
		//check for float validity later
		assert(!IsNAN(i_y));
		m_y = i_y;

	}

	inline void Vector3::z(float i_z)
	{
		//check for float validity later
		assert(!IsNAN(i_z));
		m_z = i_z;

	}

	inline Vector3& Vector3::operator+=(const Vector3& i_rhs)
	{

		m_x += i_rhs.m_x;
		m_y += i_rhs.m_y;
		m_z += i_rhs.m_z;

		return *this;

	}

	inline Vector3& Vector3::operator-=(const Vector3& i_rhs)
	{
		m_x -= i_rhs.m_x;
		m_y -= i_rhs.m_y;
		m_z -= i_rhs.m_z;

		return *this;
	}

	inline Vector3& Vector3::operator*=(float i_val)
	{
		assert(!IsNAN(i_val));
		m_x *= i_val;
		m_y *= i_val;
		m_z *= i_val;

		return *this;
	}

	inline Vector3& Vector3::operator/=(float i_val)
	{
		assert(!IsNAN(i_val));
		assert(!IsZero(i_val));
		m_x /= i_val;
		m_y /= i_val;
		m_z /= i_val;

		return *this;
	}

	inline Vector3 Vector3::operator-(void)
	{

		return Vector3(-m_x, -m_y, -m_z);

	}

	inline Vector3 operator+(const Vector3& i_lhs, const Vector3& i_rhs) {

		return Vector3(i_lhs.x() + i_rhs.x(), i_lhs.y() + i_rhs.y(), i_lhs.z() + i_rhs.z());

	}

	inline Vector3 operator-(const Vector3& i_lhs, const Vector3& i_rhs) {

		return Vector3(i_lhs.x() - i_rhs.x(), i_lhs.y() - i_rhs.y(), i_lhs.z() - i_rhs.z());

	}

	inline Vector3 operator*(const Vector3& i_lhs, const Vector3& i_rhs)
	{

		return Vector3(i_lhs.x() * i_rhs.x(), i_lhs.y() * i_rhs.y(), i_lhs.z() * i_rhs.z());

	}

	inline Vector3 operator*(const Vector3& i_lhs, const float i_rhs) {
		assert(!IsNAN(i_rhs));
		return Vector3(i_lhs.x() * i_rhs, i_lhs.y() * i_rhs, i_lhs.z() * i_rhs);

	}

	inline Vector3 operator*(const float i_lhs, const Vector3& i_rhs) {
		assert(!IsNAN(i_lhs));
		return Vector3(i_lhs * i_rhs.x(), i_lhs * i_rhs.y(), i_lhs * i_rhs.z());

	}

	inline Vector3 operator/(const Vector3& i_lhs, const float i_rhs)
	{
		assert(!IsNAN(i_rhs));
		assert(!IsZero(i_rhs));
		return Vector3(i_lhs.x() / i_rhs, i_lhs.y() / i_rhs, i_lhs.z() / i_rhs);
	}

	inline bool operator==(const Vector3& i_lhs, const Vector3& i_rhs)
	{
		return AreEqual_Eps(i_lhs.x(), i_rhs.x()) && AreEqual_Eps(i_lhs.y(), i_rhs.y()) && AreEqual_Eps(i_lhs.z(), i_rhs.z());
	}

	inline bool operator!=(const Vector3& i_lhs, const Vector3& i_rhs)
	{
		return !AreEqual_Eps(i_lhs.x(), i_rhs.x()) || !AreEqual_Eps(i_lhs.y(), i_rhs.y()) || !AreEqual_Eps(i_lhs.z(), i_rhs.z());
	}

	inline float dot(const Vector3& i_lhs, const Vector3& i_rhs)
	{
		return (i_lhs.x() * i_rhs.x() + i_lhs.y() * i_rhs.y() + i_lhs.z() * i_rhs.z());
	}

	inline Vector3 cross(const Vector3& i_lhs, const Vector3& i_rhs)
	{
		return Vector3(i_lhs.y() * i_rhs.z() - i_lhs.z() * i_rhs.y(), i_lhs.z() * i_rhs.x() - i_lhs.x() * i_rhs.z(), i_lhs.x() * i_rhs.y() - i_lhs.y() * i_rhs.x());
	}
}
