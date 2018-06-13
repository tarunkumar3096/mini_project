#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
extern int max_row;
extern int max_col;

void display(char grid[max_row][max_col])
{
	int i = 0;
	int j = 0;

	printf("enter display\n");
	for (i = 0; i < max_row; i++) {
		for (j = 0; grid[i][j]; j++) {
			switch (grid[i][j]) {
			case '#':
				start_color();
				init_pair(1, COLOR_RED, COLOR_BLACK);
				attron(COLOR_PAIR(1));
				printw("#");
				attroff(COLOR_PAIR(1));
				break;
			case '.':
				init_pair(3, COLOR_YELLOW, COLOR_BLACK);
				attron(COLOR_PAIR(3));
				printw(".");
				attroff(COLOR_PAIR(3));
				break;
			case '$':
				init_pair(4, COLOR_BLUE, COLOR_BLACK);
				attron(COLOR_PAIR(4));
				printw("$");
				attroff(COLOR_PAIR(4));
				break;
			case '*':
				init_pair(2, COLOR_GREEN, COLOR_BLACK);
				attron(COLOR_PAIR(2));
				printw("*");
				attroff(COLOR_PAIR(2));
				break;
			case '@':
				init_pair(7, COLOR_WHITE, COLOR_BLACK);
				attron(COLOR_PAIR(7));
				printw("@");
				attroff(COLOR_PAIR(7));
				break;
			case ' ':
				init_pair(7, COLOR_WHITE, COLOR_BLACK);
				attron(COLOR_PAIR(7));
				printw(" ");
				attroff(COLOR_PAIR(7));
				break;
			default:
				printw("%c", grid[i][j]);
			}
		}
	}
}

int get_input(WINDOW *win, int *ret)
{
	noecho();
	keypad(win, true);
	printw("enter direction\n");	
	*ret = getch();
	if (*ret == KEY_UP || *ret == KEY_DOWN
	    || *ret == KEY_LEFT || *ret == KEY_RIGHT)
		return 0;
	return 1;
}
