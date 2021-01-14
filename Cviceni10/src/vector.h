#ifndef _VECTOR_H
#define _VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** @brief Násobitel zvětšení pole při realokaci. */
#define VECTOR_SIZE_MULT 2

/** @brief Počáteční velikost vektoru. */
#define VECTOR_INIT_SIZE 4

/** @brief Nevalidní index. */
#define INVALID_INDEX -1

/**
 * @brief Definice ukazatele na obecnou funkci, která umí uvolnit prvek uložený v vektor.
 *        Využívá se ve funkci vector_destroy a vector_at_destroy.
 */
typedef void (*vector_item_destroyer)(void **item);

/**
 * @brief Struktura _vector
 * Přestavuje obecné dynamicky alokované pole, do které lze přidávat prvky, manipulovat s nimi a
 * odstraňovat je (včetně jejich uvolnění).
 */
typedef struct _vector {
    void *data;         /* Ukazatel na data vektoru*/
    unsigned long count; /* Reálný počet prvků ve vektoru*/
    unsigned long item_size; /* Velikost prvku vektoru v Bytech */
    unsigned long capacity; /* Aktuální kapacita vektoru*/
} vector;

/**
 * @brief Alokuje na haldě prázdný vektor s kapacitou VECTOR_INIT_SIZE.
 * @param item_size Velikost jednoho prvku vektoru.
 * @return vector* Ukazatel na alokovaný vektor.
 */
vector *vector_create(unsigned long item_size);

/**
 * @brief Uvolní vektor z paměti a v případě zadání ukazatele na funkci,
 *        která umí uvolnit prvek seznamu se uvolní i prvky.
 * @param v Ukazatel na vektor.
 * @param destroyer Ukazatel na funkci, která umí uvolnit prvek seznamu.
 */
void vector_destroy(vector **v, vector_item_destroyer destroyer);

/**
 * @brief Realokuje zadaný vektor tak, aby jeho kapacita byla size.
 * @param v Realokovaný vektor.
 * @param size Nová kapacita vektoru. 
 * @return int Nová kapacita vektoru pokud realokace proběhla v pořádku, jinak 0.
 */
int vector_realloc(vector *v, unsigned long size);

/**
 * @brief Vrací prvek vektoru dané prvním parametrem podle indexu daným druhým parametrem.
 *        V případě neexistence prvku vratí NULL.
 * 
 * @param v Ukazatel na vektor.
 * @param at Index ve vektoru.
 * @return void* Prvek vektoru nebo NULL při neexitenci prvku.
 */
void *vector_at(vector *v, unsigned long at);

/**
 * @brief Přidá prvek do vektoru. Vrací index, kam byl prvek v vektor uložen
 *        nebo INVALID_INDEX v případě chyby.
 * @param v Ukazatel na vektor, kam se prvke přidává.
 * @param item Ukazatel na prvek k přidání.
 * @return int Index, kam byl prvek do vektoru zapsán nebo UNDEFINED při chybě.
 */
int vector_pushback(vector *v, void *item);

/**
 * @brief Říká, zda je zadaný vektor prázdný nebo obsahuje nějaké prvky.
 * @param v Ukazatel na vektor.
 * @return int 1, pokud je vektor prázdný, jinak 0.
 */
int vector_isempty(vector *v);

/**
 * @brief Vrátí počet prvků vektoru.
 * @param v Ukazatel na vektor.
 * @return int Počet zapsaných prvků ve vektoru.
 */
int vector_count(vector *v);

#endif