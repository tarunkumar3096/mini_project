#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ncurses.h>
#include <sokoban.h>

static void bit_reset_set(char *var, int data)
{
	*var &= ~(*var);
	*var |= data;
}

static void bit_init(char grid[max_row][max_col])
{
	int i = 0;
	int j = 0;

	for (i = 0; i < max_row; i++) {
		for (j = 0; grid[i][j]; j++) {
			switch (grid[i][j]) {
			case '#':
				bit_reset_set(&grid[i][j], WALL);
				break;
			case '.':
				bit_reset_set(&grid[i][j], GOAL);
				break;
			case '$':
				bit_reset_set(&grid[i][j], BOX);
				break;
			case '*':
				bit_reset_set(&grid[i][j], BOX_ON_GOAL);
				break;
			case '@':
				bit_reset_set(&grid[i][j], MAN);
				break;
			case ' ':
				bit_reset_set(&grid[i][j], FLOOR);
				break;
			}
		}
	}
}

static int locate_dot(char grid[max_row][max_col])
{
	int i = 0;
	int j = 0;
	int flag = 1;

	for (i = 0; ((i < max_row) && (flag == 1)); i++) {
		for (j = 0; ((grid[i][j] != '\0') && (flag == 1)); j++) {
			if ((grid[i][j] & GOAL) || (grid[i][j] & MAN_ON_GOAL))
				flag = 0;
		}
	}

	return flag;
}

static void ref_grid_comparator(char grid[max_row][max_col],
				char ref_grid[max_row][max_col])
{
	int i = 0;
	int j = 0;

	for (i = 0; i < max_row; i++) {
		for (j = 0; grid[i][j] != '\n'; j++) {
			if ((ref_grid[i][j] & GOAL) ||
			    (ref_grid[i][j] & BOX_ON_GOAL)) {
				if (grid[i][j] & FLOOR)
					bit_reset_set(&grid[i][j], GOAL);
			}

			if ((grid[i][j] & BOX_ON_GOAL) &&
			    ((ref_grid[i][j] & FLOOR) || (ref_grid[i][j] & BOX)))
				bit_reset_set(&grid[i][j], BOX);

			if (grid[i][j] & MAN) {
				if ((ref_grid[i][j] & BOX_ON_GOAL) ||
				    (ref_grid[i][j] & GOAL))
					bit_reset_set(&grid[i][j], MAN_ON_GOAL);
			}
		}
	}
}

static int scan_box_on_goal(int row, int column,
			    char grid[max_row][max_col], int data)
{
	if ((grid[row][column] & FLOOR) || (grid[row][column] & GOAL)) {
		if ((grid[row][column] & GOAL) && (data & BOX))
			bit_reset_set(&grid[row][column], BOX_ON_GOAL);
		else
			bit_reset_set(&grid[row][column], data);
		return SUCCESS;
	}

	return FAILURE;
}

static int detect_obstacle(int row, int column,
			   char grid[max_row][max_col], char dir)
{
	char data = grid[row][column];
	int ret_goal = 0;

	if ((data & FLOOR) || (data & GOAL)) {
		bit_reset_set(&grid[row][column], MAN);
		return SUCCESS;
	} else if (!(data & WALL)) {
		if ((data & BOX_ON_GOAL) || (data & BOX)) {

			switch (dir) {
			case KEY_UP_ARROW:
				ret_goal = scan_box_on_goal((row - 1),
							    column, grid, data);
				break;
			case KEY_LEFT_ARROW:
				ret_goal = scan_box_on_goal
					(row, (column - 1), grid, data);
				break;
			case KEY_DOWN_ARROW:
				ret_goal = scan_box_on_goal((row + 1),
							    column, grid, data);
				break;
			case KEY_RIGHT_ARROW:
				ret_goal = scan_box_on_goal
					(row, (column + 1), grid, data);
				break;
			default:
				print_scr("undefined location\n");
				return FAILURE;
			}
		}

		if (ret_goal == 0) {
			bit_reset_set(&grid[row][column], MAN);
			return SUCCESS;
		}
	}

	return FAILURE;
}

static void push_at_dir(char grid[max_row][max_col], int dir,
			int *rows, int *columns)
{
	assert(rows != NULL);
	assert(columns != NULL);
	int row = *rows;
	int column = *columns;
	int ret = 0;

	switch (dir) {
	case KEY_UP_ARROW:
		ret = detect_obstacle(--(*rows), column, grid, KEY_UP_ARROW);
		break;
	case KEY_LEFT_ARROW:
		ret = detect_obstacle(row, --(*columns), grid, KEY_LEFT_ARROW);
		break;
	case KEY_DOWN_ARROW:
		ret = detect_obstacle(++(*rows), column, grid, KEY_DOWN_ARROW);
		break;
	case KEY_RIGHT_ARROW:
		ret = detect_obstacle(row, ++(*columns), grid, KEY_RIGHT_ARROW);
		break;
	default:
		print_scr("undefined location\n");
	}
	if (ret == 0) {
		bit_reset_set(&grid[row][column], FLOOR);
		return;
	}

	*rows = row;
	*columns = column;
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
	int ret_cmp = 0;
	char ref_grid[max_row][max_col];
	int arrow;
	int row = man_row;
	int column = man_col;

	bit_init(grid);
	grid_cpy(ref_grid, grid);

	while (1) {
		display(grid, grid_name);
		print_scr("Enter Arrow keys, 'r' to reset, 'q' to quit\n");

		while (get_input(&arrow) != 0) {
			if (tolower(arrow) == 'r') {
				row = man_row;
				column = man_col;
				grid_cpy(grid, ref_grid);
				display(grid, grid_name);
				print_scr("Arrow keys,'r'->reset,q->quit\n");
			} else if (tolower(arrow) == 'q') {
				return FAILURE;
			} else {
				display(grid, grid_name);
				print_scr("Error: invalid data enter again\n");
			}
		}
		push_at_dir(grid, arrow, &row, &column);
		ref_grid_comparator(grid, ref_grid);
		ret_cmp = locate_dot(grid);
		if (ret_cmp == 1) {
			display(grid, grid_name);
			break;
		}
	}
	return SUCCESS;
}
