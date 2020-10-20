#include "mereni.h"
#include "datetime.h"
#include <stdlib.h>
#include <stdio.h>

tMereni* vytvorMereni(int idMereni, tDateTime ts, float m3) {
    tMereni* mereni = malloc(sizeof(tMereni));
    mereni->idMereni = idMereni;
    mereni->m3 = m3;
    mereni->timestamp = ts;
    mereni->dalsi = NULL;

    return mereni;
}

void vypisMereni(tMereni* mereni) {
    if (mereni == NULL) {
        printf("Zadne mereni k vypsani");
        return;
    }
    printf("ID: %d, Vody: %.4f, TimeStamp: %d-%d-%d %d:%d:%d, Den: %d\n", mereni->idMereni, mereni->m3, mereni->timestamp.year,
            mereni->timestamp.month, mereni->timestamp.day, mereni->timestamp.hour, mereni->timestamp.min,
            mereni->timestamp.sec, mereni->timestamp.dayInWeek);
}