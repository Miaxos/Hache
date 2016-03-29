#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>

unsigned int RepSize(char *file);

int main(int argc,char *argv[])
{
	unsigned int size;
	int i;

	if (argc==1) size=RepSize(".");
	else
	{
		size=0;
		for (i=1;i<argc;i++)
			size+=RepSize(argv[i]);
	}

	printf("Taille : %u\n",size);

	return(0);
}

unsigned int RepSize(char *file)
{
	struct stat st;
	char path[PATH_MAX];
	unsigned int size;
	DIR *dirp;
	struct dirent *dptr;

	if (lstat(file,&st)==-1)
	{
		fprintf(stderr,"error (%d) %s\n",errno,strerror(errno));
		return(0);
	}
	size=st.st_size;

	if (S_ISDIR(st.st_mode))
	{
		if ((dirp=opendir(file))==NULL)
			fprintf(stderr,"error (%d) %s\n",errno,strerror(errno));
		else
		{
			while (dptr=readdir(dirp))
			{
				if (!strcmp(dptr->d_name,".") || !strcmp(dptr->d_name,"..")) continue;

				if (file[strlen(file)-1]=='/') sprintf(path,"%s%s",file,dptr->d_name);
				else sprintf(path,"%s/%s",file,dptr->d_name);

				size+=RepSize(path);
			}
			closedir(dirp);
		}
	}

	return(size);
}

