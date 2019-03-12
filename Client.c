#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "Client.h"

int main(){
    int net_socket;
    net_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int conection_status = connect(net_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    printf("%i\n", conection_status);

    //char mensaje[200] = "Hola soy dereck";
    //send(net_socket,mensaje,sizeof(mensaje),0);
	
    char server_response[256];

    recv(net_socket, &server_response, sizeof(server_response), 0);


    printf("The server sent %s\n", server_response);

    close(net_socket);

    return 0;
}