#include <stdio.h>
#include <ncurses.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <sokoban.h>

extern int max_row;
extern int max_col;

void get_row_column(FILE *fd, long *cur_pos, int *man_row1, int *man_col1)
{
	char display_buff[LINE_MAX];
	char *ret;
	int rows = 0;
	int columns = 0;
	int check = 0;
	int i = 0;
	char *man_loc;

	*cur_pos = ftell(fd);	
	while (1) {
		ret = fgets(display_buff, sizeof(display_buff), fd);
		if (ret == NULL)
			break;
		
		if (display_buff[0] == ':')
			break;

		if (man_loc = strchr(ret, '@')) {       		
			*man_col1 = man_loc - ret;
			*man_row1 = rows;
		}
		
		check = strlen(display_buff);
		if (check > columns)
			columns = check;
		rows++;
		memset(display_buff, 0, sizeof(display_buff));
	}

	max_row = rows;
	max_col = columns + 2;
}

void data_parsing(FILE *fd, char grid[max_row][max_col], long cur_pos, char *grid_name)
{
	char *ret;
	int i = 0;
	int j = 0;
	
	fseek(fd, cur_pos, SEEK_SET);
	
	for (i = 0; i < max_row; i++) {
		ret = fgets(grid[i], max_col, fd);
		if (ret == NULL)
			break;
	}
	fgets(grid_name, LINE_MAX, fd);
}
