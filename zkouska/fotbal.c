#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fotbal.h"

#define MAX_INPUT_LENGTH 25

void umazPismeno (char *str, char odstran) {
    char *src, *dst;

    for (src = dst = str; *src != '\0'; src++){
        *dst = *src;
        if (*dst != odstran) dst++;
    }
    *dst = '\0';

}

void kontrolaSlova (char *vstup,char *slovo){
    unsigned long iterSlova,iterVstupu;
    char *vstupik = vstup;
    iterSlova = 0;
    iterVstupu = 0;
    while (42){
        if (vstup[iterVstupu] == slovo[iterSlova]){
            iterSlova++;
            iterVstupu = 0;
            if (iterSlova == strlen(slovo)){
                printf("%s\n",slovo);
                break;
            }
        } else {
            iterVstupu++;
        }
        if (iterVstupu > strlen(vstup)){
            break;
        }

    }
}

int load_word(slova **existujiciSlova,char *exactSlovo,char *vstup){
    slova *slovo;
    slova *slovoProIteraci = NULL;

    if (!existujiciSlova || !exactSlovo) {
        return 0;
    }

    slovo = (slova *) malloc(sizeof (slova));

    if (!slovo) {
        return 0;
    }

    strtok(exactSlovo,"\n");

    slovo->slovo = exactSlovo;
    slovo->dalsi_slovo = NULL;

    if (*existujiciSlova){
        slovoProIteraci = *existujiciSlova;
        while (42) {
            if (!slovoProIteraci->dalsi_slovo){
                slovoProIteraci->dalsi_slovo = slovo;
                break;
            } else {
                slovoProIteraci = slovoProIteraci->dalsi_slovo;
            }
        }
    } else {
        *existujiciSlova = slovo;
    }

    kontrolaSlova(vstup,exactSlovo);

    return 1;
}

void uvolni(slova *slovaa){
    /* Použitý pro uchování dalšího vrcholu */
    slova *docasne = NULL;

    if(!slovaa) {
        return;
    }

    while(slovaa) {
        docasne = slovaa->dalsi_slovo;
        free(slovaa);
        slovaa = docasne;
    }
}


void kontrola(slova *seznamSlov,char *vstup){
    unsigned long iterSlova,iterVstupu;

    while (42) {
        iterSlova = 0;
        iterVstupu = 0;
        while (42){
            if (vstup[iterVstupu] == seznamSlov->slovo[iterSlova]){
                iterVstupu = 0;
                iterSlova++;
                if (iterSlova == strlen(seznamSlov->slovo)){
                    printf("%s",seznamSlov->slovo);
                }
            }
            if (iterVstupu > strlen(vstup)+1){
                seznamSlov = seznamSlov->dalsi_slovo;
                break;
            }
            iterVstupu++;
        }

        if (!seznamSlov->dalsi_slovo){
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *file;
    slova *slova = NULL;
    char buffer[MAX_INPUT_LENGTH];


    if (argc < 3){
        printf("Use - slovnik.txt \'input chars\'");
    }
    if (argc > 3){
        printf("Use - slovnik.txt \'input chars\'");
    }

    file = fopen(argv[1],"r");

    if (!file) {
        printf("Cannot open input file!");
        return EXIT_FAILURE;
    }

    while (fgets(buffer,MAX_INPUT_LENGTH,file)){
        load_word(&slova,buffer,argv[2]);

    }

    /*kontrola(slova,vstup);*/

    uvolni(slova);
    fclose(file);
    return EXIT_SUCCESS;
}

