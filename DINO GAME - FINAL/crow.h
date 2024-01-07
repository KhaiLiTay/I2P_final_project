#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include "global.h"

typedef enum {
    LOW,
    MEDIUM,
    HIGH
} CrowHeight;

CrowHeight getCrowHeight();
float getCrowY(CrowHeight height);

typedef enum {
    Low,
    Medium,
    High
} CoinHeight;

CoinHeight getCoinHeight();
float getCoinY(CoinHeight height);

#endif // CHARACTER_H_INCLUDED
