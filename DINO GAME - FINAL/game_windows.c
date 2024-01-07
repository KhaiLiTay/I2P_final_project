#include "game_windows.h"
#include "global.h"
#include "place.h"
#include "crow.h"

//初始化
ALLEGRO_FONT* font; // 字体指针变量
ALLEGRO_SAMPLE *sample;   // 音频样本指针变量
ALLEGRO_SAMPLE_INSTANCE *startSound;// 音频样本实例指针变量
ALLEGRO_BITMAP *frame = NULL;   // 位图指针变量
ALLEGRO_SAMPLE_INSTANCE* newBackgroundMusic;
ALLEGRO_SAMPLE* newBackgroundSample;
ALLEGRO_SAMPLE_INSTANCE* GameOverMusic;

ALLEGRO_SAMPLE* pressSound;
ALLEGRO_SAMPLE_INSTANCE* pressQ;

bool invincible = false; // 无敌模式状态
double invincibleTimer = 0.0; // 无敌模式计时器
double invincibleDuration = 3.0; // 无敌模式持续时间

void game_play(){
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(2);

    al_set_sample_instance_playmode(newBackgroundMusic, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(newBackgroundMusic, al_get_default_mixer());
    al_play_sample_instance(newBackgroundMusic);
    al_init_image_addon();// 初始化图像附加库
    al_install_keyboard();// 安装键盘
    coin = al_load_bitmap("coin.png");

    dinoX = 50; // 设置恐龙的初始X坐标
    dinoY = SCREEN_HEIGHT - DINO_HEIGHT;// 设置恐龙的初始Y坐标
    cactusX = SCREEN_WIDTH + rand() % DISTANCE_BETWEEN_OBSTACLES;// 设置仙人掌的初始X坐标
    cactusY = SCREEN_HEIGHT - CACTUS_HEIGHT; // 设置仙人掌的初始Y坐标
    crowX = SCREEN_WIDTH + DISTANCE_BETWEEN_OBSTACLES + rand() % DISTANCE_BETWEEN_OBSTACLES;// 设置乌鸦的初始X坐标
    CrowHeight crowHeight = getCrowHeight(); // 调用函数获取乌鸦的高度
    crowY = getCrowY(crowHeight);// 根据乌鸦的高度获取乌鸦的Y坐标
    backgroundX = 0; // 设置背景的初始X坐标
    gravity = 0.5; // 设置重力
    jump = 0;// 设置跳跃力度为0
    game_over = false;// 设置游戏结束状态为false

    coinX = SCREEN_WIDTH + DISTANCE_BETWEEN_OBSTACLES + rand() % DISTANCE_BETWEEN_OBSTACLES;// 设置乌鸦的初始X坐标
    CoinHeight coinHeight = getCoinHeight(); // 调用函数获取乌鸦的高度
    coinY = getCoinY(coinHeight);// 根据乌鸦的高度获取乌鸦的Y坐标
     hitcount = al_create_timer(1.0);//

     //彩蛋音效
    ALLEGRO_SAMPLE* pressSound = al_load_sample("baby-talk-so-cute.mp3");
    ALLEGRO_SAMPLE_INSTANCE* pressQ = al_create_sample_instance(pressSound);
    al_attach_sample_instance_to_mixer(pressQ, al_get_default_mixer());
    al_set_sample_instance_playmode(pressQ, ALLEGRO_PLAYMODE_ONCE);

    timer = al_create_timer(1.0 / 60);//用于控制游戏的帧率
    event_queue = al_create_event_queue();//事件队列用于存储各种输入事件，例如键盘按键、鼠标移动、定时器触发等
    al_register_event_source(event_queue, al_get_timer_event_source(timer));//将定时器事件源注册到事件队列中。这样，当定时器触发时，相应的事件将被添加到事件队列中，以便后续处理。
    al_register_event_source(event_queue, al_get_keyboard_event_source());//将键盘事件源注册到事件队列中。这样，当用户按下键盘上的键时，相应的键盘事件将被添加到事件队列中，以便后续处理。

    al_start_timer(timer);//启动定时器。这会导致定时器以指定的频率触发定时器事件，并将其添加到事件队列中。

    srand(time(NULL));//生成伪随机数

    while (!game_over) {
        ALLEGRO_EVENT ev;// 创建事件变量
        al_wait_for_event(event_queue, &ev);// 等待事件的发生并将其存储在ev中

        if (ev.type == ALLEGRO_EVENT_TIMER) {// 如果是定时器事件
            updateGame();// 更新游戏状态
            drawGame();// 绘制游戏画面
        }
         if (ev.type == ALLEGRO_EVENT_KEY_CHAR) { // 如果是键盘字符事件
            if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {// 如果按下的是空格键
                if (dinoY == SCREEN_HEIGHT - DINO_HEIGHT) {
                    jump = 26; // 調整跳躍的力度
                }
            }
        }


          if(ev.keyboard.keycode == ALLEGRO_KEY_Q){ //觸發彩蛋
                    al_play_sample_instance(pressQ);
            }

        if (dinoY <= SCREEN_HEIGHT - DINO_HEIGHT) {// 如果恐龙没有触底
            dinoY -= jump;// 更新恐龙的垂直位置
            jump -= gravity; // 根据重力更新跳跃力度
        }
        else {
            dinoY = SCREEN_HEIGHT - DINO_HEIGHT;// 恐龙触底时将其位置重置为地面高度
            jump = 0;// 清零跳跃力度
        }

        if(hit == false){
        if (cactusX <= dinoX + DINO_WIDTH && cactusX + CACTUS_WIDTH >= dinoX && cactusY <= dinoY + DINO_HEIGHT && cactusY + CACTUS_HEIGHT >= dinoY) {
        if (score % 5 == 0 && score>0) {
            invincible = true; // 进入无敌模式
            invincibleTimer = al_get_time(); // 重置无敌模式计时器
        }
        else {
            if (!invincible) {
                life --;
            hit = true;
            al_start_timer(hitcount);}
            if (life<0){
                game_over = true; // 如果恐龙与仙人掌碰撞且不处于无敌模式，则游戏结束
                }
            }
        }



    if (crowX <= dinoX + DINO_WIDTH && crowX + CROW_WIDTH >= dinoX && crowY <= dinoY + DINO_HEIGHT && crowY + CACTUS_HEIGHT >= dinoY) {
        if (score % 5 == 0 && score>0) {
            invincible = true; // 进入无敌模式
            invincibleTimer = al_get_time(); // 重置无敌模式计时器
        }
        else {
            if (!invincible) {
                    life--;
                    hit = true;
                    al_start_timer(hitcount);}
                    if (life<0){
                game_over = true;
                }// 如果恐龙与乌鸦碰撞且不处于无敌模式，则游戏结束
            }
        }}


    if (invincible) {
        double currentTime = al_get_time();
        if (currentTime - invincibleTimer >= 3.0) { // 无敌模式持续3秒
            invincible = false; // 无敌模式结束
        }
    }
}
//初始化遊戲設定

    al_stop_sample_instance(newBackgroundMusic);
    game_over1();

    al_destroy_bitmap(dino);
    al_destroy_bitmap(cactus);
    al_destroy_bitmap(crow);
    al_destroy_bitmap(background);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
}

void game_over1() {
    ALLEGRO_BITMAP* backgroundphoto = al_load_bitmap("END.png");
    al_clear_to_color(al_map_rgb(0, 0, 0));
    int originalWidth = al_get_bitmap_width(backgroundphoto);
    int originalHeight = al_get_bitmap_height(backgroundphoto);
    al_draw_scaled_bitmap(backgroundphoto, 0, 0, originalWidth, originalHeight, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    al_draw_text(font, al_map_rgb(255, 0, 0), SCREEN_WIDTH - 10, 0, ALLEGRO_ALIGN_RIGHT, "Game Over");
    al_draw_textf(font, al_map_rgb(255, 0, 0), SCREEN_WIDTH - 10, 40, ALLEGRO_ALIGN_RIGHT, "Score: %d", score);
    al_draw_textf(font, al_map_rgb(255, 0, 0), SCREEN_WIDTH - 10, 80, ALLEGRO_ALIGN_RIGHT, "HighestScore: %d", highScore);

    ALLEGRO_SAMPLE* backgroundSample = al_load_sample("end.mp3");
    GameOverMusic = al_create_sample_instance(backgroundSample);
    al_set_sample_instance_playmode(GameOverMusic, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(GameOverMusic, al_get_default_mixer());
    al_play_sample_instance(GameOverMusic);

    al_flip_display();
    al_rest(4.0);  //等待四秒
    al_stop_sample_instance(GameOverMusic);
    returnToMenu();  // 返回菜單
}
//gameover的狀態

void game_destroy() {//销毁
    al_destroy_display(display);
    al_destroy_font(font);
    al_destroy_bitmap(background);
    al_destroy_sample_instance(startSound);
    al_destroy_sample(sample);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}

