#include "point.hpp"

Point::Point(int rank) {
	this->vector = Locus(rank, 0.0);
}
Point::Point(Locus vector) {
	this->vector = vector;
}
Point::Point(int rank, int axis, double v) {
	this->vector = Locus(rank, 0.0);
	(*this)[axis] = v;
}

double Point::operator [] (int n) const {
	if(n < 0)
		n = this->getRank() + n;
	return this->vector[n];
}

double& Point::operator [] (int n) {
	if(n < 0)
		n = this->getRank() + n;
	return this->vector[n];
}

double Point::getMagnitude() const {
	int ptrank = this->getRank();
	double dist = 0.0;
	double dist0;
	for(int i = 0; i < ptrank; i++) {
		dist0 = this->vector[i];
		dist += dist0 * dist0;
	}
	return sqrt(dist);
}

int Point::getRank() const {
	return this->vector.size();
}

void Point::p_addCoordinates(Point &b, int place) {
	if(place == 0)
		this->vector.insert(this->vector.begin(), b.vector.begin(), b.vector.end());
	if(place == 1)
		this->vector.insert(this->vector.end(), b.vector.begin(), b.vector.end());
}

void Point::p_addDimension(int axis, double v) {
	int ptdim = this->getRank();
	
	if(axis > ptdim) {
		puts("Redimension axis dimension larger than point dimension!\n");
		return;
	}
	if(axis == -1) {
		this->vector.push_back(v);
	}
	else {
		this->vector.insert(this->vector.begin() + axis, v);
	}
}

void Point::p_axisTranslate(int axis, double v) {
	int ptdim = this->getRank();
	
	if(axis > ptdim - 1) {
		puts("Translation axis dimension larger than point dimension!\n");
		return;
	}
	
	(*this)[axis] += v;
}

void Point::p_invert() {
	int ptdim = this->getRank();
	
	for(int i = 0; i < ptdim; i++) {
		this->vector[i] = -this->vector[i];
	}
}

void Point::p_mirror(int axis) {
	int ptdim = this->getRank();
	
	if(axis > ptdim) {
		puts("Mirroring axis dimension larger than point dimension!\n");
		return;
	}
	
	(*this)[axis] = -(*this)[axis];
}

void Point::p_rotate(int axis1, int axis2, double ang) {
	int ptdim = this->getRank();
	
	if(axis1 > ptdim - 1 || axis2 > ptdim - 1) {
		puts("Rotation axis dimension larger than point dimension!\n");
		return;
	}
	if(ang == 0)
		return;
	
	double ax1 = (*this)[axis1];
	double ax2 = (*this)[axis2];
	(*this)[axis1] = ax1*cos(ang) - ax2*sin(ang);
	(*this)[axis2] = ax2*cos(ang) + ax1*sin(ang);
}

void Point::p_rotateRight(int axis1, int axis2, int invert) {
	int ptdim = this->getRank();
	
	if(axis1 > ptdim - 1 || axis2 > ptdim - 1) {
		puts("Rotation axis dimension larger than point dimension!\n");
		return;
	}
	
	double ax1 = (*this)[axis1];
	double ax2 = (*this)[axis2];
	(*this)[axis1] = invert * ax2;
	(*this)[axis2] = invert * ax1;
}

void Point::p_scale(double factor) {
	int ptdim = this->getRank();
	
	for(int i = 0; i < ptdim; i++) {
		(*this)[i] *= factor;
	}
}

void Point::p_scale(Point vc) {
	int ptdim = this->getRank();
	int vcdim = vc.getRank();
	
	if(vcdim > ptdim) {
		puts("Scaling vector dimension larger than point dimension!\n");
		return;
	}
	
	for(int i = 0; i < vcdim; i++) {
		(*this)[i] *= vc[i];
	}
}

void Point::p_scaleAxis(int axis, double factor) {
	int ptdim = this->getRank();
	
	if(axis > ptdim) {
		puts("Scaling vector dimension larger than point dimension!\n");
		return;
	}
	
	(*this)[axis] *= factor;
}

void Point::p_translate(Point vc) {
	int ptdim = this->getRank();
	int vcdim = vc.getRank();
	
	if(vcdim > ptdim) {
		puts("Translation vector dimension larger than point dimension!\n");
		return;
	}
	
	for(int i = 0; i < vcdim; i++) {
		(*this)[i] += vc[i];
	}
}