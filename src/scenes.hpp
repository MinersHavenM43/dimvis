#pragma once
#include "objectgen.hpp"
#include "dvoparser.hpp"

std::vector<Scene> polyScenelist() {
	std::vector<Scene> scenes = {
		// 2D
		{ o_polygon(3, 1, 1.0) },
		{ o_polygon(4, 1, 1.0) },
		{ o_polygon(5, 1, 1.0) },
		{ o_polygon(5, 2, 1.0) },
		{ o_polygon(6, 1, 1.0) },
		{ o_polygon(100, 1, 1.0) },
		
		// 3D
		{ loadDVO("3D/Tetrahedron") },
		{ loadDVO("3D/Cube") },
		{ loadDVO("3D/Octahedron") },
		{ loadDVO("3D/Dodecahedron") },
		{ loadDVO("3D/Icosahedron") },
		{ loadDVO("3D/arch/grid") },
		
		// 4D
		{ loadDVO("4D/Pentachoron") },
		{ loadDVO("4D/Tesseract") },
		{ loadDVO("4D/Hexadecachoron") },
		{ loadDVO("4D/Icositetrachoron") },
		{ loadDVO("3D/catalan/rad") },
		{ loadDVO("4D/Hecatonicosachoron") },
		{ loadDVO("4D/Hexacosichoron") },
		{ loadDVO("4D/uniform/gidpixhi") },
		/*{ o_polygon(6).prism(1.0) },
		{ o_duoprism(o_polygon(6), o_polygon(4)) },
		{ o_duoprism(o_polygon(20), o_polygon(20)) },*/
		
		// 5D
		{ loadDVO("5D/Hexateron") },
		{ loadDVO("5D/Penteract") },
		{ loadDVO("5D/Triacontaditeron") },
		{ loadDVO("5D/Demipenteract") },
		{ loadDVO("3D/Cube").recolor(sf::Color(255, 255, 255, 100)), loadDVO("3D/Tetrahedron").scale(M_SQRT2).recolor(sf::Color::Red) },
		{ loadDVO("4D/Tesseract").recolor(sf::Color(255, 255, 255, 100)), loadDVO("4D/other/Demitesseract").scale(M_SQRT2).recolor(sf::Color::Red) },
		{ loadDVO("5D/Penteract").recolor(sf::Color(255, 255, 255, 100)), loadDVO("5D/Demipenteract").scale(M_SQRT2).recolor(sf::Color::Red) },
		/*{ o_duoprism(loadDVO("3D/Cube"), o_polygon(3)) },
		{ o_duoprism(loadDVO("3D/Dodecahedron"), o_polygon(5)) },
		{ o_duoprism(loadDVO("3D/catalan/pakid"), o_polygon(18)) },*/
	};
	
	return scenes;
}

