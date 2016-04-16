#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


#define BUFFSIZE 1024
#define CP 0644

static void call_getcwd ()
{
    char * cwd;
    cwd = getcwd (0, 0);
    if (! cwd) {
	fprintf (stderr, "getcwd failed: %s\n", strerror (errno));
    } else {
	printf ("%s\n", cwd);

	printf ("\n");
	free (cwd);
    }
}

int cd(char *pth){
    char path[BUFFSIZE];
    strcpy(path,pth);

    char cwd[BUFFSIZE];
    if(pth[0] != '/')
    {
        getcwd(cwd,sizeof(cwd));
        strcat(cwd,"/");
        strcat(cwd,path);
        chdir(cwd);
    }else{
        chdir(pth);
    }

    return 0;
}


int copyf(char *src, char *dest){

    char * pch;
	char * pcs;
    printf("in funct copyf");
	call_getcwd();
    int srcFD, destFD, nread, nwrite;
    srcFD = open(src, O_RDONLY );
    char buffer[BUFFSIZE];

	char *tmpdest= (char *) malloc(100);
	char *quotPtr;
	int i=0;
	strcpy(tmpdest,dest);
	pcs = strtok(tmpdest,"/");
	while(pcs != NULL){
		i++;
        pcs = strtok(NULL,"/");
	}
	printf(" i = %d",i);
	printf("\ndest is %s\n", dest);
	quotPtr= strchr(dest, '/');
	if(quotPtr == NULL)
	{
	}
	else if (i > 2){
	pch = strtok(dest,"/");
       while(pch != NULL){
			if(i > 2){
			(mkdir(pch,0777));
            chdir(pch);
			call_getcwd();
			printf("%s !!!!!!!!!\n",dest);
            pch = strtok(NULL,"/");

			i--;
			}

         }
	}

    if(srcFD == -1){
        printf("Error, cannot open src %s : %s\n",src, strerror(errno));
        exit(1);
    }
    destFD = open(dest, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR |
S_IRGRP | S_IWGRP |S_IROTH | S_IWOTH);
	if(destFD = creat(dest,CP) == -1){

        printf("Error, cannot jjjcreate %s : %s\n", dest,strerror(errno));
        exit(1);
	}
    while((nread = read(srcFD,buffer, BUFFSIZE)) > 0){
        if(write(destFD,buffer,nread) != nread){
            printf("\n Error : enable to write data to %s\n", dest);
			exit(1);
        }
    }
	printf(" nread %d\n",nread);
    if(nread == -1){
        printf("Error : enable to read data from %s :%s\n ",src,strerror(errno));
		exit(1);
    }
    if(close(srcFD) == -1){
        printf("Error : enable to close files %s : %s\n",src,strerror(errno));
		exit(1);
    }


    return 1;
}


int is_regular_file(char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}


int copyd(char *src, char *dest){
    DIR *dirpt = NULL;
    struct dirent *dirp;
	   char tmpdst[strlen(dest)+1];
    char tmpsrc[strlen(src)+1];
    strcat(dest, "/");
    strcat(src, "/");
    strcpy(tmpdst, dest);
    strcpy(tmpsrc, src);
    printf("in funct copyd\n");

	printf("dest : %s\n", dest);
		call_getcwd();
    struct stat file_stat;

    if((dirpt = opendir(src)) == NULL){
        printf("Enable to open %s \n",src);
        return 0;
    }
    else{
	char *filename;
	 while( (dirp = readdir(dirpt)))
	                                                                                                                                                                 {
		chdir(src);
		//call_getcwd();
		if(stat(dirp->d_name,&file_stat) == -1){
			printf("%s ",dirp->d_name);
               perror("stat");
               exit(EXIT_FAILURE);
		}
	      if(is_regular_file(dirp->d_name))
	      {

          strcat(tmpdst, dirp->d_name);
          strcat(tmpsrc, dirp->d_name);
		chdir("..");

          copyf(tmpsrc, tmpdst);
          strcpy(tmpdst, dest);
          strcpy(tmpsrc, src);
	      }
      }
        closedir(dirpt);
        return 1;
    }
}

int main(int argc, char *argv[]){
    if( argc < 3){
        printf("Usage : %s source destination\n", argv[0]);
        exit(1);
    }
    if(argc==3){
        char *source = argv[1];
        char *dest = argv[2];
	int i;
        if(source[0] != '/' && dest[0] != '/'){
			printf("Copying files\n ");
            copyf(source, dest);
        }else if(source[0] == '/' && dest[0] == '/'){
			printf("Copying directories\n ");
            for(i =0; i<strlen(dest); i++){
                dest[i] = dest[i+1];
            }
            for(i =0; i<strlen(source); i++){
                source[i] = source[i+1];
            }
			printf("src %s, dest %s\n", source, dest);
            copyd(source,dest);
        }else if(source[0] != '/' && dest[0] =='/'){
			printf("Copying files\n ");
            for(i =0; i<strlen(dest); i++){
                dest[i] = dest[i+1];
            }
            strcat(dest,"/");
            strcat(dest,source);
            copyf(source,dest);
        }else{
            printf("Usage : %s source destination\n", argv[0]);
            exit(1);
        }
    }
}
