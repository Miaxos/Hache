#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


#define BUFFSIZE 4096
#define CP 0644

int executecp(int argc, char*argv[]);
int cd(char *pth);

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
#ifdef EXEC
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
#endif

void createSubDir(char *dest){
        char * pch,*pcd;
    int i=0,j;
    char *tmpdest= (char *) malloc(100);
        strcpy(tmpdest,dest);

    pcd = strtok(dest,"/");
        while(pcd != NULL){
        i++;
        pcd = strtok(NULL,"/");
    }
        int tmp_i = i;

    pch = strtok(tmpdest,"/");
    while(pch != NULL){
        if(i == 1) break;
        (mkdir(pch,0777));
        chdir(pch);
        pch = strtok(NULL,"/");
        i--;
    }

        for(j=0;j<tmp_i-1;j++){
                chdir("..");
        }
        free(tmpdest);
}

int is_regular_file(char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int copyf(char *src, char *dest){
        char * pcd,*pcs,*chr;
    int srcFD, destFD, nread, nwrite;

        char *cwd = strcat(getcwd(0,0),"/");
    char *dirv = strcat(cwd,src);
        if(!is_regular_file(src)){
        chdir("..");
        }
        printf("\nsrc : %s\n",src);

    srcFD = open(src, O_RDONLY);
    char buffer[BUFFSIZE];
    char *tmpdest= (char *) malloc(100);
    char *tmpdest_= (char *) malloc(100);
    char *quotPtr;
        strcpy(tmpdest_,dest);
        strcpy(tmpdest,dest);

        int i = 0;
    pcd = strtok(tmpdest,"/");
        while(pcd != NULL){
        i++;
        pcd = strtok(NULL,"/");
    }

        if(i>2) createSubDir(tmpdest_);
    if(srcFD == -1){
        printf("Error, cannot open %s : %s\n",src, strerror(errno));
        exit(1);
    }
    destFD = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if(destFD = creat(dest,CP) == -1){
            printf("Error, cannot create %s : %s\n", dest,strerror(errno));
               exit(1);
    }
        while((nread = read(srcFD, buffer, BUFFSIZE)) > 0)
        {
                 write(destFD, buffer, nread);
        }

    if(nread == -1){
        printf("Error : enable to read data from %s:%s\n",src,strerror(errno));
        exit(1);
    }
    if(close(srcFD) == -1){
        printf("Error : enable to close files %s :%s\n",src,strerror(errno));
        exit(1);
    }

    if(close(destFD) == -1){
        printf("Error : enable to close files %s:%s\n",dest,strerror(errno));
        exit(1);
    }

        free(tmpdest);
        free(tmpdest_);
    return 1;
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
    struct stat file_stat;

    if((dirpt = opendir(src)) == NULL){
        printf("Enable to open %s \n",src);
        return 0;
    }
    else{

    char * pcs;
    char *filename;
         chdir(src);
         while( (dirp = readdir(dirpt)))
           {
                  chdir(src);
            if(stat(dirp->d_name,&file_stat) == -1){
                perror("stat");
                exit(EXIT_FAILURE);
               }
              if(is_regular_file(dirp->d_name))
              {
                 strcat(tmpdst, dirp->d_name);
                 strcat(tmpsrc, dirp->d_name);
                 copyf(tmpsrc, tmpdst);
                 strcpy(tmpdst, dest);
                 strcpy(tmpsrc, src);
              }
      }
        closedir(dirpt);
        return 1;
    }
}


int executecp(int argc, char*argv[])
{
    if( argc < 3){
        printf("Usage : %s source destination\n", argv[0]);
        exit(1);
    }
    if(argc==3){
        char *source = argv[1];
        char *dest = argv[2];
        int i;
        if(source[0] != '/' && dest[0] != '/'){
                        call_getcwd();
                        printf("copy simple files\n");
                    copyf(source, dest);
        }else if(source[0] == '/' && dest[0] == '/'){
            for(i =0; i<strlen(dest); i++){
                dest[i] = dest[i+1];
            }
            for(i =0; i<strlen(source); i++){
                source[i] = source[i+1];
            }
            copyd(source,dest);
        }else if(source[0] != '/' && dest[0] =='/'){
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
    return 0;
}
#ifdef EXEC
int main(int argc, char *argv[]){
    return executecp(argc, argv);
}
#endif
