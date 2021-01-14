
/**
 * @file fsm_template.c
 * @author Petr Holický (holickyp@students.zcu.cz)
 * @brief soubor funkcí pro fsm.c
 *        obsahuje funkce pro správu vrcholů, hran, a vstupního řetězce
 * @version 0.1
 * @date 2020-12-04
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fsm.h"

/**
 * @brief vytvoří nový vrchol a zařadí ho do seznamu vrcholů
 * 
 * @param vrchol seznam vrcholů
 * @param name název nového vrcholu
 * @param label label nového vrcholu
 * @return int 1 - proběhlo bezchyb, 0 - funkci se nepodařilo provést správně
 */
int add_node(node **vrchol, char *name, char *label) {
    node *new, *it;

    /* kontrola vstupních parametrů */
    if(!name || !label || !vrchol) {
        return 0;
    }

    new = (node *)malloc(sizeof(node));
    if(!new) {
        /* nepodarila se alokace pameti */
        return 0; 
    }

    new->name = name;;
    new->label = label;
    new->next_node = NULL;
    new->number_of_edges = inital_value;
    new->edges_used = 0;

    new->edges = (edge**)malloc(sizeof(edge*) * inital_value);
    if(!new->edges) {
        /* nepodarila se alokace pameti */
        return 0; 
    }

    if(!*vrchol) {
        *vrchol = new;
    }
    else {
        it = *vrchol;
        while(1) {
            if(it->next_node) {
                it = it->next_node;
            }
            else {
                it->next_node = new;
                break;
            } 
        }
    }

    return 1;
}

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
int add_edge(node **start, char *from_node, char *to_node, char label) {
    edge *new, **temp;
    node *it; 

    /* kontrola vstupních parametrů */
    if(!from_node || !to_node || !label || !*start || !start) {
        return 0;
    }

    new = (edge *)malloc(sizeof(edge));
    if(!new) {
        /* nepodarila se alokace pameti */
        return 0; 
    }

    new->from_node = from_node;
    new->to_node = to_node;
    new->label = label;
    

    /* přířazení vrcholu hraně ve kterém končí */
    it = *start;
    while(it->edges){
        if(!strcmp(it->name,new->to_node)) {
            new->next_node = it;
            break;
        }
        else {
            it = it->next_node;
        }
    }

    /* přiřazení hrany vrcholu ze kterého vychází */
    it = *start;
    while(1){
        if(!strcmp(it->name,new->from_node)) {
            /* pokud jsme presáhly initial_value počet hran, dynamicky zvětšíme pole o dvojnásobek */
            if(it->number_of_edges == it->edges_used) {
                it->number_of_edges = it->number_of_edges*2;
                temp = (edge**)realloc(it->edges, it->number_of_edges * sizeof(*it->edges)); 
                if(!temp) {
                    return 0;
                }
                it->edges = temp;
            }
            it->edges[it->edges_used] = new;
            it->edges_used++;
            break;
        }
        else {
            it = it->next_node;
        }
    }  

    return 1;
}

/**
 * @brief  procházení vstupního řetězce 
 *         pokud je znak možné zpravovat -> pohyb na příslušný vrchol, jinak konec
 * 
 * @param znak  vstupní řetězec
 * @param vrchol prvni načtený vrchol
 * @return int 1 - proběhlo bezchyb, 0 - funkci se nepodařilo provést správně
 */
int process(char *retezec, node *vrchol) {
    size_t i;
    size_t j;
    int chyba = 0;
    int p = -1;

    /* kontrola vstupních parametrů */
    if(!retezec || !vrchol) {
        return 0;
    }

    /* hledání vstupního vrcholu */
    while(vrchol) {
        if(!strcmp(vrchol->label,"start")) {
            break;
        }
        else {
            vrchol = vrchol->next_node;
        }
    }  
    if(!vrchol) {
        printf("Starting node not found!\n");
        return 0;
    }

    /* procházení vstupního retězce, pokud je znak možné zpravovat -> pohyb na příslušný vrchol, jinak konec */
    for(i = 0; i < strlen(retezec); i++) {
        p = -1;
        for(j = 0; j<vrchol->edges_used; j++) {
            if(vrchol->edges[j]->label == retezec[i]) {
                p = j;
            }
        }
        if(p == -1){
            printf("Unacceptable string\n");
            chyba = 1;
            break;
        }
        else {
            vrchol = vrchol->edges[p]->next_node;
        }
    }
    /* řetězec spracován a konečná pozice je na end vrcholu */
    if(!strcmp(vrchol->label,"end") && chyba == 0) {
        printf("Acceptable string, ended on a node %s\n", vrchol->name);
        return 1;
    }
    /* řetězec spracován ale konečná pozice není na end vrcholu */
    else if(strcmp(vrchol->label,"end") && chyba == 0){
        printf("Ended on a non final node %s, unacceptable string\n", vrchol->name);
        return 0;
    }

    return 0;
}

/**
 * @brief uvolní všechny vrcholy a jejich příslušné hrany
 * 
 * @param nodes vrcholy
 */
void free_all(node *nodes) {
    size_t i;
    node *temp;

    if(!nodes) {
        return;
    }

    while(nodes) {
        for(i = 0; i<nodes->edges_used; i++) {
            free(nodes->edges[i]);
        } 
        free(nodes->edges); 
        temp = nodes->next_node;
        free(nodes);
        nodes = temp;
    }
}