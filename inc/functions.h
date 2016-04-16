typedef struct SCmd SCmd;
typedef int (*pfunc)(int, char *[]);
char* GetName(SCmd* scmd);
SCmd* AddCmd();
SCmd* ModCmd(SCmd *scmd, char *nom, int (*pf)(int, char *[]));
pfunc GetFunction(SCmd* scmd);



int callFunction(int argc, char **, char *, SCmd* tabcommandes[]);
char* getFunctionName(const char *, char *);
int isFunction(const char *);
int len(const char *);
int inputTotab(const char *, char **inputTab);
int isDelimiter(char);
int parseCommande(const char *, char **);
int executerInput(char **tab, char *workingdirlib, pid_t child, SCmd* tabcommandes[]);
