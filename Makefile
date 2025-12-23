CC = gcc
CFLAGS = -fsanitize=address

TARGET = zippy
SRC = zip-util2.c miniz/miniz/miniz.c helper.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)