#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "global.h"

typedef struct Button {
    int x, y, width, height;
    char text[20];
} Button;

//Button startButton, aboutButton, exitButton;

enum GameState {
    MENU,
    ABOUT,
    GAMEPLAY,
};

//enum GameState currentState = MENU;

void game_init();
void game_begin();
void CountDown();
void returnToMenu();


#endif // MENU_H_INCLUDED
