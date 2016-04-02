#ifndef ICOMPILE_WEBPROVIDER_H
#define ICOMPILE_WEBPROVIDER_H

#include "../server/server.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<sys/mman.h>
#include<fcntl.h>
#include <commons/log.h>

void provideStaticContent(int socket, t_provider provider);
void provideFileContent(int socket, t_provider provider);

#endif //ICOMPILE_WEBPROVIDER_H
