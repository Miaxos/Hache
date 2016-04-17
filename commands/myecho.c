#include <sys/types.h>
#include <sys/uio.h>

#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


char *newStr (char *charBuffer) {
  char *str;
  if (strlen(charBuffer) == 0)
    str = charBuffer;
  else
    str = charBuffer + 1;
  return str;
}

void divise(char *ch){
	char * pch,*pcd;
    int i=0,j;
    char *tmp= (char *) malloc(100);  
	strcpy(tmp,ch);

    pcd = strtok(ch,"\\");
	while(pcd != NULL){
        i++;
        pcd = strtok(NULL,"\\");
    }
	int tmp_i = i;
    
    pch = strtok(tmp,"\\");

		printf("\n%s",pch);
    while(pch != NULL){
        pch = strtok(NULL,"\\");
		printf("\n%s",pch);
        i--;
    }
	for(j=0;j<tmp_i-1;j++){
		chdir("..");
	}
	free(tmp);
}
int main(int argc, char *argv[]){
	int nflag,backsl,default_,notrailingnewline;
	char space[] = " ";
	char newline[] = "\n";
	int i =1;
	char *progname = argv[0];
	char option;
	 while ((option = getopt(argc, argv,"neE")) != -1) {
		switch (option) {
		     case 'e' : backsl = 1;
				i++;
		        break;
		     case 'n' : notrailingnewline = 1;			
				i++;
		        break;
		     case 'E' : default_ = 1;//default
				i++;
		        break;

		     default:  
		         exit(EXIT_FAILURE);
		}
	 }
	if(argc == 2) default_ =1;
	char *pos;
	if(backsl == 1){
		int count = 0,j;
		char* pTemp =argv[i];
		char* ptemp_tmp= (char *) malloc(100);
		 
		char * pch,*pcd;
		char *tmp= (char *) malloc(100);  
		strcpy(tmp,argv[i]);

		pcd = strtok(argv[i],"\\");
		while(pcd != NULL){
		    j++;
		    pcd = strtok(NULL,"\\");
		}
		
		pch = strtok(tmp,"\\");
		while(pch != NULL){
			if(j == 1) break;
			if(pch[0] == 'n'){
				pch = pch+1;
				printf("\n%s",pch);
			}else if(pch[0] == 'e'){
				pch = pch+1;
				printf("%d%s",0x0a,pch);
			}else if(pch[0] == 'b'){
				pch = pch+1;
				printf("\b%s",pch);
			}else if(pch[0] == 't'){
				pch = pch+1;
				printf("\t%s",pch);
			}else if(pch[0] == 'v'){
				pch = pch+1;
				printf("\v%s",pch);
			}else if(pch[0] == 'r'){
				pch = pch+1;
				printf("\r%s",pch);
			}else if(pch[0] == 'f'){
				pch = pch+1;
				printf("\f%s",pch);
			}else if(pch[0] == '\\'){
				pch = pch+1;
				printf("\\%s",pch);
			}else{
				printf("%s",pch);			
			}
		    pch = strtok(NULL,"\\");
		    j--;
		}
		printf("\n");
		free(tmp);
	
		if(notrailingnewline == 1){
			int len = strlen(argv[i]);
			char *last_two = &argv[i][len-2];
			if (strcmp(last_two,"\n"));
				*last_two = '\0';	
			//printf("%s\n",argv[i]);
		}else{
			//printf("%s\n",argv[i]);
		}
		
	}
	if(default_ == 1){
		printf("%s\n",argv[i]);	
	}
}