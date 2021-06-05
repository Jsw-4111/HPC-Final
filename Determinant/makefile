CC		= gcc
CFLAGS	= -O -Wall -std=c99 -g -fopenmp -lm

FILE_C	= DetParallel.c
FILE_O	= DetParallel.o
FILE_EXE= DetParallel

LIBS	= readmat.c

EXECUTABLE	= ${FILE_EXE}
EXECUTABLES	= ${EXECUTABLE}

default:	  ${EXECUTABLES}

clean:
		rm -f ${EXECUTABLES} *.[oadD] *.[mM][oO][dD]

${FILE_EXE}:	${FILE_O}
				${CC} ${CFLAGS} -o ${FILE_EXE} ${FILE_O} ${LIBS}

${FILE_O}:		${FILE_C}
				${CC} ${CFLAGS} -c ${FILE_C}