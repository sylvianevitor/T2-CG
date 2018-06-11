#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#ifdef __linux__
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/freeglut.h>
#elif __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>
#endif
#include "mouse.h"
#include "button.h"
#include "interface.h"

//Mouse global
Mouse TheMouse = {0,0,0,0};
//Buttons global
ButtonList *bl = NULL;

//Window scale
int winw = 800;
int winh = 800;

//Switch Objects
int SelectedObject = 0;

//Switch lighting model
int curShading = 0;

//Switch to Solid model
int SelectSolid = 0;

//Object Operation Counter and flags
int op_flags[3][4] = {{0,3,3,0},{0,3,3,0},{0,3,3,0}};

//Control keyboard events
void keyPressEvent(unsigned char key, int x, int y) {
    switch(key) {
        case '.' :
	        SelectedObject +=1;
	        if(SelectedObject == 6) SelectedObject = 0;
	        	glutPostRedisplay();
        	break;
        case '\x1b' :
            exit(0);
            break;
       	case 's':
       		if (SelectSolid){curShading = 1 - curShading;}
       		glutPostRedisplay();
       	case 'c':
       		SelectSolid = 1;
       		glutPostRedisplay();

    }
}

//Mouse button control
void MouseButton(int button,int pressed,int x, int y){
	//update position
	TheMouse.x = x;
	TheMouse.y = y;

	if (pressed == GLUT_DOWN){ //press
		switch(button){
			case GLUT_LEFT_BUTTON:
				TheMouse.lb = 1;
				ButtonSetPress(bl,x,y,op_flags);
			case GLUT_RIGHT_BUTTON:
				TheMouse.rb = 1;
				break;
		}
	}
	else { //button released
		switch(button) {
			case GLUT_LEFT_BUTTON: 
				TheMouse.lb = 0;
				ButtonRestore(bl,x,y);
				break;
			case GLUT_RIGHT_BUTTON:
				TheMouse.rb = 0;
				break;
		}
	}

	glutPostRedisplay();
}

//Mouse moving callback
void MouseMotion(int x, int y){
	//mouse position update
	TheMouse.x = x;
	TheMouse.y = y;

	//Verify if it is under object
	ButtonUnder(bl,TheMouse.x,TheMouse.y);

	glutPostRedisplay();
}

// Define light position
void setLight() {
    GLfloat light_position[4] = {800.0, 800.0, -20.0, 10.0};
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
}

// Define Flat, Gouraud or Phong lightning
void setShading(int sType) {
    switch(sType) { 
        case 0 :
            glShadeModel(GL_SMOOTH); //Gouraud
            break;            
        case 1 :
            glShadeModel(GL_FLAT); //Flat
            break;
        /*case 2 :
			Phong();
        */
    }
}


// Draw elements
void display(){
	//clear z buffer and background
	glClear( GL_COLOR_BUFFER_BIT |
			 GL_DEPTH_BUFFER_BIT );

	//enable light and z-buffer
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	//set matrix mode for 3D elements
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(winh==0)?(1):((float)winw/winh),1,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	setLight();
    setShading(curShading);

    if(SelectSolid){
   		Draw3DSolid(SelectedObject,op_flags);
    }else{Draw3D(SelectedObject,op_flags);}
	
	//disable z-buffer for 2D elements
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	//set matrix mode for 2D elements
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,winw,winh,0,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Draw2D(bl);

	glutSwapBuffers();
}

// Main function
int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(winw,winh);
	glutInitWindowPosition(200,100);
	glutCreateWindow("Trabalho 2");

	ButtonList *buttonl = init();
	bl = buttonl;
	glutDisplayFunc(display);
	glutMouseFunc(MouseButton);
	glutPassiveMotionFunc(MouseMotion);
	glutKeyboardFunc(keyPressEvent);

	glutMainLoop();

	return 0;
}
