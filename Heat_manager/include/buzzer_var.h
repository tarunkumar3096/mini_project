#include <includes.h>
extern timer_t timer8;
extern timer_t timer7;

/**
 * buzzer_init() - The function use to initate on the buzzer pin.
 *
 * Function will initate pins as a output pin.
 */
void buzzer_init(void);

/**
 * buzzer_on() - The function use to switch on the buzzer
 *
 * Function will swtich on buzzer to indicate the key press by user.
 */

void buzzer_on(void *);
/**
 * buzzer_off() - The function use to switch off the buzzer
 *
 * Function will swtich off buzzer which has been switched ON by buzzer_on().
 */
void buzzer_off(void *);
