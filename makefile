#_*_MakeFile_*_

#interest_calc: interest_calc
#    gcc interest_calc.c -o interest_calc -lncurses -lm

#calcuV2: calcuV2
#    gcc calcuV2.c -o calcuV2 -lncurses -lm

#calcuV3: calcuV3
#    gcc calcuV3.c -o calcuV3 -lncurses -lm

CC=gcc
LIB0=-lmenu
LIB1=-lpanel
LIB2=-lncurses
LIB3=-lm

calc_col: formula.o main.o
	${CC} formula.o main.o -o calc_col ${LIB0} ${LIB1} ${LIB2} ${LIB3}

formula.o: formula.c 
	${CC} -c formula.c -o formula.o ${LIB0} ${LIB1} ${LIB2} ${LIB3}

main.o: mainV5.c main2.h
	${CC} -c mainV5.c -o main.o ${LIB0} ${LIB1} ${LIB2} ${LIB3}

clean:
	rm *.o    

