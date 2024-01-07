#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include "global.h"
#include "menu.h"

enum CHOICE {
    CHARACTER1,
    CHARACTER2,
    CHARACTER3,
    BACK
};

typedef struct Button_ {
    int x;
    int y;
    int width;
    int height;
    char text[20];
} BUTTON;

void Initialize();
void show_character();
void choose_character();
void returnToCharacter();

#endif // CHARACTER_H_INCLUDED
