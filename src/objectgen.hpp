#pragma once
#include "object.hpp"

Object o_duoprism(Object a, Object b);
Object o_duotegum(Object a, Object b);
Object o_duopyramid(Object a, Object b, double height, int oriens);
Object o_join(Object a, Object b);
Object o_dyadicTiling(int x, bool centered = true);
Object o_squareTiling(int x, int y, bool centered = true);
Object o_cubicTiling(int x, int y, int z, bool centered = true);
Object o_tesseracticTiling(int x, int y, int z, int w, bool centered = true);
Object o_fastSquareTiling(int x, int y, bool centered = true);
Object o_fastCubicTiling(int x, int y, int z, bool centered = true);
Object o_fastTesseracticTiling(int x, int y, int z, int w, bool centered = true);
Object o_dyadicCloud(int n, double radius);
Object o_squareCloud(int n, double radius);
Object o_cubicCloud(int n, double radius);
Object o_tesseracticCloud(int n, double radius);
Object o_discCloud(int n, double radius);
Object o_sunflowerDiscCloud(int n, double radius);
Object o_sphericalCloud(int n, double radius);
Object o_glomeralCloud(int n, double radius);
Object o_apeirogrammon(int n, double r = 1.0);
Object o_point(Point position);
Object o_polygon(int n, int d = 1, double r = DEFAULT_FLT);