/**
 * @file fsmgen.c
 * @author Jan Pelikán (pelikanj@students.zcu.cz)
 * @brief Vstupní bod aplikace. Generuje soubor fsm.c podle zadaný parametrů (vstupního souboru).
 * @version 1.2
 * @date 30.12.2020
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* maximální počet znaků na řádce -> nastaveno na 100  */
#define MAX_CHARACTERS_IN_GRAPH 100
/* maximální počet znaků v generované řádce */
#define MAX_GENERATED_CHARACTERS 100

/**
 * @brief Odstraní tabulátor ze zadaného stringu (využito k odstranění tabulátoru ze začátku řádky)
 *
 * REMOVE TABS AND WHITE SPACE
 *
 * @param input vstupní pole znaků
 * @return pole znaků bez tabulátorů
 */
void odstran_tab(char* vstup, char* dest) {
    /* Promměné FOR cyklu*/
    size_t i,j;
    strcpy(dest, vstup);

    /* Vyzkouším všechny prvky v poli*/
    for (i = 0, j = 0; i < strlen(vstup); i++,j++)
    {
        /* Pokud není tabubátor (mezera) zapíšu do výstupu, pokud ano, decrementuji výstupní index, takže se další ne-tabulátor zapíše na pozici tabulátoru ve vstupním poli*/
        if (vstup[i] != '\t' && vstup[i] != ' ')
            dest[j] = vstup[i];
        else
            j--;
    }
    /* Přidám \0 na konec řetězce */
    dest[j] = '\0';
}

/**
 * @brief Stručné info pro uživatele
 */
void introInfo() {
    printf("DFA generator\n");
    printf("Seminar work of \"Programming in C\"\n\n");
}

/**
 * @brief Informace pro uživatele, při špatném zadání argumentů
 */
void inputInfo(){
    printf("Make sure that your input was written correctly.\n");
    printf("Don´t forget to add a suffix. e.g. '.gv' or '.txt'\n");
    printf("During the program, you should not do anything.\n\n");
}

/**
 * @brief Funkce generuje řádek do fsm.c, který přidává vrcholy
 *
 * ADD NODE
 *
 * @param radka vstupní řádek
 * @return připravený kód, podle vstupních parametrů
 */
void pridej_vrchol(char radka[],FILE *file){
    /* Vytvoření pole a předání řádky bez mezer */
    char exact_radek[MAX_GENERATED_CHARACTERS];
    odstran_tab(radka,exact_radek);
    
    /* Pokud obsahuje label (start/end) */
    if(strstr(radka, "[") != NULL) {
        /* Oddělení jména vrcholu od zbytku "stringu" */
        memmove(exact_radek,strtok(exact_radek,"["),strlen(exact_radek));
        /* Zápis do souboru */
        fputs("\tpridej_vrchol(&vrcholy, \"",file);
        fputs(exact_radek,file);
        fputs("\", \"",file);
        /* Oddělení názvu labelu */
        memmove(exact_radek,strtok(NULL, "="),strlen(exact_radek));
        strcpy(exact_radek,strtok(NULL, "]"));
        /* Zápis konce generované řádky */
        fputs(exact_radek,file);
        fputs("\");\n",file);
    }
    else
    {
        /* Oddělení středníku*/
        memmove(exact_radek,strtok(exact_radek, ";"),strlen(exact_radek));
        /* Zápis do generovaného souboru */
        fputs("\tpridej_vrchol(&vrcholy, \"",file);
        fputs(exact_radek,file);
        fputs("\", \"\");\n",file);
    }
}

/**
 * @brief Funkce generuje řádek do fsm.c, který přidává hranu.
 *
 * ADD EDGE
 *
 * @param radka vstupní řádek
 * @return připravený kód, podle vstupních parametrů
 */
void pridej_hranu(char radka[], FILE *file){
    char* pomocny_pointer;
    /* Převzetí dané řádky a odstranění mezer */
    char exact_radek[MAX_GENERATED_CHARACTERS];
    odstran_tab(radka,exact_radek);
    /* Oddělení '-', získám první vrchol hrany (startovní vrchol) */
    pomocny_pointer = strtok(exact_radek, "-");
    /* Zápis úvodu + první vrchol */
    fputs("\tpridej_hranu(&vrcholy, \"",file);
    fputs(pomocny_pointer,file);
    fputs("\", \"",file);
    /* Osekáním získám druhý (koncový) vrchol dané strany */
    pomocny_pointer = strtok(NULL,">");
    pomocny_pointer = strtok(pomocny_pointer, "[");
    /* Zapíšu druhý (koncový) vrchol*/
    fputs(pomocny_pointer,file);
    fputs("\", \'",file);
    /* Osekáním řádky získám label hrany */
    strtok(NULL, "=");
    pomocny_pointer = strtok(NULL, "]");
    /* Zapíšu label hrany */
    fputs(pomocny_pointer,file);
    fputs("\');\n",file);
}

/**
 * @brief Vstupní bod. Otevře a přečte soubor zadaný v argumentech. Vytvoří výstupní soubor graph.c.
 *
 * @param argc počet argumentů
 * @param argv ukazatel na pole argumentů
 * @return int 0 = Vše proběhlo úspěšně a soubor byl vygenerován, 1 = někde nastala chyba
 */
