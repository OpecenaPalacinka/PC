/**
 * @file graph_gen.h
 * @author Jan Pelikán (pelikanj@students.zcu.cz)
 * @brief Hlavičkový soubor s definicí struktur pro implementaci grafu
 * @version 1.3
 * @date 30.12.2020
 */

#ifndef GRAPH_GEN_H
#define GRAPH_GEN_H

/* zakladní počet hran dostupných pro vrcholy */
#define POCATECNI_HRANY 0

/**
 * @brief Struktura pro vrcholy každý vrchol má svůj vlastní název, label, následující vrchol, všechny hrany vycházející z něj a počet hran
 */
typedef struct struct_vrchol {
    char *jmeno;
    char *label;
    int pocet_hran_vrcholu;
    struct struct_vrchol *dalsi_vrchol;
    struct struct_hrana **hrany;
} vrchol;

/**
 * @brief Struktura pro hrany každá hrana má název vrcholu ze kterého vychází, název vrcholu, do kterého vede, label dané hrany a odkaz na další vrchol
 */
typedef struct struct_hrana {
    char *z_vrcholu;
    char *do_vrcholu;
    char label;
    struct struct_vrchol *dalsi_vrchol;
} hrana;

#endif