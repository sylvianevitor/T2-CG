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

static void Font(void *font,char *text,int x,int y){
	glRasterPos2i(x, y);

	while( *text != '\0' ){
		glutBitmapCharacter( font, *text );
		++text;
	}
	return ;
}

static int isbetween(int x, int l, int u){
	if( x >= l && x <= u)
		return 1;
	return 0;
}

void TheButtonCallback(char *label){
	printf("Button %s pressed\n",label);
}

int ButtonClickTest(Button* b,int x,int y){
	if(b && (isbetween(x,b->x,b->x+b->w) && isbetween(y,b->y,b->y+b->h)))
		return 1;
	else
		return 0;
}

void ButtonRestore(ButtonList *bl,int x,int y){
	int i = 0;
	for(i = 0 ; i < bl->size ; i++){
		if(ButtonClickTest(bl->b[i],x,y) && (bl->b[i]->callbackFunction))
			bl->b[i]->callbackFunction(bl->b[i]->label);
		bl->b[i]->pressed = 0;
	}
	return ;
}

void ButtonSetPress(ButtonList *bl,int x,int y, int op_flags[3][4]){
	int i = 0;
	for(i = 0 ; i < bl->size ; i++)
		if(ButtonClickTest(bl->b[i],x,y)){
			bl->b[i]->pressed = 1;
			op_flags[bl->b[i]->id][bl->b[i]->operation] += 1;
			if(bl->b[i]->operation == 3)
				op_flags[bl->b[i]->id][bl->b[i]->operation] %= 2;
			else
				op_flags[bl->b[i]->id][bl->b[i]->operation] %= 5;
		}
	
	return ;
}

void ButtonUnder(ButtonList *bl,int x,int y){
	int i = 0, redraw = 0;
	for(i = 0 ; i < bl->size ; i++){
		redraw = 0;

		if(ButtonClickTest(bl->b[i],x,y) && bl->b[i]->highlighted == 0 ){ //set highlight
				bl->b[i]->highlighted = 1;
				redraw = 1;
		}
		else if( !ButtonClickTest(bl->b[i],x,y)  && bl->b[i]->highlighted == 1 ){
			bl->b[i]->highlighted = 0; //remove highlight
			redraw=1;
		}

		if(redraw){
			printf("Over Button %s %d\n",bl->b[i]->label,i/4);
			glutPostRedisplay();
		}
	}

	return;
}

void ButtonDraw(ButtonList *bl){
	int i, fontx, fonty;
	for(i = 0 ; i < bl->size ; i++){
		if (bl->b[i]->highlighted) 
			glColor3f(0.7f,0.7f,0.8f);
		else 
			glColor3f(0.6f,0.6f,0.6f);

		//button rectangle
		glBegin(GL_QUADS);
			glVertex2i( bl->b[i]->x 		 , bl->b[i]->y      	 );
			glVertex2i( bl->b[i]->x     	 , bl->b[i]->y+bl->b[i]->h );
			glVertex2i( bl->b[i]->x+bl->b[i]->w, bl->b[i]->y+bl->b[i]->h );
			glVertex2i( bl->b[i]->x+bl->b[i]->w, bl->b[i]->y      	 );
		glEnd();

		glLineWidth(3);

		if (bl->b[i]->pressed) 
			glColor3f(0.8f,0.8f,0.8f);
		else 
			glColor3f(0.4f,0.4f,0.4f);

		//button bord
		glBegin(GL_LINE_STRIP);
			glVertex2i( bl->b[i]->x     	 , bl->b[i]->y+bl->b[i]->h );
			glVertex2i( bl->b[i]->x+bl->b[i]->w, bl->b[i]->y+bl->b[i]->h );
			glVertex2i( bl->b[i]->x+bl->b[i]->w, bl->b[i]->y      	 );
		glEnd();

		glLineWidth(1);

		//centralize
		const unsigned char *pointer = (const unsigned char *) bl->b[i]->label;
		fontx = bl->b[i]->x + (bl->b[i]->w - glutBitmapLength(GLUT_BITMAP_HELVETICA_10,pointer)) / 2 ;
		fonty = bl->b[i]->y + (bl->b[i]->h+10)/2;

		glColor3f(1,1,1);
		Font(GLUT_BITMAP_HELVETICA_10,bl->b[i]->label,fontx,fonty);
	}
}

ButtonList *init(){
	glEnable(GL_LIGHT0);

	ButtonList *butl = (ButtonList *)calloc(1,sizeof(ButtonList));
	butl->b = (Button **)realloc(butl->b,sizeof(Button *)*12);
	butl->size = 12;

	butl->b[0] = CreateButton("Rotate",TheButtonCallback,5,5,100,30,0,0);
	butl->b[1] = CreateButton("Translate",TheButtonCallback,5,45,100,30,1,0);
	butl->b[2] = CreateButton("Scale",TheButtonCallback,5,85,100,30,2,0);
	butl->b[3] = CreateButton("Mirror",TheButtonCallback,5,125,100,30,3,0);

	butl->b[4] = CreateButton("Rotate",TheButtonCallback,5,220,100,30,0,1);
	butl->b[5] = CreateButton("Translate",TheButtonCallback,5,260,100,30,1,1);
	butl->b[6] = CreateButton("Scale",TheButtonCallback,5,300,100,30,2,1);
	butl->b[7] = CreateButton("Mirror",TheButtonCallback,5,340,100,30,3,1);

	butl->b[8] = CreateButton("Rotate",TheButtonCallback,5,480,100,30,0,2);
	butl->b[9] = CreateButton("Translate",TheButtonCallback,5,520,100,30,1,2);
	butl->b[10] = CreateButton("Scale",TheButtonCallback,5,560,100,30,2,2);
	butl->b[11] = CreateButton("Mirror",TheButtonCallback,5,600,100,30,3,2);

	return butl;
}

Button *CreateButton(char *label,ButtonCallback func,int x,int y,int w,int h, int op, int id){
	Button *b = (Button *)calloc(1,sizeof(Button));

	b->x = x;
	b->y = y;
	b->w = w;
	b->h = h;
	b->operation = op;
	b->id = id;
	b->callbackFunction = func;
	b->label = (char *)malloc(sizeof(char)*(strlen(label)+1));
	sprintf(b->label,"%s",label);

	return b;
}