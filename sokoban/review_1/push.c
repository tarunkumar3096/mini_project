#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <sokoban.h>

#define FAILURE 1
#define SUCCESS 0
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

static void bit_init(char grid[max_row][max_col])
{
	int i = 0;
	int j = 0;

	for (i = 0; i < max_row; i++) {
		for (j = 0; grid[i][j]; j++) {
			switch (grid[i][j]) {
			case '#':
				grid[i][j] = WALL;
				break;
			case '.':
				grid[i][j] = GOAL;
				break;
			case '$':
				grid[i][j] = BOX;
				break;
			case '*':
				grid[i][j] = BOX_ON_GOAL;
				break;
			case '@':
				grid[i][j] = MAN;
				break;
			case ' ':
				grid[i][j] = FLOOR;
				break;
			}
		}
	}
}

static int check_win(char grid[max_row][max_col])
{
	int i = 0;
	int j = 0;
	int flag_found = 1;

	for (i = 0; ((i < max_row) && (flag_found == 1)); i++) {
		for (j = 0; ((grid[i][j] != '\0') && (flag_found == 1)); j++) {
			if ((grid[i][j] & GOAL) || (grid[i][j] & MAN_ON_GOAL))
				flag_found = 0;
		}
	}

	return flag_found;
}

static void ref_grid_comparator(char grid[max_row][max_col],
				char ref_grid[max_row][max_col])
{
	int i = 0;
	int j = 0;

	for (i = 0; i < max_row; i++) {
		for (j = 0; grid[i][j] != '\0'; j++) {
			if ((ref_grid[i][j] & GOAL) ||
			    (ref_grid[i][j] & BOX_ON_GOAL)) {
				if (grid[i][j] & FLOOR)
					grid[i][j] = GOAL;
			}

			if ((grid[i][j] & BOX_ON_GOAL) &&
			    (ref_grid[i][j] & FLOOR))
				grid[i][j] = BOX;


			if (grid[i][j] & MAN) {
				if ((ref_grid[i][j] & BOX_ON_GOAL) ||
				    (ref_grid[i][j] & GOAL))
					grid[i][j] = MAN_ON_GOAL;
			}
		}
	}
}

static int goal_loc(int row, int column, char grid[max_row][max_col], int data)
{
	if ((grid[row][column] & FLOOR) || (grid[row][column] & GOAL)) {
		if ((grid[row][column] & GOAL) && (data & BOX))
			grid[row][column] = BOX_ON_GOAL;
		else
			grid[row][column] = data;
		return 0;
	}

	return 1;
}

static int loc_wall(int row, int column, char grid[max_row][max_col], char dir)
{
	char data;
	int ret_goal;

	if ((grid[row][column] & FLOOR) || (grid[row][column] & GOAL)) {
		grid[row][column] = MAN;
		return 0;
	} else if ((grid[row][column] != GOAL) && (grid[row][column] != WALL)) {
		data = grid[row][column];
		if ((data & BOX_ON_GOAL) || (data & BOX)) {
			switch (dir) {
			case KEY_UP_ARROW:
				ret_goal = goal_loc((row - 1), column,
						    grid, data);
				break;
			case KEY_LEFT_ARROW:
				ret_goal = goal_loc(row, (column - 1),
						    grid, data);
				break;
			case KEY_DOWN_ARROW:
				ret_goal = goal_loc((row + 1), column,
						    grid, data);
				break;
			case KEY_RIGHT_ARROW:
				ret_goal = goal_loc(row, (column + 1),
						    grid, data);
				break;
			default:
				print_scr("undefined location\n");
				return 1;
			}
			if (ret_goal == 0) {
				grid[row][column] = MAN;
				return 0;
			}
		}
	}
	return 1;
}

static int push_at_dir(char grid[max_row][max_col], int dir, int *rows,
		       int *columns)
{
	int row = *rows;
	int column = *columns;
	int wall_loc = 0;

	switch (dir) {
	case KEY_UP_ARROW:
		wall_loc = loc_wall((row - 1), column, grid, KEY_UP_ARROW);
		*rows = *rows - 1;
		break;
	case KEY_LEFT_ARROW:
		wall_loc = loc_wall(row, (column - 1), grid, KEY_LEFT_ARROW);
		*columns = *columns - 1;
		break;
	case KEY_DOWN_ARROW:
		wall_loc = loc_wall((row + 1), column, grid, KEY_DOWN_ARROW);
		*rows = *rows + 1;
		break;
	case KEY_RIGHT_ARROW:
		wall_loc = loc_wall(row, (column + 1), grid, KEY_RIGHT_ARROW);
		*columns = *columns + 1;
		break;
	default:
		print_scr("undefined location\n");
	}

	if (wall_loc == 0) {
		grid[row][column] = FLOOR;
		return 0;
	}

	*rows = row;
	*columns = column;

	return 0;
}

static void grid_cpy(char dst_grid[max_row][max_col],
		     char scr_grid[max_row][max_col])
{
	int i = 0;

	for (i = 0; i < max_row; i++)
		strcpy(dst_grid[i], scr_grid[i]);
}


int push_operation(char grid[max_row][max_col], char *grid_name,
		   int man_row, int man_col)
{
	int ret_loc = 1;
	char ref_grid[max_row][max_col];
	int arrow;
	int row = man_row;
	int column = man_col;

	bit_init(grid);
	grid_cpy(ref_grid, grid);
	display(grid, grid_name);

	while (1) {
		print_scr("Enter direction by arrow keys or r to reset\n");
		while (get_input(&arrow) != 0) {
			if (arrow == 'r') {
				row = man_row;
				column = man_col;
				grid_cpy(grid, ref_grid);
				display(grid, grid_name);
				print_scr("Enter arrow keys or r to reset\n");
			} else {
				print_scr("Invalid data\n");
				print_scr("Enter arrow keys or r to reset\n");
			}
		}
		push_at_dir(grid, arrow, &row, &column);
		ref_grid_comparator(grid, ref_grid);
		display(grid, grid_name);
		ret_loc = check_win(grid);
		if (ret_loc == 1) {
			print_scr("task completed\n");
			break;
		}
	}
	return 0;
}
