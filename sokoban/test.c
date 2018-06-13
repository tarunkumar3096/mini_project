#include <ncurses.h>

int get_input(WINDOW *win)
{
	noecho();
	keypad(win, TRUE);
	int a = wgetch(win);
	printf("%d %d\n",a,KEY_UP);
	switch (a) {
	case KEY_UP:
		printw("up key\n");
		break;
	case KEY_DOWN:
		printw("down key\n");
		break;
	case KEY_LEFT:
		printw("left key\n");
		break;
	case KEY_RIGHT:
		printw("right key\n");
		break;
	default:
		printw("invalid option\n");
		break;
	}
	sleep(1);
	return a;
}

int main()
{
	int c;
	WINDOW *win;

	win = initscr();
	printw("hello world!\n");
	c = get_input(win);
	endwin();
}
