

#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>

struct addrinfo* init(char*,char*,struct addrinfo ,struct addrinfo*);

#endif /* CLIENT_H */





