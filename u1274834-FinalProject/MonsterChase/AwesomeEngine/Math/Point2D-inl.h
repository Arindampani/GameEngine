#pragma once


	inline Point2D Point2D::operator+(const Point2D& PointTwo) {

		return Point2D(this->x + PointTwo.x, this->y + PointTwo.y);
	}

	inline Point2D Point2D::operator-(const Point2D& PointTwo) {

		return Point2D(this->x - PointTwo.x, this->y - PointTwo.y);
	}


	inline Point2D Point2D::operator-() {

		return Point2D(-1 * this->x, -1 * this->y);
	}

	inline Point2D Point2D::operator*(float number) {

		return Point2D(this->x * number, this->y * number);
	}

	inline Point2D Point2D::operator/(float number) {

		return Point2D(this->x / number, this->y / number);
	}

	inline Point2D Point2D::operator*=(float number) {

		return Point2D(this->x * number, this->y * number);
	}

	inline Point2D Point2D::operator/=(float number) {

		return Point2D(this->x / number, this->y / number);
	}


	inline Point2D Point2D::operator+=(const Point2D& PointTwo) {

		return Point2D(this->x + PointTwo.x, this->y + PointTwo.y);
	}

	inline Point2D Point2D::operator-=(const Point2D& PointTwo) {

		return Point2D(this->x - PointTwo.x, this->y - PointTwo.y);
	}

	inline bool Point2D::operator!=(const Point2D& PointTwo) {

		if ((this->x != PointTwo.x) && (this->y != PointTwo.y)) {
			return true;
		}
		else {
			return false;
		}
	}
	inline Point2D Point2D::normalize() {
		return Point2D(this->x / abs(this->x), this->y / abs(this->y));
	}
