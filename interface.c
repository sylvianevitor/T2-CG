#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
#include "button.h"
#include "transform.h"
#include "interface.h"

void setMaterial(int currentMaterial){
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat no_shininess[] = { 0.0 };
    GLfloat low_shininess[] = { 5.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};

    switch (currentMaterial){
    case 0:
        // Diffuse reflection only; no ambient or specular  
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
        glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
        break;
        
    case 1:
        // Diffuse and specular reflection; low shininess; no ambient
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
        break;
        
    case 2:
        // Diffuse and specular reflection; high shininess; no ambient
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
        break;
        
    case 3:
        // Diffuse refl.; emission; no ambient or specular reflection
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
        glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
        break;
    }     
}

//Define object color
void colorObject(int oType, int SelectedObject){
    int compareObject;
    if(SelectedObject < 3) compareObject = SelectedObject+3;
    else compareObject = SelectedObject;

    if(compareObject == oType)
        glColor3f(1,1,1);
    else 
        glColor3f(0,1,1);  
          
    return ;
}

//Choose objects to display
void drawObject(int oType, int currentMaterial, int SelectedObject) {
    setMaterial(currentMaterial);
    
    colorObject(oType, SelectedObject);
    
    switch(oType) {
        case 0 :
            glutSolidCube(1.5);
            break;
        case 1 :
            glutSolidSphere(1, 100, 100);
            break;
        case 2 :
            glutSolidTeapot(1);
            break;
        case 3 :
            glutWireCube(1.5);
            break;
        case 4 :
            glutWireSphere(1, 100, 100);
            break;
        case 5 :
            glutWireTeapot(1);
            break;
    }
}

// Draw 3D wire objects
void Draw3D(int SelectedObject, int op_flags[3][4]){

    glViewport(400, -70 ,400,400);
    glLoadIdentity();
    gluLookAt(0,1,6,0,0,0,0,1,0);
    rotate(op_flags[2][0]);
    translate(op_flags[2][1]);
    scale(op_flags[2][2]);
    mirror(op_flags[2][3]);
    drawObject(3,0,SelectedObject);

    glViewport(400, 180 ,400,400);
    glLoadIdentity();
    gluLookAt(0,1,5,0,0,0,0,1,0);
    rotate(op_flags[1][0]);
    translate(op_flags[1][1]);
    scale(op_flags[1][2]);
    mirror(op_flags[1][3]);
    drawObject(4,1,SelectedObject);

    glViewport(400,400,400,400);
    glLoadIdentity();
    gluLookAt(0,1,5,0,0,0,0,1,0);
    rotate(op_flags[0][0]);
    translate(op_flags[0][1]);
    scale(op_flags[0][2]);
    mirror(op_flags[0][3]);
    drawObject(5,1,SelectedObject);
}

// Draw 3D solid objects
void Draw3DSolid(int SelectedObject, int op_flags[3][4]){

    glViewport(400, -70 ,400,400);
    glLoadIdentity();
    gluLookAt(0,1,6,0,0,0,0,1,0);
    rotate(op_flags[2][0]);
    translate(op_flags[2][1]);
    scale(op_flags[2][2]);
    mirror(op_flags[2][3]);
    drawObject(0,0,SelectedObject);

    glViewport(400, 180 ,400,400);
    glLoadIdentity();
    gluLookAt(0,1,5,0,0,0,0,1,0);
    rotate(op_flags[1][0]);
    translate(op_flags[1][1]);
    scale(op_flags[1][2]);
    mirror(op_flags[1][3]);
    drawObject(1,1,SelectedObject);

    glViewport(400,400,400,400);
    glLoadIdentity();
    gluLookAt(0,1,5,0,0,0,0,1,0);
    rotate(op_flags[0][0]);
    translate(op_flags[0][1]);
    scale(op_flags[0][2]);
    mirror(op_flags[0][3]);
    drawObject(2,2,SelectedObject);
}
//Draw 2D components - butttons 
void Draw2D(ButtonList *bl){
    glViewport(0,-95,800,800);
    ButtonDraw(bl);

    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glVertex2f(0.25,210);
    glVertex2f(800,210);
    glEnd();

    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glVertex2f(0.25,470);
    glVertex2f(800,470);
    glEnd();

}



