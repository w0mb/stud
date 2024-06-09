CC = g++
CFLAGS = -std=c++11

SRC_DIR = src/cpp
HEADERS_DIR = src/headers
BUILD_DIR = build

OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/Country.o $(BUILD_DIR)/List.o  $(BUILD_DIR)/QuickSort.o $(BUILD_DIR)/Database.o $(BUILD_DIR)/Menu.o

all: your_program_name.exe

your_program_name.exe: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(HEADERS_DIR)/Country.h $(HEADERS_DIR)/List.h $(HEADERS_DIR)/SortAlgorithm.h $(HEADERS_DIR)/QuickSort.h $(HEADERS_DIR)/Database.h $(HEADERS_DIR)/Menu.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/Country.o: $(SRC_DIR)/Country.cpp $(HEADERS_DIR)/Country.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/List.o: $(SRC_DIR)/List.cpp $(HEADERS_DIR)/List.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/QuickSort.o: $(SRC_DIR)/QuickSort.cpp $(HEADERS_DIR)/QuickSort.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/Database.o: $(SRC_DIR)/Database.cpp $(HEADERS_DIR)/Database.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/Menu.o: $(SRC_DIR)/Menu.cpp $(HEADERS_DIR)/Menu.h $(HEADERS_DIR)/Database.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del your_program_name.exe $(BUILD_DIR)\*.o

