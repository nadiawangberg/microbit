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
	

	// Configure buttons
	//GPIO->PIN_CNF[17] = 0; // A (ikke nødvendig)
	//GPIO->PIN_CNF[26] = 0; // B


	// Configure GPIOTE for A
	GPIOTE->CONFIG[0]= 1 | (17<<8) | (2 << 16); 
	// Channel 0 på GPIOTE lytter på pin A (17<<8)
	// Aktiverer event mode = 1 (hendelse modus) (1)
	// POLARITY 2 HITOLO (2 << 16), generere en hendelse(event) når A trykkes

	// Configure GPIOTE for forsyningsspenning (pin 13,14,15)
	GPIOTE->CONFIG[1]= (3) | (13<<8) | (0 << 20) | (3 << 16);
									   // initial value
						//Aktiverer task mode (oppgave modus)
				//Channel 1 på GPIOTE lytter på forsyningsspenning
	GPIOTE->CONFIG[2] = (3) | (14<<8) | (0 << 20) | (3 << 16);
	GPIOTE->CONFIG[3] = (3) | (15<<8) | (0 << 20) | (3 << 16);

	//Enable PPI Channel 0,1,2
	PPI->CHENSET=0x7; // binary num 111

	// A til 13
	PPI->PPI_CH[0].EEP = (uint32_t)&(GPIOTE->IN[0]);
	PPI->PPI_CH[0].TEP = (uint32_t)&(GPIOTE->OUT[1]);

	// A til 14
	PPI->PPI_CH[1].EEP = (uint32_t)&(GPIOTE->IN[0]);
	PPI->PPI_CH[1].TEP = (uint32_t)&(GPIOTE->OUT[2]);

	// A til 15
	PPI->PPI_CH[2].EEP = (uint32_t)&(GPIOTE->IN[0]);
	PPI->PPI_CH[2].TEP = (uint32_t)&(GPIOTE->OUT[3]);

	//PPI->CHENSET=0x7; // binary num 111


	//int sleep = 0;
	while(1){

		/*
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
		*/

		//sleep = 10000;
		//while(--sleep);
	}
	return 0;
}
