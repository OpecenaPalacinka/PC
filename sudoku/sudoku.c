#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sudoku.h"

char posnums[10] = {0};
long solution_number = 0;
int solution_depth = 0;

int valid_sudoku(sudoku *s){
    char pole[10];
    int i,j,k,a,b,counter;
    if(!s){
        return 0;
    }

    for (i = 0; i < 9;i++){ /* řádek */
        counter = 0;
        memset(pole,0,10);
        for (j = 0;  j < 9; j++) { /* sloupec */
            if (s->playfield[i][j] != '-'){
                pole[counter] = s->playfield[i][j];
                for (k = 0; k < counter; k++){
                    if (pole[k] == s->playfield[i][j]){
                        /*printf("Chyba na řádce %d a ve sloupci %d\n",i+1,j+1);*/
                        return 0;
                    }
                }
                counter++;
            }
        }
    }
    for (j = 0; j < 9;j++){ /* sloupec */
        counter = 0;
        memset(pole,0,10);
        for (i = 0;  i < 9; i++) { /* řádek */
            if (s->playfield[i][j] != '-'){
                pole[counter] = s->playfield[i][j];
                for (k = 0; k < counter; k++){
                    if (pole[k] == s->playfield[i][j]){
                         /*printf("Chyba ve sloupci na řádce %d a ve sloupci %d\n",i+1,j+1);*/
                        return 0;
                    }
                }
                counter++;
            }
        }
    }

    for (i = 0; i < 9; i += 3){
        for(j = 0; j < 9; j += 3){
            counter = 0;
            memset(pole,0,10);
            for (a = i; a < i + 3; a++){
                for (b = j; b < j + 3; b++) {

                    if (s->playfield[a][b] != '-'){
                        pole[counter] = s->playfield[a][b];
                       /* printf("%c -> a = %d b = %d\n",s->playfield[a][b],a,b);
                        printf("i = %d j = %d\n",i,j);*/
                        for (k = 0; k < counter; k++){
                            if (pole[k] == s->playfield[a][b]){
                                /*printf("Chyba ve čtverci na řádce %d a ve sloupci %d\n",i+1,j++);*/
                                return 0;
                            }
                        }
                        counter++;
                    }
                }
            }
        }
    }

    return 1;
}

int load_sudoku(char *filename, sudoku *s)
{
    FILE *inp;
    int row, col;
    int c;

    inp = fopen(filename, "r");
    if (inp == NULL) return 0;

    /* Clear the playfield */
    for (row = 0; row < SUDOKU_SIZE; row++)
        for (col = 0; col < SUDOKU_SIZE; col++)
            s->playfield[row][col] = '-';

    row = 0;
    col = 0;

    do {
        c = fgetc(inp);

        if (c == '-' || (c >= '1' && c <= '9')) {
            s->playfield[row][col] = (char) c;
            col++;

            if (col >= SUDOKU_SIZE) {
                col = 0;
                row++;
            }
        }

    } while (c != EOF);

    fclose(inp);

    return 1;
}

void print_sudoku(sudoku *s)
{
    int i, j;

    printf("|-------+-------+-------|\n");

    for (i = 0; i < SUDOKU_SIZE; i++) {
        printf("| ");
        for (j = 0; j < SUDOKU_SIZE; j++) {
            printf("%c ", s->playfield[i][j]);
            if (!((j + 1) % 3)) printf("| ");
        }

        if (!((i + 1) % 3)) printf("\n|-------+-------+-------|\n");
        else printf("\n");
    }
}

void get_possibilities(sudoku *s, int i, int j, char *pos)
{
    memset(pos, 0, 10);
    strcpy(pos, "123456789");
}

int solve_sudoku(sudoku *s, int depth)
{
    int i, j, k;
    int found = 0;
    int valck;

    printf("\x0D%d", depth);

    valck = valid_sudoku(s);
    if (!valck) return 0;

    for (i = 0; i < SUDOKU_SIZE; i++) {
        for (j = 0; j < SUDOKU_SIZE; j++)
            if (s->playfield[i][j] == '-') {
                found = 1;
                break;
            }
        if (found) break;
    }

    if (!found && valck) {
        printf("\n");
        print_sudoku(s);
        return 1;
    }

    get_possibilities(s, i, j, posnums);

    for (k = 0; k < strlen(posnums); k++) {
        s->playfield[i][j] = posnums[k];
        if (!solve_sudoku(s, depth + 1)) s->playfield[i][j] = '-';
    }

    return 0;
}
