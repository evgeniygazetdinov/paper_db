# makefile from sh script like clang -I include sources/main.c -o main.o && ./main.o
CC = clang
CFLAGS = -I include
TARGET = main.o
SOURCE = sources/main.c

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

clean:
	rm -f $(TARGET)

compile: $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean compile run


default:
	clang -I include sources/main.c -o main.o && ./main.o