std::vector<Scene> parkScenelist() {
	int diam = 8;
	double scale = 2.0;
	
	sf::Color grass_c = sf::Color(0, 191, 0);
	sf::Color trunk_c = sf::Color(127, 63, 0);
	sf::Color leaves_c = sf::Color(0, 192, 63);
	sf::Color path_c = sf::Color(127, 127, 127);
	sf::Color fence_c = sf::Color(255, 255, 255);
	
	Object Trunk3D = o_polygon(4, 1, 1.0).scale(0.5).frustum(0.6, 6.0, 1, true).recolor(trunk_c);
	Object Leaves3D = loadDVO("3D/catalan/rad").scaleUnitRadius().scale(2.5).axisTranslate(1, 6.0).recolor(leaves_c);
	Object Path3D = o_polygon(6, 1, 1.0).scale(0.8).frustum(0.6, 0.25, 1, true).recolor(path_c);
	Object Fence3D = loadDVO("2D/Square").scale(scale * diam).prism(1.0, 1, true).recolor(fence_c);
	
	Object Trunk4D = loadDVO("3D/Octahedron").scaleUnitRadius().scale(0.5).frustum(0.6, 6.0, 1, true).recolor(trunk_c);
	Object Leaves4D = loadDVO("4D/unidual/duspid").scaleUnitRadius().scale(2.5).axisTranslate(1, 6.0).recolor(leaves_c);
	Object Path4D = loadDVO("3D/arch/co").scaleUnitRadius().scale(0.8).frustum(0.6, 0.25, 1, true).recolor(path_c);
	Object Fence4D = loadDVO("3D/Cube").scale(scale * diam).prism(1.0, 1, true).recolor(fence_c);
	
	Object Trunk5D = loadDVO("4D/Hexadecachoron").scaleUnitRadius().scale(0.5).frustum(0.6, 6.0, 1, true).recolor(trunk_c);
	Object Leaves5D = loadDVO("5D/unidual/duscad").scaleUnitRadius().scale(2.5).axisTranslate(1, 6.0).recolor(leaves_c);
	Object Path5D = loadDVO("4D/uniform/rit").scaleUnitRadius().scale(0.8).frustum(0.6, 0.25, 1, true).recolor(path_c);
	Object Fence5D = loadDVO("4D/Tesseract").scale(scale * diam).prism(1.0, 1, true).recolor(fence_c);
	
	std::vector<Scene> scenes = {
		{ // 0
			o_fastSquareTiling(diam, diam).scale(scale).addDimension(1, 0.0).recolor(grass_c),
			Fence3D,
			Trunk3D,
			Leaves3D
		},
		
		{ // 1
			o_fastCubicTiling(diam, diam, diam).scale(scale).addDimension(1, 0.0).recolor(grass_c),
			Fence4D,
			Trunk4D,
			Leaves4D
		},
		{ // 2
			o_fastCubicTiling(diam, diam, diam).scale(scale).addDimension(1, 0.0).recolor(grass_c),
			Fence4D,
		},
		
		{ // 3
			o_fastTesseracticTiling(diam, diam, diam, diam).scale(scale).addDimension(1, 0.0).recolor(grass_c),
			Fence5D,
			Trunk5D,
			Leaves5D
		},
		{ // 4
			o_fastTesseracticTiling(diam, diam, diam, diam).scale(scale).addDimension(1, 0.0).recolor(grass_c),
			Fence5D,
		},
		{ // 5
			o_fastTesseracticTiling(diam, diam, diam, diam).scale(scale).addDimension(1, 0.0).recolor(grass_c),
			Fence5D,
		},
	};
	
	for(int x = -diam/2; x <= diam/2; x++) {
		scenes[2].push_back(Trunk4D.translate({0.0, 0.0, 0.0, x*scale}));
		scenes[2].push_back(Leaves4D.translate({0.0, 0.0, 0.0, x*scale}));
		scenes[4].push_back(Trunk5D.translate({0.0, 0.0, 0.0, 0.0, x*scale}));
		scenes[4].push_back(Leaves5D.translate({0.0, 0.0, 0.0, 0.0, x*scale}));
		
		if(x < -1 || x > 1) {
			scenes[0].push_back(Path3D.translate({x*scale, 0.0, 0.0}));
			scenes[1].push_back(Path4D.translate({x*scale, 0.0, 0.0, 0.0}));
			scenes[2].push_back(Path4D.translate({x*scale, 0.0, 0.0, 0.0}));
			scenes[3].push_back(Path5D.translate({x*scale, 0.0, 0.0, 0.0, 0.0}));
			scenes[4].push_back(Path5D.translate({x*scale, 0.0, 0.0, 0.0, 0.0}));
			scenes[5].push_back(Path5D.translate({x*scale, 0.0, 0.0, 0.0, 0.0}));
		}
		for(int y = -diam/2; y <= diam/2; y++) {
			scenes[5].push_back(Trunk5D.translate({0.0, 0.0, 0.0, x*scale, y*scale}));
			scenes[5].push_back(Leaves5D.translate({0.0, 0.0, 0.0, x*scale, y*scale}));
		}
	}
	
	for(int x = -1; x <= 1; x++) for(int y = -1; y <= 1; y++) {
		if(x != 0 || y != 0) {
			scenes[0].push_back(Path3D.translate({x*scale, 0.0, y*scale}));
			scenes[2].push_back(Path4D.translate({x*scale, 0.0, y*scale, 0.0}));
			scenes[5].push_back(Path5D.translate({x*scale, 0.0, y*scale, 0.0, 0.0}));
		}
		
		for(int z = -1; z <= 1; z++) {
			if(x != 0 || y != 0 || z != 0) {
				scenes[1].push_back(Path4D.translate({x*scale, 0.0, y*scale, z*scale}));
				scenes[4].push_back(Path5D.translate({x*scale, 0.0, y*scale, z*scale, 0.0}));
			}
			
			for(int w = -1; w <= 1; w++) {
				if(x != 0 || y != 0 || z != 0 || w != 0) {
					scenes[3].push_back(Path5D.translate({x*scale, 0.0, y*scale, z*scale, w*scale}));
				}
			}
		}
	}
	
	return scenes;
}