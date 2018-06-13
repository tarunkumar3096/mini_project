#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio_ext.h>
#include <time.h>

#define SIZE 3

static void get_input(char *user_guess)
{
	char buf[SIZE];
	char *retp;
	int i = 0;

	while (1) {
		i = 0;
		printf("enter the letter: ");
		retp = fgets(buf, sizeof(buf), stdin);
		if (retp == NULL || *retp == '\n') {
			printf("Error: invalid input\n");
			continue;
		}
		if (buf[strlen(buf) - 1] != '\n') {
			__fpurge(stdin);
			printf("invalid input\n");
			continue;
		}
		*user_guess = buf[0];
		if (buf[0] == 'w' || buf[0] == 'a'
		    || buf[0] == 'd' || buf[0] == 's')
			break;
		printf("Error: invalid inputs\n");
	}
}

int main(void) {
	char user_guess;
	char grid[][] = {{   ####},
			 {####  ##},
			 {#   $  #},
			 {#  *** #},
			 {#  . . ##},
			 {## * *  #},
			 { ##***  #},
			 {  # $ ###},
			 {  # @ #},
			 {  #####}};
	
	get_input(&user_guess);
	printf("input validation success\n");
	move();
	return 0;
}
