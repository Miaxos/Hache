#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#include "mypwd.h"

#ifdef DYN
typedef struct SCmd SCmd;
typedef void (*pfunc)(int, char *[]);
SCmd* ModCmd(SCmd* scmd, char *nom, int (*pf)(int, char *[]));

SCmd* Init(SCmd* s){
	s = ModCmd(s, "mypwd", &executepwd);
	return s;
}
#endif


char NomRepertoire[1024];

int pwd()
{
	if (getcwd(NomRepertoire, sizeof(NomRepertoire)) != NULL)
		printf("%s\n", NomRepertoire);
	else
		perror("getcwd() error");
	return 0;
}

int executepwd(int argc, char *argv[])
{
	int c;
	if((c=getopt(argc, argv, ":LP")) != -1)
	{
		switch(c)
		{
			case 'L' :
				pwd();
			break;
			case 'P':
				pwd();
			break;
			default :
				printf("Usage : pwd [-L] [-P] \n");
		}
	}
	else
	{
		pwd();
	}
	return 0;
}

#ifdef EXEC
int main(int argc, char *argv[])
{
	return executepwd(argc, argv);
}
#endif