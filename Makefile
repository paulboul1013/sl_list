CFLAGS=-Wall -Wextra -Werror

SOURCES=main.c st.c
OBJECTS=$(SOURCES:.c=.o)

all: $(OBJECTS)
	gcc $(CFLAGS) -o main $(OBJECTS)

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<

clean:
	rm -f main $(OBJECTS)