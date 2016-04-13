int callFunction(char **, char *);
char* getFunctionName(const char *, char *);
int isFunction(const char *);
int len(const char *);
void inputTotab(const char *, char **inputTab);
int isDelimiter(char);
int parseCommande(const char *, char **);
int executerInput(char **tab, char *workingdirlib, pid_t child);
