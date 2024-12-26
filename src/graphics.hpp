#pragma once
#include "main.hpp"
#include "object.hpp"
using sf::Vector2, sf::Vector2f, sf::Vector2i, sf::Vector2u;
typedef sf::Vector2<double> Vector2d;

typedef std::vector<std::vector<double>> Rotations;
typedef std::vector<std::vector<Vector2d>> RotationMatrix;

struct Camera {
	sf::RenderWindow *window;
	Scene *scene;
	sf::Font *font;
	Rotations rotations;
	RotationMatrix rotationmatrix;
	double scenedims;
	double scale = 200.0;
	
	int arrowdim = 5; // arrow key rotates in the 6th dimension by default
	
	bool renderpoints = false;
	bool renderlines  = true;
	bool rendertext   = true;
	
	int rendermode = 0;
	int depthdim = 3;
	double depthtemp = 1.0;
	double saturtemp = 1.0;
	bool hidefront = false;
	
	double focal3d = -2.0;
	double focal4d = -2.0;
	bool orthographic3d = false;
	bool orthographic4d = false;
	
	void refreshRotMat();
	
	Camera(sf::RenderWindow *pwindow, Scene *pscene) {
		this->window = pwindow;
		this->scene  = pscene;
		scenedims = (*pscene)[0].getRank();
		rotations = Rotations(scenedims, std::vector<double>(scenedims, 0.0));
		rotationmatrix = RotationMatrix(scenedims, std::vector<Vector2d>(scenedims, Vector2d(0.0, 0.0)));
	}
	
	void switchScene(Scene *pscene) {
		this->scene  = pscene;
		scenedims = (*pscene)[0].getRank();;
		rotations = Rotations(scenedims, std::vector<double>(scenedims, 0.0));
		rotationmatrix = RotationMatrix(scenedims, std::vector<Vector2d>(scenedims, Vector2d(0.0, 0.0)));
	}
};

void drawObject(Object object, Camera &graphs);
void drawText(std::string string, int x, int y, Camera &camera);
void drawRotationText(int plane1, int plane2, Camera &camera);
sf::Vector2f graphToScreen(sf::Vector2f g, Camera &camera);
sf::Vector2f pointToVertex(Point pt, Camera &graphs);
