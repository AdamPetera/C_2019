#include "seznamMereni.h"
#include <stdio.h>

int main(void) {

    int length = 0;
    int *pole = dejIDPoleSenzoru(&length);

    vypisIDPoleSenzoru(pole, &length);

    nactiMereni(222);

    vypisNactenaMereni();

    analyzuj(dejDateTime("2018-06-01 01:00:00"), dejDateTime("2019-08-27 12:00:00"));

    zapisDoCSV();

    puts("\n/*===========================================================*/\n"
         "/*===========================================================*/\n"
         "/*===========================================================*/\n");

    dejOdchylku(dejDateTime("2019-11-16 03:00:00"));

    puts("");

    odeberMereni(dejDateTime("2019-11-16 10:00:00"));

    puts("");

    vypisNactenaMereni();

    dealokujSeznam();

    dealokujMatici();

    puts("\n/*===========================================================*/\n"
         "/*===========================================================*/\n"
         "/*===========================================================*/\n");

    nactiMereni(1);

    vypisNactenaMereni();

    return 0;
}





