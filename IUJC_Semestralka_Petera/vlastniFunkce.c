//
// Created by Adam Petera on 18/12/2019.
//

#include "vlastniFunkce.h"
#include <string.h>

bool jsouStejne(tDateTime zadane, tDateTime tsmereni) {
    if (zadane.year == tsmereni.year && zadane.month == tsmereni.month && zadane.day == tsmereni.day &&
        zadane.hour == tsmereni.hour) {
        return true;
    }
    return false;
}

int jeVPoli(int val, int* arr, int pocet) {
    int i;
    for(i = 0; i < pocet; i++)
    {
        if(arr[i] == val)
            return 1;
    }
    return 0;
}

int pocetSloupcu(char* radek) {
    int pocet = 1;
    int delkaRadku = strlen(radek);
    for (int i = 0; i < delkaRadku; i++) {
        if (radek[i] == ';') {
            pocet++;
        }
    }
    return pocet;
}

int dejCisloDateTimu(tDateTime dt) {
    return (dt.hour) + (dt.day * 24) + (dt.month * 730) + ((dt.year-2000) * 8776);
}

int jeVRozmezi(tDateTime odDoby, tDateTime doDoby, tDateTime mereni) {
    if (dejCisloDateTimu(odDoby) <= dejCisloDateTimu(mereni) && dejCisloDateTimu(mereni) <= dejCisloDateTimu(doDoby)) {
        return 0;
    } else {
        return 1;
    }

}