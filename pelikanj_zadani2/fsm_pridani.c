/**
 * @file fsm_pridani.c
 * @author Jan Pelikán (pelikanj@students.zcu.cz)
 * @brief Soubor funkcí pro generovaný soubor fsm.c -> funkce pro přidávání hran a vrcholů
 * @version 1.2
 * @date 30.12.2020
 */

#include <stdlib.h>
#include <string.h>

#define ODPOVED_NA_OTAZKU_ZIVOTA_VESMIRU_A_VUBEC 42

/**
 * @brief Funkce vytvoří nový vrchol a následně ho zařadí do seznamu vrcholů
 *
 * @param pVrchol již přidané vrcholy
 * @param jmeno jméno pro nový vrchol
 * @param label label nového vrcholu
 * @return int 1 = vrchol přidán, 0 = nepodařilo se vykonat správně
 */
int pridej_vrchol(vrchol **pVrchol, char *jmeno, char *label) {
    vrchol *pridavany_vrchol;
    vrchol *pocatecni_vrchol;

    /* kontrola vstupních parametrů */
    if(!pVrchol || !jmeno || !label) {
        return 0;
    }

    pridavany_vrchol = (vrchol *)malloc(sizeof(vrchol));

    /* Podařilo se alokovat pamět? */
    if(!pridavany_vrchol) {
        return 0;
    }

    /* Nastavím hodnoty nového vrcholu */
    pridavany_vrchol->jmeno = jmeno;
    pridavany_vrchol->label = label;
    pridavany_vrchol->dalsi_vrchol = NULL;
    pridavany_vrchol->pocet_hran_vrcholu = POCATECNI_HRANY;

    pridavany_vrchol->hrany = (hrana**)malloc(sizeof(hrana*) * POCATECNI_HRANY);

    /* Podařilo se alokovat pamět? */
    if(!pridavany_vrchol->hrany) {
        return 0;
    }

    /* Už mám nějaké vrcholy */
    if(*pVrchol) {
        pocatecni_vrchol = *pVrchol;
        /* Nekonečný cyklus */
        while(ODPOVED_NA_OTAZKU_ZIVOTA_VESMIRU_A_VUBEC) {
            /* Pokud nemám další vrchol, nastavím další vrchol na přidávaný vrchol a končím, jinak se posunu na další vrchol */
            if(!pocatecni_vrchol->dalsi_vrchol) {
                pocatecni_vrchol->dalsi_vrchol = pridavany_vrchol;
                break;
            }
            else {
                pocatecni_vrchol = pocatecni_vrchol->dalsi_vrchol;
            }
        }
    }
    else
    {
        /* Pokud je prázdný přidám první (nový) vrchol*/
        *pVrchol = pridavany_vrchol;
    }

    return 1;
}

/**
 * @brief Funkce vytvoří novou hranu kterou přidá k vrcholu ze kterého vychází
 *        hrana odkazuje na vrchol ve kterém končí
 *
 * @param start seznam (startovní) vrcholů
 * @param z_vrchol počáteční vrchol
 * @param do_vrchol konečný vrchol
 * @param label label (název) hrany
 * @return int 1 - hrana přidána, 0 - nepodařilo se vykonat správně
 */
int pridej_hranu(vrchol **start, char *z_vrcholu, char *do_vrcholu, char label) {
    hrana *nova_hrana;
    /* Používaný vrchol */
    vrchol *pocatecni_vrchol;
    /* Počet hran daného vrcholu, aktualizuju v každém whilu*/
    int pocet_hran;

    /* kontrola vstupních parametrů */
    if(!*start || !z_vrcholu || !do_vrcholu || !label) {
        return 0;
    }

    nova_hrana = (hrana *)malloc(sizeof(hrana));

    /* Podařilo se alokovat pamět? */
    if(!nova_hrana) {
        return 0;
    }

    /* Nastavím údaje o hraně */
    nova_hrana->z_vrcholu = z_vrcholu;
    nova_hrana->do_vrcholu = do_vrcholu;
    nova_hrana->label = label;

    pocatecni_vrchol = *start;
    while(ODPOVED_NA_OTAZKU_ZIVOTA_VESMIRU_A_VUBEC){
        /* Hledám jméno vrcholu, ze kterého hrana vychází*/
        if(strcmp(pocatecni_vrchol->jmeno,nova_hrana->z_vrcholu) != 0) {
            /* Posouvám se na další vrchol*/
            pocatecni_vrchol = pocatecni_vrchol->dalsi_vrchol;
        }
        else
        {
            /* Nastavím počet hran a pocet hran vrcholu, poté zvětším počet hran vrcholu, abychom mohl přidat novou hranu*/
            pocet_hran = pocatecni_vrchol->pocet_hran_vrcholu;
            pocatecni_vrchol->pocet_hran_vrcholu++;
            pocatecni_vrchol->hrany = (hrana**)realloc(pocatecni_vrchol->hrany, pocatecni_vrchol->pocet_hran_vrcholu * sizeof(pocatecni_vrchol->hrany));
            /* Povedla se realokace paměti? */
            if(!pocatecni_vrchol->hrany) {
                return 0;
            }
            /* Pole se indexuje od 0, proto můžu použít "pocatecni_vrchol->pocet_hran_vrcholu" */
            pocatecni_vrchol->hrany[pocet_hran] = nova_hrana;
            break;
        }
    }

    /* Přiřadím hraně vrchol */
    pocatecni_vrchol = *start;
    while(pocatecni_vrchol->hrany){
        /* Pokud se jméno vrcholu schoduje s jménem vrcholu do kterého vede hrana, tak dalsi_vrchol hrany je pocatecni_vrchol*/
        if(strcmp(pocatecni_vrchol->jmeno,nova_hrana->do_vrcholu) != 0) {
            pocatecni_vrchol = pocatecni_vrchol->dalsi_vrchol;
        }
        else
        {
            nova_hrana->dalsi_vrchol = pocatecni_vrchol;
            break;
        }
    }

    return 1;
}