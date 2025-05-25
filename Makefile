CFLAGS ?= -O3

hfetch: hfetch.c
	${CC} ${CFLAGS} $^ -o $@

clean:
	rm -f hfetch
