#include "error_var.h"

void error_callback(uint8_t ecode)
{	
	lcd_clear();
	switch(ecode) {
	case ERR_I2C_NODEV:		
		lcd_puts("Error!\n");
		lcd_puts("i2c Device Not Present\n");
		break;
	case ERR_I2C_NOACK:
		lcd_puts("Error!\n");
		lcd_puts("No ACK from i2c Device Present\n");
		break;
	}
}
