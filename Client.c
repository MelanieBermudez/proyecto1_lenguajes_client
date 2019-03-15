

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include "Client.h"

struct addrinfo* init(char* ipAddress,char* port,struct addrinfo hints,struct addrinfo *res){
	
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo(ipAddress, port, &hints, &res);
    return res;
}





