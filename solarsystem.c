
#include "headers.h"


void init() {
	glClearColor(0,0,0.3,0);
	glPointSize(4);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,WIDTH, 0,HEIGHT);
	
	//initValues();

	setPlanetSizes();
	createStars();
	createPlanets();
	createAsteroids();
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
