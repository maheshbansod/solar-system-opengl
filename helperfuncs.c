
#include "headers.h"

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
