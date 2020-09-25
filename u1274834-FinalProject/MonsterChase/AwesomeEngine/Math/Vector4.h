#pragma once
#include "Vector3.h"
namespace Engine {
	class Vector4
	{
	public:

		inline Vector4(float i_x, float i_y, float i_z, float i_w);
		inline Vector4(float i_vec[4]);

		inline Vector4(const Vector4& i_rhs);

		inline Vector4(const Vector3& i_other, float i_w);


		//assignment operator
		inline Vector4& operator=(const Vector4& i_rhs);

		//getters
		inline float x(void) const;
		inline float y(void) const;
		inline float z(void) const;
		inline float w(void) const;

		//setters
		inline void x(float i_x);
		inline void y(float i_y);
		inline void z(float i_z);
		inline void w(float i_z);

		Vector4 Normalized() const;

		Vector4& operator+=(const Vector4& i_rhs);
		Vector4& operator-=(const Vector4& i_rhs);

		Vector4& operator*=(float i_val);
		Vector4& operator/=(float i_val);

		Vector4 operator-(void);

		static const Vector4 Zero;
	private:
		float m_x, m_y, m_z, m_w;
	};

	inline Vector4 operator+(const Vector4& i_lhs, const Vector4& i_rhs);
	inline Vector4 operator-(const Vector4& i_lhs, const Vector4& i_rhs);


	inline Vector4 operator*(const Vector4& i_lhs, const Vector4& i_rhs);
	inline Vector4 operator*(const Vector4& i_lhs, const float i_rhs);
	inline Vector4 operator*(const float i_lhs, const Vector4& i_rhs);
	inline Vector4 operator/(const Vector4& i_lhs, const float i_rhs);

	inline bool operator==(const Vector4& i_lhs, const Vector4& i_rhs);
	inline bool operator!=(const Vector4& i_lhs, const Vector4& i_rhs);

	inline float dot(const Vector4& i_lhs, const Vector4& i_rhs);
	//inline Vector3 cross(const Vector3& i_lhs, const Vector3& i_rhs);
}
#include "Vector4-inl.h"




