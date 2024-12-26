#include "objectgen.hpp"

// operations between two polytopes
Object o_duoprism(Object a, Object b) {
	Object object;
	int aptsize = a.points.size();
	int alnsize = a.lines.size();
	int bptsize = b.points.size();
	int blnsize = b.lines.size();
	
	for(int i = 0; i < aptsize; i++) {
		for(int j = 0; j < bptsize; j++) {
			object.addPoint(a.points[i].addCoordinates(b.points[j]));
		}
	}
	
	for(int i = 0; i < bptsize; i++) {
		for(int j = 0; j < alnsize; j++) {
			object.lines.push_back(a.lines[j]*bptsize + i);
		}
	}
	
	for(int i = 0; i < aptsize; i++) {
		for(int j = 0; j < blnsize; j++) {
			object.lines.push_back(b.lines[j] + i*bptsize);
		}
	}
	
	return object;
}

Object o_duotegum(Object a, Object b, double height) {
	Object object = o_join(a, b);
	int aptsize = a.points.size();
	int arank = a.getRank();
	int bptsize = b.points.size();
	int brank = b.getRank();
	
	Point a2b (brank);
	Point b2a (arank);
	for(int i = 0; i < aptsize; i++) {
		object.points[i].p_addCoordinates(a2b, 1);
	}
	for(int i = 0; i < bptsize; i++) {
		object.points[i + aptsize].p_addCoordinates(b2a, 0);
	}
	
	for(int i = 0; i < aptsize; i++) {
		for(int j = 0; j < bptsize; j++) {
			object.addLine(i, j + aptsize);
		}
	}
	
	return object;
}

Object o_duopyramid(Object a, Object b, double height, int oriens) {
	Object object = o_join(a, b);
	int aptsize = a.points.size();
	int arank = a.getRank();
	int bptsize = b.points.size();
	int brank = b.getRank();
	
	Point a2b (brank);
	Point b2a (arank);
	for(int i = 0; i < aptsize; i++) {
		object.points[i].p_addCoordinates(a2b, 1);
		object.points[i].p_addDimension( oriens, height / 2.0);
	}
	for(int i = 0; i < bptsize; i++) {
		object.points[i + aptsize].p_addCoordinates(b2a, 0);
		object.points[i + aptsize].p_addDimension(oriens, -height / 2.0);
	}
	
	for(int i = 0; i < aptsize; i++) {
		for(int j = 0; j < bptsize; j++) {
			object.addLine(i, j + aptsize);
		}
	}
	
	return object;
}

Object o_join(Object a, Object b) {
	if(a.getRank() != b.getRank()) {
		printf("Join objects failed: the two objects are of different rank");
	}
	
	int aptsize = a.points.size();
	int bptsize = b.points.size();
	int adgsize = a.lines.size();
	int bdgsize = b.lines.size();
	
	Object object (a.getRank(), aptsize + bptsize, adgsize + bdgsize);
	for(int i = 0; i < aptsize; i++) {
		object.points[i] = a.points[i];
	}
	for(int i = 0; i < bptsize; i++) {
		object.points[i + aptsize] = b.points[i];
	}
	
	for(int i = 0; i < adgsize; i++) {
		object.lines[i] = a.lines[i];
	}
	for(int i = 0; i < bdgsize; i++) {
		object.lines[i + adgsize] = b.lines[i] + aptsize;
	}
	
	object.color = a.color;
	
	return object;
}

// tilings
Object o_dyadicTiling(int x, bool centered) {
	Object object;
	x++;
	
	for(int i = 0; i < x; i++) {
		object.addPoint({i});
	}
	for(int i = 0; i < x-1; i++) {
		object.addLine(i, i + 1);
	}
	
	if(centered)
		object = object.translate({-(x-1)/2.});
	
	return object;
}

Object o_squareTiling(int x, int y, bool centered) {
	Object objx = o_dyadicTiling(x, centered);
	Object objy = o_dyadicTiling(y, centered);
	
	return o_duoprism(objx, objy);
}

