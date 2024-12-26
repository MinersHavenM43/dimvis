#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>

/*
 * 0: "euler rotation": rotates based on the spatial axes
 * 1: "personal rotation":  rotates based on the camera
 * 2: "horizontal rotation": blend of 0 and 1.
 */
#define ROTATION_MODE 1
/*
 * limits the drawing rate; putting it at -1.0 (or any negative number) makes fps unlimited.
 */
#define FPS_LIMIT -60.0

/*
 * location for storing DVBs (polytope files)
 */
#define DVB_LOCATION "obj/"
