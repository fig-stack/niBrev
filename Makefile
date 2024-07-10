CC = gcc
CFLAGS = -g -O0 -Wall -Wextra -Werror -I./include

SRCS = src/main.c src/getHex.c src/getExports.c src/helpers.c
OBJS = $(SRCS:src/%.c=obj/%.o)

TARGET = nibrev

all: $(TARGET)

debug: CFLAGS += -DDEBUG
debug: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clear: clean
clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf obj

.PHONY: all clean clear debug
