#pragma once
#include "point.hpp"

typedef std::vector<Point> Points;
typedef std::vector<int> Lines;

struct Object {
	Points points;
	Lines lines;
	sf::Color color = sf::Color::White;
	
	Object(Points points, Lines lines, sf::Color color = sf::Color::White);
	Object();
	Object(int rank, int numverts, int numedges, sf::Color color = sf::Color::White);
	
	int getRank() const;
	double getRadius() const;
	double getEdgeLength() const;
	
	void addPoint(Point a);
	void addLine(int a, int b);
	
	Object addDimension(int axis = 1, double v = 0.0);
	Object axisTranslate(int axis, double v);
	Object rotate(int ax1, int ax2, double ang);
	Object recolor(int r, int g, int b, int a = 255);
	Object recolor(sf::Color color);
	Object scale(double fac);
	Object scale(Point vec);
	Object scaleUnitEdge();
	Object scaleUnitRadius();
	Object skew(int ax1, int ax2, double v);
	Object translate(Point vec);

	Object pyramid(double height, int oriens = 1, bool based = false);
	Object tegum(double height, int oriens = 1);
	Object prism(double height, int oriens = 1, bool based = false);
	Object frustum(double scale, double height, int oriens = 1, bool based = false);
};

typedef std::vector<Object> Scene;