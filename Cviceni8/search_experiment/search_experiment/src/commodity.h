/**
 * @file commodity.h
 * @author František Pártl (fpartl@kiv.zcu.cz)
 * @brief Soubor obsahující definici datového typu commodity.
 * @version 1.0
 * @date 2020-09-29
 */

#ifndef COMMODITY
#define COMMODITY

/**
 * @brief Maximální délka identifikátoru včetně ukončovací nuly.
 */
#define MAX_ID_LENGTH 16

/**
 * @brief Datový typ identifikátoru komodity. Pokud je Vám zde něco divného, tak je to jedině v pořádku.
 *        O objasnění tohoto zvěrstva požádejte cvičícího.
 */
typedef char comm_id_t[MAX_ID_LENGTH];

/**
 * @brief Maximální délka jména komodity včetně ukončovací nuly. 
 */
#define MAX_NAME_LENGTH 64

/**
 * @brief Datový typ názvu komodity. Pokud je Vám zde něco divného, tak je to jedině v pořádku.
 *        O objasnění tohoto zvěrstva požádejte cvičícího.
 */
typedef char comm_name_t[MAX_NAME_LENGTH];

/**
 * @brief Definice datového typu commodity, který obluje informace o jedné komoditě vedené na 
 *        fiktivní tržnici. Všechny nabízené položky mají jedinečný identifikátor a jméno. 
 *        U každého je dále vedena informace o dostupném množnství a ceně jednotlivých položek.
 *        Posledním údajem je identifikátor obchodníka, u kterého je zboží dostupné.
 */
typedef struct _commodity {
    comm_id_t id;           /**!< Identifikátor zboží. */
    comm_name_t name;       /**!< Název zboží. */
    int quantity;           /**!< Počet dostupných položek. */
    int price;              /**!< Cena za jednu položku. */
    int merchant;           /**!< Identifikátor obchodníka, u kterého je zboží k dispozici. */
} commodity;

#endif