/**
 * @file fsm.h
 * @author Petr Holický (holickyp@students.zcu.cz)
 * @brief Hlavičkový soubor s deklaracemi funkcí pracujících s vrcholy a hranami
 * @version 0.1
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef FSM_H
#define FSM_H

#include <stdlib.h>
#include <stdio.h>

/* zakladní počet hran dostupných pro vrcholy */
#define inital_value 1

/**
 * @brief Definice seznamu vrcholů
 *        každý vrchol obsahuje svůj název, label, všechny hrany vycházející z něj, počet kolik hran můžeme přiřadit a kolich jich doopravdy má
 * 
 */
typedef struct _struct_node {
    char *name;
    char *label;
    struct _struct_node *next_node;
    struct _struct_edge **edges;
    unsigned int number_of_edges;
    unsigned int edges_used;
} node;

/**
 * @brief Definice hrany
 *        každá hrana obsahuje název ze kterého vrcholu vychází, v jakém končí a odkaz na něj, a label hrany
 * 
 */
typedef struct _struct_edge {
    char *from_node;
    char *to_node;
    char label;
    struct _struct_node *next_node;
} edge;

/**
 * @brief vytvoří nový vrchol a zařadí ho do seznamu vrcholů
 * 
 * @param vrchol seznam vrcholů
 * @param name název nového vrcholu
 * @param label label nového vrcholu
 * @return int 1 - proběhlo bezchyb, 0 - funkci se nepodařilo provést správně
 */
int add_node(node **start, char name[], char label[]);


/**
 * @brief vytvoří novou hranu, hranu přidá vrcholu ze kterého vychází
 *        hrana odkazuje na vrchol ve kterém končí
 * 
 * @param start seznam vrcholů
 * @param from_node vychází z vrcholu
 * @param to_node končí ve vrcholu
 * @param label label hrany
 * @return int 1 - proběhlo bezchyb, 0 - funkci se nepodařilo provést správně
 */
int add_edge(node **start, char from_node[], char to_node[], char label);


/**
 * @brief  procházení vstupního řetězce 
 *         pokud je znak možné zpravovat -> pohyb na příslušný vrchol, jinak konec
 * 
 * @param znak  vstupní řetězec
 * @param vrchol prvni načtený vrchol
 * @return int 1 - proběhlo bezchyb, 0 - funkci se nepodařilo provést správně
 */
int process(char znak[], node *vrchol);


/**
 * @brief uvolní všechny vrcholy a jejich příslušné hrany
 * 
 * @param nodes vrcholy
 */
void free_all(node *nodes);

#endif