/**
 * @file bubble_sort.c
 * @author František Pártl (fpartl@kiv.zcu.cz)
 * @brief Prefabrikát pro implementaci algoritmu bubble sort.
 * @version 1.0
 * @date 2020-09-24
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>		/* Potřebuju něco čím budu seedovat generátor náhodných čísel. */

/**
 * @brief Počet prvků pole, které bude generováno a následně řazeno bubble sortem.
 */
#define ARR_LEN 20

/**
 * @brief Styl výpisu vygenerovaných položek generovaných polí čísel.
 */
#define PRINT_STYLE "[%02d] %12d\n"

/**
 * @brief Tohle jenom na ukázku na konec. Kdyby třeba řadící algoritmy implementovali jako
 *        samostatnou knihovnu -> homework.
 */
typedef enum _sort_order_t {
	ASCENDING = 0,	/** Vzestupné pořadí. */
	DESCENDING = 1	/** Sestupné pořadí. */
} sort_order_t;

/**
 * @brief Funkce provede výpis zadaného pole s daným popiskem. Výpis prvků pole se řídí stylem PRINT_STYLE.
 * @param label Popisek pole.
 * @param array Ukazatel na prvky pole.
 * @param array_size Počet prvků pole.
 */
void print_array(const char *label, const int array[], const unsigned int array_size) {
	unsigned int i;

	if (!label || !array || array_size ==0){
		return;
	}

	printf("%s\n",label);

	for (i = 0; i < array_size; ++i){
		printf("[%02d] %12d\n", i, array[i]);
	}
}

/**
 * @brief Funkce naplní zadané pole array_size náhodnými čísly z intervalu <0, RAND_MAX>.
 * @param array Pole, která bude plněno náhodnými hodnotami.
 * @param array_size Počet generovaných náhodných čísel.
 */
void generate_array(int array[], const unsigned int array_size) {
	unsigned int i;

	if(!array || array_size == 0){
		return;
	}
	srand(time(NULL));

	for (i = 0; i < array_size; ++i){
		array[i] = rand();
	}
}

/**
 * @brief Funkce seřadí zadané pole pomocí algoritmu bubble sort.
 * @param array Pole čísel, které bude řazeno.
 * @param array_size Počet prvků pole.
 * @param order 
 */
void bubble_sort(int array[], const unsigned int array_size, sort_order_t order) {
	unsigned int swapped, i, end;
	int temp;

	if(!array || array_size == 0){
		return;
	}

	end = 0;

	do {
		swapped = 0;

		for(i = 0;i < array_size - end;++i){
			if((order == DESCENDING && array[i] < array[i + 1]) || (order == ASCENDING && array[i] > array[i + 1])){
				temp = array[i];
				array[i] = array[i+1];
				array[i+1] = temp;

				swapped = 1;
			}
		}
		end++;
	} while (swapped);
	
	
}

/**
 * @brief Hlavní přístpový bod aplikace, který vygeneruje ARR_LEN celých kladných čísel. Tato čísla budou
 *        následně seřazena algoritmem bublinkového řazení.
 * @return int Funkce vždy vrací hodnotu EXIT_SUCCESS.
 */
int main() {
	int array[ARR_LEN] = { 0 };	/* Pole čísel. */

	/* Vygeneruje pole náhodných prvků. */
	generate_array(array, ARR_LEN);
	print_array("Vygenerované prvky", array, ARR_LEN);

	/* Seřadím jej pomocí algoritmu bubble sort. */
	bubble_sort(array, ARR_LEN, DESCENDING);
	print_array("Seřazené prvky", array, ARR_LEN);

	return EXIT_SUCCESS;
}
