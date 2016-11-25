CC=gcc

CFLAGS=-Wall -W

PROG=lab1
OBJS= ${PROG}.o

.PHONY: clean

${PROG}: ${OBJS}
	${CC} -o $@ ${OBJS}

${PROG}.o: ${PROG}.c

.c.o:
	${CC} ${CFLAGS} -c $<

clean:
	rm -f *.o ${PROG}
