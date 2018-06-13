#include <stdio.h>
#include <string.h>
#include <error.h>
#include <errno.h>

void stages_init(FILE *fd, int *row, int *col, int level)
{
	FILE *stream = fd;
	char display_buff[50][50];
	char *ret;
	int rows = 0;
	int columns = 0;
	int i = 0;
	int check = 0;

	while (1) {
		ret = fgets((display_buff[rows]),
			    sizeof(*display_buff), stream);
		if (ret == NULL)
			break;

		if (display_buff[rows][0] == ';')
			break;

		check = strlen(display_buff[rows]);
		columns = (check >= columns ? check : columns);
		rows++;
	}
	for (i = 0; i < rows; i++)
		printf("%s", display_buff[i]);

	*row = rows;
	*col = columns;
}

static int Contin(void)
{
	char choice;

	printf("\nu wanna enter next stage ?\nif so press 'y':");
	while (getchar() != '\n')
		;
	scanf("%c", &choice);
	if (choice == 'y')
		return 1;
	else
		return 0;
}


