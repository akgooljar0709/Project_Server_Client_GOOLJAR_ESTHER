#ifndef DEF_FUNCTIONS
#define DEF_FUNCTIONS


int isFileExists(const char *server_message);//For files search
int isFileExistsAccess(const char *server_message);//For files search
int isFileExistsStats(const char *server_message);//For files search
void listFiles(const char *client_message);
void removeFiles(const char *client_message);

#endif
