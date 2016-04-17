#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>


#ifdef DYN
typedef struct SCmd SCmd;
typedef int (*pfunc)(int, char *[]);
int executemv(int argc, char *argv[]);
struct SCmd
{
    char name[20];
    char *nom;
    pfunc pf;
};

SCmd* ModCmd(SCmd* scmd, char *nom, int (*pf)(int, char *[]));
SCmd* Init(SCmd* s);

SCmd* ModCmd(SCmd* scmd, char *nom, int (*pf)(int, char *[]))
{
    scmd->nom = scmd->name;
    strcpy(scmd->nom, nom);
    scmd->pf = pf;

    return scmd;
}

SCmd* Init(SCmd* s){
    s = ModCmd(s, "mymv", &executemv);
    return s;
}
#endif

int mv(char  *oldP, char *newP)
{
	struct stat statDir;
	int SameFileSystem = 1;
	int errorMv;
	stat(newP, &statDir);
	if((SameFileSystem)  && S_ISDIR(statDir.st_mode) )
	{
		printf("%s \n",oldP);
		printf("%s \n",newP);
		errorMv = rename(oldP, newP);
		printf("%d \n", errorMv);
	}
	else
	{
		perror("mv() error");
	}
	return 0;
}

int executemv(int argc, char *argv[])
{
	char *oldpath;
	char *newpath;
	int c;
	int iflag = 0, fflag = 0;
	if(argc - optind == 2)
	{
		oldpath = argv[argc-2];
		newpath = argv[argc-1];

		//printf("%s \n", oldpath); //VALEUR DE OLDPATH (pointeur)
		//printf("%p \n", &oldpath); //ADRESSE DE OLDPATH (pointeur de pointeur)
		//printf("%s \n", newpath); //VALEUR DE NEWPATH
		//printf("%p \n", &newpath); //ADRESSE DE NEWPATH
	
		while((c=getopt(argc, argv, "fi")) != -1)
		{
			switch(c)
			{
				case 'i' :
					iflag = 1;
				break;
				case 'f' :
					fflag = 1;
				break;
				default :
					printf("Usage : mv [OPTION] SOURCE DEST \n");
				break;
			}
		}
		mv(oldpath, newpath);
	}
	return 0;
}

#ifdef EXEC
int main(int argc,char *argv[])
{
	return executemv(argc, argv);
}
#endif
