#include <board.h>
#include <gpio.h>
#include <timer.h>
#include <lcd.h>
#include <gfx.h>
#include <i2c.h>
#include <error.h>

#define TIMER_SECOND 1000
#define MOTOR_OFF 1000
#define BUZZER_VOLUME 100
#define INITIAL_TEMP_READ 1
#define TEMP_READ 2000
#define KEY_PRESS_DETECT 1
#define TEMP_COMPARE 1
#define BUZZER_ON 1
