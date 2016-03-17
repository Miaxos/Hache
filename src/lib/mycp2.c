#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <utime.h>
#include <limits.h>

#define BUFLEN 65535

void copy(char *src,char *dst);

int main(int argc,char *argv[])
{
	if (argc<3)
	{
		printf("usage: mycp src dst\n");
		return(-1);
	}
	copy(argv[1],argv[2]);

	return(0);
}

void copy(char *src,char *dst)
{
	struct stat st1,st2;
	char path[PATH_MAX],path2[PATH_MAX],*srcFile;
	unsigned int size;
	DIR *dirp;
	struct dirent *dptr;
	int fd1,fd2,i;
	char buf[BUFLEN];
	struct utimbuf times;

	printf("Copie \"%s\" -> \"%s\"\n",src,dst);

	if (lstat(src,&st1)==-1)
	{
		fprintf(stderr,"Impossible d'ouvrir le fichier \"%s\" (%d) %s\n",src,errno,strerror(errno));
		return;
	}
	if (!S_ISDIR(st1.st_mode))
	{
		// On ne copie que les fichiers réguliers
		if ((st1.st_mode & S_IFREG)==S_IFREG)
		{
			fd1=open(src,O_RDONLY);
			if (fd1==-1)
			{
				printf("Impossible d'ouvrir le fichier source \"%s\" (%d: %s)\n",src,errno,strerror(errno));
				return;
			}

			// Si la destination est un répertoire, on crée un nouveau fichier dans ce répertoire
			if ((lstat(dst,&st2)!=-1) && (S_ISDIR(st2.st_mode)))
			{
				// Extraction du nom de fichier à copier
				i=strlen(src);
				while ((i>0) && (src[i]!='/')) i--;
				if (src[i]=='/') srcFile=&src[i+1];
				else srcFile=&src[i];

				if (dst[strlen(dst)-1]=='/') sprintf(path,"%s%s",dst,srcFile);
				else sprintf(path,"%s/%s",dst,srcFile);
			}
			else strcpy(path,dst);

			// Création du nouveau fichier
			fd2=open(path,O_WRONLY | O_CREAT | O_EXCL);
			if (fd2==-1)
			{
				fprintf(stderr,"Erreur d'accès au fichier \"%s\" (%d: %s) -> copie impossible\n",path,errno,strerror(errno));
				close(fd1);
				return;
			}

			// Copie du fichier
			while ((i=read(fd1,buf,BUFLEN))!=0)
			{
				if (write(fd2,buf,i)==-1)
				{
					close(fd1);
					close(fd2);
					return;
				}
			}

			close(fd1);

			// Préservation des propriétaires (user/group) -> pas de contrôle d'erreur, ne marche que si root !
			fchown(fd2,st1.st_uid,st1.st_gid);

			// Préservation des droits
			if (fchmod(fd2,st1.st_mode)==-1)
			{
				fprintf(stderr,"Erreur de changement de droits sur \"%s\" (%d: %s)\n",path,errno,strerror(errno));
			}
			close(fd2);

			// Préservation des horodatages
			times.actime=st1.st_atime;
			times.modtime=st1.st_mtime;
			if (utime(path,&times)==-1)
			{
				fprintf(stderr,"Erreur de changement de temps sur \"%s\" (%d: %s)\n",path,errno,strerror(errno));
			}
		}
	}
	else
	{
		// Si la destination n'existe pas, on crée un nouveau répertoire
		if (lstat(dst,&st2)==-1)
		{
			if (mkdir(dst,st1.st_mode)==-1)
			{
				fprintf(stderr,"Erreur de création du répertoire \"%s\" (%d: %s) -> copie impossible\n",dst,errno,strerror(errno));
				return;
			}
			chown(dst,st1.st_uid,st1.st_gid);
		}
		else if (!S_ISDIR(st2.st_mode))
		{
			fprintf(stderr,"La destination \"%s\" existe et n'est pas un répertoire -> copie impossible\n",dst);
			return;
		}

		if((dirp=opendir(src))==NULL)
		{
			fprintf(stderr,"Erreur d'ouverture du répertoire \"%s\" (%d: %s)\n",src,errno,strerror(errno));
			return;
		}

		while (dptr=readdir(dirp))
		{
			if (!strcmp(dptr->d_name,".") || !strcmp(dptr->d_name,"..")) continue;

			if (src[strlen(src)-1]=='/') sprintf(path,"%s%s",src,dptr->d_name);
			else sprintf(path,"%s/%s",src,dptr->d_name);
			if (dst[strlen(dst)-1]=='/') sprintf(path2,"%s%s",dst,dptr->d_name);
			else sprintf(path2,"%s/%s",dst,dptr->d_name);

			copy(path,path2);
		}
		closedir(dirp);
	}
}
