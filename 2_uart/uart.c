#include <stdint.h>
#include "uart.h"
#include "gpio.h"

#define UART ((NRF_UART_REG*)0x40002000)
typedef struct {
	volatile uint32_t STARTRX;
	volatile uint32_t STOPRX;
	volatile uint32_t STARTTX;
	volatile uint32_t STOPTX;
	// volatile uint32_t RESERVED0[3];
	volatile uint32_t SUSPEND;
	volatile uint32_t RESERVED1[56];

	volatile uint32_t CTS;
	volatile uint32_t NCTS;
	volatile uint32_t RXDRDY;	
	// reserved her?? 
	volatile uint32_t TXDRDY;
	// reserved her?? 
	volatile uint32_t ERROR;
	// reserved her?? 
	volatile uint32_t RXTO;
	volatile uint32_t RESERVED2[146];

	volatile uint32_t INTEN;
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	// reserved her?? 
	volatile uint32_t ERRORSRC;
	// reserved her?? 
	volatile uint32_t ENABLE;
	// reserved her?? 
	volatile uint32_t PSELRTS;
	volatile uint32_t PSELTXD; // får pinner til å bli brukt av GPIO ??
	volatile uint32_t PSELCTS;
	volatile uint32_t PSELRXD; // får pinner til å bli brukt av GPIO ??
	volatile uint32_t RXD;
	volatile uint32_t TXD;
	// reserved her?? 
	volatile uint32_t BAUDRATE;
	// reserved her?? 
	volatile uint32_t CONFIG;

} NRF_UART_REG;


void uart_init() {
	UART->BAUDRATE = 0x00275000 // Baud9600

}

void uart_send(char letter) {

}

char uart_read() {

}

/*
STARTRX
STOPRX
STARTTX
STOPTX
SUSPEND

NCTS
RXDRDY
TXDRDY
ERROR
RXTO

Registers
INTEN
INTENSET
INTENCLR
ERRORSRC
ENABLE
PSELRTS
PSELTXD
PSELCTS
PSELRXD
RXD
TXD
BAUDRATE
CONFIG
*/