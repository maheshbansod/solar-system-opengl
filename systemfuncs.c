
#include "headers.h"

	double sunring = 5;
	double sunringvel=10;

	double SUN_SIZE=100;
	double MERCURY_SIZE=0;
	double VENUS_SIZE=0;
	double EARTH_SIZE=0;
	double MARS_SIZE=0;
	double JUPITER_SIZE=0;
	double SATURN_SIZE=0;
	double URANUS_SIZE=0;
	double NEPTUNE_SIZE=0;


struct planet planets[8];
struct stars stars[STARS_SIZE];
struct stars asteroids[ASTEROID_N];

void createStars() {
	int i;
	for(i=0;i<STARS_SIZE;i++) {
		stars[i].x = rand()%WIDTH;
		stars[i].y = rand()%HEIGHT;
	}
}

void setPlanetSizes() { 
		MERCURY_SIZE=SUN_SIZE/10;
		VENUS_SIZE=MERCURY_SIZE*2.5;
		EARTH_SIZE=MERCURY_SIZE*3.0;
		MARS_SIZE=EARTH_SIZE/2+1;
		JUPITER_SIZE=SUN_SIZE/2;
		SATURN_SIZE=MERCURY_SIZE*4.5;
		URANUS_SIZE=MERCURY_SIZE*4;
		NEPTUNE_SIZE=MERCURY_SIZE*3.8;
		planets[0].r = MERCURY_SIZE/2;
	planets[1].r = VENUS_SIZE/2;
	planets[2].r = EARTH_SIZE/2;
	planets[3].r = MARS_SIZE/2;
	planets[4].r = JUPITER_SIZE/2;
	planets[5].r = SATURN_SIZE/2;
	planets[6].r = URANUS_SIZE/2;
	planets[7].r = NEPTUNE_SIZE/2;


}

double getOrbitsDistance() {
	return JUPITER_SIZE;
}

double getFirstOrbitDistance() {
	return getOrbitsDistance()+SUN_SIZE/2.0;
}

void setPlanetColor(int i, float r, float g, float b) {
	planets[i].cr=r;
	planets[i].cg=g;
	planets[i].cb=b;
}

void createPlanets() {
	int fo = getFirstOrbitDistance();
	int d = getOrbitsDistance();
	double orb_r;
	int i;

	setPlanetColor(0, 0.2,0.2,0.2); //dark grey
	setPlanetColor(1, 0.71,0.39,0.11); //lightbrown
	setPlanetColor(2, 0, 0, 0.502); //navy blue
	setPlanetColor(3, 0.27,0.094,0.015); //mars red
	setPlanetColor(4, 0.5451,0.24,0.28); //jupiter red
	setPlanetColor(5, 0.2,0.24,0.27); //saturn color
	setPlanetColor(6, 0.39,0.53,0.55); //uranus color
	setPlanetColor(7, 0.5,0.69,0.69); //neptune color
	for(orb_r=fo,i=0;i<8;i++,orb_r+=d) {
		//orb_r = fo+i*d;
		if(i==4) {
			orb_r+=d;
		}
		planets[i].x = -orb_r+rand()%((int)(2*orb_r));
		planets[i].y = ((rand()%2)*2-1)*sqrt(orb_r*orb_r - planets[i].x*planets[i].x);

		planets[i].vel = 1;//20-i*i*2+i;
	}
}

void createAsteroids() {
	int beltwidth=getOrbitsDistance()/2;
	int n=ASTEROID_N; //no. of asteroids
	int r = getFirstOrbitDistance()+getOrbitsDistance()*4;
	int i;

	for(i=0;i<n;i++) {
		asteroids[i].x=-r+rand()%(2*r);
		asteroids[i].y=((rand()%2)*2-1)*sqrt(r*r - asteroids[i].x*asteroids[i].x) + rand()%(beltwidth/2)-beltwidth/2;
	}
}



void movePlanets(double dt) {
	int i, fo = getFirstOrbitDistance(),d = getOrbitsDistance();
	double theta,orb_r;
	for(orb_r = fo,i=0;i<8;i++, orb_r+=d) {
		//orb_r = fo+d*i;
		if(i==4) orb_r+=d;
		theta = atan2(planets[i].y,planets[i].x)+planets[i].vel/orb_r;
		planets[i].x = orb_r*cos(theta);
		planets[i].y = orb_r*sin(theta);
	}
}

void moveAsteroids(double dt) {
	double theta = 0,r=0;
	int i,n=ASTEROID_N,velrange=70;
	for(i=0;i<n;i++) {
		r = sqrt(pow(asteroids[i].x,2)+pow(asteroids[i].y,2));
		theta = atan2(asteroids[i].y, asteroids[i].x)+(rand()%velrange)*dt/r;
		asteroids[i].x = r*cos(theta);
		asteroids[i].y = r*sin(theta);
	}
}

