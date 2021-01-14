#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void odstran_tab(char* vstup, char* dest) {
    /* Promměné FOR cyklu*/
    size_t i,j;
    strcpy(dest, vstup);
    /* Vyzkouším všechny prvky v poli*/
    for (i = 0, j = 0; i < strlen(vstup); i++,j++)
    {
        /* Pokud není tabubátor zapíšu do výstupu, pokud ano, decrementuji výsupní index, takže se další ne-tabulátor zapíše na pozici tabulátoru ve vstupním poli*/
        if (vstup[i] != '\t' && vstup[i] != ' ')
            dest[j] = vstup[i];
        else
            j--;
    }
    /* Přidám \0 na konec řetězce */
    dest[j] = '\0';
}

int main() {
  char test[] = "    ABC DEF";
  char new[strlen(test)];
  odstran_tab(test, new);
  printf("%s%s",new, test);
  return EXIT_SUCCESS;
}

/* char* odstran_tab(char* vstup) {

size_t i,j;
char *vystup = vstup;
for (i = 0, j = 0; i < strlen(vstup); i++,j++)
{

if (vstup[i] != '\t' && vstup[i] != ' ')
vystup[j] = vstup[i];
else {
j--;
}

}
vystup[j] = 0;
return vystup;
} */