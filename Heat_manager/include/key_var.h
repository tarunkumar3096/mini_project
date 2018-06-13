#include <includes.h>
extern timer_t timer5;
extern uint8_t duty;
extern uint8_t rpm;
extern bool mode_control;
extern uint8_t check;
extern uint8_t deg_2;
extern uint8_t deg_1;
extern uint8_t sleep_hr1;
extern uint8_t sleep_hr2;
extern bool sleep_time_state;
extern uint8_t sleep_min1;
extern uint8_t sleep_min2;
extern uint8_t min1;
extern uint8_t min2;
extern bool state;
extern uint8_t buzzer_flag;

/**
 * key_one() - The function use to detect the key one press.
 *
 * Function will detect which key one has been pressed by the user.
 *
 */
static void key_one(void);
/**
 * key_two() - The function use to detect the key two press.
 *
 * Function will detect which key two has been pressed by the user.
 *
 */
static void key_two(void);
/**
 * key_three() - The function use to detect the key three press.
 *
 * Function will detect which key three has been pressed by the user.
 *
 */
static void key_three(void);
/**
 * key_four() - The function use to detect the key four press.
 *
 * Function will detect which key four has been pressed by the user.
 *
 */
static void key_four(void);
/**
 * key_five() - The function use to detect the key five press.
 *
 * Function will detect which key five has been pressed by the user.
 *
 */
static void key_five(void);
/**
 * keypress() - The function use to detect the key press.
 *
 * Function will detect which key has been pressed by the user.
 * It will do the operation based on the key press.
 *
 */
void keypress(void *);
