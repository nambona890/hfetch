CFLAGS ?= -O3 -march=native

hfetch: hfetch.c
	${CC} ${CFLAGS} $^ -o $@

clean:
	rm -f hfetch
