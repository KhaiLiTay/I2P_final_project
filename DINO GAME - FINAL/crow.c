#include <stdlib.h>
#include "crow.h"

CrowHeight getCrowHeight() {
    int random = rand() % 3;// 生成0到2之间的随机数，赋值给random变量
    if (random == 0) { // 如果random等于0
        return LOW;// 返回枚举值LOW
    }
    else if (random == 1) {// 如果random等于1
        return MEDIUM;// 返回枚举值MEDIUM
    }
    else {
        return HIGH;// 其他情况返回枚举值HIGH
    }
}

float getCrowY(CrowHeight height) {
    switch (height) {// 根据参数height的值进行分支判断
    case LOW:// 如果height的值是LOW
        return SCREEN_HEIGHT - CACTUS_HEIGHT;
    case MEDIUM:
        return SCREEN_HEIGHT - DINO_HEIGHT / 2 - CROW_WIDTH - 50;
    case HIGH:
        return SCREEN_HEIGHT - DINO_HEIGHT - CROW_WIDTH - 100;
    default:
        return 0;
    }
}

CoinHeight getCoinHeight() {
    int random = rand() % 3;// 生成0到2之间的随机数，赋值给random变量
    if (random == 0) { // 如果random等于0
        return LOW;// 返回枚举值LOW
    }
    else if (random == 1) {// 如果random等于1
        return MEDIUM;// 返回枚举值MEDIUM
    }
    else {
        return HIGH;// 其他情况返回枚举值HIGH
    }
}

float getCoinY(CoinHeight height) {
    switch (height) {// 根据参数height的值进行分支判断
    case LOW:// 如果height的值是LOW
        return SCREEN_HEIGHT - CACTUS_HEIGHT;
    case MEDIUM:
        return SCREEN_HEIGHT - DINO_HEIGHT / 2 - CROW_WIDTH - 50;
    case HIGH:
        return SCREEN_HEIGHT - DINO_HEIGHT - CROW_WIDTH - 100;
    default:
        return 0;
    }
}
