#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VELIKOST 6
#define INPUT_MAX_LENTGTH 15

int nactiMatici(char *fileName){
    FILE *inp;
    float **mat;
    unsigned int s = 0;
    unsigned int i = 0, k = 0;
    int size;

    char line[INPUT_MAX_LENTGTH];
    char lineCpy[INPUT_MAX_LENTGTH];
    char *row;
    printf("otevirani souboru");
    inp = fopen(fileName, "r");
    if (inp == NULL){
        printf("otevirani souboru se nezdarilo");
        return 0;
    }

    if( !fgets(line, INPUT_MAX_LENTGTH, inp) ){ /* nacti prvni radek*/
        fclose(inp);
        return 0;
    }
    strcpy(lineCpy, line);
    if((row = strtok(lineCpy, " ")) != NULL) {
        s++;
        while( (row = strtok(NULL, " ")) != NULL){
            s ++;
        }
    }
    printf("\n nacten prvni radek - velikost matice: %d \n", s);

    if(s == 0){
        fclose(inp);
        return 1;
    }

    mat = (float **) malloc(s*sizeof(float *));
    for(i = 0; i < s; i++){
        mat[i] = malloc(s*sizeof(float));
    }

    do{
        row = strtok(line, " ");
        mat[k][0] = atof(row);
        for(i = 1; i<s; i++){
            row = strtok(NULL, " ");
            mat[k][i] = atof(row);
        }
        k++;
    }while (fgets(line, INPUT_MAX_LENTGTH, inp));
    /* nactena matice */
    size = s;
    fclose(inp);
    return 1;
}

int main(int argc, char *argv[]) {
    int **matrix;
    FILE *input;
    int /*c,*/ row,collumn;
    int r = 3;
    int c = 4;
    int i, j, count;

    if (argc < 2) {
        printf("Usage: sudos <sudoku-file>\n");
        return 1;
    }
    if (argc > 2) {
        printf("Usage: sudos <sudoku-file>\n");
        return 1;
    }

    input = fopen(argv[1],"r");
    if (input == NULL) {
        printf("haloo?");
        return 1;
    }

    /*
    int **arr = (int **)malloc(r * sizeof(int *));
    for (i=0; i<r; i++)
        arr[i] = (int *)malloc(c * sizeof(int));

    count = 0;
    for (i = 0; i <  r; i++)
        for (j = 0; j < c; j++)
            arr[i][j] = ++count;

    for (i = 0; i <  r; i++)
        for (j = 0; j < c; j++)
            printf("%d ", arr[i][j]);

    for (i=0; i<r;i++){
        free(arr[i]);
    }
    free(arr);
*/


    do {
        c = fgetc(input);
        if (c != ',') {
            matrix = (int *) realloc(matrix,sizeof (int) * ((sizeof matrix) + 1));
            *matrix = c - '0';

        }
    } while (c != EOF);

    row = 0;
    collumn = 0;

    for (row = 0; row < VELIKOST; row++) {
        for (collumn = 0; collumn < VELIKOST; collumn++) {
            printf("%d -> row = %d collumn = %d\n", matrix[row][collumn],row+1,collumn+1);
        }
    }

    return 0;
}
/*     int matrix[VELIKOST][VELIKOST];
    FILE *input;
    int c,dalsiZnak,row,collumn;

    if (argc < 2) {
        printf("Usage: sudos <sudoku-file>\n");
        return 1;
    }
    if (argc > 2) {
        printf("Usage: sudos <sudoku-file>\n");
        return 1;
    }

    input = fopen(argv[1],"r");
    if (input == NULL) {
        printf("haloo?");
        return 1;
    }


    row = 0;
    collumn = 0;

    do {
        c = fgetc(input);
        if (c != '\n'){
        dalsiZnak = fgetc(input);

        if (c != ','){
            if (dalsiZnak != ',' && dalsiZnak != '\n'){
                matrix[row][collumn] = (c-'0') * 10 + (dalsiZnak-'0');
                collumn++;
            } else {
                matrix[row][collumn] = c - '0';
                collumn++;
            }
        } else {
            c = fgetc(input);
            if (c != ','){
                matrix[row][collumn] = (dalsiZnak-'0') * 10 + (c-'0');
                collumn++;
            } else {
                matrix[row][collumn] = dalsiZnak - '0';
                collumn++;
            }
        }
        if (collumn >= VELIKOST) {
            collumn = 0;
            row++;
        }
    }
    } while (c != EOF || dalsiZnak != EOF);




    for (row = 0; row < VELIKOST; row++) {
        for (collumn = 0; collumn < VELIKOST; collumn++) {
            printf("%d -> row = %d collumn = %d\n", matrix[row][collumn],row+1,collumn+1);
        }
    }

    return 0; */