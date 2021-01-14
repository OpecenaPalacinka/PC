#ifndef _PERSON_H
#define _PERSON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Struktura popisující osobu, její věk a velikost bot.
 */
typedef struct _person {
    char *name;         /**< Jméno osoby (dynamicky alokováno). */
    int age;            /**< Věk osoby. */
    int shoe_size;      /**< Velikost bot osoby. */    
} person;

/**
 * @brief Funkce vytvoří novou osobu.
 * @param name Jméno osoby.
 * @param age Věk osoby.
 * @param shoe_size Velikost bot osoby.
 * @return person* Ukazatel na nově dynamicky alokovanou instanci struktury person.
 */
person *person_create(const char *name, int age, int shoe_size);

/**
 * @brief Funkce pro uvolnění osoby.
 * @param poor Uvolňována osoba.
 */
void person_destroy(void **p);

/**
 * @brief Funkce vytiskne osobu do konzole.
 * @param p Tištěná osoba.
 */
void person_print(person *p);

#endif
