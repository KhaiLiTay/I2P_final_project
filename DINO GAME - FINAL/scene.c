//包含遊戲場景（背景、仙人掌、烏鴉等）的相關程式碼，如場景圖像載入、繪製等。
#include "scene.h"
#include "global.h"

ALLEGRO_BITMAP* dino;// 恐龙图像位图指针
ALLEGRO_BITMAP* cactus; // 仙人掌图像位图指针
ALLEGRO_BITMAP* crow;// 烏鴉图像位图指针
ALLEGRO_BITMAP* background;// 背景图像位图指针
ALLEGRO_BITMAP* menu;// 菜单图像位图指针
ALLEGRO_TIMER* timer;// Allegro 定时器指针
ALLEGRO_BITMAP* coin;
ALLEGRO_SAMPLE_INSTANCE* getCoin_SoundInstance = NULL;
ALLEGRO_SAMPLE* getCoin_Sound;
ALLEGRO_TIMER* hitcount;
//初始化coin的參數

float dinoX, dinoY;// 恐龙的坐标位置
float cactusX, cactusY;// 仙人掌的坐标位置
float crowX, crowY;// 烏鴉的坐标位置
float backgroundX; // 背景的 x 坐标位置
float gravity, jump; // 重力和跳跃参数
bool game_over;// 游戏结束标志
float coinX, coinY;
bool coinVisible;//coin的可視狀態

int life;//生命
bool hit;//判定是否撞到障礙物

int life=3;
int score = 0;// 分数
int highScore = 0;// 最高分

bool hit = false;//初始化沒撞

//繪畫物件
void drawGame() {
    // 繪製背景
    al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background),
        backgroundX, 0, al_get_bitmap_width(background), SCREEN_HEIGHT, 0);

    // 繪製背景的副本以實現循環重複
    al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background),
        backgroundX + al_get_bitmap_width(background), 0, al_get_bitmap_width(background), SCREEN_HEIGHT, 0);

    // 繪製恐龍圖像
    al_draw_scaled_bitmap(dino, 0, 0, al_get_bitmap_width(dino), al_get_bitmap_height(dino),
        dinoX, dinoY, DINO_WIDTH, DINO_HEIGHT, 0);

    // 繪製仙人掌圖像
    al_draw_scaled_bitmap(cactus, 0, 0, al_get_bitmap_width(cactus), al_get_bitmap_height(cactus),
        cactusX, cactusY, CACTUS_WIDTH, CACTUS_HEIGHT, 0);
        //font = al_load_ttf_font("pirulen.ttf", 30, 0);
        al_draw_textf(font, al_map_rgb(255, 182, 193), SCREEN_WIDTH - 10, 10, ALLEGRO_ALIGN_RIGHT, "Score: %d", score);

          al_draw_textf(font, al_map_rgb(255, 182, 193), SCREEN_WIDTH - 10, 50, ALLEGRO_ALIGN_RIGHT, "Life: %d", life);

    // 繪製烏鴉圖像
    al_draw_scaled_bitmap(crow, 0, 0, al_get_bitmap_width(crow), al_get_bitmap_height(crow),
        crowX, crowY, CROW_WIDTH, CACTUS_HEIGHT, 0);

    //當可視化==true，繪製coin
    if(coinVisible == true){
        al_draw_scaled_bitmap(coin, 0, 0, al_get_bitmap_width(coin), al_get_bitmap_height(coin),
            coinX, coinY, COIN_WIDTH, CACTUS_HEIGHT, 0);
    }
    // 更新显示
    al_flip_display();
}

void updateGame() {
     // 仙人掌移動速度
    if (score % 5 == 0 && score>0){
    cactusX -= 30;}
    else cactusX -= 10;

    // 當仙人掌超出屏幕時，重置其位置
    if (cactusX + CACTUS_WIDTH < 0) {
        cactusX = SCREEN_WIDTH + rand() % DISTANCE_BETWEEN_OBSTACLES;
        cactusY = SCREEN_HEIGHT - CACTUS_HEIGHT;
    }

    // 烏鴉移動速度
    if (score % 5 == 0 && score>0){
    crowX -= 30;}
    else crowX -= 10;

    // 當烏鴉超出屏幕時，重置其位置並重新設定高度
    if (crowX + CROW_WIDTH < 0) {
        crowX = SCREEN_WIDTH + rand() % DISTANCE_BETWEEN_OBSTACLES;
        CrowHeight crowHeight = getCrowHeight();
        crowY = getCrowY(crowHeight);
    }

    // 背景移動速度
    if (score % 5 == 0 && score>0){
    backgroundX -= 30;}
    else backgroundX -=10;

    // 當背景移出屏幕時，重置其位置
    if (backgroundX <= -al_get_bitmap_width(background)) {
        backgroundX = 0;
    }

    if (cactusX + CACTUS_WIDTH+40< dinoX || crowX + CROW_WIDTH+40 < dinoX) {
        score += 1; // 躲過障礙物就加分
    }

    // 金幣移動速度
     if (score % 5 == 0 && score>0){
    coinX -= 30;}
    else coinX -=10;

    // 當coin超出屏幕時，重置其位置並重新設定高度
        if (coinX + COIN_WIDTH <0 ||coinX + COIN_WIDTH ==0) {
                coinVisible = false;
            coinX = SCREEN_WIDTH + rand() % DISTANCE_BETWEEN_OBSTACLES;
            CoinHeight coinHeight = getCoinHeight();
            coinY = getCoinY(coinHeight);
        }

    //如果角色吃到coin，加分，不可視，等待超出屏幕后重置位置重新繪製
     if (coinX <= dinoX + DINO_WIDTH && coinX + COIN_WIDTH >= dinoX &&
        coinY <= dinoY + DINO_HEIGHT && coinY + COIN_HEIGHT >= dinoY) {
            score++;
            coinVisible = false;
            coinX = SCREEN_WIDTH + rand() % DISTANCE_BETWEEN_OBSTACLES;
            CoinHeight coinHeight = getCoinHeight();
            coinY = getCoinY(coinHeight);
            coinVisible = true;
            }
    if(life == 0) game_over = true; // 生命=0時游戏结束

    //傷害保護，扣命一定時間后不會再受傷避免暴斃
    if(al_get_timer_count(hitcount) == 2){
            al_stop_timer(hitcount);
            al_set_timer_count(hitcount, 0);
            hit = false;
    }
        updateHighScore(score);
    }

//最高分賦值
void updateHighScore(int score) {
    if (score > highScore)
        highScore = score;
}
