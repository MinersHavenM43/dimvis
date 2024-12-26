// graphics. does the areometry for rendering
#include "graphics.hpp"

void Camera::refreshRotMat() {
	int rtsize = rotations.size();
	double r;
	for(int i = 1; i < rtsize; i++)
		for(int j = 0; j < i; j++) {
			r = this->rotations[i][j];
			this->rotationmatrix[i][j] = Vector2d(cos(r), sin(r));
		}
}

sf::Color HSVToRGB(float H, double S, double V) { // taken from https://github.com/Inseckto/HSV-to-RGB/blob/master/HSV2RGB.c
	float h = H / 360;
	float s = S;
	float v = V;
	
	int i = floor(h * 6);
	float f = h * 6 - i;
	float p = v * (1 - s);
	float q = v * (1 - f * s);
	float t = v * (1 - (1 - f) * s);
	
	float r, g, b;
	switch(i % 6) {
		case 0: r = v, g = t, b = p; break;
		case 1: r = q, g = v, b = p; break;
		case 2: r = p, g = v, b = t; break;
		case 3: r = p, g = q, b = v; break;
		case 4: r = t, g = p, b = v; break;
		case 5: r = v, g = p, b = q; break;
	}
	
	sf::Color color (r * 255, g * 255, b * 255);	
	return color;
}

double pointDist(Point &pt, int depthdim) {
	int ptrank = pt.getRank();
	if(depthdim > 1) // the normal case
		return pt[depthdim];
	
	// in special cases (dim 0, 1, and 2)
	// 0: distance from origin
	// 1: total hidden distance
	// 2: total non-3D distance
	if(depthdim < 0);
		depthdim = -depthdim;
	
	double dist = 0;
	for(int i = depthdim; i < ptrank; i++) {
		dist += pt[i] * pt[i];
	}
	dist = sqrt(dist);
	
	return dist;
}

sf::Color colorDepth(double z, Camera &camera) {
	double hue = 125 * tanh(z * camera.depthtemp)+125;
	return HSVToRGB(hue, 1.0, 1.0);
}

/*sf::Color colorDepthVal(double w, double z, Camera &camera) {
	double hue = 125 * tanh(w * camera.saturtemp)+125;
	double val = (1 + tanh(2 * z * camera.depthtemp))/2;
	return HSVToRGB(hue, 1.0, val);
}*/

sf::Color colorCycle(double w, double v, double z, Camera &camera) {
	double distwv  = sqrt(w*w + v*v);
	double anglewv = atan2(v, w);
	if(anglewv < 0) anglewv += 2 * M_PI;
	
	double distwvtemp = distwv * camera.saturtemp;
	double zdepthtemp = z * camera.depthtemp;
	
	double hue = 180.0 * M_1_PI * anglewv;
	double sat = tanh(distwvtemp);
	double val = (camera.depthtemp + tanh(2 * zdepthtemp))/(camera.depthtemp + 1);
	
	// printf("%.2f\t%.2f\t%.2f ->\t%.2f\t%.2f\t%.2f\n", anglewv, distwv, zdepthtemp, hue, sat, val);
	
	return HSVToRGB(hue, sat, val);
}

Point rotatePointWithMatrix(Point point, RotationMatrix &rotationmatrix) {
	int rtsize = rotationmatrix.size();
	double pti;
	
	#if ROTATION_MODE == 0
		for(int i = 1; i < rtsize; i++)
			for(int j = 0; j < i; j++) {
				pti = point[i];
				point[i] = pti * rotationmatrix[i][j].x - point[j] * rotationmatrix[i][j].y;
				point[j] = point[j] * rotationmatrix[i][j].x + pti * rotationmatrix[i][j].y;
			}
	#elif ROTATION_MODE == 2
		for(int i = 2; i < rtsize; i++) {
			pti = point[i];
			point[i] = pti * rotationmatrix[i][1].x - point[1] * rotationmatrix[i][1].y;
			point[1] = point[1] * rotationmatrix[i][1].x + pti * rotationmatrix[i][1].y;
		}
	#endif
	
	return point;
}

