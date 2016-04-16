NO_COLOR=\x1b[0m
OK_COLOR=\x1b[32;01m
ERROR_COLOR=\x1b[31;01m
WARN_COLOR=\x1b[33;01m

OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)
ERROR_STRING=$(ERROR_COLOR)[ERRORS]$(NO_COLOR)
WARN_STRING=$(WARN_COLOR)[WARNINGS]$(NO_COLOR)

CFLAGS=-DEXEC


all: clean proper myls mydu mypwd test

all-lib: clean proper myls mydu mypwd-lib-stat test-lib

mypwd-lib-stat:
	gcc -Wall -c -o ./build/mypwd.o ./commands/mypwd.c
	@echo "\033[33;32m\t✓ Mypwd-lib-stat: done."
	@ar crv ./lib/libmypwd.a build/mypwd.o

mypwd:
	gcc $(CFLAGS) -Wall -c -o ./build/mypwd.o ./commands/mypwd.c
	gcc $(CFLAGS) -o ./commands/mypwd ./build/mypwd.o
	@echo "\033[33;32m\t✓ Mypwd: done."

myls: myls.o
	gcc $(CFLAGS) -o ./commands/myls ./build/myls.o

myls-lib-stat: myls.o
	gcc -Wall -o ./commands/myls ./build/myls.o
	@echo "\033[33;32m\t✓ myls: done."

mydu: mydu.o
	gcc $(CFLAGS) -o ./commands/mydu ./build/mydu.o

test-lib: main-lib.o getInput-lib.o functions-lib.o socket-lib.o
	gcc -o ./bin/test ./build/main.o ./build/getInput.o ./build/functions.o -L./lib/ -lmypwd
	@echo "\033[33;32m\t✓ Build: done."
	@echo "\033[33;00m=== Compilation in debug mode\t\t\tDONkjn"

test: main.o getInput.o functions.o socket.o
	gcc $(CFLAGS) -o ./bin/test ./build/main.o ./build/getInput.o ./build/functions.o
	@echo "\033[33;32m\t✓ Build: done."
	@echo "\033[33;00m=== Compilation in debug mode\t\t\tDONkjn"

main.o: ./src/main.c ./inc/getInput.h ./inc/functions.h
	@mkdir -p build	
	gcc $(CFLAGS) -Wall -c ./src/main.c -o ./build/main.o
	#gcc -Wall -o ./build/main.o ./src/main.c -L. -lmypwd
	@echo "\033[33;32m\t✓ Build: main done."
	@echo "\033[33;00m"

main-lib.o: ./src/main.c ./inc/getInput.h ./inc/functions.h
	@mkdir -p build	
	gcc -Wall -c ./src/main.c -o ./build/main.o
	#gcc -Wall -o ./build/main.o ./src/main.c -L. -lmypwd
	@echo "\033[33;32m\t✓ Build: main done."
	@echo "\033[33;00m"

getInput.o: ./src/getInput.c
	gcc $(CFLAGS) -Wall -c ./src/getInput.c -o ./build/getInput.o
	@echo "\033[33;32m\t✓ Build: input done."
	@echo "\033[33;00m"

getInput-lib.o: ./src/getInput.c
	gcc -Wall -c ./src/getInput.c -o ./build/getInput.o
	@echo "\033[33;32m\t✓ Build: input done."
	@echo "\033[33;00m"

functions.o: ./src/functions.c
	gcc $(CFLAGS) -Wall -c ./src/functions.c -o ./build/functions.o
	@echo "\033[33;32m\t✓ Build: function done."
	@echo "\033[33;00m"

functions-lib.o: ./src/functions.c
	gcc -Wall -c ./src/functions.c -o ./build/functions.o
	@echo "\033[33;32m\t✓ Build: function done."
	@echo "\033[33;00m"

socket.o: ./src/socket.c
	gcc $(CFLAGS) -Wall -c ./src/socket.c -o ./build/socket.o
	@echo "\033[33;32m\t✓ Build: socket done."
	@echo "\033[33;00m"

socket-lib.o: ./src/socket.c
	gcc -Wall -c ./src/socket.c -o ./build/socket.o
	@echo "\033[33;32m\t✓ Build: socket done."
	@echo "\033[33;00m"

myls.o: ./commands/myls.c
	gcc -c ./commands/myls.c -o ./build/myls.o -w

myls2.o: ./commands/myls2.c
	gcc -c ./commands/myls2.c -o ./build/myls2.o -w

myls2: myls2.o
	gcc -o ./commands/myls2 ./build/myls2.o

mydu.o: ./commands/mydu.c
	gcc -c ./commands/mydu.c -o ./build/mydu.o -w



clean:
	rm -rf ./build/*.o

proper: clean
	rm -rf ./bin/test ./commands/myls ./commands/mydu ./commands/myls2
