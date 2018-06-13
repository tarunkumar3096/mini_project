#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ncurses.h>
//#include <sokoban.h>

#define FAILURE 1
#define SUCCESS 0
#define KEY_UP_ARROW 1
#define KEY_LEFT_ARROW 2
#define KEY_DOWN_ARROW 3
#define KEY_RIGHT_ARROW 4

#define MAN 1
#define WALL (1 << 1)
#define BOX (1 << 2)
#define BOX_ON_GOAL (1 << 3)
#define GOAL (1 << 4)
#define MAN_ON_GOAL (1 << 5)
#define FLOOR (1 << 6)

extern int max_row;
extern int max_col;


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

static void ref_grid_comparator(char grid[max_row][max_col], char ref_grid[max_row][max_col])
{
	int i = 0;
	int j = 0;

	for (i = 0; i < max_row; i++) {
		for (j = 0; grid[i][j] != '\n'; j++) {
			if ((ref_grid[i][j] & GOAL) || (ref_grid[i][j] & BOX_ON_GOAL)) {
				if (grid[i][j] & FLOOR)
					bit_reset_set(&grid[i][j], GOAL);
			}

			if ((grid[i][j] & BOX_ON_GOAL) && (ref_grid[i][j] & FLOOR))
				bit_reset_set(&grid[i][j], BOX);
			
			if (grid[i][j] & MAN) {
				if ((ref_grid[i][j] & BOX_ON_GOAL) || (ref_grid[i][j] & GOAL))
					bit_reset_set(&grid[i][j], MAN_ON_GOAL);
			}			
		}
	}
}
	
static int scan_box_on_goal(int row, int column, char grid[max_row][max_col], int data)
{
	if ((grid[row][column] & FLOOR) || (grid[row][column] & GOAL)) {
		if ((grid[row][column] & GOAL) && (data & BOX))
			bit_reset_set(&grid[row][column], BOX_ON_GOAL);
		else
			bit_reset_set(&grid[row][column], data);
		return 0;
	}

	return 1;
}

static int detect_obstacle(int row, int column, char grid[max_row][max_col], char dir)
{
	char data = grid[row][column];
	int ret_goal = 0;
	
	if ((data & FLOOR) || (data & GOAL)) {		
		bit_reset_set(&grid[row][column], MAN);		
		return 0;
	} else if (!(data & GOAL) && !(data & WALL)) {		
		if ((data & BOX_ON_GOAL) || (data & BOX)) {

			switch (dir) {
			case KEY_UP_ARROW:
				ret_goal = scan_box_on_goal((row - 1), column, grid, data);
				break;
			case KEY_LEFT_ARROW:
				ret_goal = scan_box_on_goal(row, (column - 1), grid, data);
				break;
			case KEY_DOWN_ARROW:
				ret_goal = scan_box_on_goal((row + 1), column, grid, data);
				break;
			case KEY_RIGHT_ARROW:
				ret_goal = scan_box_on_goal(row, (column + 1), grid, data);
				break;
			default:
				print_scr("undefined location\n");
				return 1;
			}
		}
		
		if (ret_goal == 0) {
			bit_reset_set(&grid[row][column], MAN);
			return 0;
		}
	}
	
	return 1;
}

static void push_at_dir(char grid[max_row][max_col], int dir, int *rows, int *columns)	
{
	assert(rows != NULL);
	assert(columns != NULL);	
	int row = *rows;
	int column = *columns;
	int ret = 0;
	
	switch (dir) {
	case KEY_UP_ARROW:
		ret = detect_obstacle((row - 1), column, grid, KEY_UP_ARROW);
		*rows = *rows - 1; 
		break;
	case KEY_LEFT_ARROW:
		ret = detect_obstacle(row, (column - 1), grid, KEY_LEFT_ARROW);
		*columns = *columns - 1;
		break;
	case KEY_DOWN_ARROW:
		ret = detect_obstacle((row + 1), column, grid, KEY_DOWN_ARROW);
		*rows = *rows + 1;
		break;
	case KEY_RIGHT_ARROW:
		ret = detect_obstacle(row, (column + 1), grid, KEY_RIGHT_ARROW);
		*columns = *columns + 1;
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


static void grid_cpy(char dst_grid[max_row][max_col], char scr_grid[max_row][max_col])
{
	int i = 0;

	for (i = 0; i < max_row; i++)
		strcpy(dst_grid[i], scr_grid[i]);
}


int push_operation(char grid[max_row][max_col], char *grid_name, int man_row, int man_col)
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
		print_scr("1) Enter Arrow keys\n");
		print_scr("2) 'r' to Reset\n");
		print_scr("3) 'q' to Quit\n");
		
		while (get_input(&arrow) != 0) {
			if (tolower(arrow) == 'r') {
				row = man_row;
				column = man_col;
				grid_cpy(grid, ref_grid);
				display(grid, grid_name);
			} else if (tolower(arrow) == 'q') {
				return 1;
			} else {
				print_scr("Invalid data\n");
			}
			print_scr("Enter arrow keys\n");	
		}
		push_at_dir(grid, arrow, &row, &column);
		ref_grid_comparator(grid, ref_grid);
		ret_cmp = locate_dot(grid);
		if (ret_cmp == 1) {
			display(grid, grid_name);
			print_scr("task completed\n");
			break;
		}
	}
	return 0;
}
		
	
	
