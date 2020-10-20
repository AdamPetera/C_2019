//
// Created by Adam Petera on 18/12/2019.
//

#include <stdbool.h>
#include "datetime.h"

int jeVPoli(int val, int *arr, int pocet);
int pocetSloupcu(char* radek);
bool jsouStejne(tDateTime zadane, tDateTime tsmereni);
int dejCisloDateTimu(tDateTime dt);
int jeVRozmezi(tDateTime odDoby, tDateTime doDoby, tDateTime mereni);