#pragma once
#include "main.hpp"
// arbitrary constants, really
#define DEFAULT_INT 484654863
#define DEFAULT_FLT 892437698565989.928

typedef std::vector<double> Locus;

struct Point {
	Locus vector;
	
	Point(int rank);
	Point(Locus vector);
	Point(std::initializer_list<double> initList) : vector (initList) {} // taken from https://www.geeksforgeeks.org/how-to-use-initializer-lists-in-constructors-in-cpp/. i have no fucking idea what this actually does but it does the job i guess
	Point(int rank, int axis, double v);
	double  operator [] (int n) const;
	double& operator [] (int n);
	
	double getMagnitude() const;
	int getRank() const;
	
	void p_addCoordinates(Point &b, int place = 1);
	void p_addDimension(int axis = 1, double v = 0.0);
	void p_axisTranslate(int axis, double vc);
	void p_invert();
	void p_mirror(int axis);
	void p_rotate(int axis1, int axis2, double angle);
	void p_rotateRight(int axis1, int axis2, int invert = 1);
	void p_scale(double factor);
	void p_scale(Point vc);
	void p_scaleAxis(int axis, double factor);
	void p_translate(Point vc);
	
	Point addCoordinates(Point &b, int place = 1) {
		Point pt = *this; pt.p_addCoordinates(b, place); return pt;
	}
	Point addDimension(int axis = 1, double v = 0.0) {
		Point pt = *this; pt.p_addDimension(axis, v); return pt;
	}
	Point axisTranslate(int axis, double vc) {
		Point pt = *this; pt.p_axisTranslate(axis, vc); return pt;
	}
	Point invert() {
		Point pt = *this; pt.p_invert(); return pt;
	}
	Point mirror(int axis) {
		Point pt = *this; pt.p_mirror(axis); return pt;
	}
	Point rotate(int axis1, int axis2, double angle) {
		Point pt = *this; pt.p_rotate(axis1, axis2, angle); return pt;
	}
	Point rotateRight(int axis1, int axis2, int invert = 1) {
		Point pt = *this; pt.p_rotateRight(axis1, axis2, invert); return pt;
	}
	Point scale(double factor) {
		Point pt = *this; pt.p_scale(factor); return pt;
	}
	Point scale(Point vc) {
		Point pt = *this; pt.p_scale(vc); return pt;
	}
	Point scaleAxis(int axis, double factor) {
		Point pt = *this; pt.p_scaleAxis(axis, factor); return pt;
	}
	Point translate(Point vc) {
		Point pt = *this; pt.p_translate(vc); return pt;
	}
};