/**
 * @file search_experiment.c
 * @author František Pártl (fpartl@kiv.zcu.cz)
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "config.h"
#include "commodity.h"
#include "searchers/searchers.h"

/**
 * @brief Funkce ze zadaného souboru načte maximálně max_n komodit do pole daného ukazatelem out. Kvůli možnosti
 *        přetečení zásobníku jsou záznamy načítány do dynamické paměti. Výsledek je tedy třeba uvolnit pomocí
 *        funkce free.
 * @param input_file Umístění souboru s načítanými daty.
 * @param out Ukazatel na pole, kam budou data načtena.
 * @param max_n Maximální počet načítaných prvků.
 * @return int Počet reálně načtených prvků, nebo 0 při chybě.
 */
int load_commodities(char *input_file, commodity **out, int max_n) {
    char line[MAX_LINE_LENGTH] = { 0 };    
    commodity *temp;
    char *token;
    FILE *file;
    int i;

    if (!input_file || !out || max_n <= 0){
        return 0;
    }


    file = fopen(input_file, "r");
    if (!file)
        return 0;

    temp = (commodity *)malloc(max_n * sizeof(commodity));
    if (!temp) {
        fclose(file);
        return 0;
    }

    for (i = 0; i < max_n && fgets(line, MAX_LINE_LENGTH, file); ++i) {
        /* Pro jednoduchost zde neprovádím žádné kontroly, které by zde samozřejmě být měly! */
        token = strtok(line, CSV_DELIMETER);
        strncpy(temp[i].id, token, MAX_ID_LENGTH);

        token = strtok(NULL, CSV_DELIMETER);
        strncpy(temp[i].name, token, MAX_NAME_LENGTH);

        token = strtok(NULL, CSV_DELIMETER);
        temp[i].quantity = atoi(token);

        token = strtok(NULL, CSV_DELIMETER);
        temp[i].price = atoi(token);

        token = strtok(NULL, CSV_DELIMETER);
        temp[i].merchant = atoi(token);
    }

    fclose(file);
    *out = temp;
    return i;
}

/**
 * @brief Funkce načítá hledané identifikátory ze souboru ids_file do pole out. Načteno bude maximálně max_n identifikátorů.
 * @param ids_file Soubors identifikátory.
 * @param out Ukazatel na pole, kam budou identifátory načteny.
 * @param max_n Maximální počet načtených identifikátorů.
 * @return int Reálný počet načtených identifikátorů.
 */
int load_identifiers(char *ids_file, comm_id_t **out, int max_n) {
    comm_id_t *temp;
    FILE *file;
    int i;

    if (!ids_file || !out || max_n <= 0)
        return 0;


    file = fopen(ids_file, "r");
    if (!file)
        return 0;


    temp = (comm_id_t *)malloc(sizeof(comm_id_t) * max_n);
    if (!temp) {
        fclose(file);
        return 0;
    }

    for (i = 0; i < max_n && fgets(temp[i], sizeof(comm_id_t), file); ++i)      /* Tady je schovaná krásná chyba, jestli ji sami nenajdete, tak si řekněte cvičícímu. */
        temp[i][strcspn(temp[i], "\r\n")] = 0;
    
    fclose(file);
    *out = temp;
    return i;
}

/**
 * @brief Funkce, která spustí vyhledávací algoritmus zadaný ukazatelem na funkci. Funkce bude spuštěna TEST_RUNSkrát. Bude počítán čas na procesoru při každém spuštění.
 *        Výsledkem měření je pak průměr těchto měření a rozptyl měření. Ostatní parametry funkce jsou předány vyhledávacímu algoritmu.
 * @param searcher Ukazatel na spuštěnou funkci (vyhledávací algoritmus).
 * @param searcher_label Popisek vyhledávacího algoritmu, který bude vypisován do konzolového výstupu aplikace.
 * @param comms Data, ve kterých bude prováděno vyhledávání.
 * @param comms_count Počet prvků pole comms.
 * @param ids Pole vyhledávaných identifikátorů.
 * @param ids_count Počet prvků pole ids.
 * @param quantities Pole, do kterého bude vyhledávací algoritmus ukládat nalezené hodnoty.
 */
