#_*_MakeFile_*_

PWD = /home/bernie/Desktop/C_Projects/ncurses_programs/programs_bernard_ncurses/
CC=gcc
LIB0=-lmenu
LIB1=-lpanel
LIB2=-lncurses
LIB3=-lm

CFLAGS = -c
LIBS = ${LIB0} ${LIB1} ${LIB2} ${LIB3}


calcu_lib_with_form: formula.o window_creation.o calcu_functions.o main.o
	${CC} formula.o window_creation.o calcu_functions.o main.o -o calc_col_with_form $(LIBS)

formula.o: formula.c 
	${CC} ${CFLAGS} formula.c -o formula.o $(LIBS)
	
window_creation.o: window_creation.c main_with_form.h
	${CC} ${CFLAGS} window_creation.c -o window_creation.o $(LIBS)

calcu_functions.o: calcu_functions.c main_with_form.h
	${CC} ${CFLAGS} calcu_functions.c -o calcu_functions.o $(LIBS)

main.o: calcu_lib_with_form.c main_with_form.h
	${CC} ${CFLAGS} calcu_lib_with_form.c -o main.o $(LIBS)
	
clean:
	rm *.o    

