#include "i2c_var.h"
#define FREQUENCY 100
#define PORT_ADDR 0x48

static uint8_t lthb_reg[1];
uint8_t temp[2];
uint8_t check;
uint8_t deg_2;
uint8_t deg_1;

void read_temp(void *tmp)
{
	i2c_init(FREQUENCY);
	lthb_reg[0] = 0x0;
	i2c_tx(PORT_ADDR, lthb_reg, 1);
	i2c_rx(PORT_ADDR, temp, 2);
	if ((check != temp[0]) && (!mode_control)) {
		check = temp[0];
		duty = motor_speed(check);
		deg_2 = check/10;
		deg_1 = check%10;
		motor_init(0);
		lcd(2, 2, deg_1, deg_2);
	}
	i2c_stop();
	timer_ack(&timer1);
	timer_setup(&timer1, TEMP_READ);
}
