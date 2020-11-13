/**
 * @file parser.c
 * @author František Pártl (fpartl@ntis.zcu.cz)
 * @brief Zdrojový kód jednoduchého parseru, který využívá implementovaný zásobník.
 * @version 1.O
 * @date 2020-09-08
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stack.h"
#include "operators.h"

/**
 * @brief Maximální velikost zásobníku a maximální délka vstupu.
 */
#define MAX_INPUT_LEN 128
#define STACK_SIZE 32

/**
 * @brief Funkce slouží k vyhodnocení výrazu zapsaného v reverzní polské notaci (RPL).
 * @param input Zpracovávaný výraz.
 * @param result Ukazatel na paměť, kam bude zkopírován výsledek výrazu.
 * @return int 1, pokud zpracování proběhlo v pořádku, jinak 0.
 */
int evalutate_rpl_expression(const char *input, int *result) {
    stack *s = NULL;
    int i, input_len, a, b, temp;
    fcalc handler;

    if (!input || !result)
        return 0;

    input_len = strlen(input);
    if (input_len == 0)
        return 0;

    s = stack_create(input_len, sizeof(int));
    if (!s)
        return 0;

    for (i = 0; i < input_len; ++i) {
        if (input[i] >= '0' && input[i] <= '9') {
            temp = (int)(input[i] - '0');
            stack_push(s, &temp);
        }
        else if ((handler = get_handler(input[i]))) {
            if (stack_pop(s, &b) && stack_pop(s, &a)) {
                temp = handler(a, b);
                stack_push(s, &temp);
            }
            else {
                stack_free(&s);
                return 0;
            }
        }
        else {
            stack_free(&s);
            return 0;
        }
    }

    if (stack_item_count(s) == 1) {
        stack_pop(s, result);
        stack_free(&s);
        return 1;
    }
    else {
        stack_free(&s);
        return 0;
    }
}

/**
 * @brief Hlavní přístupový bod aplikace pro zpracování postfixových výrazů.
 * @return int Funkce vždy vrací hodnotu EXIT_SUCCESS.
 */
int main() {
    char input[MAX_INPUT_LEN] = { 0 };
    int result;

    while (1) {
        printf("> ");
        fgets(input, MAX_INPUT_LEN, stdin);
        input[strlen(input) - 1] = '\r\n';      /* Odstraním \n z konce řetězce. */

        if (strcmp(input, "quit") == 0) {
            printf("see ya!\n");
            break;
        }

        if (evalutate_rpl_expression(input, &result)) {
            printf("= %d\n", result);
        }
        else printf("syntax error\n");
    }

    return EXIT_SUCCESS;
}