#ifndef _BUTTON_H_
#define _BUTTON_H_

typedef void (*ButtonCallback)(char *);
typedef struct Button Button;
struct Button {
	char *label;						//button name
	int x, y;							//button position (coordinate)
	int w, h;							//button width and height
	int pressed, highlighted;			//interface flags
	int operation, id;					//button info
	ButtonCallback callbackFunction;	//pointer to call function when pressed
};

typedef struct ButtonList ButtonList;
struct ButtonList{
	Button **b;
	int size;
};

void TheButtonCallback(char *);

int ButtonClickTest(Button* ,int ,int );

void TheButtonCallback(char *);

void ButtonRestore(ButtonList *,int ,int );

void ButtonSetPress(ButtonList *,int ,int , int [3][4]);

void ButtonUnder(ButtonList *,int ,int );

void ButtonDraw(ButtonList *);

ButtonList *init();

Button *CreateButton(char *,ButtonCallback ,int ,int ,int ,int ,int ,int );

#endif
