CC=gcc

CFLAGS=-Wall -W

PROG=lab3
OBJS=${PROG}.o

.PHONY: clean

${PROG}: ${OBJS}
	${CC} -o $@ ${OBJS}

${PROG}.o: ${PROG}.c

.c.o:
	${CC} ${CFLAGS} -c $<

clean:
	rm -f *.o ${PROG}
