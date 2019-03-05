#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "ubit.h"
#include "bluetooth.h"

int main(){
	ubit_uart_init();

	uint32_t err_code_bt = 0;
	uint32_t err_code_adv = 0;

	err_code_bt = bluetooth_init();
	ubit_uart_print("BLE Enable error code: %d\n\r", err_code_bt);

	err_code_adv=bluetooth_gap_advertise_start();
	ubit_uart_print("BLE adv transmission error code: %d\n\r", err_code_adv);

	return 0;
}
