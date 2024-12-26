#pragma once
#include "graphics.hpp"

#define KEY_NULL         sf::Keyboard::Key::Unknown

#define KEY_TOGGLEPOINTS sf::Keyboard::Key::F1
#define KEY_TOGGLEFACES  sf::Keyboard::Key::F2
#define KEY_TOGGLETEXT   sf::Keyboard::Key::F3

#define KEY_COLORDISPLAY sf::Keyboard::Key::F5
#define KEY_DEPTHDISPLAY sf::Keyboard::Key::F6
#define KEY_DEPTHCHANGE  sf::Keyboard::Key::RControl
#define KEY_SATURDISPLAY sf::Keyboard::Key::F7
#define KEY_SATURCHANGE  sf::Keyboard::Key::RShift
#define KEY_TOGGLEFRONT sf::Keyboard::Key::F8

#define KEY_INVROTATION    sf::Keyboard::Key::LControl
#define KEY_SLWROTATION    sf::Keyboard::Key::LShift
#define KEY_ORTHOGRAPHIC3D sf::Keyboard::Key::LBracket
#define KEY_ORTHOGRAPHIC4D sf::Keyboard::Key::RBracket

#define KEY_PITCH_1  sf::Keyboard::Key::S
#define KEY_PITCH_2  sf::Keyboard::Key::W

#define KEY_YAW_1    sf::Keyboard::Key::A
#define KEY_YAW_2    sf::Keyboard::Key::D
#define KEY_ROLL_1   sf::Keyboard::Key::Q
#define KEY_ROLL_2   sf::Keyboard::Key::E

#define KEY_REEL_1   sf::Keyboard::Key::F
#define KEY_REEL_2   sf::Keyboard::Key::H
#define KEY_TWIRL_1  sf::Keyboard::Key::R
#define KEY_TWIRL_2  sf::Keyboard::Key::Y
#define KEY_TUMBLE_1 sf::Keyboard::Key::G
#define KEY_TUMBLE_2 sf::Keyboard::Key::T

#define KEY_COIL_1   sf::Keyboard::Key::J
#define KEY_COIL_2   sf::Keyboard::Key::L
#define KEY_GNARL_1  sf::Keyboard::Key::U
#define KEY_GNARL_2  sf::Keyboard::Key::O
#define KEY_WHIRL_1  sf::Keyboard::Key::M
#define KEY_WHIRL_2  sf::Keyboard::Key::Comma
#define KEY_TOPPLE_1 sf::Keyboard::Key::K
#define KEY_TOPPLE_2 sf::Keyboard::Key::I

#define KEY_NYAW_1   sf::Keyboard::Key::Right
#define KEY_NYAW_2   sf::Keyboard::Key::Left

#define KEY_NROLL_1  sf::Keyboard::Key::Up
#define KEY_NROLL_2  sf::Keyboard::Key::Down

#define KEY_NTWIRL_1 sf::Keyboard::Key::BackSlash
#define KEY_NTWIRL_2 sf::Keyboard::Key::Z
#define KEY_NTWIRL_3 sf::Keyboard::Key::X
#define KEY_NTWIRL_4 sf::Keyboard::Key::C
#define KEY_NTWIRL_5 sf::Keyboard::Key::V
#define KEY_NTWIRL_6 sf::Keyboard::Key::B
#define KEY_NTWIRL_7 sf::Keyboard::Key::N

void actEvent(sf::Event event, Camera &camera, double dt);
void moveCamera(sf::Event event, Camera &camera, double dt);