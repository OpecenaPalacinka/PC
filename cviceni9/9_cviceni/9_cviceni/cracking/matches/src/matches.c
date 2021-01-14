#include "matches.h"

int matches_pc_move(int current_mathces) {
    const int moves[] = { 1, 2 }, moves_count = 2;      /* Možné tahy počítače. */
    const int core[] = { 9, 6, 3, 0}, core_count = 4;   /* Jádro orientovaného grafu hry. */
    int i, j;
    
    /* BTW: Tohle je napraseno schválně. ;-) */

    for (i = 0; i < moves_count; ++i) {
        for (j = 0; j < core_count; ++j) {
            if (current_mathces - moves[i] == core[j]) {
                printf("Pocitac odebral %d zapalek.\n", moves[i]);
                return moves[i];
            }  
        }
    }

    printf("Ted se deje neco opravu divneho...");
    return 1;   /* K tomuto nikdy nedojde... */
}

int matches_player_move(int current_matches) {
    char input[MAX_INPUT_LENGTH];
    int to_remove;
    
    printf("Kolik chcete odebrat vy? (1 nebo 2): ", current_matches);

    while (1) {
        fgets(input, MAX_INPUT_LENGTH, stdin);
        to_remove = input[0] - '0';

        if (to_remove == 1 || to_remove == 2) {
            return to_remove;  
        }
        else printf("Staci zadat 1 nebo 2. Zkuste to jeste jednou: ");
    }
}

void run_matches() {
    unsigned int current_player = 0;            /* Aktuální hráč na tahu (0 = pc nebo 1 = hrac). */
    int matches_count = 11;                     /* Aktuální počet zápalek ve hře. */

    printf("Vitejte ve hre \"zapalky\".\nNa zacatku je 11 zapalek. Hraci postupne odebiraji 1 nebo 2 zapalky.\nVyhrava ten, kdo odebere posledni zapalku.\nProtoze si cenime Vasi \"financni pomoci\", tak zacina pocitac.\nJdeme na to! \n\n");
    while (1) {
        printf("Na stole je nyni %d zapalek.\n", matches_count);

        matches_count -= (current_player == 0) ? matches_pc_move(matches_count)
                                               : matches_player_move(matches_count); 

        if (matches_count <= 0)
            break;

        current_player = (current_player + 1) % 2;
    }

    printf((current_player == 0) ? "Prohrali jste. Ale neveste hlavu, pocitac v teto hre nemuze prohrat. \n"
                                 : "Gratuluji, porazili jste nepremozitelny pocitac.\n" );
    
}