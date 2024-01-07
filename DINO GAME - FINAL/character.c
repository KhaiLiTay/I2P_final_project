#include "global.h"
#include "character.h"
#include "place.h"

//初始化
ALLEGRO_BITMAP* character1Image;
ALLEGRO_BITMAP* character2Image;
ALLEGRO_BITMAP* character3Image;
ALLEGRO_SAMPLE_INSTANCE* characterMusic;

enum CHOICE selectedChoice = CHARACTER1;

const int CHARACTER1_X = 300;
const int CHARACTER2_X = 800;
const int CHARACTER3_X = 1300;
const int CHARACTER_Y = 300;
const int CHARACTER_WIDTH = 400;
const int CHARACTER_HEIGHT = 400;

//初始化
BUTTON character1Button;
BUTTON character2Button;
BUTTON character3Button;
BUTTON backButton;

void show_character() {
    setup_buttons();
    al_clear_to_color(al_map_rgb(0, 0, 0));

    // 加載位圖
    character1Image = al_load_bitmap("qiaopai.png");
    character2Image = al_load_bitmap("sensen.png");
    character3Image = al_load_bitmap("turtle.png");

    // 繪製圖片
    ALLEGRO_BITMAP* character_background = al_load_bitmap("character_background.jpg");
    al_draw_scaled_bitmap(character_background, 0, 0, al_get_bitmap_width(character_background), al_get_bitmap_height(character_background),
        0, 0, al_get_display_width(display), al_get_display_height(display), 0);

    // 繪製字體
    al_draw_text(font, al_map_rgb(255, 0, 255), 1000, 100, ALLEGRO_ALIGN_CENTER, "CHARACTER SELECTION");
    al_draw_text(font, al_map_rgb(128, 0, 128), character1Button.x + character1Button.width / 2, CHARACTER_Y + CHARACTER_HEIGHT + 10, ALLEGRO_ALIGN_CENTER, "QIAOPAI");
    al_draw_text(font, al_map_rgb(128, 0, 128), character2Button.x + character2Button.width / 2, CHARACTER_Y + CHARACTER_HEIGHT + 10, ALLEGRO_ALIGN_CENTER, "SENSEN");
    al_draw_text(font, al_map_rgb(128, 0, 128), character3Button.x + character3Button.width / 2, CHARACTER_Y + CHARACTER_HEIGHT + 10, ALLEGRO_ALIGN_CENTER, "MR.KUN");

    // 繪製按鈕
    al_draw_scaled_bitmap(character1Image, 0, 0, al_get_bitmap_width(character1Image), al_get_bitmap_height(character1Image),
        character1Button.x, CHARACTER_Y, CHARACTER_WIDTH+100, CHARACTER_HEIGHT, 0);

    al_draw_scaled_bitmap(character2Image, 0, 0, al_get_bitmap_width(character2Image), al_get_bitmap_height(character2Image),
        character2Button.x, CHARACTER_Y, CHARACTER_WIDTH, CHARACTER_HEIGHT, 0);

    al_draw_scaled_bitmap(character3Image, 0, 0, al_get_bitmap_width(character3Image), al_get_bitmap_height(character3Image),
        character3Button.x, CHARACTER_Y, CHARACTER_WIDTH, CHARACTER_HEIGHT, 0);

    // 繪製‘return’按鈕
    al_draw_text(font, al_map_rgb(0, 0, 0), backButton.x + backButton.width / 2, backButton.y + (backButton.height - al_get_font_line_height(font)) / 2, ALLEGRO_ALIGN_LEFT, backButton.text);

    ALLEGRO_SAMPLE* backgroundSample = al_load_sample("character.mp3");
    characterMusic = al_create_sample_instance(backgroundSample);
    al_set_sample_instance_playmode(characterMusic, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(characterMusic, al_get_default_mixer());
    al_play_sample_instance(characterMusic); //播放bgm

    // 將前buffer的畫面交換到後臺顯示出來
    al_flip_display();
}

//設置按鈕
void setup_buttons() {
    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    character1Button.x = CHARACTER1_X;
    character1Button.y = CHARACTER_Y;
    character1Button.width = CHARACTER_WIDTH;
    character1Button.height = CHARACTER_HEIGHT;
    strcpy(character1Button.text, "Character 1");

    character2Button.x = CHARACTER2_X;
    character2Button.y = CHARACTER_Y;
    character2Button.width = CHARACTER_WIDTH;
    character2Button.height = CHARACTER_HEIGHT;
    strcpy(character2Button.text, "Character 2");

    character3Button.x = CHARACTER3_X;
    character3Button.y = CHARACTER_Y;
    character3Button.width = CHARACTER_WIDTH;
    character3Button.height = CHARACTER_HEIGHT;
    strcpy(character3Button.text, "Character 3");

    backButton.x = 20;
    backButton.y = 20;
    backButton.width = 60;
    backButton.height = 30;
    strcpy(backButton.text, "Back");

}

//通過鼠標點擊選擇角色
void choose_character() {
    bool running = true;

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            int mouseX = event.mouse.x;
            int mouseY = event.mouse.y;

            if (mouseX >= character1Button.x && mouseX <= character1Button.x + character1Button.width &&
                mouseY >= character1Button.y && mouseY <= character1Button.y + character1Button.height) {
                selectedChoice = CHARACTER1;
                running = false;
            } else if (mouseX >= character2Button.x && mouseX <= character2Button.x + character2Button.width &&
                       mouseY >= character2Button.y && mouseY <= character2Button.y + character2Button.height) {
                selectedChoice = CHARACTER2;
                running = false;
            } else if (mouseX >= character3Button.x && mouseX <= character3Button.x + character3Button.width &&
                       mouseY >= character3Button.y && mouseY <= character3Button.y + character3Button.height) {
                selectedChoice = CHARACTER3;
                running = false;
            } else if (mouseX >= backButton.x && mouseX <= backButton.x + backButton.width &&
                       mouseY >= backButton.y && mouseY <= backButton.y + backButton.height) {
                // 执行返回菜单的操作
                selectedChoice = BACK;
                running = false;
            }
        }
    }


    if (selectedChoice == CHARACTER1) {
        // 执行游戏进行的操作
        dino = al_load_bitmap("qiaopai.png");// 加载牛排巧巧位图
        al_stop_sample_instance(characterMusic);
        show_place();
        choose_place();
    } else if (selectedChoice == CHARACTER2) {
        // 执行游戏进行的操作
        dino = al_load_bitmap("sensen.png");// 加载森森位图
        al_stop_sample_instance(characterMusic);
        show_place();
        choose_place();
    } else if (selectedChoice == CHARACTER3) {
        // 执行遊戲進行的操作
        dino = al_load_bitmap("turtle.png");// 加載昆明龜位图
        al_stop_sample_instance(characterMusic);
        show_place();
        choose_place();
    }
    //選擇角色後選擇遊戲場景
    else if (selectedChoice == BACK){
        al_stop_sample_instance(characterMusic);
        returnToMenu(); //返回menu
    }
}

void returnToCharacter()
{
    show_character();
    choose_character();
}
//返回選取角色




