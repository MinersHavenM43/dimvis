#include "controls.hpp"

sf::Keyboard::Key dimkeys[] {
	sf::Keyboard::Key::Quote,
	sf::Keyboard::Key::Num1,
	sf::Keyboard::Key::Num2,
	sf::Keyboard::Key::Num3,
	sf::Keyboard::Key::Num4,
	sf::Keyboard::Key::Num5,
	sf::Keyboard::Key::Num6,
	sf::Keyboard::Key::Num7,
	sf::Keyboard::Key::Num8,
	sf::Keyboard::Key::Num9,
	sf::Keyboard::Key::Num0,
	sf::Keyboard::Key::Hyphen,
	sf::Keyboard::Key::Equal
};

void otherControls(sf::Event event, Camera &camera) {
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		camera.window->close();
	}
}

void actEvent(sf::Event event, Camera &camera, double dt) {
	if(event.type == sf::Event::MouseWheelScrolled) {
		double rate = sf::Keyboard::isKeyPressed(KEY_SLWROTATION) ? 0.2 : 1.0;
		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			if(event.mouseWheelScroll.delta > 0)
				camera.focal3d += rate;
			else
				camera.focal3d -= rate;
		}
		else if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
			if(event.mouseWheelScroll.delta > 0)
				camera.focal4d += rate;
			else
				camera.focal4d -= rate;
		}
		else if(sf::Keyboard::isKeyPressed(KEY_DEPTHCHANGE)) {
			if(event.mouseWheelScroll.delta > 0)
				camera.depthtemp *= 1 + 0.2 * rate;
			else
				camera.depthtemp /= 1 + 0.2 * rate;
			
			if(camera.depthtemp < 0)
				camera.depthtemp = 0;
		}
		else if(sf::Keyboard::isKeyPressed(KEY_SATURCHANGE)) {
			if(event.mouseWheelScroll.delta > 0)
				camera.saturtemp *= 1 + 0.4 * rate;
			else
				camera.saturtemp /= 1 + 0.4 * rate;
			
			if(camera.saturtemp < 0)
				camera.saturtemp = 0;
		}
		else {
			if(event.mouseWheelScroll.delta > 0)
				camera.scale *= 1.1;
			else
				camera.scale /= 1.1;
		}
	}
	if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(KEY_TOGGLEPOINTS)) {
		camera.renderpoints = !camera.renderpoints;
	}
	if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(KEY_TOGGLEFACES)) {
		camera.renderlines = !camera.renderlines;
	}
	if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(KEY_TOGGLETEXT)) {
		camera.rendertext = !camera.rendertext;
	}
	if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(KEY_ORTHOGRAPHIC3D)) {
		camera.orthographic3d = !camera.orthographic3d;
	}
	if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(KEY_ORTHOGRAPHIC4D)) {
		camera.orthographic4d = !camera.orthographic4d;
	}
	if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(KEY_COLORDISPLAY)) {
		camera.rendermode = 0;
	}
	if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(KEY_DEPTHDISPLAY)) {
		camera.rendermode = 1;
	}
	if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(KEY_SATURDISPLAY)) {
		camera.rendermode = 2;
	}
	if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(KEY_TOGGLEFRONT)) {
		camera.hidefront = !camera.hidefront;
	}
	
	for(int i = 0; i < 13; i++) {
		if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(dimkeys[i])) {
			if(sf::Keyboard::isKeyPressed(KEY_DEPTHDISPLAY))
				camera.depthdim = i-1;
			else if(i > 1)
				camera.arrowdim = i-1;
		}
	}
}

void moveCamera(sf::Event event, Camera &camera, double dt) {
	#if ROTATION_MODE == 0
		#define ROTATEOBJ(x, y, r) \
			camera.rotations[y][x] += r; \
			drawRotationText(x, y, camera);
	#elif ROTATION_MODE == 1
		#define ROTATEOBJ(x, y, r)  \
			for(int i = 0; i < camera.scene->size(); i++) \
				(*camera.scene)[i] = (*camera.scene)[i].rotate(y, x, r); \
			drawRotationText(x, y, camera);
	#elif ROTATION_MODE == 2
		#define ROTATEOBJ(x, y, r)  \
			for(int i = 0; i < camera.scene->size(); i++) { \
				if(x != 1) \
					(*camera.scene)[i] = (*camera.scene)[i].rotate(y, x, r); \
			} \
			if(x == 1) \
				camera.rotations[y][1] += r; \
			drawRotationText(x, y, camera);
	#endif
	
	#define ROTATEPLANE(x, y, k1, k2) \
		if( camera.scenedims > (x>y?x:y) && y > x) { \
			if(sf::Keyboard::isKeyPressed(k1)) { \
				ROTATEOBJ(x, y, -rotspeed) \
			} \
			if(sf::Keyboard::isKeyPressed(k2)) { \
				ROTATEOBJ(x, y, rotspeed) \
			} \
		}
	
	double slowrotmult = 0.25;
	double rotspeed0 = 1 * dt; // in radians per second
	double rotspeed1 = sf::Keyboard::isKeyPressed(KEY_INVROTATION) ? -rotspeed0 : rotspeed0; // invert rotation if ctrl is pressed. this is necessary for 6D+ twirls
	double rotspeed  = sf::Keyboard::isKeyPressed(KEY_SLWROTATION) ? slowrotmult*rotspeed1 : rotspeed1; // slow rotation
	
	ROTATEPLANE(1, 2, KEY_PITCH_1, KEY_PITCH_2)
	
	ROTATEPLANE(0, 2, KEY_YAW_1, KEY_YAW_2)
	ROTATEPLANE(0, 1, KEY_ROLL_1, KEY_ROLL_2)
	
	ROTATEPLANE(0, 3, KEY_REEL_1,   KEY_REEL_2)
	ROTATEPLANE(1, 3, KEY_TUMBLE_1, KEY_TUMBLE_2)
	ROTATEPLANE(2, 3, KEY_TWIRL_1,  KEY_TWIRL_2)
	
	ROTATEPLANE(0, 4, KEY_COIL_1,   KEY_COIL_2)
	ROTATEPLANE(1, 4, KEY_TOPPLE_1, KEY_TOPPLE_2)
	ROTATEPLANE(2, 4, KEY_GNARL_1,  KEY_GNARL_2)
	ROTATEPLANE(3, 4, KEY_WHIRL_1,  KEY_WHIRL_2)
	
	ROTATEPLANE(0,  camera.arrowdim, KEY_NYAW_1,  KEY_NYAW_2)
	ROTATEPLANE(1,  camera.arrowdim, KEY_NROLL_1, KEY_NROLL_2)
	ROTATEPLANE(2,  camera.arrowdim, KEY_NTWIRL_1, KEY_NULL)
	ROTATEPLANE(3,  camera.arrowdim, KEY_NTWIRL_2, KEY_NULL)
	ROTATEPLANE(4,  camera.arrowdim, KEY_NTWIRL_3, KEY_NULL)
	ROTATEPLANE(5,  camera.arrowdim, KEY_NTWIRL_4, KEY_NULL)
	ROTATEPLANE(6,  camera.arrowdim, KEY_NTWIRL_5, KEY_NULL)
	ROTATEPLANE(7,  camera.arrowdim, KEY_NTWIRL_6, KEY_NULL)
	ROTATEPLANE(8,  camera.arrowdim, KEY_NTWIRL_7, KEY_NULL)
	
	otherControls(event, camera);
}