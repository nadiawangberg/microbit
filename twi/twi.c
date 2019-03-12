#include <stdint.h>
#include "twi.h"
#include "gpio.h"

#define TWI0 ((NRF_TWI_REG*)0x40003000)

typedef struct {
	// Tasks
	volatile uint32_t STARTRX;
	volatile uint32_t RESERVED0;
	volatile uint32_t STARTTX;
	volatile uint32_t RESERVED1[2];
	volatile uint32_t STOP;
	volatile uint32_t RESERVED2;
	volatile uint32_t SUSPEND;
	volatile uint32_t RESUME;
	// Events
	volatile uint32_t RESERVED3[56];
	volatile uint32_t STOPPED;
	volatile uint32_t RXDREADY;
	volatile uint32_t RESERVED4[4];
	volatile uint32_t TXDSENT;
	volatile uint32_t RESERVED5;
	volatile uint32_t ERROR;
	volatile uint32_t RESERVED6[4];
	volatile uint32_t BB;
	// Registers
	volatile uint32_t RESERVED7[49];
	volatile uint32_t SHORTS;
	volatile uint32_t RESERVED8[63];
	volatile uint32_t INTEN;
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t RESERVED9[110];
	volatile uint32_t ERRORSRC;
	volatile uint32_t RESERVED10[14];
	volatile uint32_t ENABLE;
	volatile uint32_t RESERVED11;
	volatile uint32_t PSELSCL;
	volatile uint32_t PSELSDA;
	volatile uint32_t RESERVED12[2];
	volatile uint32_t RXD;
	volatile uint32_t TXD;
	volatile uint32_t RESERVED13;
	volatile uint32_t FREQUENCY;
	volatile uint32_t RESERVED14[24];
	volatile uint32_t ADDRESS;
} NRF_TWI_REG;

void twi_init(){

    /* Your task: */

    /* 1) To use TWI, you must configure the SDA- and SCL lines in */
    /*    the GPIO module. Read the TWI section in the nRF51822 */
    /*    datasheet to determine which direction the pins should */
    /*    have, as well as whatTWI0 drive strength you should apply. */

    /* 2) Use pin 0 on the micro:bit as SCL; 30 as SDA. */

    /* 3) Use normal I2C speed, i.e. 100 kHz operation. */


	//initialize GPIO (2)
	GPIO->PIN_CNF[0]=0; // Pin 0 (SCL) to input
	GPIO->PIN_CNF[30]=0; // Pin 30 (SDA) to input

	//activate drive for SCL og SDA (1 / 2)
	GPIO->PIN_CNF[0]=(6<<8);//SCL activate drive (???), bitshifter tallet 6 åtte ganger bortover
	GPIO->PIN_CNF[30]=(6<<8); //SDA
	
	//initialize TWI (1)
	TWI0->PSELSCL=0; // selecting what pin is SCL
	TWI0->PSELSDA=30; // selecting what pin is SCL
	TWI0->FREQUENCY=0x01980000; //sets frequency to 100Kbps (3)

	TWI0->ENABLE=5; // Enable Twi
}

void twi_multi_read(
		uint8_t slave_address,
		uint8_t start_register,
		int registers_to_read,
		uint8_t * data_buffer // array which is a container of what we read
		){

    /* Your task: */

    /* 1) Write the register address you want to the slave */
    /*    device. Busy-wait until the register address has */
    /*    been sent by the TWI peripheral. */

    TWI0->ADDRESS=slave_address;//Accelerometer er slave (??)
	TWI0->STARTTX=1; // Activate transmit sequence (start en skriveoperasjon)
	
	TWI0->TXDSENT=0; //TWI TXD byte sent (foreløbig er ingenting sendt)
	TWI0->TXD=start_register; //Overfør SELVE start_register på TXD register (sende register på TWI-bussen) (???)
	while(!TWI0->TXDSENT); 
	//Har fått ACK tilbake fra slaven


    /* As explained in the guidance lecture, these "no-operation" */
    /* instructions are necessary because of a timing issue between */
    /* nRF51822 and the LSM303AGR. The reason we use inline assembly */
    /* is to always force the compiler to keep these instructions, */
    /* regardless of optimization level. */
    for(int i = 0; i < 10; i++){
        __asm("nop"); // Hack for å få assembly kode til å få bedre tid
    }

    /* Your task: */

    /* 1) Read back the register that you asked the slave to */
    /*    supply. This amounts to generating a repeated start */
    /*    condition, and reading the amount of registers you */
    /*    want. */

    //Starter en lese operasjon uten å stoppe bussen (kalles repeated start sequence)
	TWI0->RXDREADY = 0; // 0 just in den var 1 for some reason
	TWI0->STARTRX = 1; // start reading from TWI bus
	// RXDREADY = 1, we are ready to REAAAAD (we have correct data on bus, not søppel data)

	for(int i = 0; i < registers_to_read-1; i++){
		while(!TWI0->RXDREADY); // gets auto ACK
		TWI0->RXDREADY = 0; // setter til 0 pga RXDREADY er IKKE ready for neste iterasjon i for løkke
		
		data_buffer[i] = TWI0->RXD; // Leser et register, lagrer i data_buffer array
	}


	TWI0->STOP=1;
	while(!TWI0->RXDREADY); // generates auto NACK (cuz we ran STOP B4 it)
	data_buffer[registers_to_read-1] = TWI0->RXD;


    /* 2) Remember that you need to generate a NACK at */
    /*    the of the sequence, read the TWI section to figure */
    /*    out how to do this. */




}

void twi_multi_write(
		uint8_t slave_address,
		uint8_t start_register,
		int registers_to_write,
		uint8_t * data_buffer
		){
	TWI0->ADDRESS = slave_address;
	TWI0->STARTTX = 1;

	TWI0->TXDSENT = 0;
	TWI0->TXD = start_register;
	while(!TWI0->TXDSENT);

	for(int i = 0; i < registers_to_write; i++){
		TWI0->TXDSENT = 0;
		TWI0->TXD = data_buffer[i];
		while(!TWI0->TXDSENT);
	}

	TWI0->STOP = 0;
}
