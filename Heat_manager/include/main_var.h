#include <includes.h>

extern void read_temp(void *);
extern void motor_start(void *);
extern void clock(void *);
extern void keypress(void *);
extern void time_compare(void *);
extern void temperature_compare(void *);
extern void buzzer_off(void *);
extern void buzzer_on(void *);
extern void error_callback(uint8_t);
extern uint8_t duty;
