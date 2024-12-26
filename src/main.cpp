#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "controls.hpp"
#include "graphics.hpp"
#include "controls.hpp"
#include "object.hpp"
#include "objectgen.hpp"
#include "dvoparser.hpp"
#include "scenes.hpp"

int main(int argc, char **argv) {	
	std::vector<Scene> scenes;
	if(argc > 2) {
		scenes = polyScenelist();
	}
	else if(argc == 2) {
		std::string polyname = std::string(argv[1]);
		scenes = {{ loadDVO(polyname) }};
	}
	else {
		scenes = parkScenelist();
		// Object object = loadDVB("4D/Hecatonicosachoron");
		// Object prismed = loadDVB("3D/Co").prism(1.0);
		// Object t = o_cubicTiling(20, 20, 20, true);
		// Object u = o_duoprism(o_polygon(5, 2), o_polygon(5, 2));
		// scenes = polyScenelist();
		/*int n = 16;
		Object ngon = o_polygon(4);
		scenes = {{}};
		for(int i = 0; i <= n; i++) {
			scenes[0].push_back(o_duoprism(
				ngon.scale(sin((M_PI_2*i)/n)),
				ngon.scale(cos((M_PI_2*i)/n))
			));
		}*/
		/*Object plane = o_polygon(50, 1, 1.0);
		scenes = {
			{
				plane.addDimension(0),
				plane.addDimension(1),
				plane.addDimension(2),
			},
			{ // nvm some of them are duplicates wtf
				plane.addDimension(0).addDimension(0).recolor(sf::Color::Red),
				plane.addDimension(0).addDimension(1),
				plane.addDimension(0).addDimension(2),
				plane.addDimension(0).addDimension(3).recolor(sf::Color::Blue),
				plane.addDimension(1).addDimension(1),
				plane.addDimension(1).addDimension(2),
				plane.addDimension(1).addDimension(3),
				plane.addDimension(2).addDimension(2),
				plane.addDimension(2).addDimension(3),
			},
		};*/
	}
	int scid = 0;
	
	int dim = scenes[scid][0].getRank();
	
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Dimvis"
	, sf::Style::Fullscreen
	);
	Camera camera ( &window, &scenes[scid] );
	sf::Font font;
	font.loadFromFile("DejaVuSans.ttf");
	camera.font = &font;
	
	sf::Clock clock;
	sf::Time dt;
	#define DTARR_SIZE 10
	double dtarr[DTARR_SIZE] = { 0.016 };
	double dtavg = 0.016;
	long ticks = 0;
	sf::Time minframe = sf::seconds(1/FPS_LIMIT);
	
	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			actEvent(event, camera, dt.asSeconds());
			
			if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F12)) {
				scid++;
				camera.switchScene(&scenes[scid]);
				printf("%i\n", scid);
			}
			if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F11)) {
				scid--;
				camera.switchScene(&scenes[scid]);
				printf("%i\n", scid);
			}
			
			if(event.type == sf::Event::Closed) {
				window.close();
			}
		}
		
		window.clear(sf::Color::Black);
		
		moveCamera(event, camera, dt.asSeconds());
		camera.refreshRotMat();
		
		if(!camera.orthographic3d) {
			drawText("focal: " + std::to_string((int)(10*camera.focal3d)), 10, window.getSize().y - 54, camera);
			if(!camera.orthographic4d)
				drawText("4d focal: " + std::to_string((int)(10*camera.focal4d)), 10, window.getSize().y - 30, camera);
		}
		drawText("fps: " + std::to_string(1/dtavg), window.getSize().x - 100, window.getSize().y - 30, camera);
		
		for(int i = 0; i < camera.scene->size(); i++) {
			drawObject((*camera.scene)[i], camera);
		}
		
		window.display();
		
		dt = clock.restart();
		dtarr[ticks % DTARR_SIZE] = dt.asSeconds();
		for(int i = 0; i < DTARR_SIZE; i++) {
			dtavg += dtarr[i];
		}
		dtavg /= DTARR_SIZE;
		if(dt < minframe) {
			sf::sleep(minframe - dt);
		}
		ticks++;
	}
	
	return 0;
}
