#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <sokoban.h>

#define KEY_UP_ARROW 1
#define KEY_LEFT_ARROW 2
#define KEY_DOWN_ARROW 3
#define KEY_RIGHT_ARROW 4

#define MAN 1
#define WALL 2
#define BOX 4
#define BOX_ON_GOAL 8
#define GOAL 16
#define MAN_ON_GOAL 32
#define FLOOR 64

extern int max_row;
extern int max_col;

void print_scr(char *display_msg)
{
	initscr();
	printw("%s", display_msg);
	endwin();
}

static void display_in_color(int color_code, int backgrd_color, int data)
{	
	start_color();
	init_pair(color_code, color_code, backgrd_color);
	attron(COLOR_PAIR(color_code));
	printw("%c", data);
	attroff(COLOR_PAIR(color_code));
}

void display(char grid[max_row][max_col], char *grid_name)
{
	int i = 0;
	int j = 0;

	
	initscr();
	clear();

	printw("SUKOBAN%s\n", grid_name);
	for (i = 0; i < max_row; i++) {
		for (j = 0; grid[i][j]; j++) {
			switch (grid[i][j]) {
			case WALL:
				display_in_color(COLOR_RED, COLOR_BLACK, '#');
				break;
			case GOAL:
				display_in_color(COLOR_YELLOW, COLOR_BLACK, '.');
				break;
			case BOX:
				display_in_color(COLOR_MAGENTA, COLOR_BLACK, '$');
				break;
			case BOX_ON_GOAL:
				display_in_color(COLOR_GREEN, COLOR_BLACK, '*');
				break;
			case MAN:
				display_in_color(COLOR_WHITE, COLOR_BLACK, '@');
				break;
			case FLOOR:
				display_in_color(COLOR_WHITE, COLOR_BLACK, ' ');
				break;
			case MAN_ON_GOAL:
				display_in_color(COLOR_CYAN, COLOR_BLACK, '+');
				break;				
			default:
				printw("%c", grid[i][j]);
			}
		}
	}
	endwin();
}


int get_input(int *ret)
{
	WINDOW *win;
	int flag = 0;

	win = initscr();
	noecho();
	keypad(win, true);	
	*ret = getch();
	switch (*ret) {
	case KEY_UP:
		*ret = KEY_UP_ARROW;
		break;
	case KEY_DOWN:
		*ret = KEY_DOWN_ARROW;
		break;
	case KEY_LEFT:
		*ret = KEY_LEFT_ARROW;
		break;
	case KEY_RIGHT:
		*ret = KEY_RIGHT_ARROW;
		break;
	default:
		flag = 1;
	}
	endwin();
	if (flag == 1)
		return 1;
	return 0;
}
