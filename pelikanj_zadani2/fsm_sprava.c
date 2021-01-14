/**
 * @file fsm_sprava.c
 * @author Jan Pelikán (pelikanj@students.zcu.cz)
 * @brief Soubor funkcí pro generovaný soubor fsm.c -> funkce pro správu vrcholů, hran a vstupního řetězce
 * @version 1.2
 * @date 30.12.2020
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fsmgen.h"

/**
 * @brief Zkontroluje, zda se v grafu nachází startovní vrchol
 * @param vrchol vrcholy grafu
 * @return 1 - obsahuje start, 0 - neobsahuje start (chyba)
 */
int zkouska_grafu(vrchol *vrchol){
    if (!vrchol){
        return 0;
    }
    /* hledání vstupního vrcholu */
    while(vrchol) {
        if(strcmp(vrchol->label,"start") != 0) {
            vrchol = vrchol->dalsi_vrchol;
        }
        else {
            break;
        }
    }
    /* Pokud nenajdu startovní vrchol, vypíšu hlášku */
    if(!vrchol) {
        printf("Node with label \"start\" was not found!\n");
        return 0;
    }
    return 1;
}

/**
 * @brief  Funkce pro zpracování vstupního řetězce, pokud se jedná o validní vstupní řetězec, tak se vykoná, jinak končí chybou
 *
 * @param retezec zadávaný vstupní řetězec
 * @param vrchol Načtené vrcholy
 * @return int 1 - vstupní řetezec je validní, 0 - nepovedlo se rozpoznat vstupní řetězec CHYBA
 */
int zkouska_vstupniho_retezce(char *retezec, vrchol *vrchol) {
    /* Promměné pro FOR cykly */
    int i,j;

    /* kontrola vstupních parametrů */
    if(!retezec || !vrchol) {
        return 0;
    }

    if(zkouska_grafu(vrchol)) {
        /* Projdu přes celou délku vstupního řetězce */
        for (i = 0; i < strlen(retezec); i++) {
            for (j = 0; j < vrchol->pocet_hran_vrcholu; j++) {
                if (vrchol->hrany[j]->label == retezec[i]) {
                    vrchol = vrchol->hrany[j]->dalsi_vrchol;
                    break;
                }
                /* Zkontroluji zda nějaká hrana existuje */
                if (j + 1 == vrchol->pocet_hran_vrcholu) {
                    printf("Wrong input string!\n");
                    return 0;
                }
            }
        }

        /* Kontrola zda konečný vrchol má label end a zda je na konci řetězce*/
        if(strcmp(vrchol->label, "end") == 0 && '\0' == retezec[i]){
            printf("ACCEPTED, your input ended on an \"end\" node, which is \"%s\"!\n", vrchol->jmeno);
            return 1;
        }
        else
        {
            printf("Wrong input string, last node was \"%s\" -> it is not the \"end\" node!\n", vrchol->jmeno);
            return 0;
        }
    }

    return 0;
}

/**
 * @brief Uvolní celou použitou pamět, po všech vrcholech a příslušných hranách
 *
 * @param vrcholy Vrcholy, které chceme mazat
 */
void free_vsechno(vrchol *vrcholy) {
    /* Proměnná pro FOR cyklus*/
    int i;
    /* Použitý pro uchování dalšího vrcholu */
    vrchol *docasnyVrchol;

    /* Není co mazat (kontrola parametrů) */
    if(!vrcholy) {
        return;
    }

    /* procházím vrcholy */
    while(vrcholy) {
        /* pro každý vrchol projdu všechny jeho hrany a uvolním */
        for(i = 0; i < vrcholy->pocet_hran_vrcholu; i++) {
            free(vrcholy->hrany[i]);
        }

        free(vrcholy->hrany);
        docasnyVrchol = vrcholy->dalsi_vrchol;
        free(vrcholy);
        vrcholy = docasnyVrchol;
    }
}