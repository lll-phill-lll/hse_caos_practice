TARGET = main

CC = gcc
CFLAGS = -std=c11

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

# Правило для очистки скомпилированных файлов
clean:
	rm -f $(TARGET)