void run_searcher(searcher_function searcher, const char *searcher_label, const commodity comms[], int comms_count, comm_id_t ids[], int ids_count, int quantities[])  {
    double times[TEST_RUNS] = { .0 }, average = .0, variance = .0;
    clock_t tic, toc;
    int i, ret_code;
    
    for (i = 0; i < TEST_RUNS; ++i) {
        memset(quantities, 0, sizeof(int) * ids_count);     /* Před každým spuštěním vynuluji pole výsledků. */

        tic = clock();
        ret_code = searcher(comms, comms_count, ids, ids_count, quantities);
        toc = clock();

        if (ret_code == EXIT_SUCCESS) {
            times[i] = (double)(toc - tic) / CLOCKS_PER_SEC;
            average += times[i];        
        }
        else {
            printf("%s skoncilo chybou %d!", searcher_label, ret_code);
            return;
        }
    }
    average /= (double)TEST_RUNS;

    for (i = 0; i < TEST_RUNS; ++i) {
        variance += pow(times[i] - average, 2);
    }
    variance /= (double)TEST_RUNS;
    
    printf("%s trvalo %f sekund s rozptylem %f sekund.\n", searcher_label, average, variance);
}

/**
 * @brief Funkce porovnává dvě zadaná pole stejné dimenze.
 * @param lin_results Výsledky lineárního vyhledávání.
 * @param btree_results Výsledky vyhledávání pomocí BVS.
 * @param count Počet výsledků v polích lin_results a btree_results.
 * @return int 1, pokud pole obsahují stejné prvky, jinak 0.
 */
int results_equal(int lin_results[], int btree_results[], int count) {
    int i;

    for (i = 0; i < count; ++i) {
        if (lin_results[i] != btree_results[i]) {
            return 0;
        }
    }
    
    return 1;
}

/**
 * @brief Hlavní přístupový bod aplikace, která porovnává rychlost lineárního vyhledávání a vyhledávání pomocí BVS.
 * @return int Funkce při úspěchu vrací EXIT_SUCCESS, jinak EXIT_FAILURE. Chyby ve vyhledávacích aglritmech jsou ignorovány.
 */
int main() {
    /* Data načítám raději dynamicky, aby nedošlo k přetečení zásobníku. */
    int comm_count, ids_count;
    comm_id_t *identifiers;
    commodity *commodities;

    /* Výsledky alokuji normálně staticky na zásobník. */
    int lin_results[FIND_COUNT], btree_results[FIND_COUNT];

    ids_count = load_identifiers(IDS_FILE, &identifiers, FIND_COUNT);

    if (ids_count <= 0) {
        printf("Chyba pri nacitani vyhledavanych identifikatoru!\n");
        return EXIT_FAILURE;
    }


    comm_count = load_commodities(INPUT_FILE, &commodities, COMMODITIES_COUNT);
    if (comm_count <= 0) {
        free(identifiers);
        printf("Chyba pri nacitani dat!\n");
        return EXIT_FAILURE;
    }

    /*
        Zde si můžete zkusit vypsat načtené komodity a identifikátory.

        printf("Nactene komodity:\n");
        for (i = 0; i < comm_count; ++i)
            printf("%s, %s, %d, %d, %d\n", commodities[i].id, commodities[i].name, commodities[i].quantity, commodities[i].price, commodities[i].merchant);

        printf("Načteno %d komodit.\n", comm_count);

        printf("Hledané identifikátory:\n");
        for (i = 0; i < ids_count; ++i)
            printf("%s\n", identifiers[i]);

        printf("Načteno %d identifikátorů.\n", comm_count);
    */

    printf("Nacteno %d komodit.\nSpoustim vyhledavani %d klicu...\n", comm_count, ids_count);

    run_searcher(linear_search, "Linearni vyhledavani", commodities, comm_count, identifiers, ids_count, lin_results);
    run_searcher(btree_search, "Vyhledavani s BVS", commodities, comm_count, identifiers, ids_count, btree_results);

    printf("Vysledky vyhledavani jsou %s.\n", results_equal(lin_results, btree_results, FIND_COUNT)
                                                ? "STEJNE! GRATULUJI!" 
                                                : "RUZNE! NEKDE MATE CHYBU.");

    free(identifiers);
    free(commodities);
    return EXIT_SUCCESS;
}