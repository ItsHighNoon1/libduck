LIB_NAME = duck
VERSION_MAJOR = 1
VERSION_MINOR = 0
CFLAGS = -Wall -std=c99

DUCK_SRC = $(wildcard src/*.c)
DUCK_OBJ = $(patsubst src/%.c,obj/%.o,$(DUCK_SRC))
TEST_SRC = $(wildcard test/*.c)
TEST_BIN = $(patsubst test/%.c,bin/%.test,$(TEST_SRC))

bin/lib$(LIB_NAME).so.$(VERSION_MAJOR).$(VERSION_MINOR): $(DUCK_OBJ)
	@rm -f bin/$(LIB_NAME).so
	@rm -f bin/$(LIB_NAME).so.$(VERSION_MAJOR)
	gcc -shared -o $@ -Wl,-soname,lib$(LIB_NAME).so.$(VERSION_MAJOR) $^ 
	@ln -s lib$(LIB_NAME).so.$(VERSION_MAJOR).$(VERSION_MINOR) bin/lib$(LIB_NAME).so.$(VERSION_MAJOR)
	@ln -s lib$(LIB_NAME).so.$(VERSION_MAJOR) bin/lib$(LIB_NAME).so

test: $(TEST_BIN)
	@for test in $(TEST_BIN); do \
		LD_LIBRARY_PATH=bin ./$${test} || (echo "./$${test} failed with RC $$?"); \
	done;

obj/%.o: src/%.c
	gcc $(CFLAGS) -Iinclude -c $^ -o $@ -fvisibility=hidden

bin/%.test: test/%.c bin/lib$(LIB_NAME).so.$(VERSION_MAJOR).$(VERSION_MINOR)
	gcc $(CFLAGS) -Iinclude $< -o $@ -Lbin -l$(LIB_NAME)

clean:
	@rm -f bin/*
	@rm -f obj/*
	@echo Done
