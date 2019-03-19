#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "string.h"
#include "Client.h"
#define MSG_LEN 256
#define USERNAME_LEN 32
#define IP_LEN 16

// Globals
int clientSocket;
char username[USERNAME_LEN];





int main(){

    //Username input
    validInput(username);

    //Create client socket
    clientSocket = socket(AF_INET , SOCK_STREAM , 0);
    if (clientSocket == -1) {
        printf("Error fatal al crear el socket del cliente");
        exit(-1);
    }

    // Socket address set up
    struct sockaddr_in serverInfo;
    struct sockaddr_in clientInfo;

    int serverAddrLen = sizeof(serverInfo);
    int clientAddrLen = sizeof(clientInfo);

    //Make sure they don't contain garbage
    memset(&serverInfo, 0, serverAddrLen);
    memset(&clientInfo, 0, clientAddrLen);

    serverInfo.sin_addr.s_addr = inet_addr("10.0.2.15"); //TODO cambiar esto por el del .config
    serverInfo.sin_port = htons(9001);
    serverInfo.sin_family = AF_INET;


    // Connect to Server
    int connectStatus = connect(clientSocket, (struct sockaddr *)&serverInfo, serverAddrLen);
    if (connectStatus == -1) {
        printf("Error faltal al conectarse con el servidor\n");
        exit(-1);
    }

    //Send username to server
    send(clientSocket, username, USERNAME_LEN, 0);
    
    //Make a child process
    int pid = fork();

    if (pid == 0) {
        sendMessages(clientSocket);
    }

    else{
        reciveMessages(clientSocket);
    }
    	
    close(clientSocket);
    return 0;
}
