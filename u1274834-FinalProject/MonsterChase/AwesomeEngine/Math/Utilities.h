#pragma once

#include <stdint.h>

namespace Engine {
	

		inline bool 			IsNAN(float i_val);
		inline bool 			IsZero(float i_val);

		// fastest
		inline bool 			AreEqual_Eps(float i_lhs, float i_rhs, float i_maxDiff = 0.00001f);
		// balanced
		inline bool 			AreEqual_Rel(float i_lhs, float i_rhs, float i_maxDiff = 0.00001f);

}
#include "Utilities-inl.h"

