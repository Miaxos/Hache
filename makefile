all: test myls mydu

myls: myls.o
	gcc -o ./commands/myls ./build/myls.o

mydu: mydu.o
	gcc -o ./commands/mydu ./build/mydu.o

test: main.o getInput.o functions.o socket.o
	gcc -o ./bin/test ./build/main.o ./build/getInput.o ./build/functions.o

main.o: ./src/main.c ./inc/getInput.h ./inc/functions.h
	gcc -Wall -c ./src/main.c -o ./build/main.o

getInput.o: ./src/getInput.c
	gcc -Wall -c ./src/getInput.c -o ./build/getInput.o

functions.o: ./src/functions.c
	gcc -Wall -c ./src/functions.c -o ./build/functions.o 

socket.o: ./src/socket.c
	gcc -Wall -c ./src/socket.c -o ./build/socket.o

myls.o: ./commands/myls.c
	gcc -c ./commands/myls.c -o ./build/myls.o -w

mydu.o: ./commands/mydu.c
	gcc -c ./commands/mydu.c -o ./build/mydu.o -w

clean:
	rm -rf ./build/*.o

proper: clean
	rm -rf ./bin/test ./commands/myls