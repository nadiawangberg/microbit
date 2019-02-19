#include <stdint.h>
#include <stdio.h>
#include "gpio.h"
#include "uart.h"
//#include "uart.c"



ssize_t _write(int fd, const void *buf, size_t count){
	char * letter = (char *)(buf);
	for(int i = 0; i < count; i++){
		uart_send(*letter);
		letter++;
	}
	return count;
}

ssize_t _read(int fd, void *buf, size_t count){
	char *str = (char *)(buf);
	char letter;

	do {
		letter = uart_read();
	} while(letter == '\0');

	*str = letter;
	return 1;
}


int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}
	uart_init();
	// Configure buttons
	GPIO->PIN_CNF[17] = 0; // A
	GPIO->PIN_CNF[26] = 0; // B
	int sleep = 0;
	//char letter;
	
	char bokstav;
	int i0;
	int i1;
	char c2;

	while(1){

		/*
		if (!(GPIO->IN & (1 << 26))) { // if B trykket
			uart_send('B');

			for(int i = 13; i <= 15; i++){
				GPIO->OUTSET = (1 << i);
			}
			for(int i = 4; i <= 12; i++){ // Ground (aktiv lav)
				GPIO->OUTCLR = (1 << i);
			}
		}


		if (!(GPIO->IN & (1 << 17))) { // if A trykket
			uart_send('A');

			for(int i = 13; i <= 15; i++){
				GPIO->OUTCLR = (1 << i);
			}
			for(int i = 4; i <= 12; i++){ // Ground (aktiv lav)
				GPIO->OUTSET = (1 << i);
			}
		} 
		


		letter = uart_read();
		if(letter=='a'){
			// SKRU PÅ LED MATRISE
				for(int i = 13; i <= 15; i++){
					GPIO->OUTSET = (1 << i);
				}
				for(int i = 4; i <= 12; i++){ // Ground (aktiv lav)
					GPIO->OUTCLR = (1 << i);
				}
			}
		else if (letter=='b') {
				//SKRU AV LED MATRISE
				for(int i = 13; i <= 15; i++){
					GPIO->OUTCLR = (1 << i);
				}
				for(int i = 4; i <= 12; i++){ // Ground (aktiv lav)
					GPIO->OUTSET = (1 << i);
				}
			}
		

        iprintf("Norway has %d counties.\n\r", 18);
        */


		bokstav = uart_read();
		while (bokstav=='\0'){
			bokstav = uart_read();
		}
		i0 = (int)bokstav; 
		
		bokstav = uart_read();
		while (bokstav=='\0'){
			bokstav = uart_read();
		}
		i1 = (int)bokstav;

		c2 = (char)(i0*i1);
		uart_send(c2);
		
		sleep = 100;
		while(--sleep);
	}

	return 0;
}
