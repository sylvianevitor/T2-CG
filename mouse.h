#ifndef _MOUSE_H_
#define _MOUSE_H_

typedef struct Mouse Mouse;
struct Mouse {
    int x, y;      //mouse position (coordinate)

    //booleans 1 - pressed, 0 - not pressed
    int lb;    // left mouse button
    int rb;    //right button 
};

#endif
