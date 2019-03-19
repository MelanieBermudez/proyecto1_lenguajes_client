#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include "Client.h"

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
char *validInput(char *username){
    printf("Ingrese su nombre: ");
    if (fgets(username, USERNAME_LEN, stdin) != NULL) {
        char* c = strchr(username, '\n');
        *c = '\0';
        return username;
    }

    if (strlen(username) <= 0) {
        printf("\nEl usuario no ingresó un nombre. Cerrando el cliente\n");
        exit(-1);
    }
    
}




