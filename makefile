CC = gcc
CFLAGS = -Wall -Werror
TARGET = mon_programme

all: $(TARGET)

$(TARGET): main.c image_process.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)
