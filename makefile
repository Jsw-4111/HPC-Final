CC		= gcc
CFLAGS	= -O -Wall -std=c99 -g 

FILE_C	= DetSerial.c
FILE_O	= DetSerial.o
FILE_EXE= DetSerial

LIBS	= -fopenmp readmat.c -lm

EXECUTABLE	= ${FILE_EXE}
EXECUTABLES	= ${EXECUTABLE}

default:	  ${EXECUTABLES}

clean:
		rm -f ${EXECUTABLES} *.[oadD] *.[mM][oO][dD]

${FILE_EXE}:	${FILE_O}
				${CC} ${CFLAGS} -o ${FILE_EXE} ${FILE_O} ${LIBS}

${FILE_O}:		${FILE_C}
				${CC} ${CFLAGS} -c ${FILE_C}