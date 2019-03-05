#include "twi.h"

void twi_init(){
	//initialize GPIO
	GPIO->PIN_CNF[0]=0; // Pin 0 (SCL) to input
	GPIO->PIN_CNF[30]=0; // Pin 30 (SDA) to input

	//activate drive for SCL og SDA (???)
	GPIO->PIN_CNF[0]=(6<<8);//SCL activate drive (???), bitshifter tallet 6 åtte ganger bortover
	GPIO->PIN_CNF[30]=(6<<8); //SDA
	
	//initialize TWI
	TWI0->PSELSCL=0; // selecting what pin is SCL
	TWI0->PSELSDA=30; // selecting what pin is SCL
	TWI0->FREQUENCY=0x01980000; //sets frequency to 100Kbps

	TWI0->ENABLE=5; // Enable Twi

}

void twi_multi_read(uint8_t slave_address, uint8_t start_register, int registers_to_read, uint8_t * data_buffer) {
	TWI0->ADDRESS=slave_address;//Accelerometer er slave (??)
	TWI0->STARTTX=1; // Activate transmit sequence (start en skriveoperasjon)
	
	TWI0->TXDSENT=0; //TWI TXD byte sent
	TWI0->TXD=start_register; //sender vi start_register på TXD register
	while(!TWI0->TXDSENT); //Har fått ACK tilbake fra slaven
	
	//Starter en lese operasjon uten å stoppe (kalles repeated start sequence)
	[...]
	TWI0->RXDREADY = 0;
	TWI0->STARTRX = 1;




}


void twi_multi_write(uint8_t slave_address,uint8_t start_register,int registers_to_write,uint8_t * data_buffer) {

}