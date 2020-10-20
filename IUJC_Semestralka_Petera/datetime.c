//
// Created by Adam Petera on 02/12/2019.
//

#include "datetime.h"
#include <string.h>
#include <stdio.h>

int dejDenVTydnu(int r, int m, int d) {
    int pomocna = 0;
    int cislo = 0;
    int den = 0;
    if (r == 18) {
        cislo += (r+1);
    } else {
        cislo += r;
    }
    if (r%4 == 0) {
        cislo += r/4;
    } else {
        pomocna = r%4;
        cislo += pomocna;
    }

    switch (m) {
        case 1:
        case 10:
            cislo += 6;
            break;
        case 2:
        case 3:
        case 11:
            cislo += 2;
            break;
        case 4:
        case 7:
            cislo += 5;
            break;
        case 5:
            cislo += 0;
            break;
        case 6:
            cislo += 3;
            break;
        case 8:
            cislo += 1;
            break;
        case 9:
        case 12:
            cislo += 4;
            break;
    }

    cislo += d;
    den = (cislo%7);
    return den;
}

tDateTime dejDateTime(char* datetime) {
    tDateTime date;
    sscanf(datetime, "%d-%d-%d %d:%d:%d", &date.year, &date.month, &date.day, &date.hour, &date.min, &date.sec);
    int denVTydnu = dejDenVTydnu(date.year - 2000, date.month, date.day);
    date.dayInWeek = denVTydnu;
    /*printf("%d\n", date.year);
    printf("%d\n", date.month);
    printf("%d\n", date.day);
    printf("%d\n", date.hour);
    printf("%d\n", date.min);
    printf("%d\n", date.sec);
    printf("%d\n", date.dayInWeek);*/

    return date;

}