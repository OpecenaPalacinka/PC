#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100


int main(int argc, char *argv[]) {
    FILE *file;
    int i,j;
    unsigned long zmena,zmenaMax;
    unsigned long delka;
    char *buffer;
    char hledaneSlovo[MAX_SIZE];
    char pole[MAX_SIZE];


    if (argc < 2){
        printf("Use - \'input chars\'");
    }
    if (argc > 2){
        printf("Use - \'input chars\'");
    }

    strcpy(hledaneSlovo,argv[1]);
    zmenaMax = MAX_SIZE;
    buffer = malloc(MAX_SIZE * sizeof (char));

    file = fopen("czech_925705.dic","r");

    while (fgets(buffer,MAX_SIZE,file)){
        delka = 0;
        if (strlen(buffer) - 2 > strlen(hledaneSlovo)){
            delka = strlen(buffer) - 2 - strlen(hledaneSlovo);
        }
        for (i = 0; i < MAX_SIZE;i++){
            zmena = i;
            for (j = 0; j < MAX_SIZE; j++) {
                if (hledaneSlovo[j] == '\0'){
                    break;
                }
                if (j + i < MAX_SIZE){
                    if (buffer[j+i] != hledaneSlovo[j]){
                        zmena++;
                    }
                }
            }
            if ((zmena + delka) < zmenaMax){
                zmenaMax = zmena + delka;
                strcpy(pole,buffer);
            }
        }
    }

    if (!file) {
        printf("Cannot open input file!");
        return EXIT_FAILURE;
    }


    printf("%s (%lu)",pole,zmenaMax);
    free(buffer);
    return EXIT_SUCCESS;
}
