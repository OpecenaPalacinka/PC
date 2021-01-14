/**
 * @file fsmgen.c
 * @author your name (you@domain.com)
 * @brief Vygeneruje soubor fsm.c podle vstupního souboru
 * @version 0.1
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* maximální počet znaků na řádce */
#define max_characters 100

/**
 * @brief zbavý řetězce bílych znaků
 * 
 * @param str vstupní řetězec
 * @return char* řetězec bez bílých znaků
 */
char *trim_space(char *str) {
    char *end;

    /* odstranění bílých znaků před řetězcem */
    while (isspace(*str)) {
        str++;
    }

    /* odstranění bílých znaků za řetězcem */
    end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) {
        end--;
    }

    /* zapsání konečného znaku na konec řetězce */
    end[1] = '\0';
    
    return str;
}

/**
 * @brief Otevře soubor načtený z argumentu a vygeneruje příslušný fsm.c soubor
 * 
 * @param argc počet argumentů
 * @param argv argumenty
 * @return int 
 */
int main(int argc, char *argv[]) {
    /* nazev vstupního souboru*/
    char *input_file;
    /* vstupní soubor */
    FILE *f;
    /* výstupní soubor */
    FILE *out;
    /* buffer pro čtení řádek */
    char buf[max_characters]; 
    /* módy zápisů do souboru, 0 = default, 1=nodes, 2=edges*/
    int mode = 0; 
    /* část načteného řádku */
    char *line_part;

    /* kontrola vstupních argumentů */
    if(argc < 2 || argc > 2) {
        if(argc > 2) {
            printf("Error: Too many arguments!\n");
        }
        else {
            printf("Error: Missing argument!\n");
        }     
        printf("Write the name of the input file as an argument (with filename extension)\n");
        printf("The file needs to be located in the same folder and contain appropriate content\n"); 
        return EXIT_FAILURE;
    }

    /* název vstupního souboru načtený z argumentu */
    input_file = argv[1];

    /* otevření souborů */
    f = fopen(input_file, "r");
    out = fopen("fsm.c", "w");

    /* kontrola otevření souborů */
    if (f == NULL || out == NULL) {
        perror("Failed: ");
        return EXIT_FAILURE;
    }

    /* zápis hlavičky fsm.c */
    fputs("\n#include \"fsm_template.c\"\n\n", out);
    /* zápis prní části mainu */
    fputs("int main(int argc, char *argv[]) {\n\tchar *input_string;\n\tnode *nodes = NULL;\n\n\tif(argc < 2) {\n\t\tprintf(\"Error: Missing argument!\");\n\t\treturn EXIT_FAILURE;\n\t}\n\n\tinput_string = argv[1];\n\n", out);

    /* čtení vstupního souboru a zápis příslušných příkazů do mainu */
    while(fgets(buf, max_characters, f)) {
        /* při načtení řádky //nodes se přepne do zápisu vrcholů */
        if(strstr(buf, "//nodes") != NULL) {
            mode = 1;
            fgets(buf, max_characters, f);
        }
        /* při načtení řádky //edges se přepne do zápisu hran */
        if(strstr(buf, "//edges") != NULL) {
            mode = 2;
            fgets(buf, 100, f);
        }
        /* konec souboru = reset módu zápisu */
        if(strstr(buf, "}") != NULL) {
            mode = 0;
        }
        /* rozsekani nactene radky a zapis vrcholu do výstupního souboru */
        if(mode == 1) {
            /* pokud obsahuje label */
            if(strstr(buf, "[") != NULL) {
                line_part = strtok(buf, "[");
                line_part = trim_space(line_part);
                fputs("\tadd_node(&nodes, \"", out);
                fputs(line_part, out); 
                fputs("\", \"", out); 
                line_part = strtok(NULL, "=");
                line_part = strtok(NULL, "]");
                fputs(line_part, out); 
                fputs("\");\n", out); 
            }
            /* jenom nazev */
            else {
                line_part = strtok(buf, ";");
                line_part = trim_space(line_part);
                fputs("\tadd_node(&nodes, \"", out);
                fputs(line_part, out); 
                fputs("\", \"\");\n", out); 
            }
        }
        /* rozsekani nactene radky a zapis hrany do výstupního souboru */
        else if(mode == 2) {
                line_part = strtok(buf, "-");
                line_part = trim_space(line_part);
                fputs("\tadd_edge(&nodes, \"", out);
                fputs(line_part, out);
                fputs("\", \"", out);
                line_part = strtok(NULL, ">");
                line_part = strtok(line_part, "[");
                fputs(line_part, out); 
                fputs("\", \'", out);
                line_part = strtok(NULL, "=");
                line_part = strtok(NULL, "]");
                fputs(line_part, out); 
                fputs("\');\n", out); 
        }
    }

    /* zápis zbytku main funkce */
    fputs("\n\tif(process(input_string, nodes)){\n\t\tfree_all(nodes);\n\t\treturn EXIT_SUCCESS;\n\t}\n	else {\n\t\tfree_all(nodes);\n\t\treturn EXIT_FAILURE;\n\t}\n}", out);

    /* close souborů*/
    fclose(f);
    fclose(out);

    return EXIT_SUCCESS;
}