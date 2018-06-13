#ifndef SOKOBAN_H
#define SOKOBAN_H

#include <limits.h>
#include <ctype.h>

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

#define FAILURE 1
#define SUCCESS 0

#ifndef EXTERN
#define EXTERN
extern int max_row;
extern int max_col;
#endif

void get_row_column(FILE *fd, long *cur_pos, int *man_row1, int *man_col1);
void data_parsing(FILE *fd, char grid[][LINE_MAX], long cur_pos, char *grid_name);
void print_scr(char *display_msg);
void display(char grid[][LINE_MAX], char *grid_name);
int get_input(int *ret);
int push_operation(char grid[][LINE_MAX], char *grid_name, int man_row, int man_col);

#endif
