/**
 * @file matches.h
 * @author František Pártl (fpartl@kiv.zcu.cz)
 * @brief Implementace hry "zápalky". Na začátku je 11 zápalek. Hráči se střídají v odebírání jedné
 *        nebo dvou zápalek. Kdo první odebere všechny zápalky vyhrává.
 */

#ifndef MATCHES_GAME
#define MATCHES_GAME

#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Maximální délka vstupu od uživatele.
 */
#define MAX_INPUT_LENGTH 4

/**
 * @brief Spustí hru "zápalky".
 */
void run_matches();

/**
 * @brief Tah počítače.
 * @param current_mathces Aktuální počet zápalek na stole.
 * @return int Kolik zápalek odebral počítač.
 */
int matches_pc_move(int current_mathces);

/**
 * @brief Tah hráče.
 * @param current_matches Aktuální počet zápalek na stole. 
 * @return int Kolik zápalek odebral hráč.
 */
int matches_player_move(int current_matches);

#endif