sf::Vertex pointToVertex(Point &point0, Object &object, Camera &camera) {
	#if ROTATION_MODE == 1
		// Point point = point0;
		#define POINT point0
	#endif
	#if (ROTATION_MODE == 0 || ROTATION_MODE == 2)
		Point point_ = rotatePointWithMatrix(point0, camera.rotationmatrix);
		#define POINT point_
	#endif
	sf::Vertex vertex;
	sf::Vector2f gcoords (POINT[0], POINT[1]);
	
	int ptrank = POINT.getRank();
	if(! (camera.orthographic3d || ptrank < 3) ) {
		double perspective = 1.0 / (POINT[2] - camera.focal3d);
		double persp4d_mul = 1.0;
		if(!camera.orthographic4d)
			for(int i = 1; i < ptrank-2; i++) {
				perspective /= perspective * POINT[i+2] - camera.focal4d;
				persp4d_mul *= -camera.focal4d;
			}
			if(perspective < 0.0)
				perspective = 1e+5;
		
		gcoords *= (float)(perspective * persp4d_mul);
	}
	
	if(camera.hidefront && POINT[ptrank - 1] < 0) {
		vertex.color = sf::Color::Transparent;
		goto skipcoloring;
	}
	
	if(camera.rendermode == 0) { // color mode
		vertex.color = object.color;
	}
	
	if(camera.rendermode == 1) { // depth mode
		vertex.color = colorDepth(POINT[camera.depthdim], camera);
	}
	
	if(camera.rendermode == 2) { // hsv mode
		if(ptrank <= 2)
			vertex.color = sf::Color::White;
		else if(ptrank == 3)
			vertex.color = colorCycle(0.0, 0.0, -POINT[2], camera);
		/* else if(ptrank == 4)
			vertex.color = colorDepthVal(POINT[3], -POINT[2], camera); */
		else
			vertex.color = colorCycle(POINT[-2], POINT[-1], -POINT[2], camera);
	}
	
	skipcoloring:
	
	sf::Vector2u windowsize = camera.window->getSize();
	vertex.position = sf::Vector2f(
		camera.scale * gcoords.x + windowsize.x / 2,
		windowsize.y / 2 - camera.scale * gcoords.y
	);
	
	return vertex;
}

void drawPoint(sf::Vertex ptvert, sf::Shape &ptshape, Camera &camera) {
	ptshape.setPosition(ptvert.position);
	ptshape.setFillColor(ptvert.color);
	camera.window->draw(ptshape);
}

void drawEdges(std::vector<sf::Vertex> &ptverts, Lines &edges, Camera &camera) {
	int dgsize = edges.size();
	sf::VertexArray dgverts (sf::PrimitiveType::Lines, dgsize);
	for(int i = 0; i < dgsize; i++) {
		int ptindex = edges[i];
		dgverts[i] = ptverts[ptindex];
	}
	camera.window->draw(dgverts);
}

void drawObject(Object object, Camera &camera) {
	int objptsize = object.points.size();
	int objdgsize = object.lines.size();
	
	sf::CircleShape ptshape(2, 10);
	ptshape.setOrigin(2, 2);
	
	std::vector<sf::Vertex> ptverts (objptsize, sf::Vertex());
	for(int i = 0; i < objptsize; i++) {
		ptverts[i] = pointToVertex(object.points[i], object, camera);
		/*ptverts[i].position = graphToScreen(pointToVertex(object.points[i], camera), camera);
		if(camera.rendermode == 0)
			ptverts[i].color = object.color;
		else if(camera.rendermode == 1)
			ptverts[i].color = colorDist(pointDist(object.points[i], camera.depthdim), 0.0, camera);
		else // if(camera.rendermode == 2)
			ptverts[i].color = colorDist(pointDist(object.points[i], 2), pointDist(object.points[i], -3), camera);*/
	}
	
	if(camera.renderpoints)
		for(int i = 0; i < objptsize; i++) { // draw points
			drawPoint(ptverts[i], ptshape, camera);
		}
	
	if(camera.renderlines) {
		drawEdges(ptverts, object.lines, camera);
	}
}

void drawText(std::string string, int x, int y, Camera &camera) {
	if(camera.rendertext) {
		sf::Text text;
		text.setFont(*camera.font);
		text.setCharacterSize(18);
		text.setFillColor(sf::Color::White);
		text.setPosition(x, y);
		
		text.setString(string);
		camera.window->draw(text);
	}
}

std::string genRotationName(int plane1, int plane2) {
	std::string stdrotations[4][4] = {
		{ "roll", "yaw"  , "reel"  , "coil"   },
		{ ""    , "pitch", "tumble", "topple" },
		{ ""    , ""     , "twirl" , "gnarl"  },
		{ ""    , ""     , ""      , "whirl"  }
	};
	if(plane1 < 4 && plane2 < 5)
		return stdrotations[plane1][plane2-1];
	
	std::string res;
	if(plane1 == 0) {
		res =  std::to_string(plane2+1);
		res += "-yaw";
	}
	else if(plane1 == 1) {
		res =  std::to_string(plane2+1);
		res += "-roll";
	}
	else if(plane1 > 1) {
		res =  std::to_string(plane2+1);
		res += "-twirl-";
		res += std::to_string(plane1-1);
	}
	
	return res;
}

void drawRotationText(int plane1, int plane2, Camera &camera) {
	drawText(
		genRotationName(plane1, plane2),
		10 + 60 * plane1,
		10 + 24 * (plane2 - 1),
		camera
	);
}