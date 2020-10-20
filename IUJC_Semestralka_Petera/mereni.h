#pragma once
#include "datetime.h"

typedef struct mereni{
    int idMereni;
    tDateTime timestamp;
    float m3;
    struct mereni* dalsi;
} tMereni;

tMereni* vytvorMereni(int idMereni, tDateTime ts, float m3);
void vypisMereni (tMereni* mereni);