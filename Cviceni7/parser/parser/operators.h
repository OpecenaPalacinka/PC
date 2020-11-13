/**
 * @file operators.h
 * @author František Pártl (fpartl@kiv.zcu.cz)
 * @version 1.0
 * @date 2020-09-18
 */

#ifndef OPERATORS_H
#define OPERATORS_H

#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Definice datového typu, se kterým funkce pracují. Pokud chcete vidět, jak se toto dělá
 *        lépe a radostněji, tak přijďte na předposlední cvičení.
 */
typedef int number;

/**
 * @brief Definice datového typu ukazatele na funkci vykonávající aritmetickou operaci.
 */
typedef number(*fcalc)(number, number);

/**
 * @brief Struktura, která obaluje operátor a k němu přidruženou obslužnou funkci.
 */
typedef struct _calc_oper {
    char operator;              /** Znak, kterým je operace popsána. */
    fcalc handler;              /** Přidružená aritmetická operace. */
} calc_oper;

/**
 * @brief Funkce vrátí ukazatel na obslužnou funkci podle zadaného operátoru. Operátory a k nim
 *        přidružené funkce musejí být uvedeny v poli OPERATORS, které je definováno v souboru .c.
 * 
 * @param operator Operátor, ke kterému je hledána jeho obslužná funkce.
 * @return fcalc Ukazatel na oblužnou funkci, nebo konstanta NULL pokud operátor nebyl nalezen v poli OPERATORS.
 */
fcalc get_handler(char operator);

/* Odtud začínají deklarace funkcí, které vykonávají aritmetické operace. */
/**
 * @brief Funkce vrátí součet zadaných parametrů.
 * @param a Sčítanec.
 * @param b Sčítanec.
 * @return number Součet.
 */
number sum(number a, number b);

/**
 * @brief Funkce vrátí rozdíl zadaných parametrů.
 * @param a Menšenec.
 * @param b Menšenec.
 * @return number Rozdíl.
 */
number sub(number a, number b);

/**
 * @brief Funkce vrátí součin zadaných parametrů. 
 * @param a Činitel.
 * @param b Činitel.
 * @return number Součin.
 */
number mul(number a, number b);

/**
 * @brief Funkce vrátí podíl zadaných parametrů.
 * @param a Dělenec.
 * @param b Dělitel.
 * @return number Podíl.
 */
number divide(number a , number b);

#endif