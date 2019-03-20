#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define WIDTH 1024
#define HEIGHT 768
#define STARS_SIZE 50
#define ASTEROID_N 500
#define SUN_L_LIMIT 10

#define FPS 50

struct stars {
	double x;
	double y;
	//double r; //distance from center.. not used for stars
};
struct stars stars[STARS_SIZE];
struct stars asteroids[ASTEROID_N];

struct planet {
	double x,y, r, vel;
	float cr,cg,cb; //color
};
struct planet planets[8];

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

void drawCircle(int cx, int cy, int r) {
	double x,y;

	glPushMatrix();
	glTranslated(cx,cy,0);
	glBegin(GL_LINE_LOOP);
		for(x=-r ; x<=r;x++) {
			y = sqrt(r*r-x*x);
			glVertex2f(x,round(y));
		}
		for(x=r; x >=-r;x--) {
			y = -sqrt(r*r - x*x);
			glVertex2f(x,round(y));
		}
	glEnd();
	glPopMatrix();
}

void fillCircle(int cx, int cy, int r) {
	double x,y;

	glPushMatrix();
	glTranslated(cx,cy,0);
	glBegin(GL_POLYGON);
		for(x=-r ; x<=r;x++) {
			y = sqrt(r*r-x*x);
			glVertex2f(x,round(y));
		}
		for(x=r; x >=-r;x--) {
			y = -sqrt(r*r - x*x);
			glVertex2f(x,round(y));
		}
	glEnd();
	glPopMatrix();
}

void init() {
	glClearColor(0,0,0.3,0);
	glPointSize(4);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,WIDTH, 0,HEIGHT);

	setPlanetSizes();
	createStars();
	createPlanets();
	createAsteroids();
}

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

void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	drawStars();
	drawOrbits();
	drawSun();
	drawAsteroids();
	drawPlanets();

	glFlush();
}

void mykeyboard(unsigned char key, int xx, int yy) {
	switch(key) {
	case '+':
		SUN_SIZE+=2;
		setPlanetSizes();
		createAsteroids();
		break;
	case '-':
		if(SUN_SIZE > SUN_L_LIMIT) {
			SUN_SIZE-=2;
			setPlanetSizes();
			createAsteroids();
		}
		break;
	default: break;
	}
}

void update() {
	static int old_t = 0;
	int t = glutGet(GLUT_ELAPSED_TIME);
	double dt = (t-old_t)/1000.0;
	if(dt >= 1.0/FPS) {
		movePlanets(dt);
		moveAsteroids(dt);
		sunring += sunringvel*dt;
		if(sunring>10 || sunring<5) sunringvel=-sunringvel;
		glutPostRedisplay();
		old_t = t;
	}
}

void main(int argc, char **argv) {
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(350,350);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Solar system");
	glutFullScreen();
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(mykeyboard);
	glutIdleFunc(update);
	init();
	glutMainLoop();
}
