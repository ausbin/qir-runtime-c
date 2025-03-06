CFLAGS = -Wall -Wextra -Wpedantic
CFILES = callables.c example.c
OFILES = $(patsubst %.c,%.o,$(CFILES))

.PHONY: clean

example: $(OFILES)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(wildcard *.o) example
