# Мейкфайл для компиляции исполняемого файла pr01.exe в папке console

# Компилятор
CC = gcc

# Флаги компиляции
CFLAGS = -Wall -Wextra -g

# Папка для объектных файлов
OBJ_DIR = obj

# Исходные файлы
SOURCES = pr01.c io.c

# Объектные файлы
OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

# Путь к библиотеке
LIB_PATH = ../mySimpleComputer/

# Имя библиотеки
LIB_NAME = mrc

# Включение библиотеки
LIB = -L$(LIB_PATH) -l$(LIB_NAME)

# Цель по умолчанию
all: pr01.exe

# Компиляция файлов
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Создание папки для объектных файлов
$(OBJ_DIR):
	mkdir $(OBJ_DIR)

# Создание исполняемого файла
pr01.exe: $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(LIB) -o $@

# Очистка временных файлов
clean:
	del /q $(OBJ_DIR)\*.o
	del /q pr01.exe
	rmdir /q $(OBJ_DIR)
