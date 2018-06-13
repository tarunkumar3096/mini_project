#include <limits.h> 

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

extern int max_row;
extern int max_col;

void get_row_column(FILE *fd, long *cur_pos, int *man_row1, int *man_col1);
void data_parsing(FILE *fd, char grid[][LINE_MAX], long cur_pos, char *grid_name);
void print_scr(char *display_msg);
void display(char grid[][LINE_MAX], char *grid_name);
int get_input(int *ret);
int push_operation(char grid[][LINE_MAX], char *grid_name, int man_row, int man_col);
