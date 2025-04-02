CC = g++
CFLAGS = -std=c++11 -Wall
LDFLAGS = -lpthread

TARGET = testThread
SRC = testThread.cc

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(TARGET)
