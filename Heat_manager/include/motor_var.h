#include <includes.h>
extern timer_t timer2;
extern timer_t timer4;
extern timer_t timer6;
extern uint8_t hr1;
extern uint8_t hr2;
extern uint8_t min1;
extern uint8_t min2;
extern bool sleep_time_state;
extern bool mode_control;
extern uint8_t menu_select;
extern uint8_t timer_set;
extern uint8_t key_detect;
extern uint8_t temp[2];
extern uint8_t check;

/**
 * motor_speed() - The function use to return the speed of the motor.
 *
 * Function will return the speed of the motor based on the temperature.
 *
 * @arg1: It is unsigned 8 bit integer value
 * 
 * Return:  Returns the speed of the motor.
 */
int motor_speed(uint8_t);

/**
 * time_compare() - The function use to switch off the motor.
 *
 * Function will switch off the motor, when sleep time and timer is matched.
 *
 */
void time_compare(void *);

/**
 * motor_start() - The function use to switch on/off the motor.
 *
 * Function will switch on/off the motor based on the state variable.
 *
 */
void motor_start(void *);

/**
 * motor_init() - The function use to initate the motor pin.
 *
 * Function will initate the Pins as a output Pins.
 *
 */
void motor_init(void);

/**
 * temperature_compare() - The function use to compare
 the room temperature with user set temperature.
 *
 * Function will vary the speed of the motor by
comparing with room temperature and user set temperature.
 *
 */
void temperature_compare(void *);


