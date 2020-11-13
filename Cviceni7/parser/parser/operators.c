#include "operators.h"

/**
 * @brief Pole dostupných operací a konstanta, která udržuje jejich počet.
 */
const int OPERATORS_COUNT = 4;
const calc_oper OPERATORS[] = {
    { '+', sum },       /* Sčítání. */
    { '-', sub },       /* Odčítání. */
    { '*', mul },       /* Násobení. */
    { '/', divide }     /* Dělení. */
};

fcalc get_handler(char operator) {
    int i;

    for (i = 0; i < OPERATORS_COUNT; ++i) {
        if (OPERATORS[i].operator == operator) {
            return OPERATORS[i].handler;
        }
    }

    return NULL;
}

number sum(number a, number b) {
    return a + b;
}

number sub(number a, number b) {
    return a - b;
}

number mul(number a, number b) {
    return a * b;
}

number divide(number a , number b) {
    return a / b;
}