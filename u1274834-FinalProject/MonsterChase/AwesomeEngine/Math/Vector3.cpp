#include "Vector3.h"

namespace Engine {
	const Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);

	Vector3 Vector3::Normalized() const
	{
		float length = static_cast<float>(sqrt((m_x * m_x) + (m_y * m_y) + (m_z * m_z)));

		if (IsZero(length))
			return Zero;
		else
		{
			float inv_length = 1.0f / length;

			return *this * inv_length;
		}
	}
}


