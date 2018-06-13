  #include <includes.h>


/**
 * led_init() - The function will initate the led pins.
 *
 * Function will fix the led pins as a output pin.
 *
 */
void led_init(void);
/**
 * led_state() - The function use to toggle led state.
 *
 * Function will switch ON the red led and switch OFF the green led to indicate the motor state is OFF.
 * Function will switch ON the green led and switch on the red led to indicate the motor state is ON.
 *
 *
 * @arg1: It is a boolean data type
 */
void led_state(bool);
