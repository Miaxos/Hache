#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

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

int main(int argc,char *argv[])
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
