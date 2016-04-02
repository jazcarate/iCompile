//
// Created by florius on 01/04/16.
//

#ifndef ICOMPILE_SERVER_H
#define ICOMPILE_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <commons/log.h>

typedef void (*t_provider )(int, void*, size_t);

void serve(char *port, void(*run)(int, t_provider ));

#endif //ICOMPILE_SERVER_H
