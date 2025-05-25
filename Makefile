CFLAGS ?= -O3

hfetch: jfetch.c
	${CC} ${CFLAGS} $^ -o $@

clean:
	rm -f jfetch
