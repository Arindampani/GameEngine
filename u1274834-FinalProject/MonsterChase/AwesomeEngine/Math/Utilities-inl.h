#pragma once
#include <assert.h>
#include <stdlib.h>


#include <math.h>

namespace Engine {
	inline bool IsNAN(float i_val)
	{
		volatile float val = i_val;

		return val != val;
	}

	// safe check for zero
	inline bool IsZero(float i_val)
	{
		return AreEqual_Eps(i_val, .000000001f);
	}

	inline bool AreEqual_Eps(float i_lhs, float i_rhs, float i_maxDiff)
	{
		return fabs(double(i_lhs) - i_rhs) < i_maxDiff;
	}

	inline bool AreEqual_Rel(float i_lhs, float i_rhs, float i_maxDiff)
	{
		if (i_lhs == i_rhs)
			return true;

		float relDiff;

		if (fabs(i_rhs) > fabs(i_lhs))
			relDiff = static_cast<float>(fabs((i_lhs - i_rhs) / i_rhs));
		else
			relDiff = static_cast<float>(fabs((i_lhs - i_rhs) / i_lhs));

		return relDiff <= i_maxDiff;
	}


}