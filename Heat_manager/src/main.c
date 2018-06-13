#include <main_var.h>
timer_t timer1;
timer_t timer2;
timer_t timer3;
timer_t timer4;
timer_t timer5;
timer_t timer6;
timer_t timer7;
timer_t timer8;

void module_init(void)
{
	board_init();
	lcd_init();
	gpio_init();
	timer_init();
	delay_init();
	gfx_init();
}

void user_module_init(void)
{
	led_init();
	motor_init();
	buzzer_init();
}
	
int main(void)
{
	module_init();
	user_module_init();
	gfx_clear();	
	lcd(0,0);
	led_state(false);
	error_setcb(error_callback);
	timer_setup(&timer1, INITIAL_TEMP_READ);
	timer_setcb(&timer1, read_temp);
	timer_setup(&timer2, duty);
	timer_setcb(&timer2, motor_start);
	timer_setup(&timer3, TIMER_SECOND);
	timer_setcb(&timer3, clock);
	timer_setup(&timer4, MOTOR_OFF);
	timer_setcb(&timer4, time_compare);
	timer_setup(&timer5, KEY_PRESS_DETECT);
	timer_setcb(&timer5, keypress);
	timer_setup(&timer6, TEMP_COMPARE);
	timer_setcb(&timer6, temperature_compare);
	timer_setup(&timer7, BUZZER_ON);
	timer_setcb(&timer7, buzzer_on);
	timer_setup(&timer8, BUZZER_VOLUME);
	timer_setcb(&timer8, buzzer_off);
	event_poll();
	return 0;
}
