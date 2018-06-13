#include <stdio.h>
#include <ncurses.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <sokoban.h>

#define MAX_LEVEL 16
#define GAME_FILE "levels.txt"
int max_row;
int max_col;

static int game_level_up(void)
{
	int choice;

	while (1) {
		print_scr("\nEnter 'y' to continue 'n' to exit:\n");
		get_input(&choice);
		if ((tolower(choice) != 'y') && (tolower(choice) != 'n')) {
			clear();			
			print_scr("Invalid input\n");
			continue;
		}
		break;
	}
	
	if  (tolower(choice) == 'y')
		return 1;
	return 0;
}

int main(void)
{
	FILE *fd;
	long cur_pos;
	int i = 0;
	int ret;
	int man_row_loc;
	int man_col_loc;
	
	fd = fopen(GAME_FILE, "r");
	if (fd == NULL)
		error(1, errno, "Error in opening file");
	
	for (i = 0; i < MAX_LEVEL; i++) {
		get_row_column(fd, &cur_pos, &man_row_loc, &man_col_loc);

		char grid_name[max_col];		
		char grid[max_row][max_col];

		data_parsing(fd, grid, cur_pos, grid_name);		
		display(grid, grid_name);
		if (push_operation(grid, grid_name, man_row_loc, man_col_loc) == 1)
			break;
		
		memset(grid, 0, max_row * max_col);
		if (game_level_up() == 0)
			break;
	} 	

	ret = fclose(fd);
	if (ret == -1)
		error(1, errno, "error in closing fp");
	return 0;
}