Object o_cubicTiling(int x, int y, int z, bool centered) {
	Object objx = o_dyadicTiling(x, centered);
	Object objy = o_dyadicTiling(y, centered);
	Object objz = o_dyadicTiling(z, centered);
	
	return o_duoprism(objx, o_duoprism(objy, objz));
}

Object o_tesseracticTiling(int x, int y, int z, int w, bool centered) {
	Object objx = o_dyadicTiling(x, centered);
	Object objy = o_dyadicTiling(y, centered);
	Object objz = o_dyadicTiling(z, centered);
	Object objw = o_dyadicTiling(w, centered);
	
	return o_duoprism(o_duoprism(objx, objy), o_duoprism(objz, objw));
}

Object o_fastSquareTiling(int x, int y, bool centered) {
	Object object;
	int cpoints = 0;
	
	for(int i = 0; i < x+1; i++) {
		object.addPoint({i, 0});
		object.addPoint({i, y});
		object.addLine(2*i + cpoints, 2*i+1 + cpoints);
	}
	cpoints += 2*(x+1);
	for(int i = 0; i < y+1; i++) {
		object.addPoint({0, i});
		object.addPoint({x, i});
		object.addLine(2*i + cpoints, 2*i+1 + cpoints);
	}
	
	if(centered)
		object = object.translate({-x/2., -y/2.});
	
	return object;
}

Object o_fastCubicTiling(int x, int y, int z, bool centered) {
	Object object;
	int cpoints = 0;
	
	for(int i = 0; i < x+1; i++) {
		for(int j = 0; j < y+1; j++) {
			object.addPoint({i,j,0});
			object.addPoint({i,j,z});
			object.addLine(2*j + cpoints, 2*j+1 + cpoints);
		}
		cpoints += 2*(y+1);
	}
	for(int i = 0; i < x+1; i++) {
		for(int j = 0; j < z+1; j++) {
			object.addPoint({i,0,j});
			object.addPoint({i,y,j});
			object.addLine(2*j + cpoints, 2*j+1 + cpoints);
		}
		cpoints += 2*(z+1);
	}
	for(int i = 0; i < y+1; i++) {
		for(int j = 0; j < z+1; j++) {
			object.addPoint({0,i,j});
			object.addPoint({x,i,j});
			object.addLine(2*j + cpoints, 2*j+1 + cpoints);
		}
		cpoints += 2*(z+1);
	}
	
	if(centered)
		object = object.translate({-x/2., -y/2., -z/2.});
	
	return object;
}

Object o_fastTesseracticTiling(int x, int y, int z, int w, bool centered) {
	Object object;
	int cpoints = 0;
	
	for(int i = 0; i < x+1; i++) for(int j = 0; j < y+1; j++) {
		for(int k = 0; k < z+1; k++) {
			object.addPoint({i,j,k,0});
			object.addPoint({i,j,k,w});
			object.addLine(2*k + cpoints, 2*k+1 + cpoints);
		}
		cpoints += 2*(z+1);
	}
	
	for(int i = 0; i < x+1; i++) for(int j = 0; j < y+1; j++) {
		for(int k = 0; k < w+1; k++) {
			object.addPoint({i,j,0,k});
			object.addPoint({i,j,z,k});
			object.addLine(2*k + cpoints, 2*k+1 + cpoints);
		}
		cpoints += 2*(w+1);
	}
	
	for(int i = 0; i < x+1; i++) for(int j = 0; j < z+1; j++) {
		for(int k = 0; k < w+1; k++) {
			object.addPoint({i,0,j,k});
			object.addPoint({i,y,j,k});
			object.addLine(2*k + cpoints, 2*k+1 + cpoints);
		}
		cpoints += 2*(w+1);
	}
	
	for(int i = 0; i < y+1; i++) for(int j = 0; j < z+1; j++) {
		for(int k = 0; k < w+1; k++) {
			object.addPoint({0,i,j,k});
			object.addPoint({x,i,j,k});
			object.addLine(2*k + cpoints, 2*k+1 + cpoints);
		}
		cpoints += 2*(w+1);
	}
	
	if(centered)
		object = object.translate({-x/2., -y/2., -z/2., -w/2.});
	
	return object;
}

