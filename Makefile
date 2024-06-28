CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRCS = main.c StrList.c

HEADERS = StrList.h

TARGET = StrList

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
