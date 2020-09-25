#pragma once
#include "Vector4.h"
#include "Vector3.h"
namespace Engine {
	class Matrix4
	{
	public:

		Matrix4();
		Matrix4(
			float i_11, float i_12, float i_13, float i_14,
			float i_21, float i_22, float i_23, float i_24,
			float i_31, float i_32, float i_33, float i_34,
			float i_41, float i_42, float i_43, float i_44);

		Matrix4(const Matrix4& i_other);
		Matrix4& operator=(const Matrix4& i_other);

		Matrix4 operator*(const Matrix4& i_other) const;

		static Matrix4 CreateIdentity(void);
		static Matrix4 CreateScale(float i_scaleX, float i_scaleY, float i_scaleZ);
		static Matrix4 CreateZRotation(float i_RotationRadians);

		static Matrix4 CreateTranslation(float i_transX, float i_transY, float i_transZ);
		inline static Matrix4 CreateTranslation(const Vector3& i_trans);
		inline Vector3 TransformPoint(const Vector3& i_point) const;
		// Invert this instance
		void Invert(void);

		Matrix4 GetInverse(void) const;
		void GetInverse(Matrix4& o_out) const;

		void Transpose(void);


		Matrix4 GetTranspose(void) const;
		void GetTranspose(Matrix4& o_out) const;


		void Multiply(const Matrix4& i_other, Matrix4& o_out) const;


		Vector4 MultiplyLeft(const Vector4& i_Vector) const;

		Vector4 MultiplyRight(const Vector4& i_Vector) const;

		static const Matrix4 Identity;

	private:
		float

			m_11, m_12, m_13, m_14, 
			m_21, m_22, m_23, m_24, 
			m_31, m_32, m_33, m_34, 
			m_41, m_42, m_43, m_44; 

		void MultiplyInt(const Matrix4& i_other, Matrix4& o_out) const;
		void Inverse(Matrix4 o_out) const;
	};

	inline Vector4 operator*(const Matrix4& i_mtx, const Vector4& i_vec);
	inline Vector4 operator*(const Vector4& i_vec, const Matrix4& i_mtx);


}



#include "Matrix4-inl.h"
