#include <buzzer_var.h>
#define BUZZER_PIN GPIO2_4

uint8_t buzzer_flag;
static bool buzzer_state = true;
extern uint8_t key_falling_edge;

void buzzer_init(void)
{
	gpio_enable_pin(BUZZER_PIN);
	gpio_direction_output(BUZZER_PIN, 1);
}

void buzzer_on(void *tmp)
{
	if (key_falling_edge == 1) {
		gpio_set_pin(BUZZER_PIN, buzzer_state);
		buzzer_flag = 0;
	}
	timer_ack(&timer7);
	timer_setup(&timer7, BUZZER_ON);
}

void buzzer_off(void *tmp)
{
	if (!buzzer_flag)
		gpio_set_pin(BUZZER_PIN, !(buzzer_state));
	timer_ack(&timer8);
	timer_setup(&timer8, BUZZER_VOLUME);
}
