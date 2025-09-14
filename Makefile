CFLAGS ?= -O3 -march=native
#CFLAGS ?= -g

hfetch: hfetch.c
	${CC} ${CFLAGS} $^ -o $@

clean:
	rm -f hfetch
