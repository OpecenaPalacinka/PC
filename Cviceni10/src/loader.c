/**
 * @file loader.c
 * @author František Pártl (fpartl@kiv.zcu.cz)
 * @brief Příklad, na kterém si ukážeme načítání dat ze souborů do automaticky realokovaného pole.
 * @version 1.0
 * @date 2020-12-07
 */

#include <stdio.h>
#include <stdlib.h>

#include "person.h"
#include "vector.h"

/** @brief Používaný znak k oddělování hodnotu v CSV souboru. */
#define CSV_DELIMETER ";"

/** @brief Souboru s načítanými osobami. */
#define PERSON_FILE "../data/persons.csv"

/** @brief Soubor s načítanými integery. */
#define INTEGER_FILE "../data/integers.txt"

/** @brief Velikost načítacího bufferu. */
#define CHAR_BUFFER_SIZE 256

/**
 * @brief Ukázka načítání integerů.
 */
void integer_loader() {
    char line[CHAR_BUFFER_SIZE] = { 0 };
    vector *numbers;
    FILE *file;
    int temp, i;

    file = fopen(INTEGER_FILE, "r");
    if (!file)
        return;

    numbers = vector_create(sizeof(int));
    if (!numbers) {
        fclose(file);
        return;
    }

    while (fgets(line, CHAR_BUFFER_SIZE, file)) {
        temp = atoi(line);
        if (vector_pushback(numbers, &temp) == INVALID_INDEX) {
            vector_destroy(&numbers, NULL);
            fclose(file);
        }
    }

    for (i = 0; i < vector_count(numbers); ++i)
        printf("%d\n", *(int *)vector_at(numbers, i));

    vector_destroy(&numbers, NULL);
    fclose(file);
}

/**
 * @brief Ukázka načítání osob.
 */
void person_loader() {
    char line[CHAR_BUFFER_SIZE] = { 0 }, *name;
    int age, shoe_size, i;
    FILE *file;
    vector *persons;
    person *p;

    file = fopen(PERSON_FILE, "r");
    if (!file)
        return;

    persons = vector_create(sizeof(person *));
    if (!persons) 
        return;

    while (fgets(line, CHAR_BUFFER_SIZE, file)) {
        if (strlen(line) == 0) 
            continue;

        age = atoi(strtok(line, CSV_DELIMETER));
        shoe_size = atoi(strtok(NULL, CSV_DELIMETER));
        name = strtok(NULL, CSV_DELIMETER);
        name[strlen(name) - 1] = '\000';

        p = person_create(name, age, shoe_size);
        if (!p) {
            vector_destroy(&persons, person_destroy);
            fclose(file);
            return;
        }

        vector_pushback(persons, &p);
    }

    for (i = 0; i < vector_count(persons); ++i)
        person_print(*(person **)vector_at(persons, i));

    fclose(file);
    vector_destroy(&persons, person_destroy);
}

/**
 * @brief Hlavní přístupový bod aplikace.
 * @return int Vždy vrací hodnotu EXIT_SUCCESS.
 */
int main() {
    person_loader();
    integer_loader();

    return EXIT_SUCCESS;
}