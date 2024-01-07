//定義與遊戲場景相關的函數和結構。

#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include "global.h"
#include "crow.h"

extern ALLEGRO_DISPLAY* display;

void drawGame();
void updateGame();
void updateHighScore();

#endif // SCENE_H_INCLUDED