// clouds
Object o_dyadicCloud(int n, double radius) {
	Object object;
	Point point (1);
	for(int i = 0; i < n; i++) {
		point = { radius * ((2.0 * i)/n - 1.0) };
		object.addPoint(point);
	}
	return object;
}

Object o_squareCloud(int n, double radius) {
	Object object;
	Point point (2);
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++) {
		point = {
			radius * ((2.0 * i)/n - 1.0),
			radius * ((2.0 * j)/n - 1.0)
		};
		object.addPoint(point);
	}
	return object;
}

Object o_cubicCloud(int n, double radius) {
	Object object;
	Point point (3);
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++)
	for(int k = 0; k < n; k++) {
		point = {
			radius * ((2.0 * i)/n - 1.0),
			radius * ((2.0 * j)/n - 1.0),
			radius * ((2.0 * k)/n - 1.0)
		};
		object.addPoint(point);
	}
	return object;
}

Object o_tesseracticCloud(int n, double radius) {
	Object object;
	Point point (4);
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++)
	for(int k = 0; k < n; k++)
	for(int l = 0; l < n; l++) {
		point = {
			radius * ((2.0 * i)/n - 1.0),
			radius * ((2.0 * j)/n - 1.0),
			radius * ((2.0 * k)/n - 1.0),
			radius * ((2.0 * l)/n - 1.0)
		};
		object.addPoint(point);
	}
	return object;
}

Object o_discCloud(int n, double radius) {
	Object object;
	Point point (2);
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++) {
		point = {
			radius * ((2.0 * i)/n - 1.0),
			radius * ((2.0 * j)/n - 1.0)
		};
		if(point.getMagnitude() <= radius)
			object.addPoint(point);
	}
	return object;
}

Object o_sunflowerDiscCloud(int n, double radius) {
	Object object;
	double phi = (1 + sqrt(5)) / 2;
	
	for(int i = 1; i <= n; i++) {
		double theta = 2*M_PI/(phi*phi) * i;
		double radii = radius * sqrt(i) / sqrt(n);
		
		object.addPoint({
			radii * cos(theta),
			radii * sin(theta)
		});
	}
	
	object.addPoint({0.0, 0.0});
	
	return object;
}

Object o_sphericalCloud(int n, double radius) {
	Object object;
	Point point (3);
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++)
	for(int k = 0; k < n; k++) {
		point = {
			radius * ((2.0 * i)/n - 1.0),
			radius * ((2.0 * j)/n - 1.0),
			radius * ((2.0 * k)/n - 1.0)
		};
		if(point.getMagnitude() <= radius)
			object.addPoint(point);
	}
	return object;
}

Object o_glomeralCloud(int n, double radius) {
	Object object;
	Point point (4);
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++)
	for(int k = 0; k < n; k++)
	for(int l = 0; l < n; l++) {
		point = {
			radius * ((2.0 * i)/n - 1.0),
			radius * ((2.0 * j)/n - 1.0),
			radius * ((2.0 * k)/n - 1.0),
			radius * ((2.0 * l)/n - 1.0)
		};
		if(point.getMagnitude() <= radius)
			object.addPoint(point);
	}
	return object;
}

// miscellaneous
Object o_apeirogrammon(int n, double r) {
	Object object;
	
	Point a = Point(n);
	for(int i = 0; i < n; i++) {
		object.addPoint(a);
		object.addLine(i, i+1);
		a[i] = 1.0;
	}
	object.addPoint(a);
	
	return object;
}

Object o_point(Point position) {
	Object object ( {position}, {} );
	return object;
}

Object o_polygon(int n, int d, double r) {
	Object object;
	
	bool edge1 = false;
	if(r == DEFAULT_FLT) {
		r = 1;
		edge1 = true;
	}
	for(int i = 0; i < n; i++) {
		object.addPoint({ r*sin(2*i*M_PI*d/n), r*cos(2*i*M_PI*d/n) });
		object.addLine(i, (i+1) % n);
	}
	
	if(edge1) { // make edge length 1
		object = object.scale(1.0 / object.getEdgeLength());
	}
	
	return object;
}