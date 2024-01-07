#include "global.h"
#include "place.h"
#include "character.h"
#include "game_windows.h"

ALLEGRO_BITMAP* place1Image;
ALLEGRO_BITMAP* place2Image;
ALLEGRO_BITMAP* place3Image;
ALLEGRO_SAMPLE_INSTANCE* placeMusic;
//初始化素材

enum PLACE selectedPlace = PLACE1;

//初始化參數
const int PLACE1_X = 150;
const int PLACE2_X = 750;
const int PLACE3_X = 1350;
const int PLACE_Y = 300;
const int PLACE_WIDTH = 500;
const int PLACE_HEIGHT = 300;

//初始化選項按鈕
BUTTON2 place1Button;
BUTTON2 place2Button;
BUTTON2 place3Button;
BUTTON2 backButton2;

void show_place() {
    setup_buttons2();
    al_clear_to_color(al_map_rgb(0, 0, 0));

    // 賦值選項圖片
    place1Image = al_load_bitmap("desert.png");
    place2Image = al_load_bitmap("city.jpg");
    place3Image = al_load_bitmap("sea.png");

    // 繪製背景圖
    ALLEGRO_BITMAP* place_background = al_load_bitmap("place_background.jpg");
    al_draw_scaled_bitmap(place_background, 0, 0, al_get_bitmap_width(place_background), al_get_bitmap_height(place_background),
        0, 0, al_get_display_width(display), al_get_display_height(display), 0);

    //繪製按鈕文組
    al_draw_text(font, al_map_rgb(135, 206, 250), 1000, 100, ALLEGRO_ALIGN_CENTER, "PLACE SELECTION");
    al_draw_text(font, al_map_rgb(255, 165, 0), place1Button.x + place1Button.width / 2, PLACE_Y + PLACE_HEIGHT + 10, ALLEGRO_ALIGN_CENTER, "DESERT");
    al_draw_text(font, al_map_rgb(255, 165, 0), place2Button.x + place2Button.width / 2, PLACE_Y + PLACE_HEIGHT + 10, ALLEGRO_ALIGN_CENTER, "CITY");
    al_draw_text(font, al_map_rgb(255, 165, 0), place3Button.x + place3Button.width / 2, PLACE_Y + PLACE_HEIGHT + 10, ALLEGRO_ALIGN_CENTER, "SEA");

    // 繪製場景選項圖
    al_draw_scaled_bitmap(place1Image, 0, 0, al_get_bitmap_width(place1Image), al_get_bitmap_height(place1Image),
        place1Button.x, PLACE_Y, PLACE_WIDTH, PLACE_HEIGHT, 0);

    al_draw_scaled_bitmap(place2Image, 0, 0, al_get_bitmap_width(place2Image), al_get_bitmap_height(place2Image),
        place2Button.x, PLACE_Y, PLACE_WIDTH, PLACE_HEIGHT, 0);

    al_draw_scaled_bitmap(place3Image, 0, 0, al_get_bitmap_width(place3Image), al_get_bitmap_height(place3Image),
        place3Button.x, PLACE_Y, PLACE_WIDTH, PLACE_HEIGHT, 0);

    // 繪製'back'按鈕
    al_draw_text(font, al_map_rgb(255, 255, 255), backButton2.x + backButton2.width / 2, backButton2.y + (backButton2.height - al_get_font_line_height(font)) / 2, ALLEGRO_ALIGN_LEFT, backButton2.text);

    //背景音效
    ALLEGRO_SAMPLE* backgroundSample = al_load_sample("place.mp3");
    placeMusic = al_create_sample_instance(backgroundSample);
    al_set_sample_instance_playmode(placeMusic, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(placeMusic, al_get_default_mixer());
    al_play_sample_instance(placeMusic);

    // 將前buffer的畫面交換到後臺顯示出來
    al_flip_display();
}


void setup_buttons2() {
    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    place1Button.x = PLACE1_X;
    place1Button.y = PLACE_Y;
    place1Button.width = PLACE_WIDTH;
    place1Button.height = PLACE_HEIGHT;
    strcpy(place1Button.text, "place 1");

    place2Button.x = PLACE2_X;
    place2Button.y = PLACE_Y;
    place2Button.width = PLACE_WIDTH;
    place2Button.height = PLACE_HEIGHT;
    strcpy(place2Button.text, "place 2");

    place3Button.x = PLACE3_X;
    place3Button.y = PLACE_Y;
    place3Button.width = PLACE_WIDTH;
    place3Button.height = PLACE_HEIGHT;
    strcpy(place3Button.text, "place 3");

    backButton2.x = 20;
    backButton2.y = 20;
    backButton2.width = 60;
    backButton2.height = 30;
    strcpy(backButton2.text, "Back");

}

void choose_place() {
    bool running = true;

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            int mouseX = event.mouse.x;
            int mouseY = event.mouse.y;

            if (mouseX >= place1Button.x && mouseX <= place1Button.x + place1Button.width &&
                mouseY >= place1Button.y && mouseY <= place1Button.y + place1Button.height) {
                selectedPlace = PLACE1;
                running = false;
            } else if (mouseX >= place2Button.x && mouseX <= place2Button.x + place2Button.width &&
                       mouseY >= place2Button.y && mouseY <= place2Button.y + place2Button.height) {
                selectedPlace = PLACE2;
                running = false;
            } else if (mouseX >= place3Button.x && mouseX <= place3Button.x + place3Button.width &&
                       mouseY >= place3Button.y && mouseY <= place3Button.y + place3Button.height) {
                selectedPlace = PLACE3;
                running = false;
            } else if (mouseX >= backButton2.x && mouseX <= backButton2.x + backButton2.width &&
                       mouseY >= backButton2.y && mouseY <= backButton2.y + backButton2.height) {
                // 执行返回菜单的操作
                selectedPlace = RETURN;
                running = false;
            }
        }
    }


    if (selectedPlace == PLACE1) {
        // 执行游戏进行的操作
        background = al_load_bitmap("desert_1.jpg");// 加载沙漠位图
        cactus = al_load_bitmap("cactus.png");// 加载仙人掌位图
        crow = al_load_bitmap("crow.png");// 加载乌鸦位图
        al_stop_sample_instance(placeMusic);
        newBackgroundSample = al_load_sample("mixkit-comical-2.mp3"); //加載背景音樂
        newBackgroundMusic = al_create_sample_instance(newBackgroundSample);
        CountDown(); //倒數
        game_play(); //遊戲開始
    } else if (selectedPlace == PLACE2) {
        // 执行游戏进行的操作
        background = al_load_bitmap("city_1.jpg");// 加载城市位图
        cactus = al_load_bitmap("car.png");// 加载汽車位图
        crow = al_load_bitmap("plane.png");// 加载飛機位图
        al_stop_sample_instance(placeMusic);
        newBackgroundSample = al_load_sample("city.mp3"); //加載背景音樂
        newBackgroundMusic = al_create_sample_instance(newBackgroundSample);
        CountDown(); //倒數
        game_play(); //遊戲開始
    } else if (selectedPlace == PLACE3) {
        // 执行倒计时的操作
        background = al_load_bitmap("sea_1.jpg");// 加载海洋位图
        cactus = al_load_bitmap("grass.png");// 加载海草位图
        crow = al_load_bitmap("fish.png");// 加载魚魚位图
        al_stop_sample_instance(placeMusic);
        newBackgroundSample = al_load_sample("sea.mp3"); //加載背景音樂
        newBackgroundMusic = al_create_sample_instance(newBackgroundSample);
        CountDown(); //倒數
        game_play(); //遊戲開始
    }
    //點'return'回菜單
    else if (selectedPlace == RETURN){
        al_stop_sample_instance(placeMusic);
        returnToCharacter();
    }
}


