CC = gcc
CFLAGS = #-DMINIZ_NO_EXPORT

TARGET = zippy
SRC = zip-util.c miniz/miniz/miniz.c helper.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)