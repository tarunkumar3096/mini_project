#include <led_var.h>
#define GREEN_LED GPIO3_0
#define RED_LED GPIO0_7

void led_init(void)
{
	gpio_enable_pin(GREEN_LED);	
	gpio_enable_pin(RED_LED);
	gpio_direction_output(GREEN_LED, 1);
	gpio_direction_output(RED_LED, 1);
}

void led_state(bool state)
{
	if (state) {
		gpio_set_pin(GREEN_LED, true); //Glow Green led
		gpio_set_pin(RED_LED, false); 
	} else {
		gpio_set_pin(GREEN_LED, false);
		gpio_set_pin(RED_LED, true); //Glow Red led
	}
}
