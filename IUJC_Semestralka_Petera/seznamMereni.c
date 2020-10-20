#include "seznamMereni.h"
#include "vlastniFunkce.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

static tSeznamMereni* seznam = NULL;
static float** analyzaMereni = NULL;

int* dejIDPoleSenzoru(int *length) {
    FILE* file = fopen("../data.csv", "r");
    if (file == NULL) {
        printf("Soubor %s nebyl nalezen!\n", "data.csv");
        return NULL;
    }

    int j = 0, pocetID = 0;
    int *poleID = calloc(10, sizeof(int));
    char line[256], *token, **tokenStringy;
    fgets(line, 256, file);
    int pocet = pocetSloupcu(line);
    tokenStringy = calloc(pocet, sizeof(tokenStringy));

    while (fgets(line, 256, file)) {
        int id;
        token = strtok(line, ";");
        for (int i = 0; i < pocet; i++) {
            tokenStringy[i] = token;
            token = strtok(NULL, ";");
        }

        id = atoi(tokenStringy[1]);


        if (jeVPoli(id, poleID, pocetID) == 0) {
            (*length)++;
            poleID[j] = id;
            j++;
            pocetID++;
            //printf("%d\n", id);

        }
    }


    free(tokenStringy);
    fclose(file);
    return poleID;
}

void vypisIDPoleSenzoru(int* pole, int *length) {
    for (int i = 0; i < *length; i++) {
        printf("%d, ", pole[i]);
    }
    puts("");
}

tSeznamMereni* nactiMereni(int idSenzoru) {
    FILE* file = fopen("../data.csv", "r");
    if (file == NULL) {
        printf("Soubor \"%s\" nebyl nalezen!\n", "data.csv");
        return NULL;
    }

    seznam = malloc(sizeof(tSeznamMereni));
    tMereni* mereni;
    tMereni* pom;

    char line[256];
    char pomocnePole[19];
    int cisloID = 0;
    float cisloM3 = 0;
    while(fgets(line, 256, file)) {

        sscanf(line, "%*d;%d;%*19c;%*f", &cisloID);

        if (cisloID == idSenzoru) {

            sscanf(line, "%*d;%*d;%19c;%f", pomocnePole, &cisloM3);
            tDateTime td = dejDateTime(pomocnePole);
            mereni = vytvorMereni(cisloID, td, cisloM3);

            if (seznam->seznam == NULL) {
                seznam->seznam = mereni;
                seznam->idSenzoru = idSenzoru;
                pom = mereni;
            } else {
                pom->dalsi = mereni;
                pom = mereni;
            }

        }

    }

    fclose(file);
    return seznam;
}

tMereni* odeberMereni(tDateTime timestamp) {
    tMereni* mereni = seznam->seznam;

    if (jsouStejne(mereni->timestamp, timestamp) == true) {
        seznam->seznam = mereni->dalsi;
        return mereni;
    }

    while(mereni != NULL) {

        if (jsouStejne(mereni->dalsi->timestamp, timestamp) == true) {
            if (mereni->dalsi->dalsi == NULL) {
                tMereni *pom = mereni->dalsi;
                mereni->dalsi = NULL;
                return pom;
            } else {
                tMereni *pom = mereni->dalsi;
                tMereni *naslednik = mereni->dalsi->dalsi;
                mereni->dalsi = naslednik;
                return pom;
            }

        }

        mereni = mereni->dalsi;
    }

    return NULL;
}

void dealokujSeznam() {
    tMereni* mereni = seznam->seznam;
    while (mereni != NULL) {
        tMereni* pomocne = mereni->dalsi;
        free(mereni);
        mereni = pomocne;
    }

    seznam->seznam = NULL;
    free(seznam);
    seznam = NULL;
}

void vypisNactenaMereni() {
    tMereni* mereni = seznam->seznam;
    while (mereni != NULL) {
        vypisMereni(mereni);
        mereni = mereni->dalsi;
    }
}

void dealokujMatici() {
    for (int i = 0; i < 7; i++) {
        free(analyzaMereni[i]);
        analyzaMereni[i] = NULL;
    }

    free(analyzaMereni);
    analyzaMereni = NULL;
}

float** analyzuj(tDateTime odDoby, tDateTime doDoby) {
    float** poleMereni;
    int** pocetMereni;
    poleMereni = calloc(7, sizeof(float*));
    pocetMereni = calloc(7, sizeof(int*));
    for (int i = 0; i < 7; i++) {
        poleMereni[i] = calloc(24, sizeof(float));
    }
    for (int j = 0; j < 7; j++) {
        pocetMereni[j] = calloc(24, sizeof(int));
    }

    tMereni* mereni = seznam->seznam;

    while(mereni != NULL) {
        if (jeVRozmezi(odDoby, doDoby, mereni->timestamp) == 0) {
            poleMereni[mereni->timestamp.dayInWeek][mereni->timestamp.hour] += mereni->m3;
            pocetMereni[mereni->timestamp.dayInWeek][mereni->timestamp.hour]++;
        }
        mereni = mereni->dalsi;
    }

    for (int k = 0; k < 7; k++) {
        for (int l = 0; l < 24; l++) {
            if (pocetMereni[k][l] != 0) {
                poleMereni[k][l] = poleMereni[k][l] / pocetMereni[k][l];
            }
            //printf("%.4f, ", poleMereni[k][l]);
        }
        //printf("\n");
    }

    for (int m = 0; m < 7; m++) {
        free(pocetMereni[m]);
    }

    analyzaMereni = poleMereni;
    return analyzaMereni;
}

float dejOdchylku(tDateTime timestamp) {
    float hodnotaVMatici;
    hodnotaVMatici = analyzaMereni[timestamp.dayInWeek][timestamp.hour];

    tMereni* mereni = seznam->seznam;

    while(mereni != NULL) {
      if(jsouStejne(timestamp, mereni->timestamp)) {
           printf("Odchylka = %.4f m3", hodnotaVMatici - mereni->m3);
           return hodnotaVMatici - mereni->m3;
       }
       mereni = mereni->dalsi;
    }

    free(mereni);
    return 0;

}

void zapisDoCSV() {
    FILE* file = fopen("analyza.csv", "w");
    fputs("den v tydnu/hodina;0;1;2;3;4;5;6;7;8;9;10;11;12;13;14;15;16;17;18;19;20;21;22;23\n", file);
    char pomocne[10];
    for (int i = 0; i < 7; i++) {
        fprintf(file, "%d", i);

        /*sprintf(pomocne, "%d", i);
        fputs(pomocne, file);*/

        for (int j = 0; j < 24; j++) {
            sprintf(pomocne, ";%.4f", analyzaMereni[i][j]);
            fputs(pomocne, file);
            //fprintf(file, "%.4f;", analyzaMereni[i][j]);
        }
        fputs("\n", file);
    }
}
