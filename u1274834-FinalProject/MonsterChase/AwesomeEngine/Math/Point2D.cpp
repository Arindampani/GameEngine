#include "Point2D.h"
#include <math.h>


const Point2D Point2D::Zero(0.0f, 0.0f);
	Point2D::Point2D()
	{
	}

	Point2D::Point2D(float xPosition, float yPosition)
	{
		this->x = xPosition;
		this->y = yPosition;
	}

	Point2D::~Point2D()
	{
	}

