#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#if !defined AMIGA && !defined VMS && !defined WINDOWS32 \
    && !defined __MINGW32__
  #include <pwd.h>
  #include <grp.h>
#endif
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>


int main(int argc,char *argv[])
{

    DIR* rep = NULL;
    struct dirent* folder = NULL;
    char *dir;
    struct stat st;
    int singleColFormat, all, size,formatLong, lastAccess, sortByDate, inode, classify, noGroup, invertSort, showSize, ignoreBackups, almostAll;
    int opt;

    struct group *group;
    struct passwd *pwd;


    if(argc > 2){
        printf("ls \n");
        return(-1);
    }
    if(argc == 1){
        dir == '.';
    }else{
        dir = argv[1];
    }
    if (!S_ISDIR(st.st_mode))
        {
            printf("%s is not a directory\n",dir);
            return(-1);
        }

    if((rep=opendir(dir)) == NULL){
        printf("error\n");
        return(-1);
    }


    while((opt = getopt(argc, argc, "l1utiFR"))!= -1){
        switch(opt){
            case '1':
                singleColFormat = 1;
                break;
            case 'l':
                //type, permission
                formatLong = 1;
                break;
            case 'u':
                lastAccess = 1;
                break;
            case 't':
                sortByDate = 1;
                break;
            case 'i':
                inode == 1;
                break;
            case 'F':
                //parametre -F
                classify = 1;
                break;
            case 'G':
                noGroup =1;
                // ne pas afficher le groupe dans le format large ???

                break;
            case 'r' :
                invertSort = 1;
                break;
            case 'a' :
                all = 1;
                break;
            case 's':
                size = 1;
                break;
            case 'A' :
                almostAll = 1;
                break;
        }
    }


    while((folder = readdir(rep))){
        if(formatLong == 1){
            if(all != 1 && almostAll!= 1){
                if(folder->d_name[0] != '.'){
                    if(inode == 1){
                        printf("%s  ", folder->d_ino);
                    }
                    if(size == 1){
                        printf("%9jd   ", st.st_size);  //size
                    }

                         printf("%s  %4d  \n", st.st_mode, st.st_nlink); //permissions
                         if((pwd = getpwd(st.st_uid)) != NULL){ //propriétaire
                            printf("%-8.8s  ", pwd->pw_name);
                        }else{
                            printf("%-8s  ", st.st_uid);
                        }
                        if(noGroup != 1){
                          if((group = getgrrid(st.st_gid)) != NULL){ //group
                                printf("%-8.8s  ", group->gr_name);
                            }else{
                                printf("%-8s  ", st.st_gid);
                            }
                        }

                        time_t time = st.st_mtime;
                        struct tm tm = *localtime(&time);
                        char s[32];

                        strftime(s, sizeof s, "%d/%m/%Y %H:%M:%S", &tm);

                        printf("%-14s %s\n", folder->d_name, s); //date et h de modif
                        if(classify == 1){
                            if(S_ISLNK(st.st_mode)){
                                printf("%s@", folder->d_name);
                            }else if(S_FIFO(st.st_mode)){
                                printf("%s|", folder->d_name);
                            }else if(S_ISDIR(st.st_mode)){
                                printf("%s/", folder->d_name);
                            }else if(stat(folder, &st) == 0 && st.st_mode & S_IXUSR) {
                                printf("%s*", folder->d_name);
                            }
                        }else{
                            printf("%s\n", folder->d_name);
                        }
                    }

                }else if(almostAll == 1){
                    if(folder->d_name[0]!= '.' && folder->d_name[1] != '.' ){
                        if(inode == 1){
                            printf("%s  ", folder->d_ino);
                        }
                        if(size == 1){
                            printf("%9jd   ", st.st_size);  //size
                        }

                             printf("%s  %4d  \n", st.st_mode, st.st_nlink); //permissions
                             if((pwd = getpwd(st.st_uid)) != NULL){ //propriétaire
                                printf("%-8.8s  ", pwd->pw_name);
                            }else{
                                printf("%-8s  ", st.st_uid);
                            }
                            if(noGroup != 1){
                              if((group = getgrrid(st.st_gid)) != NULL){ //group
                                    printf("%-8.8s  ", group->gr_name);
                                }else{
                                    printf("%-8s  ", st.st_gid);
                                }
                            }

                            time_t time = st.st_mtime;
                            struct tm tm = *localtime(&time);
                            char s[32];
                            strftime(s, sizeof s, "%d/%m/%Y %H:%M:%S", &tm);
                            printf("%s", s);

                            if(classify == 1){
                                if(S_ISLNK(st.st_mode)){
                                    printf("%s@", folder->d_name);
                                }else if(S_FIFO(st.st_mode)){
                                    printf("%s|", folder->d_name);
                                }else if(S_ISDIR(st.st_mode)){
                                    printf("%s/", folder->d_name);
                                }else if(stat(folder, &st) == 0 && st.st_mode & S_IXUSR) {
                                    printf("%s*", folder->d_name);
                                }
                            }else{
                                printf("%s\n", folder->d_name);
                            }
                        }
                    }

                else if(all == 1){
                    if(inode == 1){
                        printf("%s  ", folder->d_ino);
                    }
                    if(size == 1){
                        printf("%9jd   ",st.st_size);  //size
                    }

                         printf("%s  %4d  \n", st.st_mode, st.st_nlink); //permissions
                         if((pwd = getpwd(st.st_uid)) != NULL){ //propriétaire
                            printf("%-8.8s  ", pwd->pw_name);
                        }else{
                            printf("%-8s  ", st.st_uid);
                        }
                        if(noGroup != 1){
                          if((group = getgrrid(st.st_gid)) != NULL){ //group
                                printf("%-8.8s  ", group->gr_name);
                            }else{
                                printf("%-8s  ", st.st_gid);
                            }
                        }

                        printf("%-14s" , folder->d_name); //date et h de modif
                        time_t time = st.st_mtime;
                        struct tm tm = *localtime(&time);
                        char s[32];
                        strftime(s, sizeof s, "%d/%m/%Y %H:%M:%S", &tm);
                        printf("%s", s);

                        if(classify == 1){
                            if(S_ISLNK(st.st_mode)){
                                printf("%s@", folder->d_name);
                            }else if(S_FIFO(st.st_mode)){
                                printf("%s|", folder->d_name);
                            }else if(S_ISDIR(st.st_mode)){
                                printf("%s/", folder->d_name);
                            }else if(stat(folder, &st) == 0 && st.st_mode & S_IXUSR) {
                                printf("%s*", folder->d_name);
                            }
                        }else{
                            printf("%s\n", folder->d_name);
                        }
            }

        }
        else if(singleColFormat == 1){
            if(inode == 1){
                printf("%s  ", folder->d_ino);
            }
            if(size == 1){
                printf("%9jd   ", st.st_size);  //size
            }
            if(classify == 1){
                if(S_ISLNK(st.st_mode)){
                    printf("%s@", folder->d_name);
                }else if(S_FIFO(st.st_mode)){
                    printf("%s|", folder->d_name);
                }else if(S_ISDIR(st.st_mode)){
                    printf("%s/", folder->d_name);
                }else if(stat(folder, &st) == 0 && st.st_mode & S_IXUSR) {
                    printf("%s*", folder->d_name);
                }
            }else{
                printf("%s\n", folder->d_name);
            }
        }

    }
}