int main(int argc, char *argv[]) {
    /* buffer pro čtení řádek */
    char buffer_radky[MAX_CHARACTERS_IN_GRAPH];
    /* vstupní soubor */
    FILE *vstupni_soubor;
    /* výstupní soubor */
    FILE *vystupni_soubor;

    /* kontrola vstupních argumentů */
    if(argc < 2) {
        printf("ERROR -> too few arguments!\n");
        inputInfo();
        return EXIT_FAILURE;
    }

    /* kontrola vstupních parametrů */
    if(argc > 2) {
        printf("ERROR -> too many arguments!\n");
        inputInfo();
        return EXIT_FAILURE;
    }

    /* Vypíšu uvodní info o programu */
    introInfo();

    /* otevření vstupního souboru */
    vstupni_soubor = fopen(argv[1], "r");

    /* Podařilo se otevřít soubory? */
    if (vstupni_soubor == NULL) {
        printf("ERROR -> input file cannot be opened properly!");
        return EXIT_FAILURE;
    }

    /* otevření výstupního souboru */
    vystupni_soubor = fopen("fsm.c", "w");

    /* Chyba by neměla nastat, ale jen pro jistotu */
    if (vystupni_soubor == NULL) {
        printf("ERROR -> output file was not opened properly!");
        return EXIT_FAILURE;
    }

    /* Úvodní komentář pro soubor */
    fputs("/**\n"
          " * @file fsm.c\n"
          " * @author Jan Pelikán (pelikanj@students.zcu.cz)\n"
          " * @brief Generovaný soubor, obsahuje definici předaného grafu.\n"
          " * @version 1.8\n"
          " * @date 30.12.2020\n"
          " *\n"
          " */\n",vystupni_soubor);

    /* zápis hlavičky fsm.c */
    fputs("\n#include \"fsm_sprava.c\"", vystupni_soubor);
    fputs("\n#include \"fsm_pridani.c\"\n\n", vystupni_soubor);

    /* zápis prní části mainu */
    fputs("int main(int argc, char *argv[]) {"
          "\n\tint jeValidni;\n\t"
          "vrchol *vrcholy = NULL;\n\n", vystupni_soubor);

    fputs("\tif(argc < 2) {\n\t\t"
          "printf(\"ERROR: No input arguments!\");\n\t\t"
          "return EXIT_FAILURE;\n\t"
          "}\n\n", vystupni_soubor);
    fputs("\tif(argc > 2) {\n\t\t"
          "printf(\"ERROR: Too many input arguments!\");\n\t\t"
          "return EXIT_FAILURE;\n\t"
          "}\n\n", vystupni_soubor);

    /* Přečtení prvních tří (zbytečných řádek) */
    fgets(buffer_radky, MAX_CHARACTERS_IN_GRAPH, vstupni_soubor);
    fgets(buffer_radky, MAX_CHARACTERS_IN_GRAPH, vstupni_soubor);
    fgets(buffer_radky, MAX_CHARACTERS_IN_GRAPH, vstupni_soubor);
    /* Čtení, řádek po řádku, zapisuji do mainu vrcholy grafu*/
    while (fgets(buffer_radky, MAX_CHARACTERS_IN_GRAPH, vstupni_soubor)){
        /* Pokud narazím na řádku na //edges tak začnu přidávat hrany, dokud nenarazím na } -> znamení konce souboru*/
        if(strstr(buffer_radky, "//edges") != NULL) {
            fputs("\n\t/* Přidávání hran */\n",vystupni_soubor);
            while (fgets(buffer_radky, MAX_CHARACTERS_IN_GRAPH, vstupni_soubor)){
                if (strstr(buffer_radky, "}") != NULL){
                    break;
                }
                /* Přidám aktuální hranu do generovaného souboru */
                pridej_hranu(buffer_radky,vystupni_soubor);
            }
        }
        /* Vyskočení z celého cyklu */
        if (strstr(buffer_radky, "}") != NULL){
            break;
        }
        /* Přidám vrchol do generovaného souboru */
        pridej_vrchol(buffer_radky,vystupni_soubor);
    }

    /* Kontrola vstupního řetězce -> Validní */
    fputs("\n\t /* Zkouška validnosti zadaného vstupu*/",vystupni_soubor);
    fputs("\n\tjeValidni = zkouska_vstupniho_retezce(argv[1], vrcholy);\n",vystupni_soubor);
    fputs("\n\tif(jeValidni){"
          "\n\t\tfree_vsechno(vrcholy);"
          "\n\t\treturn EXIT_SUCCESS;"
          "\n\t}\n\t",vystupni_soubor);
    /* Nevalidní */
    fputs("else \n\t"
          "{\n\t\t"
          "free_vsechno(vrcholy);"
          "\n\t\treturn EXIT_FAILURE;"
          "\n\t}\n}", vystupni_soubor);

    /* zavření použítých souborů a vypsání úspěšné hlášky */
    fclose(vstupni_soubor);
    fclose(vystupni_soubor);
    printf("File fsm.c was successfully generated!\n");
    return EXIT_SUCCESS;
}