
#include <stdio.h>
#include <unistd.h>// close function
#include <fcntl.h> // open function
#include <netdb.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
#include <sys/stat.h>//For files search
#include <unistd.h>//For files search
#include <string.h>
#include <sys/types.h>//For list files
#include <dirent.h>//For list files
#include "../include/functions.h"

/**
 * Function to check whether a file exists or not.
 * It returns 1 if file exists at given path otherwise
 * returns 0.
 */
int isFileExists(const char *server_message)
{
    // Try to open file
    FILE *fptr = fopen(server_message, "r");

    // If file does not exists 
    if (fptr == NULL)
        return 0;

    // File exists hence close file and return true.
    fclose(fptr);

    return 1;
}



/**
 * Function to check whether a file exists or not using 
 * access() function. It returns 1 if file exists at 
 * given path otherwise returns 0.
 */
int isFileExistsAccess(const char *server_message)
{
    // Check for file existence
    if (access(server_message, F_OK) == -1)
        return 0;

    return 1;
}



/**
 * Function to check whether a file exists or not using
 * stat() function. It returns 1 if file exists at 
 * given path otherwise returns 0.
 */
int isFileExistsStats(const char *server_message)
{
    struct stat stats;

    stat(server_message, &stats);

    // Check for file existence
    if (stats.st_mode & F_OK)
        return 1;

    return 0;
}


//list files
void listFiles(const char *client_message)
{
    struct dirent *dp;
    DIR *dir = opendir(client_message);

    // Unable to open directory stream
    if (!dir){

         printf("Files Doesn't exists...Please Write the Exact pathway\n");
         return ;
    }

    while ((dp = readdir(dir)) != NULL)
    {
        printf("%s\n", dp->d_name);
    }

    // Close directory stream
    closedir(dir);
}


//remove file from the server
void removeFiles(const char *client_message)
{
    if (remove(client_message) == 0) {
        printf("The file is deleted successfully.");
    } else {
        printf("The file is not deleted or the file does not exists");
    }
}