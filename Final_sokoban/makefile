FLAGS = gcc -Wall
LN = -I. -lncurses
OBJ = main.o push.o data_parsing.o get_display.o

games:$(OBJ)
	$(FLAGS) -o games $^ $(LN)
%.o:%.c
	$(FLAGS) -c $< $(LN)

clean:
	rm games
	rm *.o

