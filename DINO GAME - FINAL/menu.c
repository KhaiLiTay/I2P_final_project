//包含與遊戲選單相關的程式碼，包括遊戲開始、關於和退出按鈕的處理函數。
//game_init()，main.c會呼叫
//game_begin()，main.c會呼叫
#include "menu.h"
#include "global.h"
#include "character.h"
#include "place.h"
#include "window.h"

Button startButton, aboutButton, exitButton; //设定按键
enum GameState currentState = MENU;  //设定游戏状态
ALLEGRO_SAMPLE_INSTANCE* CountDownMusic; //倒计时音乐
extern ALLEGRO_SAMPLE_INSTANCE* windowMusic;

//游戏开始前倒数
void CountDown() {
    int countdown = 3;
    ALLEGRO_BITMAP* backgroundphoto = al_load_bitmap("countdown.png");
    int originalWidth = al_get_bitmap_width(backgroundphoto);
    int originalHeight = al_get_bitmap_height(backgroundphoto);

    while (countdown > 0) {
        al_clear_to_color(al_map_rgb(0, 0, 0));

        al_draw_scaled_bitmap(backgroundphoto, 0, 0, originalWidth, originalHeight, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

        ALLEGRO_SAMPLE* backgroundSample = al_load_sample("countdown.WAV");
        CountDownMusic = al_create_sample_instance(backgroundSample);
        al_set_sample_instance_playmode(CountDownMusic, ALLEGRO_PLAYMODE_LOOP);
        al_attach_sample_instance_to_mixer(CountDownMusic, al_get_default_mixer());
        al_play_sample_instance(CountDownMusic);

        al_draw_textf(font, al_map_rgb(0, 0, 0), WIDTH / 2, HEIGHT / 2 - al_get_font_line_height(font) / 2 - 80, ALLEGRO_ALIGN_CENTER, "%d", countdown);
        al_flip_display();
        al_rest(1.0);
        countdown--;
        al_stop_sample_instance(CountDownMusic);
}
//用al_rest来实现等三秒
    // 在程式結束前，釋放資源
    al_destroy_bitmap(backgroundphoto);
}

//初始化游戲
void game_init() {
    //初始化 Allegro 库
    al_init();
    // 安装键盘
    al_install_keyboard();
    //安装鼠标
    al_install_mouse();
    // 初始化字体插件
    al_init_font_addon();
    // 初始化 TTF 插件
    al_init_ttf_addon();
    // 初始化图像插件
    al_init_image_addon();
    // 初始化基本图元插件
    al_init_primitives_addon();

    al_set_window_position(display, 0, 0);// 设置窗口位置

    // 设置开始按钮的位置和文本
    startButton.x = WIDTH / 1.2 - 50;
    startButton.y = HEIGHT / 2 - 50;
    startButton.width = 100;
    startButton.height = 30;
    strcpy(startButton.text, "Start");

    // 设置关于按钮的位置和文本
    aboutButton.x = WIDTH / 1.2 - 50;
    aboutButton.y = HEIGHT / 2 + 10;
    aboutButton.width = 100;
    aboutButton.height = 30;
    strcpy(aboutButton.text, "About");

    // 设置退出按钮的位置和文本
    exitButton.x = WIDTH / 1.2 - 50;
    exitButton.y = HEIGHT / 2 + 70;
    exitButton.width = 100;
    exitButton.height = 30;
    strcpy(exitButton.text, "Exit");

    font = al_load_ttf_font("pirulen.ttf", 40, 0);// 加载字体
    menu = al_load_bitmap("menu.png");// 加载菜单图片
    event_queue = al_create_event_queue(); // 创建事件队列
}

//開始游戲的基本邏輯
void game_begin() {
    ALLEGRO_EVENT_QUEUE* eventQueue = al_create_event_queue();// 创建事件队列
    al_register_event_source(eventQueue, al_get_display_event_source(display));// 注册显示器事件源
    al_register_event_source(eventQueue, al_get_mouse_event_source());// 注册鼠标事件源
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(2); //設定兩個位置保留給音頻
    ALLEGRO_SAMPLE* backgroundSample = al_load_sample("mixkit-feeling-happy-5.mp3");
    ALLEGRO_SAMPLE_INSTANCE* backgroundMusic = al_create_sample_instance(backgroundSample);
    al_set_sample_instance_playmode(backgroundMusic, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(backgroundMusic, al_get_default_mixer());
    al_play_sample_instance(backgroundMusic);
    //設定bgm

    while (1) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(eventQueue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { // 如果关闭显示窗口事件发生
            break;}
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {// 如果鼠标按钮抬起事件发生
            int mouseX = ev.mouse.x;
            int mouseY = ev.mouse.y;

            if (currentState == MENU) {
                     sample = al_load_sample("background_music.wav");
                 // 如果鼠标点击在开始按钮上

                if (mouseX >= startButton.x && mouseX <= startButton.x + startButton.width &&
                    mouseY >= startButton.y && mouseY <= startButton.y + startButton.height) {
                    currentState = GAMEPLAY;// 切换到游戏进行状态
                }
                 // 如果鼠标点击在关于按钮上
                else if (mouseX >= aboutButton.x && mouseX <= aboutButton.x + aboutButton.width &&
                    mouseY >= aboutButton.y && mouseY <= aboutButton.y + aboutButton.height) {
                    currentState = ABOUT; // 切换到关于状态
                }
                // 如果鼠标点击在退出按钮上
                else if (mouseX >= exitButton.x && mouseX <= exitButton.x + exitButton.width &&
                    mouseY >= exitButton.y && mouseY <= exitButton.y + exitButton.height) {
                    break;// 退出程序
                }
            }
            else if (currentState == ABOUT || currentState == GAMEPLAY) {
                // 如果鼠标点击在退出按钮上
                if (mouseX >= exitButton.x && mouseX <= exitButton.x + exitButton.width &&
                    mouseY >= exitButton.y && mouseY <= exitButton.y + exitButton.height) {
                    currentState = MENU; // 切换到菜单状态
                }
            }
            startSound = al_create_sample_instance(sample);// 创建声音实例
            al_set_sample_instance_playmode(startSound, ALLEGRO_PLAYMODE_LOOP);// 设置声音实例的播放模式

            // 将声音实例附加到默认混音器
           al_attach_sample_instance_to_mixer(startSound, al_get_default_mixer());

            // 播放背景音乐
          al_play_sample_instance(startSound);
          al_rest(1.0);// 暂停 1 秒钟

          // 停止播放背景音乐
          al_stop_sample_instance(startSound);
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));// 清空屏幕为黑色

        if (currentState == MENU) {// 如果当前状态为菜单状态
            // 绘制菜单背景图
            al_draw_scaled_bitmap(menu, 0, 0, al_get_bitmap_width(menu), al_get_bitmap_height(menu), 0, 0, MENU_WIDTH, MENU_HEIGHT, 0);
            // 绘制标题文本
            al_draw_text(font, al_map_rgb(128, 0, 128), WIDTH / 1.2, HEIGHT / 2 - al_get_font_line_height(font) / 2 - 100, ALLEGRO_ALIGN_CENTER, "Menu");
            // 绘制开始按钮
            al_draw_filled_rectangle(startButton.x, startButton.y, startButton.x + startButton.width, startButton.y + startButton.height, al_map_rgb(255, 255, 255));
            al_draw_text(font, al_map_rgb(0, 0, 0), startButton.x + startButton.width / 2, startButton.y + (startButton.height - al_get_font_line_height(font)) / 2 -10, ALLEGRO_ALIGN_CENTER, startButton.text);
            // 绘制关于按钮
            al_draw_filled_rectangle(aboutButton.x, aboutButton.y, aboutButton.x + aboutButton.width, aboutButton.y + aboutButton.height, al_map_rgb(255, 255, 255));
            al_draw_text(font, al_map_rgb(0, 0, 0), aboutButton.x + aboutButton.width / 2, aboutButton.y + (aboutButton.height - al_get_font_line_height(font)) / 2 -10, ALLEGRO_ALIGN_CENTER, aboutButton.text);
            // 绘制退出按钮
            al_draw_filled_rectangle(exitButton.x, exitButton.y, exitButton.x + exitButton.width, exitButton.y + exitButton.height, al_map_rgb(255, 255, 255));
            al_draw_text(font, al_map_rgb(0, 0, 0), exitButton.x + exitButton.width / 2, exitButton.y + (exitButton.height - al_get_font_line_height(font)) / 2 -10, ALLEGRO_ALIGN_CENTER, exitButton.text);
        }
        else if (currentState == ABOUT) { // 如果当前状态为关于状态
             // 绘制菜单背景图
            al_draw_scaled_bitmap(menu, 0, 0, al_get_bitmap_width(menu), al_get_bitmap_height(menu), 0, 0, MENU_WIDTH, MENU_HEIGHT, 0);
            // 绘制标题文本
            al_draw_text(font, al_map_rgb(255, 0, 0), WIDTH / 1.2, HEIGHT / 2 - al_get_font_line_height(font) / 2 - 100, ALLEGRO_ALIGN_CENTER, "About");
            al_draw_text(font, al_map_rgb(128, 0, 128), WIDTH/1.2 , HEIGHT /2 - al_get_font_line_height(font) / 2 - 40, ALLEGRO_ALIGN_CENTER, "Let Me PASS!!!!!");
            // 绘制退出按钮
            al_draw_filled_rectangle(exitButton.x, exitButton.y, exitButton.x + exitButton.width, exitButton.y + exitButton.height, al_map_rgb(255, 255, 255));
            al_draw_text(font, al_map_rgb(0, 0, 0), exitButton.x + exitButton.width / 2, exitButton.y + (exitButton.height - al_get_font_line_height(font)) / 2, ALLEGRO_ALIGN_CENTER, exitButton.text);
        }
        else if (currentState == GAMEPLAY) {// 如果当前状态为游戏进行状态
        al_stop_sample_instance(backgroundMusic);

        show_character();//帶去character.c
        choose_character();//帶去character.c
        }
        al_flip_display();// 將前buffer的畫面交換到後臺顯示出來
    }
    al_destroy_event_queue(eventQueue);// 销毁声音实例
}

void returnToMenu() {
    // 重新初始化遊戲相關變數
    score=0;
    life =3;
    hit = false;
    // 切換到菜單狀態
    currentState = MENU;
    game_begin(currentState);
}
//character.c和game_windows.c會呼叫
