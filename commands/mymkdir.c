#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#define BUFFERSIZE 200
int executemkdir(int argc, char *argv[]);

int cd(char *pth){
    char path[BUFFERSIZE];
    strcpy(path,pth);

    char cwd[BUFFERSIZE];
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

#ifdef DYN
typedef struct SCmd SCmd;
typedef int (*pfunc)(int, char *[]);

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
    s = ModCmd(s, "mymkdir", &executemkdir);
    return s;
}
#endif

int executemkdir(int argc, char *argv[])
{
    int mode=0777,c;
    int m, p, v, i=1;
    char * pch;
    while((c=getopt(argc,argv,"m:pv")) != -1){
            switch(c){
            case 'm' :
                    i++;
                    sscanf(argv[i],"%o",&mode);
                    if(mode == 0){
                            printf("%s : Permissions invalides\n", argv[0]);
                            exit(1);
                    }
                    i++;
            break;
            case 'p' :
                    i++;
                    pch = strtok(argv[i],"/");
                    while(pch != NULL){
                            (mkdir(pch, (mode_t) mode));
                            cd(pch);
                            pch = strtok(NULL,"/");
                    }
            case 'v' :
                    v=1;
                    i++;
            case '?' :
            default :
                    printf("Usage : mkdir [-pv] [-m mode] directory... \n");
            }
    }

    if(mkdir(argv[i], (mode_t) mode)== -1) perror(argv[0]);
    else {
            if(v == 1){
                    printf("%s : Création du répertoire %s\n", argv[0],argv[i]);
            }
    }
    return 0;
}

#ifdef EXEC
int main(int argc, char *argv[]) {
    return executemkdir(argc, argv);
}
#endif
