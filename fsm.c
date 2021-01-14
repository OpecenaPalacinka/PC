/**
 * @file fsm.c
 * @author Jan Pelikán (pelikanj@students.zcu.cz)
 * @brief Generovaný soubor, obsahuje definici předaného grafu.
 * @version 1.8
 * @date 30.12.2020
 *
 */

#include "fsm_sprava.c"
#include "fsm_pridani.c"

int main(int argc, char *argv[]) {
	int jeValidni;
	vrchol *vrcholy = NULL;

	if(argc < 2) {
		printf("ERROR: No input arguments!");
		return EXIT_FAILURE;
	}

	if(argc > 2) {
		printf("ERROR: Too many input arguments!");
		return EXIT_FAILURE;
	}

	pridej_vrchol(&vrcholy, "states", "start");
	pridej_vrchol(&vrcholy, "statee", "end");
	pridej_vrchol(&vrcholy, "statej", "");
	pridej_vrchol(&vrcholy, "statee1", "");
	pridej_vrchol(&vrcholy, "statel1", "");
	pridej_vrchol(&vrcholy, "statel2", "");
	pridej_vrchol(&vrcholy, "statee2", "");
	pridej_vrchol(&vrcholy, "statee3", "");
	pridej_vrchol(&vrcholy, "staten", "");
	pridej_vrchol(&vrcholy, "stateo", "");
	pridej_vrchol(&vrcholy, "statev", "");
	pridej_vrchol(&vrcholy, "statei", "");
	pridej_vrchol(&vrcholy, "statep", "");

	/* Přidávání hran */
	pridej_hranu(&vrcholy, "states", "statej", 'j');
	pridej_hranu(&vrcholy, "statej", "statee1", 'e');
	pridej_hranu(&vrcholy, "statee1", "statel1", 'l');
	pridej_hranu(&vrcholy, "statel1", "statee2", 'e');
	pridej_hranu(&vrcholy, "statee2", "staten", 'n');
	pridej_hranu(&vrcholy, "staten", "stateo", 'o');
	pridej_hranu(&vrcholy, "stateo", "statev", 'v');
	pridej_hranu(&vrcholy, "statev", "statei", 'i');
	pridej_hranu(&vrcholy, "statei", "statep", 'p');
	pridej_hranu(&vrcholy, "statep", "statei", 'i');
	pridej_hranu(&vrcholy, "statei", "statev", 'v');
	pridej_hranu(&vrcholy, "statev", "stateo", 'o');
	pridej_hranu(&vrcholy, "stateo", "staten", 'n');
	pridej_hranu(&vrcholy, "staten", "statee2", 'e');
	pridej_hranu(&vrcholy, "statee2", "statee3", 'l');
	pridej_hranu(&vrcholy, "statee3", "statel2", 'e');
	pridej_hranu(&vrcholy, "statel2", "statee", 'j');

	 /* Zkouška validnosti zadaného vstupu*/
	jeValidni = zkouska_vstupniho_retezce(argv[1], vrcholy);

	if(jeValidni){
		free_vsechno(vrcholy);
		return EXIT_SUCCESS;
	}
	else 
	{
		free_vsechno(vrcholy);
		return EXIT_FAILURE;
	}
}