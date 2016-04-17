NO_COLOR=\x1b[0m
OK_COLOR=\x1b[32;01m
ERROR_COLOR=\x1b[31;01m
WARN_COLOR=\x1b[33;01m

OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)
ERROR_STRING=$(ERROR_COLOR)[ERRORS]$(NO_COLOR)
WARN_STRING=$(WARN_COLOR)[WARNINGS]$(NO_COLOR)

EXEC=Hache
CFLAGS=-DEXEC
LIBFLAG=-DLIB
DYNFLAG=-DDYN
hello: 
	@echo "\033[31;01m\t✕ make <all | all-lib | all-lib-dyn | cmd>"

all: clean proper init myls mydu mypwd mymkdir mycp mymv test

all-lib: clean proper init myls-lib-stat mydu-lib-stat mypwd-lib-stat mymkdir-lib-stat mycp-lib-stat mymv-lib-stat test-lib

all-lib-dyn: clean proper init myls-lib-dyn mydu-lib-dyn mypwd-lib-dyn mymkdir-lib-dyn mycp-lib-dyn mymv-lib-dyn test-dyn

cmd: clean proper init myls mydu mypwd mymkdir mycp mymv

init:
	@mkdir -p build	
	@mkdir -p lib

mypwd-lib-dyn:
	gcc $(DYNFLAG) -Wall -fPIC -c -o ./build/mypwd.o ./commands/mypwd.c
	gcc $(DYNFLAG) -v -shared -o ./lib/libmypwddyn.so ./build/mypwd.o
	@echo "\033[33;32m\t✓ Mypwd-lib-dyn: done."
	@echo "\033[33;00m"

mypwd-lib-stat:
	gcc $(LIBFLAG) -Wall -c -o ./build/mypwd.o ./commands/mypwd.c
	@echo "\033[33;32m\t✓ Mypwd-lib-stat: done."
	@echo "\033[33;00m"
	@ar crv ./lib/libmypwd.a build/mypwd.o

mypwd:
	gcc $(CFLAGS) -Wall -c -o ./build/mypwd.o ./commands/mypwd.c
	gcc $(CFLAGS) -o ./commands/mypwd ./build/mypwd.o
	@echo "\033[33;32m\t✓ Mypwd: done."
	@echo "\033[33;00m"

mymv-lib-dyn:
	gcc $(DYNFLAG) -Wall -fPIC -c -o ./build/mymv.o ./commands/mymv.c
	gcc $(DYNFLAG) -v -shared -o ./lib/libmymvdyn.so ./build/mymv.o
	@echo "\033[33;32m\t✓ Mymv-lib-dyn: done."
	@echo "\033[33;00m"

mymv-lib-stat:
	gcc $(LIBFLAG) -Wall -c -o ./build/mymv.o ./commands/mymv.c
	@echo "\033[33;32m\t✓ Mymv-lib-stat: done."
	@echo "\033[33;00m"
	@ar crv ./lib/libmymv.a build/mymv.o

mymv:
	gcc $(CFLAGS) -Wall -c -o ./build/mymv.o ./commands/mymv.c
	gcc $(CFLAGS) -o ./commands/mymv ./build/mymv.o
	@echo "\033[33;32m\t✓ Mymv: done."
	@echo "\033[33;00m"

mycp-lib-dyn:
	gcc $(DYNFLAG) -Wall -fPIC -c -o ./build/mycp.o ./commands/mycp.c
	gcc $(DYNFLAG) -v -shared -o ./lib/libmycpdyn.so ./build/mycp.o
	@echo "\033[33;32m\t✓ Mycp-lib-dyn: done."
	@echo "\033[33;00m"

mycp-lib-stat:
	gcc $(LIBFLAG) -Wall -c -o ./build/mycp.o ./commands/mycp.c
	@echo "\033[33;32m\t✓ Mycp-lib-stat: done."
	@echo "\033[33;00m"
	@ar crv ./lib/libmycp.a build/mycp.o

mycp:
	gcc $(CFLAGS) -Wall -c -o ./build/mycp.o ./commands/mycp.c
	gcc $(CFLAGS) -o ./commands/mycp ./build/mycp.o
	@echo "\033[33;32m\t✓ Mycp: done."
	@echo "\033[33;00m"

myls:
	gcc $(CFLAGS) -Wall -c ./commands/myls.c -o ./build/myls.o -w
	gcc $(CFLAGS) -o ./commands/myls ./build/myls.o
	@echo "\033[33;32m\t✓ myls: done."
	@echo "\033[33;00m"

myls-lib-stat:
	gcc $(LIBFLAG) -Wall -c -o ./build/myls.o ./commands/myls.c
	@echo "\033[33;32m\t✓ myls-lib-stat: done."
	@echo "\033[33;00m"
	@ar crv ./lib/libmyls.a build/myls.o

myls-lib-dyn:
	gcc $(DYNFLAG) -Wall -fPIC -c -o ./build/myls.o ./commands/myls.c
	gcc $(DYNFLAG) -v -shared -o ./lib/libmylsdyn.so ./build/myls.o
	@echo "\033[33;32m\t✓ Myls-lib-dyn: done."
	@echo "\033[33;00m"

mydu:
	gcc $(CFLAGS) -c ./commands/mydu.c -o ./build/mydu.o -w
	gcc $(CFLAGS) -o ./commands/mydu ./build/mydu.o
	@echo "\033[33;32m\t✓ mydu: done."
	@echo "\033[33;00m"

mydu-lib-stat:
	gcc $(LIBFLAG) -c ./commands/mydu.c -o ./build/mydu.o -w
	@echo "\033[33;32m\t✓ mydu-lib-stat: done."
	@echo "\033[33;00m"
	@ar crv ./lib/libmydu.a build/mydu.o

mydu-lib-dyn:
	gcc $(DYNFLAG) -Wall -fPIC -c -o ./build/mydu.o ./commands/mydu.c
	gcc $(DYNFLAG) -v -shared -o ./lib/libmydudyn.so ./build/mydu.o
	@echo "\033[33;32m\t✓ Mydu-lib-dyn: done."
	@echo "\033[33;00m"

mymkdir:
	gcc $(CFLAGS) -Wall -c ./commands/mymkdir.c -o ./build/mymkdir.o -w
	gcc $(CFLAGS) -o ./commands/mymkdir ./build/mymkdir.o
	@echo "\033[33;32m\t✓ mymkdir: done."
	@echo "\033[33;00m"

mymkdir-lib-stat:
	gcc $(LIBFLAG) -Wall -c ./commands/mymkdir.c -o ./build/mymkdir.o -w
	@echo "\033[33;32m\t✓ mymkdir-lib-stat: done."
	@echo "\033[33;00m"
	@ar crv ./lib/libmymkdir.a build/mymkdir.o

mymkdir-lib-dyn:
	gcc $(DYNFLAG) -Wall -fPIC -c -o ./build/mymkdir.o ./commands/mymkdir.c
	gcc $(DYNFLAG) -v -shared -o ./lib/libmymkdirdyn.so ./build/mymkdir.o
	@echo "\033[33;32m\t✓ Mymkdir-lib-dyn: done."
	@echo "\033[33;00m"

test-dyn: main-dyn.o getInput.o functions-lib.o
	gcc $(DYNFLAG) -o ./bin/$(EXEC) ./build/main.o ./build/getInput.o ./build/functions.o -ldl
	@echo "\033[33;32m\t✓ Build: done."
	@echo "\033[33;00m"
	@echo "\033[33;00m=== Compilation effectué en mode LIBRAIRIE DYNAMIQUE\t\t\tDone"


test-lib: main-lib.o getInput-lib.o functions-lib.o
	gcc $(LIBFLAG) -o ./bin/$(EXEC) ./build/main.o ./build/getInput.o ./build/functions.o -L./lib/ -lmypwd -lmyls -lmydu -lmymkdir -lmycp -lmymv
	@echo "\033[33;32m\t✓ Build: done."
	@echo "\033[33;00m"
	@echo "\033[33;00m=== Compilation effectué en mode LIBRAIRIE STATIQUE\t\t\tDone"

test: main.o getInput.o functions.o
	gcc $(CFLAGS) -o ./bin/$(EXEC) ./build/main.o ./build/getInput.o ./build/functions.o
	@echo "\033[33;32m\t✓ Build: done."
	@echo "\033[33;00m"
	@echo "\033[33;00m=== Compilation effectué en mode EXECUTABLE\t\t\tDone"

main.o: ./src/main.c ./inc/getInput.h ./inc/functions.h
	gcc $(CFLAGS) -Wall -c ./src/main.c -o ./build/main.o
	@echo "\033[33;32m\t✓ Build: main done."
	@echo "\033[33;00m"

main-lib.o: ./src/main.c ./inc/getInput.h ./inc/functions.h
	gcc $(LIBFLAG) -Wall -c ./src/main.c -o ./build/main.o
	@echo "\033[33;32m\t✓ Build: main-lib done."
	@echo "\033[33;00m"

main-dyn.o: ./src/main.c ./inc/getInput.h ./inc/functions.h
	gcc $(DYNFLAG) -Wall -c ./src/main.c -o ./build/main.o
	@echo "\033[33;32m\t✓ Build: main-dyn done."
	@echo "\033[33;00m"

getInput.o: ./src/getInput.c
	gcc $(CFLAGS) -Wall -c ./src/getInput.c -o ./build/getInput.o
	@echo "\033[33;32m\t✓ Build: input done."
	@echo "\033[33;00m"

getInput-lib.o: ./src/getInput.c
	gcc $(LIBFLAG) -Wall -c ./src/getInput.c -o ./build/getInput.o
	@echo "\033[33;32m\t✓ Build: input done."
	@echo "\033[33;00m"

functions.o: ./src/functions.c
	gcc $(CFLAGS) -Wall -c ./src/functions.c -o ./build/functions.o
	@echo "\033[33;32m\t✓ Build: function done."
	@echo "\033[33;00m"

functions-lib.o: ./src/functions.c
	gcc $(LIBFLAG) -Wall -c ./src/functions.c -o ./build/functions.o
	@echo "\033[33;32m\t✓ Build: function done."
	@echo "\033[33;00m"



clean:
	rm -rf ./build/*.o

proper: clean
	rm -rf ./bin/test ./commands/myls ./commands/mydu ./commands/myls2
