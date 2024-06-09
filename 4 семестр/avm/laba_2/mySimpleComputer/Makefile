# Мейкфайл для создания библиотеки libmrc.a

# Компилятор
CC = gcc

# Флаги компиляции
CFLAGS = -Wall -Wextra -g

# Каталог для объектных файлов
OBJ_DIR = obj

# Объектные файлы
OBJECTS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(wildcard *.c))

# Цель по умолчанию
all: libmrc.a

# Правило компиляции файлов .c в объектные файлы
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Создание каталога для объектных файлов
$(OBJ_DIR):
	mkdir $(OBJ_DIR)

# Создание библиотеки
libmrc.a: $(OBJECTS)
	ar rcs $@ $^

# Очистка временных файлов
clean:
	rm -rf $(OBJ_DIR) libmrc.a
