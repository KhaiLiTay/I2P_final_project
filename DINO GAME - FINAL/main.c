//主程式
#include "global.h"

int main(int argc, char* argv[]) {
    show_window();
    game_init();
    game_begin();
    game_destroy();
    return 0;
}
//game_init()，带去menu.c
//game_begin();，带去menu.c
//game_destroy();
