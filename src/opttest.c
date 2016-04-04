/*
 * Utilisation de optarg():
 * un programme qui reconnait trois options, a, b et c dont 
 * l'option c attend un argument. 
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int errflg = 1; 
int cflag = 0;

int main(int argc , char ** argv){

  void usage();
  int c; 
  char *carg;
  extern char * optarg; 
  extern int optind, opterr; 
  char * progname = argv[0];

  while ((c = getopt(argc , argv, "abc:")) != -1)
    switch (c) {
    case 'a':
      puts("option a");
      break;
    case 'b':
      puts("option b");
      break;
    case 'c':
      cflag++;
      puts("option c");
      carg = optarg;
      break;
    case '?':
      errflg++;
      break;
    }
  if (errflg)
    usage(progname);
  if(cflag)    
    printf("%s\n", carg); 
}      

void usage(char *prog) {
  
  fprintf(stderr, "usage: %s [-ab] [-c arg]\n", prog);
  exit(1);
}