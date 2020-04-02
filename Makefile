#
# In order to execute this "Makefile" just type "make"
#	File generated thanks to https://www.nicomedes.assistedcoding.eu/#/app/makefilegen
#

OBJS	= main.o affichage.o fir.o iir.o integration.o lecture.o mesure.o fichiers.o
SOURCE	= main.c affichage.c fir.c iir.c integration.c lecture.c mesure.c fichiers.c
HEADER	= affichage.h define.h fir.h iir.h integration.h lecture.h mesure.h fichiers.h
OUT	= Pulse_Oximeter
CC	 = gcc
FLAGS	 = -g3 -c -Wall
LFLAGS	 =
# -g option enables debugging mode
# -c flag generates object code for separate files


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)


# create/compile the individual files >>separately<<
main.o: main.c
	$(CC) $(FLAGS) main.c -std=c99

affichage.o: affichage.c
	$(CC) $(FLAGS) affichage.c -std=c99

fir.o: fir.c
	$(CC) $(FLAGS) fir.c -std=c99

iir.o: iir.c
	$(CC) $(FLAGS) iir.c -std=c99

integration.o: integration.c
	$(CC) $(FLAGS) integration.c -std=c99

lecture.o: lecture.c
	$(CC) $(FLAGS) lecture.c -std=c99

mesure.o: mesure.c
	$(CC) $(FLAGS) mesure.c -std=c99

fichiers.o: fichiers.c
	$(CC) $(FLAGS) fichiers.c -std=c99


# clean house
clean:
	rm -f $(OBJS) $(OUT)

# run the program
run: $(OUT)
	./$(OUT)

# compile program with debugging information
debug: $(OUT)
	valgrind $(OUT)

# run program with valgrind for errors
valgrind: $(OUT)
	valgrind $(OUT)

# run program with valgrind for leak checks
valgrind_leakcheck: $(OUT)
	valgrind --leak-check=full $(OUT)

# run program with valgrind for leak checks (extreme)
valgrind_extreme: $(OUT)
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes $(OUT)