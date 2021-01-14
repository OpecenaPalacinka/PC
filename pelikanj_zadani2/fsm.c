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

	pridej_vrchol(&vrcholy, "s1", "start");
	pridej_vrchol(&vrcholy, "s2", "");
	pridej_vrchol(&vrcholy, "s3", "");
	pridej_vrchol(&vrcholy, "s4", "end");
	pridej_vrchol(&vrcholy, "s5", "end");
	pridej_vrchol(&vrcholy, "s6", "");
	pridej_vrchol(&vrcholy, "s7", "");
	pridej_vrchol(&vrcholy, "s8", "");
	pridej_vrchol(&vrcholy, "s9", "");

	/* Přidávání hran */
	pridej_hranu(&vrcholy, "s1", "s2", 'a');
	pridej_hranu(&vrcholy, "s1", "s3", 'c');
	pridej_hranu(&vrcholy, "s1", "s2", 'b');
	pridej_hranu(&vrcholy, "s3", "s4", 'b');
	pridej_hranu(&vrcholy, "s2", "s4", 'd');
	pridej_hranu(&vrcholy, "s3", "s6", 'e');
	pridej_hranu(&vrcholy, "s6", "s5", 'e');
	pridej_hranu(&vrcholy, "s2", "s7", 'e');
	pridej_hranu(&vrcholy, "s7", "s7", 'q');
	pridej_hranu(&vrcholy, "s6", "s8", 'w');
	pridej_hranu(&vrcholy, "s4", "s7", 'e');
	pridej_hranu(&vrcholy, "s7", "s1", 't');
	pridej_hranu(&vrcholy, "s7", "s9", 'z');

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