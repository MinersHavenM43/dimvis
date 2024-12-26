#include "object.hpp"

Object::Object(Points points, Lines lines, sf::Color color) {
	this->points = points;
	this->lines  = lines;
	this->color  = color;
}

Object::Object() {
	*this = Object({}, {});
}
Object::Object(int rank, int numverts, int numedges, sf::Color color) {
	*this = Object(Points(numverts, Point(rank)), Lines(numedges), color);
}

double Object::getEdgeLength() const {
	int dgsize = (this->lines.size()) / 2;
	double dglensum = 0.0;
	for(int i = 0; i < dgsize; i++) {
		Point point1 = this->points[this->lines[2 * i]];
		Point point2 = this->points[this->lines[2 * i + 1]];
		
		dglensum += point1.translate(point2.invert()).getMagnitude();
	}
	
	return dglensum / dgsize;
}

double Object::getRadius() const {
	int ptsize = this->points.size();
	double radiussum = 0.0;
	for(int i = 0; i < ptsize; i++) {
		radiussum += this->points[i].getMagnitude();
	}
	
	return radiussum / ptsize;
}

int Object::getRank() const {
	return this->points[0].getRank();
}

void Object::addPoint(Point a) {
	// maybe try a better method to do this?
	points.push_back(a);
}
void Object::addLine(int a, int b) {
	// maybe try a better method to do this?
	lines.push_back(a);
	lines.push_back(b);
}

Object Object::addDimension(int axis, double v) {
	Object object = *this;
	int ptsize = object.points.size();
	
	for(int i = 0; i < ptsize; i++) {
		object.points[i].p_addDimension(axis, v);
	}
	return object;
}

Object Object::axisTranslate(int axis, double v) {
	Object object = *this;
	int ptsize = object.points.size();
	
	for(int i = 0; i < ptsize; i++) {
		object.points[i].p_axisTranslate(axis, v);
	}
	return object;
}

Object Object::recolor(int r, int g, int b, int a) {
	Object object = *this;
	object.color = sf::Color(r, g, b, a);
	return object;
}

Object Object::recolor(sf::Color color) {
	Object object = *this;
	object.color = color;
	return object;
}

Object Object::rotate(int ax1, int ax2, double ang) {
	Object object = *this;
	int ptsize = object.points.size();
	
	for(int i = 0; i < ptsize; i++) {
		object.points[i].p_rotate(ax1, ax2, ang);
	}
	return object;
}

Object Object::scale(double fac) {
	Object object = *this;
	int ptsize = object.points.size();
	
	for(int i = 0; i < object.points.size(); i++) {
		object.points[i].p_scale(fac);
	}
	return object;
}

Object Object::scale(Point vec) {
	Object object = *this;
	int ptsize = object.points.size();
	
	for(int i = 0; i < ptsize; i++) {
		object.points[i].p_scale(vec);
	}
	return object;
}

Object Object::scaleUnitEdge() {
	Object object = *this;
	int ptsize = object.points.size();
	double edglen = object.getEdgeLength();
	
	for(int i = 0; i < ptsize; i++) {
		object.points[i].p_scale(1.0 / edglen);
	}
	return object;
}

Object Object::scaleUnitRadius() {
	Object object = *this;
	int ptsize = object.points.size();
	double radius = object.getRadius();
	
	for(int i = 0; i < ptsize; i++) {
		object.points[i].p_scale(1.0 / radius);
	}
	return object;
}

Object Object::skew(int ax1, int ax2, double v) {
	Object object = *this;
	int ptsize = object.points.size();
	
	for(int i = 0; i < ptsize; i++) {
		object.points[i].p_axisTranslate(ax1, v * object.points[i][ax2]);
	}
	return object;
}

Object Object::translate(Point vec) {
	Object object = *this;
	int ptsize = object.points.size();
	
	for(int i = 0; i < ptsize; i++) {
		object.points[i].p_translate(vec);
	}
	return object;
}

// now begins the operations

Object Object::pyramid(double height, int oriens, bool based) {
	Object object = *this;
	int ptsize0 = object.points.size();
	int lnsize0 = object.lines.size();
	int objdim0 = object.getRank();
	
	if(oriens == -1) oriens = objdim0;
	
	object = object.addDimension(oriens, 0.0);
	Point pyrpoint (objdim0+1, oriens, height);
	
	object.addPoint(pyrpoint);
	for(int i = 0; i < ptsize0; i++) {
		object.addLine(i, ptsize0);
	}
	
	if(!based) {
		object = object.axisTranslate(oriens, -height/2);
	}
	
	return object;
}
Object Object::tegum(double height, int oriens) {
	Object object = *this;
	int ptsize0 = object.points.size();
	int lnsize0 = object.lines.size();
	int objdim0 = object.getRank();
	
	if(oriens == -1) oriens = objdim0;
	
	object = object.addDimension(oriens, 0.0);
	Point pyrpoint1 (objdim0+1, oriens, height/2);
	Point pyrpoint2 (objdim0+1, oriens, -height/2);
	
	for(int i = 0; i < ptsize0; i++) {
		object.addLine(i, ptsize0);
		object.addLine(i, ptsize0+1);
	}
	
	return object;
}
Object Object::prism(double height, int oriens, bool based) {
	Object object = *this;
	int ptsize0 = object.points.size();
	int lnsize0 = object.lines.size();
	int objdim0 = object.getRank();
	
	object = object.addDimension(oriens, 0.0);
	
	for(int i = 0; i < ptsize0; i++) {
		object.addPoint(
			object.points[i].axisTranslate(oriens, height)
		);
		object.addLine(i, i + ptsize0);
	}
	for(int i = 0; i < lnsize0; i++) {
		object.lines.push_back(object.lines[i] + ptsize0);
	}
	
	if(!based) {
		object = object.axisTranslate(oriens, -height/2);
	}
	
	return object;
}
Object Object::frustum(double scale, double height, int oriens, bool based) {
	Object object = *this;
	int ptsize0 = object.points.size();
	int lnsize0 = object.lines.size();
	int objdim0 = object.getRank();
	
	if(oriens == -1) oriens = objdim0;
	
	object = object.addDimension(oriens, 0.0);
	
	for(int i = 0; i < ptsize0; i++) {
		object.addPoint(
			object.points[i].scale(scale).axisTranslate(oriens, height)
		);
		object.addLine(i, i + ptsize0);
	}
	for(int i = 0; i < lnsize0; i++) {
		object.lines.push_back(object.lines[i] + ptsize0);
	}
	
	if(!based) {
		object = object.axisTranslate(oriens, -height/2);
	}
	
	return object;
}