#include "Vector4.h"

namespace Engine {
	const Vector4 Vector4::Zero(0.0f, 0.0f, 0.0f, 0.0f);

	Vector4 Vector4::Normalized() const
	{
		float length = sqrt((m_x * m_x) + (m_y * m_y) + (m_z * m_z) + (m_w * m_w));

		if (IsZero(length))
			return Zero;
		else
		{
			float inv_length = 1.0f / length;

			return *this * inv_length;
		}
	}
}