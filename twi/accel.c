#include <stdint.h>
#include "accel.h"
#include "twi.h"

#define ACCEL_ADDR          0x19 //???
#define ACCEL_DATA_REG      0x28 // OUT_X_L_A (XYZ Accel data)
#define ACCEL_CTRL_REG_1    0x20
#define ACCEL_CTRL_REG_4    0x23

//start_register = 10 101000; // where 101000 is ACCEL_DATA_REG as binary
#define start_register  0xA8 // 10101000 as hex

#define ACCEL_100_HZ_HR_ON  0x57
#define ACCEL_HR_SELECT     0x08

#include "uart.h"
#include "utility.h"

void accel_init(){
    uint8_t data;

    data = ACCEL_100_HZ_HR_ON;
    twi_multi_write(ACCEL_ADDR, ACCEL_CTRL_REG_1, 1, &data);

    data = ACCEL_HR_SELECT;
    twi_multi_write(ACCEL_ADDR, ACCEL_CTRL_REG_4, 1, &data);
}

void accel_read_x_y_z(int * p_data_buffer){
    uint8_t raw_data[6];

    /* Your task: */

    /* 1) Read the X-, Y-, and Z accelerometer registers. */
    /*    You do not need to apply any transformations to */
    /*    the data that you read; this is already done */
    /*    below. */

    //start_register = 10 101000; // where 101000 is ACCEL_DATA_REG as binary
    //start_register = 0xA8; // 10101000 as hex

    twi_multi_read(ACCEL_ADDR, start_register,6,raw_data); // array which is a container of what we read
        

    int16_t x_accel, y_accel, z_accel;

    x_accel = ((raw_data[1] << 8) | raw_data[0]) >> 4;
    if(x_accel & (1 << 11)){
        x_accel |= 0xf000;
    }

    y_accel = ((raw_data[3] << 8) | raw_data[2]) >> 4;
    if(y_accel & (1 << 11)){
        y_accel |= 0xf000;
    }

    z_accel = ((raw_data[5] << 8) | raw_data[4]) >> 4;
    if(z_accel & (1 << 11)){
        z_accel |= 0xf000;
    }

	p_data_buffer[0] = (int)x_accel;
	p_data_buffer[1] = (int)y_accel;
	p_data_buffer[2] = (int)z_accel;
}
