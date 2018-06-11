#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#ifdef __linux__
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/freeglut.h>
#elif __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>
#endif
#include "button.h"
#include "interface.h"
#include "transform.h"

void rotate(int param){
	glRotatef(param*(360/5),0,1,0);
;
}

void translate(int param){
	switch(param){
		case 0:
			glTranslated(-1,0,1);
		break;
		case 1:
			glTranslated(-1,0,-1);
		break;
		case 2:
			glTranslated(1,0,-1);
		break;
		case 3:
			glTranslated(0,0,0);
		break;
		case 4:
			glTranslated(1,0,1);
		break;
	}

}

void scale(int param){
	glScalef((0.25*param)+0.1, (0.25*param)+0.1, (0.25*param)+0.1);
}

void mirror(int param){
	gluLookAt(pow(-1,param)*1,0,pow(-1,param)*1,0,0,0,0,1,0);
}