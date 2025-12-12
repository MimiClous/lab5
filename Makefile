CC = gcc

TARGET = app
SRCS = main.c database.c files.c menu.c
HEADERS = database.h files.h

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(CC)  -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET) *.o

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run