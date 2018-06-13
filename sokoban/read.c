void display(char (*grid)[15])
{
	int i = 0;
	int j = 0;

	for (i = 0; i < 8; i++) {
		for (j = 0; grid[i][j] != '\0'; j++) {
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
			default:
				printw("%c", grid[i][j]);
			}
		}
		printw("\n");				
	}
}

int get_input(WINDOW *win, int *ret)
{
	noecho();
	keypad(win, true);	
	*ret = getch();
	if (*ret == KEY_UP || *ret == KEY_DOWN
	    || *ret == KEY_LEFT || *ret == KEY_RIGHT)
		return 0;
	printw("invalid input\n");
	return 1;
}
