all: test myls

myls: myls.o
	gcc -o ./commands/myls ./build/myls.o

test: main.o getInput.o functions.o
	gcc -o ./bin/test ./build/main.o ./build/getInput.o ./build/functions.o

main.o: ./src/main.c ./inc/getInput.h ./inc/functions.h
	gcc -c ./src/main.c -o ./build/main.o -Wall

getInput.o: ./src/getInput.c
	gcc -c ./src/getInput.c -o ./build/getInput.o -Wall

functions.o: ./src/functions.c
	gcc -c ./src/functions.c -o ./build/functions.o -Wall

myls.o: ./commands/myls.c
	gcc -c ./commands/myls.c -o ./build/myls.o -w

clean:
	rm -rf ./build/*.o

proper: clean
	rm -rf ./bin/test ./commands/myls
