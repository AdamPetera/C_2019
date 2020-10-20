#pragma once
#include "datetime.h"
#include "seznamMereni.h"
#include "mereni.h"
typedef struct {
    int idSenzoru;
    tDateTime odDoby;
    tDateTime doDoby;
    tMereni* seznam;
} tSeznamMereni;

int *dejIDPoleSenzoru(int *length);
tSeznamMereni* nactiMereni(int idSenzoru);
void vypisNactenaMereni();
tMereni *odeberMereni(tDateTime timestamp);
void dealokujSeznam();
float** analyzuj(tDateTime odDoby, tDateTime doDoby);
void dealokujMatici();
float dejOdchylku(tDateTime timestamp);
void zapisDoCSV();
void vypisIDPoleSenzoru(int* pole, int *length);