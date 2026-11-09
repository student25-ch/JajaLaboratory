# Jajalaboratory Makefile
# Copyright (C) 2024 student25-ch - GPLv3

CC      = gcc
CFLAGS  = -Wall -Wextra -O2 -Iinclude -std=c11
LDFLAGS =
TARGET  = build/jajalab
SRCS    = src/main.c src/lab.c src/equipment.c src/substance.c src/reaction.c
OBJS    = $(SRCS:src/%.c=build/%.o)

.PHONY: all clean run install readme

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p build
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
	@echo "构建完成: $@"

build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

readme:
	@if [ -f gen_readme.sh ]; then ./gen_readme.sh .; else echo "gen_readme.sh 不存在"; fi

clean:
	rm -rf build

install: $(TARGET)
	install -m 755 $(TARGET) /usr/local/bin/jajalab

distclean: clean
