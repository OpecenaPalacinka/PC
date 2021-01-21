#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINE_SIZE 128


int getSlovo(FILE *fp, char *line){

    char znak;
    int index = 0;

    while(1){
        znak = fgetc(fp);
        if(znak == EOF){
            line[index] = '\0';
            return 0;
        }
        if(znak == '\n'){
            line[index] = '\0';
            return 1;
        }
        line[index] = znak;
        index++;
    }
}


int main(int argc, char const *argv[])
{
    char line[LINE_SIZE] = {0};
    FILE *fp = NULL;
    int i, j;
    unsigned long delka_nacteneho;
    unsigned long delka_argv = strlen(argv[2]);
    char aktualni_znak;
    char *slovo = NULL;
    int nalezeno = 0;


    if(argc != 3){
        printf("Spatny pocet parametru\n");
        return EXIT_FAILURE;
    }

    fp = fopen(argv[1],"r");

    if(!fp){
        printf("Soubor nelze otevrit\n");
        return EXIT_FAILURE;
    }

    slovo = malloc(sizeof(char) * (delka_argv + 1));

    if(!slovo){
        printf("Fail with malloc\n");
        return EXIT_FAILURE;
    }

    while(getSlovo(fp, line)){

        strcpy(slovo, argv[2]);

        delka_nacteneho  = strlen(line);

        for(i = 0; i <= delka_nacteneho; i++){
            nalezeno = 0;
            aktualni_znak = line[i];

            for(j = 0; j <= delka_argv; j++){
                if(slovo[j] == aktualni_znak){
                    nalezeno = 1;
                    slovo[j] = 0;
                    break;
                }
            }
            if(nalezeno == 0){
                break;
            }
        }

        if(nalezeno == 1){
            printf("%s\n", line);
        }
    }

    free(slovo);
    fclose(fp);
    return 0;
}