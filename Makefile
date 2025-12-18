CC = gcc
CFLAGS = #-DMINIZ_NO_EXPORT

TARGET = smu_zip_util
SRC = zip-util.c miniz/miniz/miniz.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)