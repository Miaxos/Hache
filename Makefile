# Config UNIX
MKDIR_P = mkdir -p


# Options de build
CC=gcc
CFLAGS=-W -Wall
LDFLAGS=
EXEC=main


# Chemin de dest
SRC_PROMPT=./src/prompt/
SRC_LIB=./src/lib/
DEST_BUILD=./build/
DEST_LIB=./lib/



# Builds
all: ${DEST_BUILD} ${DEST_LIB} main.o prompt.o callFunction.o myls.o
	gcc $(DEST_BUILD)main.o $(DEST_BUILD)prompt.o $(DEST_BUILD)callFunction.o -o $(EXEC)

	gcc $(DEST_BUILD)myls.o -o $(DEST_LIB)myls

clean:
	rm -rf $(DEST_BUILD)*.o
	rmdir $(DEST_BUILD)

proper:
	rm $(EXEC)
	rm -r $(DEST_LIB)

# Création du dossier de build
${DEST_BUILD}:
	${MKDIR_P} ${DEST_BUILD}

${DEST_LIB}:
	${MKDIR_P} ${DEST_LIB}

# Prompt
main.o: $(SRC_PROMPT)main.c
	gcc -c $(SRC_PROMPT)main.c -o $(DEST_BUILD)main.o

prompt.o: $(SRC_PROMPT)prompt.c
	gcc -c $(SRC_PROMPT)prompt.c -o $(DEST_BUILD)prompt.o

callFunction.o: $(SRC_PROMPT)callFunction.c
	gcc -c $(SRC_PROMPT)callFunction.c -o $(DEST_BUILD)callFunction.o

# Librairies

myls.o: $(SRC_LIB)myls.c
	gcc -c $(SRC_LIB)myls.c -o $(DEST_BUILD)myls.o



