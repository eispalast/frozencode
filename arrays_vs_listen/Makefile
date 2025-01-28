NAME		:= listen
OBJFILES	:= build/listen.o 
CFLAGS		:= -Wall -g
CC			:= clang

build/$(NAME): $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $^

run: build/$(NAME)
	./build/$(NAME)

clean:
	rm -f build/* 
