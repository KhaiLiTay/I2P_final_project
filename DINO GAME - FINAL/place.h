#ifndef PLACE_H_INCLUDED
#define PLACE_H_INCLUDED

#include "global.h"
#include "menu.h"

enum PLACE {
    PLACE1,
    PLACE2,
    PLACE3,
    RETURN
};

typedef struct Button2 {
    int x;
    int y;
    int width;
    int height;
    char text[20];
} BUTTON2;


void show_place();
void setup_buttons2();
void choose_place();


#endif // PLACE_H_INCLUDED
