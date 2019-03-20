#include "headers.h"

void drawStars() {
	int i,n=50;
	float p;
	glBegin(GL_POINTS);
	for(i=0;i<STARS_SIZE;i++) {
		p=(rand()%1000)/1000.0;
		glColor3f(p,p,p);
		glVertex2f(stars[i].x, stars[i].y);
	}
	glEnd();
}

void drawSun() {
	glColor3f(1,0.67,0);
	fillCircle(WIDTH/2, HEIGHT/2, SUN_SIZE/2 +sunring);
	glColor3f(1,1,(sunring-5)/10.0);
	fillCircle(WIDTH/2,HEIGHT/2,SUN_SIZE/2);

}

void drawPlanets() {
	int i;
	glPushMatrix();
	glTranslated(WIDTH/2,HEIGHT/2,0);
	for(i=0;i<8;i++) {
		glColor3f(planets[i].cr, planets[i].cg, planets[i].cb);
		fillCircle(planets[i].x,planets[i].y,planets[i].r);
	}
	glPopMatrix();
}

void drawAsteroids() {
	int i,n = ASTEROID_N;
	double r = getOrbitsDistance()/10;
	double theta = 0;
	glPushMatrix();
	glTranslated(WIDTH/2, HEIGHT/2, 0);
	for(i=0;i<n;i++) {
		glColor3f(0.51,0.196,0.114);
		fillCircle(asteroids[i].x,asteroids[i].y, r+2);
		glColor3f(0.71,0.396,0.114);
		fillCircle(asteroids[i].x,asteroids[i].y, r);
	}

	glPopMatrix();
}

void drawOrbits() {
	int i;
	double inc = getOrbitsDistance(),s=0;
	glColor3f(1,1,1);
	for(s=getFirstOrbitDistance(),i=0;i<8;i++,s+=inc) {
		if(i==4) s+=inc;
		drawCircle(WIDTH/2,HEIGHT/2,s);
	}
}

