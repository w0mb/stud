DIRS := mySimpleComputer myTerm console # myBigChars myReadKey simpleassebler simplebasic
DEPS = $(filter-out console/%, $(filter-out myTerm/%, $(foreach dir,$(DIRS),$(wildcard $(dir)/*.o)))) # $(filter-out console/*, )
CC := gcc
CCFLAGS := -I./include -Wall -Wextra -o
SOURCES := $(wildcard $(foreach dir,$(DIRS),$(dir)/*.c))
OBJECTS := $(SOURCES:.c=.o)

all: $(DIRS) complete.exe
#	cls
	@echo "Build complete!"

$(DIRS):
	@$(MAKE) -C $@
	
complete.exe: $(OBJECTS)
	$(CC) $(CCFLAGS) $@ $^ -LmySimpleComputer -lMySC -LmyTerm -lMyTerm

.PHONY: all $(DIRS) clean

clean:
	@for dir in $(DIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	rm -f complete.exe