CC = gcc
CFLAGS = -Wall -Wextra -pedantic

TARGET = email
SRC = email.c main.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -f $(TARGET)
