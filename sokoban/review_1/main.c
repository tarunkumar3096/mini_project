#include <stdio.h>
#include <ncurses.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <sokoban.h>

#define NO_OF_STAGES 11

int max_row;
int max_col;

static int game_level_up(void)
{
	int choice;

	while (1) {
		print_scr("\nEnter 'y' to continue 'n' to exit:\n");
		choice  = getch();
		if ((choice != 'y') && (choice != 'n')) {
			clear();
			print_scr("Invalid input\n");
			continue;
		}
		break;
	}

	if (choice == 'y')
		return 1;
	return 0;
}

int main(void)
{
	FILE *fd;
	long cur_pos;
	int i = 0;
	int man_row_loc;
	int man_col_loc;

	fd = fopen("100Boxes.txt", "r");
	if (fd == NULL)
		error(1, errno, "Error in opening file");

	for (i = 0; i < NO_OF_STAGES; i++) {
		get_row_column(fd, &cur_pos, &man_row_loc, &man_col_loc);

		char grid[max_row][max_col];
		char grid_name[max_col];

		data_parsing(fd, grid, cur_pos, grid_name);
		display(grid, grid_name);
		push_operation(grid, grid_name, man_row_loc, man_col_loc);

		memset(grid, 0, max_row * max_col);
		if (game_level_up() == 0)
			break;
	}
	print_scr("********Game over*******");

	fclose(fd);
	return 0;
}
