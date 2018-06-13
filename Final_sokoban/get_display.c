#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <sokoban.h>

void print_scr(char *display_msg)
{
	int height;
	int width;

	initscr();

	getmaxyx(stdscr, height, width);
	height = (height/2) + (max_row) + 2;
	width = (width -  strlen(display_msg)) / 2;
	mvprintw(height, width, "%s", display_msg);
	endwin();
}

static void display_in_color(int x, int y, int color_code, int data)
{
	start_color();
	init_pair(color_code, color_code, COLOR_BLACK);
	attron(COLOR_PAIR(color_code));
	mvprintw(x, y, "%c", data);
	attroff(COLOR_PAIR(color_code));
}

void display(char grid[max_row][max_col], char *grid_name)
{
	int i = 0;
	int j = 0;
	int height;
	int width;
	int tmp_width;

	initscr();
	clear();

	getmaxyx(stdscr, height, width);
	height = (height/2) - (max_row/2);
	width = (width -  strlen(grid_name)) / 2;
	mvprintw(height++, width, "SUKOBAN%s\n", grid_name);
	for (i = 0; i < max_row; i++) {
		height++;
		tmp_width = width;
		for (j = 0; grid[i][j]; j++) {
			switch (grid[i][j]) {
			case WALL:
				display_in_color(height, tmp_width++,
						 COLOR_RED, '#');
				break;
			case GOAL:
				display_in_color(height, tmp_width++,
						 COLOR_YELLOW, '.');
				break;
			case BOX:
				display_in_color(height, tmp_width++,
						 COLOR_MAGENTA, '$');
				break;
			case BOX_ON_GOAL:
				display_in_color(height, tmp_width++,
						 COLOR_GREEN, '*');
				break;
			case MAN:
				display_in_color(height, tmp_width++,
						 COLOR_WHITE, '@');
				break;
			case FLOOR:
				display_in_color(height, tmp_width++,
						 COLOR_WHITE, ' ');
				break;
			case MAN_ON_GOAL:
				display_in_color(height, tmp_width++,
						 COLOR_CYAN, '+');
				break;
			default:
				mvprintw(height, tmp_width++,
					 "%c", grid[i][j]);
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
	
	return flag;
}
