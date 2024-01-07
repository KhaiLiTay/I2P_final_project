#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 2000
#define SCREEN_HEIGHT 1000
#define DINO_WIDTH 250
#define DINO_HEIGHT 250
#define CACTUS_WIDTH 250
#define CACTUS_HEIGHT 250
#define CROW_WIDTH 200
#define COIN_HEIGHT 150
#define COIN_WIDTH 150
#define WIDTH 2000
#define HEIGHT 1000
#define MENU_WIDTH 2000
#define MENU_HEIGHT 1000
#define DISTANCE_BETWEEN_OBSTACLES 1000 // 增加距離

extern ALLEGRO_DISPLAY* display;
extern ALLEGRO_FONT* font;
extern ALLEGRO_BITMAP* background;
extern ALLEGRO_BITMAP* dino;
extern ALLEGRO_BITMAP* cactus;
extern ALLEGRO_BITMAP* crow;
extern ALLEGRO_BITMAP* coin;
extern ALLEGRO_BITMAP* menu;
extern ALLEGRO_TIMER* timer;
extern ALLEGRO_EVENT_QUEUE* event_queue;
extern ALLEGRO_SAMPLE *sample;
extern ALLEGRO_SAMPLE_INSTANCE *startSound;
extern ALLEGRO_BITMAP *frame;
extern ALLEGRO_SAMPLE* newBackgroundSample;
extern ALLEGRO_SAMPLE_INSTANCE* newBackgroundMusic;

extern int life;
extern bool hit;
extern ALLEGRO_TIMER* hitcount;
extern ALLEGRO_SAMPLE *pressSound;
extern ALLEGRO_SAMPLE_INSTANCE *pressQ;

extern float dinoX, dinoY;
extern float cactusX, cactusY;
extern float crowX, crowY;
extern float coinX, coinY;
extern bool coinVisible;
extern float backgroundX;
extern float gravity, jump;
extern bool game_over;
extern int score;
extern int highScore;
extern bool judge_next_window;

extern enum Character selectedCharacter;
extern enum GameState currentState;

//聲明各種需要的參數

#endif // GLOBAL_H_INCLUDED


