
#ifndef STRUCTS_H
#define STRUCTS_H

struct stars {
	double x;
	double y;
	//double r; //distance from center.. not used for stars
};

struct planet {
	double x,y, r, vel;
	float cr,cg,cb; //color
};
extern struct planet planets[8];
extern struct stars stars[STARS_SIZE];
extern struct stars asteroids[ASTEROID_N];

#endif
