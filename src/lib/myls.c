#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <limits.h>

int main(int argc,char *argv[])
{
	DIR *dirp;
	struct dirent *dptr;
	char *dir;
	struct stat st;
	char path[PATH_MAX];
	struct passwd *userInfo;
	struct group *groupInfo;
	struct tm *timeInfo;

	if (argc>2)
	{
		printf("usage: myls [dir]\n");
		return(-1);
	}
	if (argc==1) dir=".";
	else dir=argv[1];

	if (stat(dir,&st)==-1)
	{
		printf("error (%d) %s\n",errno,strerror(errno));
		return(-1);
	}
	if (!S_ISDIR(st.st_mode))
	{
		printf("%s doit être un répertoire\n",dir);
		return(-1);
	}

	if ((dirp=opendir(dir))==NULL)
	{
		printf("error (%d) %s\n",errno,strerror(errno));
		return(-1);
	}

	while ((dptr = readdir(dirp)))
	{
		if (dir[strlen(dir)-1]=='/') sprintf(path,"%s%s",dir,dptr->d_name);
		else sprintf(path,"%s/%s",dir,dptr->d_name);

		if (lstat(path,&st)==-1)
			printf("error (%d) %s\n",errno,strerror(errno));
		else
		{
			if ((st.st_mode & S_IFSOCK)==S_IFSOCK) printf("s");	// socket
			else if ((st.st_mode & S_IFLNK)==S_IFLNK) printf("l");	// symbolic link
			else if ((st.st_mode & S_IFREG)==S_IFREG) printf("-");	// regular file
			else if ((st.st_mode & S_IFBLK)==S_IFBLK) printf("b");	// block device
			else if ((st.st_mode & S_IFDIR)==S_IFDIR) printf("d");	// directory
			else if ((st.st_mode & S_IFCHR)==S_IFCHR) printf("c");	// character device
			else if ((st.st_mode & S_IFIFO)==S_IFIFO) printf("p");	// FIFO

			printf("%c",(st.st_mode & S_IRUSR)==S_IRUSR ? 'r' : '-');	// owner R
			printf("%c",(st.st_mode & S_IWUSR)==S_IWUSR ? 'w' : '-');	// owner W
			printf("%c",(st.st_mode & S_IXUSR)==S_IXUSR ? 'x' : '-');	// owner X
			printf("%c",(st.st_mode & S_IRGRP)==S_IRGRP ? 'r' : '-');	// group R
			printf("%c",(st.st_mode & S_IWGRP)==S_IWGRP ? 'w' : '-');	// group W
			printf("%c",(st.st_mode & S_IXGRP)==S_IXGRP ? 'x' : '-');	// group X
			printf("%c",(st.st_mode & S_IROTH)==S_IROTH ? 'r' : '-');	// other R
			printf("%c",(st.st_mode & S_IWOTH)==S_IWOTH ? 'w' : '-');	// other W
			printf("%c",(st.st_mode & S_IXOTH)==S_IXOTH ? 'x' : '-');	// other X

			printf(" %d",st.st_nlink);

			userInfo=getpwuid(st.st_uid);
			printf(" %s",userInfo->pw_name);

			groupInfo=getgrgid(st.st_gid);
			printf(" %s",groupInfo->gr_name);

			printf(" %8lld",st.st_size);

			timeInfo=localtime(&st.st_mtime);
			printf(" %4d-%02d-%02d %02d:%02d",timeInfo->tm_year+1900,timeInfo->tm_mon+1,timeInfo->tm_mday,timeInfo->tm_hour,timeInfo->tm_min);

			printf(" %s\n",dptr->d_name);
		}
	}
	closedir(dirp);

	return(0);
}
