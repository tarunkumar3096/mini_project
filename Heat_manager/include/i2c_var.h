#include <includes.h>

extern timer_t timer1;
extern uint8_t duty;
extern uint8_t mode_control;
/**
 * read_temp() - The function use to read the room temperature.
 *
 * Function use to display the room temperature.
 * It will display temperature, if any chage in room temperature is detected.
 *
 */
void read_temp(void *);
