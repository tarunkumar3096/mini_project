#include <key_var.h>
#include <lcd.h>
#define SET_TEMPERATURE GPIO2_8
#define SET_TIME GPIO2_9
#define VALUE_INCREMENT GPIO2_10
#define VALUE_DECREMENT GPIO2_11
#define SET_OK_ON_OFF GPIO1_11
uint8_t menu_select;
uint8_t inc_dec;
uint8_t key_falling_edge;
static uint8_t led_toggle;
static uint8_t count;

static void set_temperature(bool state)
{
	if (state) {
		if (check >= 33)
			check = 32;
		check++;
	} else {
		if (check <= 28)
			check = 29;
		check--;
	}
	deg_2 = check/10;
	deg_1 = check%10;
	rpm = motor_speed();
	lcd(2,2,deg_1,deg_2);
}

static void set_time(bool state)
{
	int hour[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
	
	if (state) {
		count++;
		if (count >= 12)
			count = 12;
	} else {
		count--;
		if (count <= 1)
			count = 1;
	}
	sleep_hr1 = hour[count-1]%10;
	sleep_hr2 = hour[count-1]/10;
	lcd(4, 2, sleep_hr1, sleep_hr2);
}	

static void system_state(void)
{
	if ((!led_toggle) ||  (menu_select)) {
		led_state(1);
		state = 1;
		if ((!led_toggle) || (inc_dec)) {
			led_toggle = 1;
			inc_dec = 0;
			menu_select = 0;
		}
	} else if (led_toggle) {
		key_falling_edge = 1;
		led_state(0);
		led_toggle = 0;
		menu_select = 0;
		if (state)
			state = !state;			
		if (mode_control) {
			mode_control = !mode_control;
			lcd(1,1,mode_control);
		}
		if (sleep_time_state) {			
			sleep_time_state = !sleep_time_state;
		}
		sleep_hr1 = 0;
		sleep_hr2 = 0;
		lcd(3, 1, sleep_time_state);
		lcd(4, 2, sleep_hr1, sleep_hr2);
	}
}
//key one for set temperature	
static void key_one(void)
{
	if ((!gpio_get_pin(SET_TEMPERATURE) && (!key_falling_edge) &&
	     (led_toggle) && (!menu_select))) {
		rpm = duty;
		key_falling_edge = 1;
		menu_select = 1;
	}
}
//key two for set time
static void key_two(void)
{
	if ((!gpio_get_pin(SET_TIME) && (!key_falling_edge) &&
	     (led_toggle)  && (!menu_select))) {
		key_falling_edge = 1;
		menu_select = 2;
	}
}
//key three for increment either temperature or time
static void key_three(void)
{
	if ((!gpio_get_pin(VALUE_INCREMENT) && (!key_falling_edge) &&
	     (led_toggle) && (menu_select))) {
		key_falling_edge = 1;
		mode_control = 1;
		if (menu_select == 1) {
			inc_dec = 1;
			set_temperature(true);
		} else if (menu_select == 2) {
			inc_dec = 2;
			set_time(true);
		}
	}
}
//key four for decrement either temperature or time
static void key_four(void)
{
	if ((!gpio_get_pin(VALUE_DECREMENT) && (!key_falling_edge) &&
	     (led_toggle) && (menu_select))) {
		key_falling_edge = 1;
		mode_control = 1;
		if (menu_select == 1) {
			inc_dec = 1;
			set_temperature(false);
		} else if (menu_select == 2) {
			inc_dec = 2;
			set_time(false);
		}
	}
}
//key five for toggle system state and set OK for changed time and temperature
static void key_five(void)
{
	if ((!gpio_get_pin(SET_OK_ON_OFF)) && (gpio_get_pin(SET_TIME)) &&
	    (gpio_get_pin(VALUE_INCREMENT)) && (gpio_get_pin(VALUE_DECREMENT)) &&
	    (gpio_get_pin(SET_TEMPERATURE)) && (!key_falling_edge)) {
		if (!led_toggle || (menu_select && inc_dec)) {
			key_falling_edge = 1;
		} else
			key_falling_edge = 2;		
		if ((menu_select == 2) && (inc_dec == 2)) {
			sleep_time_state = 1;
			sleep_min1 = min1;
			sleep_min2 = min2;
			lcd(3, 1, sleep_time_state);
		}
		if (menu_select == 1 && inc_dec)
			duty = 150 - rpm;
		system_state();
	}
}

void keypress(void *tmp)
{
	key_one();
	key_two();
	key_three();
	key_four();
	key_five();
	if (key_falling_edge) {
		if ((gpio_get_pin(SET_TEMPERATURE)) && (gpio_get_pin(SET_TIME)) &&
		    (gpio_get_pin(VALUE_INCREMENT)) && (gpio_get_pin(VALUE_DECREMENT)) &&
		    (gpio_get_pin(SET_OK_ON_OFF))) {
			key_falling_edge = 0;
		}
	}
	timer_ack(&timer5);
	timer_setup(&timer5, KEY_PRESS_DETECT);
}

