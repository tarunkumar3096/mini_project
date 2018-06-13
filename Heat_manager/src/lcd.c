#include <lcd_var.h>
#include <stdarg.h>
#define WIDTH 16
#define DEGREE_WIDTH 7
#define DEGREE_HEIGHT 7
#define CENTI_WIDTH 8
#define CENTI_HEIGHT 13
#define TIME_WIDTH 16
#define TIME_HEIGHT 14
#define DIGIT_HEIGHT 34
#define LINE_HEIGHT 64

bool sleep_time_state;
bool mode_control;
static uint8_t hr1;
static uint8_t hr2;
static uint8_t min1;
static uint8_t min2;
static uint8_t sleep_hr1;
static uint8_t sleep_hr2;
static uint8_t deg_1;
static uint8_t deg_2;

static void centigrade(uint8_t deg1, uint8_t deg2)
{
	gfx_blit_bmp(89, 8, show[deg_1], WIDTH, DIGIT_HEIGHT);
	gfx_blit_bmp(93, 8, show1[deg_1], WIDTH, DIGIT_HEIGHT);
	gfx_blit_bmp(59, 8, show[deg_2], WIDTH, DIGIT_HEIGHT);
	gfx_blit_bmp(63, 8, show1[deg_2], WIDTH, DIGIT_HEIGHT);
}

static void mode_logo(bool mode_control)
{
	char smart[] = "Auto";
	char man[] = "Man";
	char *mode_set[] = {smart, man};

	gfx_set_font(FONT_8x8);
	gfx_draw_string(53, 50, "MODE:", 10);
	gfx_draw_string(93, 50, mode_set[mode_control], 10);
}	

static void sleep_time_logo(bool sleep_time_state)
{
	char on[] = "ON";
	char off[] = "OFF";
	char *sleep_state[] = {off, on};

	gfx_set_font(FONT_4x6);
	gfx_draw_string(23, 34, "SLEEP", 10);
	gfx_draw_string(27, 41, sleep_state[sleep_time_state], 10);
}

static void display_segment(void)
{
	uint8_t i;
	uint8_t j;

	gfx_blit_bmp(50, 0, divider, WIDTH, LINE_HEIGHT);
	for (i = 0; i < 5; i++) {
		j = 16*i;
		gfx_blit_bmp(51+j, 45, splitter, WIDTH, LINE_HEIGHT);
	}
	for (i = 0; i <= 3; i++) {
		if (i <= 2) {
			j = 16*i;
			gfx_blit_bmp(j, 31, splitter, WIDTH, LINE_HEIGHT);
		} else
			gfx_blit_bmp(j+2, 31, splitter,
				     WIDTH, LINE_HEIGHT);
	}
}	
	
static void sleep_time(uint8_t sleep_hr2, uint8_t sleep_hr1)
{
	char s_h1[3];
	char s_h2[3];

	sprintf(s_h1, "%d", sleep_hr2);
	sprintf(s_h2, "%d", sleep_hr1);
	gfx_set_font(FONT_NUM_10x18);
	gfx_draw_string(2, 48, "", 10);	
	gfx_draw_string(2, 48, s_h1, 10);
	gfx_draw_string(12, 48, "", 10);		
	gfx_draw_string(12, 48, s_h2, 10);
	gfx_draw_string(21, 48, ":", 10);
	gfx_draw_string(28, 48, "00", 10);
}

static void digital_clock(uint8_t hr1, uint8_t hr2, uint8_t min1, uint8_t min2)
{
	char t_hr1[3];
	char t_hr2[3];
	char t_min1[3];
	char t_min2[3];

	sprintf(t_hr1, "%d", hr2);
	sprintf(t_hr2, "%d", hr1);
	sprintf(t_min1, "%d", min2);
	sprintf(t_min2, "%d", min1);
	gfx_set_font(FONT_4x6);
	gfx_draw_string(20, 5, "TIMER", 10);
	gfx_set_font(FONT_NUM_10x18);
	gfx_draw_string(2, 15, t_hr1, 10);
	gfx_draw_string(12, 15, t_hr2, 10);
	gfx_draw_string(21, 15, ":", 10);
	gfx_draw_string(28, 15, t_min1, 10);
	gfx_draw_string(38, 15, t_min2, 10);
}

static void lcd_logos(void)
{
	gfx_blit_bmp(1, 0, time, TIME_WIDTH, TIME_HEIGHT);
	gfx_blit_bmp(114, 3, degree, DEGREE_WIDTH, DEGREE_HEIGHT);
	gfx_blit_bmp(114, 30, centi, CENTI_WIDTH, CENTI_HEIGHT);
	gfx_blit_bmp(1, 33, alarm, TIME_WIDTH, TIME_HEIGHT);
}

static void lcd_update(void)
{
	display_segment(); // to divide the lcd display
	lcd_logos(); // to display logos in lcd
	mode_logo(mode_control); // to display current mode in display
	centigrade(deg_1,deg_2); // to display centigrade in lcd display
	sleep_time_logo(sleep_time_state); // to display sleep time state
	sleep_time(sleep_hr2, sleep_hr1);// to display sleep time
	digital_clock(hr1, hr2, min1, min2); //To display the clock
}
	
void lcd(int func_value, int arg_count, ...)
{
	va_list arg_point;

	va_start (arg_point, arg_count);
	switch (func_value) {
	case 0:
		display_segment(); // to divide the lcd display
		lcd_logos(); // to display logos in lcd
		lcd_update();
		break;
	case 1:
		mode_control = va_arg (arg_point, int);
		mode_logo(mode_control); // to display current mode in display
		lcd_update();
		break;
	case 2:
		deg_1 = va_arg (arg_point, unsigned int);
		deg_2 = va_arg (arg_point, unsigned int);
		centigrade(deg_1, deg_2); // to display centigrade in lcd display
		lcd_update();
		break;
	case 3:
		sleep_time_state = va_arg (arg_point, int);
		sleep_time_logo(sleep_time_state); // to display sleep time state
		lcd_update();
		break;
	case 4:
		sleep_hr1 = va_arg (arg_point, unsigned int);
		sleep_hr2 = va_arg (arg_point, unsigned int);
		sleep_time(sleep_hr2, sleep_hr1);// to display sleep time
		lcd_update();
		break;
	case 5:
		hr1 = va_arg (arg_point, unsigned int);
		hr2 = va_arg (arg_point, unsigned int);
		min1 = va_arg (arg_point, unsigned int);
		min2 = va_arg (arg_point, unsigned int);
		digital_clock(hr1, hr2, min1, min2); //To display the clock
		lcd_update();
		break;
	}
	gfx_update();
}
