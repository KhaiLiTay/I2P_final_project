#include "global.h"
#include "window.h"
#include "menu.h"

const int WINDOW_WIDTH = SCREEN_WIDTH;
const int WINDOW_HEIGHT = SCREEN_HEIGHT;
ALLEGRO_SAMPLE_INSTANCE* windowMusic;
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_DISPLAY* display;
ALLEGRO_BITMAP* window_background;  // 添加這行宣告

void show_window() {
    // 初始化 Allegro 库
    al_init();
    // 安装键盘
    al_install_keyboard();
    // 安装鼠标
    al_install_mouse();
    // 初始化字体插件
    al_init_font_addon();
    // 初始化 TTF 插件
    al_init_ttf_addon();
    // 初始化图像插件
    al_init_image_addon();
    // 初始化基本图元插件
    al_init_primitives_addon();

    event_queue = al_create_event_queue();

    display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
      al_set_window_position(display, 0, 0);// 设置窗口位置

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_clear_to_color(al_map_rgb(100, 100, 100));

    window_background = al_load_bitmap("window_background.png");
   al_draw_scaled_bitmap(window_background, 0, 0, al_get_bitmap_width(window_background), al_get_bitmap_height(window_background),
                      0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    al_flip_display();
    al_rest(1);
}
