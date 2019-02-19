#include <stdint.h>
#include <stdio.h>

#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"



int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// ??? Jordpinner settes logiskt lavt

	// Configure buttons
	GPIO->PIN_CNF[17] = 0; // A (ikke nødvendig)
	GPIO->PIN_CNF[26] = 0; // B


	// Configure GPIOTE for A
	GPIOTE->CONFIG[0].PSEL=17; // Channel 0 på GPIOTE lytter på pin A
	GPIOTE->CONFIG[0].MODE=1; // Aktiverer event mode (hendelse modus)
	// generere en hendelse(event) når A trykkes
	// POLARITY 2 HITOLO?? 

	// Configure GPIOTE for forsyningsspenning (pin 13,14,15)
	GPIOTE->CONFIG[1].PSEL=13; // Channel 1 på GPIOTE lytter på forsyningsspenning
	GPIOTE->CONFIG[1].MODE=3; // Aktiverer task mode (oppgave modus)
	GPIOTE->CONFIG[2].OUTINIT=0; // initial value

	GPIOTE->CONFIG[2].PSEL=14;
	GPIOTE->CONFIG[2].MODE=3;
	GPIOTE->CONFIG[2].OUTINIT=0;

	GPIOTE->CONFIG[3].PSEL=15;
	GPIOTE->CONFIG[3].MODE=3;
	GPIOTE->CONFIG[2].OUTINIT=0;

	int sleep = 0;
	while(1){

		if (!(GPIO->IN & (1 << 26))) { // if B trykket
			for(int i = 13; i <= 15; i++){
				GPIO->OUTSET = (1 << i);
			}
			for(int i = 4; i <= 12; i++){ // Ground (aktiv lav)
				GPIO->OUTCLR = (1 << i);
			}
		}


		if (!(GPIO->IN & (1 << 17))) { // if A trykket
			for(int i = 13; i <= 15; i++){
				GPIO->OUTCLR = (1 << i);
			}
			for(int i = 4; i <= 12; i++){ // Ground (aktiv lav)
				GPIO->OUTSET = (1 << i);
			}
		}

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
