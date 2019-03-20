#ifndef HEADERS_H
#define HEADERS_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "values.h"
#include "structs.h"

void fillCircle(int cx, int cy, int r);
void drawCircle(int cx, int cy, int r);

void drawStars();
void drawOrbits();
void drawSun();
void drawAsteroids();
void drawPlanets();
double getFirstOrbitDistance();
double getOrbitsDistance();

void moveAsteroids(double dt);
void movePlanets(double dt);
void createAsteroids();
void createPlanets();
void setPlanetColor(int i, float r, float g, float b);
void setPlanetSizes();
void createStars();
void initValues();

#endif
