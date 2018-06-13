#include <timer_var.h>
uint8_t sec1;
uint8_t sec2;
uint8_t min1;
uint8_t min2;
uint8_t hr1;
uint8_t hr2;

void clock(void *tmp)
{
		sec1++;
		if (sec1 == 10) {
			sec1 = 0;
			sec2++;
		}
		if (sec2 == 6) {
			sec2 = 0;
			sec1 = 0;
			min1++;
			gfx_clear();
			lcd(5, 4, hr1, hr2, min1, min2);
		}
		if (min1 == 10) {
			min1 = 0;
			min2++;
		}
		if (min2 == 6) {
			min2 = 0;
			min1 = 0;
			hr1++;
		}
		if (hr2 == 0) {
			if (hr1 == 10) {
				hr2++;
				hr1 = 0;
			}
		} else if (hr2 == 1) {
			if (hr1 > 2) {
				hr1 = 1;
				hr2 = 0;
			}
		}
	timer_ack(&timer3);
	timer_setup(&timer3, TIMER_SECOND);
}
