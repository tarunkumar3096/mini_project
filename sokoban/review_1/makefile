FLAGS = gcc -Wall
OBJ = -I. -lncurses

game:*.o
	$(FLAGS) -o game *.o $(OBJ)
%.o:*.c *.h
	$(FLAGS) -c *.c $(OBJ)

clean:
	rm game
	rm *.o

