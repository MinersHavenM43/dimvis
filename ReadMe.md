# Dimvis
nD rendering engine

# Using
* To visualize a polytope from the library, put its file path after the command. Example: `./build/dimvis.o 4D/Tesseract`.
* To visualize the "park scenes", simply leave the argument blank. Example: `./build/dimvis.o`.
* To visualize the "polytope scenes", write two arguments. Example: `./build/dimvis.o 1 2`.

To visualize these scenes better, set `ROTATION_MODE` in `src/main.hpp` to `1` (free rotation) in the former and to `2` (horizontal rotation) in the latter, then recompile.

# Compiling
To compile, simply run `make`. You need SFML (graphics engine) and Make (compilation "engine").

## Controls
Navigating through the controls of this thing is about as hard as navigating an airplane.

### Screen
* Zoom: Scroll
* Change 3D perspective: LMouse + Scroll
* Change nD perspective: RMouse + Scroll
* Orthographic projection: [
* nD Orthographic projection: ]

### Perspective
* Normal coloring: F5
* Axis depth coloring: F6 + (axis dimension, 1-9)
* "Normal depth coloring": F7 (seriously need reworking)
* Cull front of the polytope: F8
* Change axis distance coloring: Ctrl+Scroll* (works with F6 and F7)
* Change radial distance coloring: Shift+Scroll (works with F7)

### Rotations
Note: *x* is front/back, *y* is up/down, *z* is left/right, *w* is on/gain, and I think you can infer the rest.
Set *n* with the number keys (1-9).
#### 2D
* Pitch (*xy*): W/S
#### 3D
* Yaw (*xz*): A/D
* Roll (*yz*): Q/E
#### 4D
* Reel (*xw*): F/H
* Tumble (*yw*): T/G
* Twirl (*zw*): R/Y
#### 5D
* Coil (*xv*): J/L
* Topple (*yv*): I/K
* Gnarl (*zv*): U/O
* Whirl (*wv*): M/,
#### General
* *n*-yaw (*xn*): ←/→
* *n*-roll (*yn*): ↑/↓
To reverse these, use LCtrl.
* *n*-twirl-1 (*zn*): \
* *n*-twirl-2 (*wn*): Z
* *n*-twirl-3 (*vn*): X
* *n*-twirl-4 (*un*): C
* *n*-twirl-5 (*tn*): V
* *n*-twirl-6 (*sn*): B
* *n*-twirl-7 (*rn*): N
