#pragma once
#include <cmath>

	class Point2D
	{
	public:
		float x = 0;
		float y = 0;
		Point2D();
		Point2D(float, float);
		inline Point2D operator+(const Point2D& PointTwo);
		inline Point2D operator-(const Point2D& PointTwo);
		inline Point2D operator*(float number);
		inline Point2D operator/(float number);
		inline Point2D operator*=(float number);
		inline Point2D operator/=(float number);
		inline Point2D operator-();
		inline Point2D operator+=(const Point2D& PointTwo);
		inline Point2D operator-=(const Point2D& PointTwo);
		inline Point2D normalize();
		inline bool operator!=(const Point2D& PointTwo);
		~Point2D();

		static const Point2D Zero;
	};

#include "Point2D-inl.h"
