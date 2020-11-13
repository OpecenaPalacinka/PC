/**
 * @file stack.h
 * @author František Pártl (fpartl@kiv.zcu.cz)
 * @brief Hlavičkový soubor s deklaracemi funkcí pracujících se zásobníkovou strukturou.
 * @version 1.0
 * @date 2020-09-08
 */

#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Definice neznaménkového typu, abychom se neupsali k smrti. */
typedef unsigned int uns_int;

/**
 * @brief Definice zásobníkové struktury s možností vložení libovolně velkého prvku.
 */
typedef struct _struct {
    uns_int size;  /** Počet prvků zásobníku */
    uns_int  item_size;     /** Velikost prvku */
    void *items;   /** Ukazatel na prvky zásobníku */
    int  sp; /** Index prvku v poli items, který je vrcholem zásobníku*/

} stack;

/**
 * @brief Funkce pro vytvoření nového zásobníku.
 * @param size Maximální počet položek zásobníku.
 * @param item_size Velikost jednoho prvku zásobníku.
 * @return stack* Ukazatel na nově dynamicky alokovaný zásobník nebo NULL při chybě.
 */
stack *stack_create(uns_int size, uns_int item_size);

/**
 * @brief Funkce pro vložení nového prvku na vrchol zásobníku.
 * @param s Zásobník, do kterého bude vložen nový záznam.
 * @param item Vkládaný záznam.
 * @return int 1 pokud vše dopadlo dobře, jinak 0.
 */
int stack_push(stack *s, void *item);

/**
 * @brief Funkce pro odebrání prvku z vrcholu zásobníku.
 * @param s Zásobník, ze kterého bude prvek odebrán.
 * @param item Ukazatel na paměť, kam bude odebraný prvek zkopírován.
 * @return int 1, pokud vše dopadlo dobře, jinak 0.
 */
int stack_pop(stack *s, void *item);

/**
 * @brief Funkce pro získání prvku z vrcholu zásobníku.
 * @param s Zásobník, jehož poslední přidaný prvek pozorujeme.
 * @param item Ukazatel na paměť, kam se přečtený prvek zkopíruje.
 * @return int 1, pokud všech dopadlo dobře, jinak 0.
 */
int stack_head(stack *s, void *item);

/**
 * @brief Funkce vrátí počet prvků v zásobníku.
 * @param s Ukazatel na zásobník.
 * @return uint Počet prvků v zásobníku.
 */
uns_int stack_item_count(stack *s);

/**
 * @brief Funkce pro uvolnění zásobníkové struktury z paměti.
 * @param ss Ukazatel na ukazatel na zásobník, který bude uvolněn.
 */
void stack_free(stack **s);

#endif