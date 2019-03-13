
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>

int main(){
    struct addrinfo hints, *res;
    int sockfd;
    int a = 0;

	// first, load up address structs with getaddrinfo():
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo("10.0.2.15", "9000", &hints, &res);


    char username[32];

    printf("Ingrese su nombre: \0");
    scanf("%[^\n]%*c", &username);

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    int conection_status = connect(sockfd, res->ai_addr, res->ai_addrlen);

    send(sockfd, &username, sizeof (username), 0);

    int quit = 0;
    while(quit == 0){

    	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	    int conection_status = connect(sockfd, res->ai_addr, res->ai_addrlen);

	    if(conection_status == 0){
		    char server_response[256];

		    printf("\033[0;36m");
		    printf("Esciba su mensaje: \0");

		    printf("\033[0m");

		    scanf("%[^\n]%*c", &server_response);


		    send(sockfd, &server_response, sizeof(server_response), 0);

		    if(strcasecmp(server_response, "/quit") != 0){
		    	recv(sockfd, &server_response, sizeof(server_response), 0);

		    	printf("El servidor envia: %s\n\n", server_response);
		    }

		    else{
	    		quit = 1;
		    }

	    }

	    else{
		    printf("La conexion no puede ser establecida");
		    quit = 1;
	    }

	}

    close(sockfd);

    return 0;
}
