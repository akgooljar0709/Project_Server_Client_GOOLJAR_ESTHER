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



int main(int argc, char **argv)
{
    int socket_desc;
    struct sockaddr_in server_addr;
    char server_message[100], client_message[100];
    int choice;
    
    // Directory path to list files
    char path[100];
    unsigned char ip[]={0};
    
  
    
    // Clean buffers:
    memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));
    
    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    
    if(socket_desc < 0){
        printf("Unable to create socket\n");
        return -1;
    }
    
    printf("Socket created successfully\n");
    
    // Set port and IP the same as server-side:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);

    if (argv[1] == 0)
    {
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    }
    
    else {
        server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    }



   
    
    // Send connection request to server:
    if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        printf("Unable to connect\n");
        return -1;
    }





        printf("\nConnected with server successfully\n");
        printf("\n************************************\n");
        printf("\t\tSELECT A MODE\n");
        printf("\n1) Find a Specific Files in a The Server Directory\n");
        printf("\n2) List all Files from The Server Directory\n");
        printf("\n3) Remove a File from The Server Directory\n");
        printf("\n4) Exit the connection\n");
        printf("\n************************************\n");

        printf("\nSELECT 1/2/3/4\n");
        scanf("%d",&choice);


        if(choice == 1){
                // Get input from the user:
            printf("Enter directory pathway: ");
            scanf("%s",client_message);


             // Check if file exists or not
            if (isFileExistsAccess(client_message))
            {
                printf("File exists at path '%s'\n", client_message);
            }
            else
            {
                printf("File does not exists at path '%s'\n", client_message);
            }


        }





        if (choice == 2)
        {
                 // Input path from user
            printf("Enter path to list files: ");
            scanf("%s", client_message);

            listFiles(client_message);

            
        }

        if (choice == 3)
        {
                 // Input path from user
            printf("Enter path to remove files: ");
            scanf("%s", client_message);

            removeFiles(client_message);

            
        }

        


        
        // Send the message to server:
        if(send(socket_desc, client_message, strlen(client_message), 0) < 0){
            printf("Unable to send message\n");
            return -1;
        }
        
        // Receive the server's response:
        if(recv(socket_desc, server_message, sizeof(server_message), 0) < 0){
            printf("Error while receiving server's msg\n");
            return -1;
        }
        
        printf("Server's response: %s\n",server_message);


        
        // Close the socket:
        close(socket_desc);
        
    return 0;
}


