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

void reciveMessages(int clientSocket) {
    char recvBuffer[MSG_LEN];
    while (1) {
        int recvStatus = recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
        if (recvStatus > 0) {
            printf("\r%s\n", recvBuffer);
        }

        else if (recvStatus < 0) {
            printf("Error fatal al recibir mensaje\n");
            exit(-1);
        }
    }
}
void sendMessages(int clientSocket) {
    char sendBuffer[MSG_LEN];
    while (1) {
	printf("Input: ");
        while (fgets(sendBuffer, MSG_LEN, stdin) != NULL) {

            if (strlen(sendBuffer) == 0) {
                continue;
            }

            else {
                break;
            }
        }

        send(clientSocket, sendBuffer, sizeof(sendBuffer), 0);
        if (strcmp(sendBuffer, "/quit") == 0) {
            break;
        }
    }
}
void validInput(char *username){
    printf("Ingrese su nombre: ");
    if (fgets(username, USERNAME_LEN, stdin) != NULL) {
        char* c = strchr(username, '\n');
        *c = '\0';
        
    }

    if (strlen(username) <= 0) {
        printf("\nEl usuario no ingresó un nombre. Cerrando el cliente\n");
        exit(-1);
    }
    
}

void createClient(int * clientSocket){
    *clientSocket = socket(AF_INET , SOCK_STREAM , 0);
    if (*clientSocket == -1) {
        printf("Error fatal al crear el socket del cliente");
        exit(-1);
    }
    
    
}

void initialize(struct sockaddr_in* serverInfo,struct sockaddr_in *clientInfo,int *serverAddrLen ,int *clientAddrLen){
    memset(serverInfo, 0, *serverAddrLen);
    memset(clientInfo, 0, *clientAddrLen);

    serverInfo->sin_addr.s_addr = inet_addr("10.0.2.15"); //TODO cambiar esto por el del .config
    serverInfo->sin_port = htons(9001);
    serverInfo->sin_family = AF_INET;
}

void connection(int clientSocket , struct sockaddr* serverInfo,int serverAddrLen, int connectStatus,char * username){
    connectStatus = connect(clientSocket,serverInfo, serverAddrLen);
    if (connectStatus == -1) {
        printf("Error falta al conectarse con el servidor\n");
        exit(-1);
    }

    //Send username to server
    send(clientSocket, username, USERNAME_LEN, 0);
}

int start(){
    //Initialize variables
    struct sockaddr_in serverInfo;
    struct sockaddr_in clientInfo;
    int serverAddrLen = sizeof(serverInfo);
    int clientAddrLen = sizeof(clientInfo);
    int connectStatus;
    
    //Username input
    validInput(username);

    //Create client socket
    createClient(&clientSocket);

    //Initialize client socket
    initialize(&serverInfo,&clientInfo,&serverAddrLen,&clientAddrLen);


    // Connect to Server
    connection(clientSocket,&serverInfo,serverAddrLen, connectStatus,username);
    
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


