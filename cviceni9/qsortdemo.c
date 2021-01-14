/**
 * @file qsortdemo.c
 * @author František Pártl (fpartl@kiv.zcu.cz)
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>

/* 
	Takhle to vychází mně:
		a) Implementace funkce swap v tomto souboru									? s
		b) Impelemntace funkce swap v assembleru									? s
		c) Impelementace funkce swap v tomto souboru s -O3							? s

	Měření byla samozřejmě prováděna bez výpisu s NUMBER_COUNT 214748364.
*/

/** @brief Počet generovaných čísel, která budou následně řazena algoritmem Quicksort. */
#define NUMBER_COUNT 10 /* 250000000 */

/** @brief Při deklaraci tohoto symbolu bude proveden výpis dat před a po jejich seřazení. */
#define PRINT_INFO

/**
 * @brief Vytvoří dynamicky alokované pole, které naplní size náhodně generovanými celými
 *        čísly ...otázka: Proč je zde použita dynamická alokace paměti, když počet prvků 
 *        v tomto případě známe už při překladu programu?
 * @param size Počet náhodných prvků generovaného pole.
 * @return Ukazatel na nově dynamicky alokované pole nebo NULL při chybě.
 */
int *generate_array(unsigned long size) {
	unsigned int i;
	int *array;

	if (!size)
		return NULL;

	array = (int *)malloc(size * sizeof(int));
	if (!array) {
		printf("Tolik mista nam operacni system nechce dat.\n");
		return NULL;
	}

	srand(time(NULL));			/* Inicializace generátoru náhodných čísel. */
	for (i = 0; i < size; ++i)
		array[i] = rand();

	return array;
}

/**
 * @brief Vypíše size prvků pole array na standardní výstup programu. Pokud ukazatel
 *        na pole neplatný nebo má pole nulovou délku, funkce neprovede žádnou akci.
 * @param array Pole celých čísel, které bude tištěno.
 * @param size Počet tištěných prvků.
 */
void print_array(int *array, unsigned long size) {
	unsigned int i;

	if (!array || !size) {
		printf("Tady neni co tisknout!\n");
		return;
	}

	for (i = 0; i < size; ++i)
		printf("%2d. <%5d>\n", i, array[i]);
}

/**
 * @brief Prohodí hodnoty dvou proměnných, které jsou dány zadanými ukazateli. Pokud
 *        je některý z ukazatelů neplatný, funkce neprovede žádnou akci.
 * @param a Ukazatel na první proměnnou.
 * @param b Ukazatel na druhou proměnnou.
 */
void swap(int *a, int *b) {
	int temp;

#ifdef PRINT_INFO
	printf("Volani funkce swap...\n");
#endif

	if (!a || !b)
		return;

	temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * @brief Funkci můžu samozřejmě pouze deklarovat a její tělo definovat v jiném souboru.
 *        Volací konvence __fastcall znamená, že parametry nebudou předávány prostřednicvím
 *        zásobníku, ale pomocí registrů ECX a EDX.
 */
/* extern void __fastcall swap(int *, int *); */

/**
 * @brief Rekurzivní implementace řadícího algoritmu Quicksort.
 * @param array Pole řazených prvků. 
 * @param first Index první prvku 
 * @param last Index posledního prvku.
 */
void quicksort(int *array, int first, int last){
	int fi = first, li = last;

	/* Žádný optimalizátor nám tohle nevyřeší. ;-) */
	const int pivot = first;		

	if (!array || first >= last)
		return;

	while (fi < li) {
		while (array[fi] <= array[pivot] && fi < last) fi++;
		while (array[li] > array[pivot]) li--;

		if (fi < li)
			swap(&array[fi], &array[li]);
	}

	swap(&array[pivot], &array[li]);
	quicksort(array, first, li - 1);
	quicksort(array, li + 1, last);
}

/**
 * @brief Hlavní přístupový bod aplikace, která vygeneruje NUMBER_COUNT čísel, které 
 *        seřadí algoritmem QuickSort.
 * @return int Vrací EXIT_SUCCESS při úspěchu, jinak EXIT_FAILURE.
 */
int main() {
	int *numbers;
	clock_t tic, toc;

	numbers = generate_array(NUMBER_COUNT);
	if (!numbers)
		return EXIT_FAILURE;

#ifdef PRINT_INFO
	printf("Vygenerovane hodnoty:\n");
	print_array(numbers, NUMBER_COUNT);
	printf("\n");
#endif

	/* Spustím algoritmus Quicksort a měřím čas. */
	tic = clock();
	quicksort(numbers, 0, NUMBER_COUNT - 1);
	toc = clock();
	printf("Quicksort razeni trvalo: %0.3f sekund.\n", (double)(toc - tic) / CLOCKS_PER_SEC);


#ifdef PRINT_INFO
	printf("\nSerazene hodnoty:\n");
	print_array(numbers, NUMBER_COUNT);
#endif
    free(numbers);
	return EXIT_SUCCESS;
}
