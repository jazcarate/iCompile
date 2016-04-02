#include "webProvider.h"

extern t_log *logger;

void provideStaticContent(int socket, t_provider provider){
    char* string = "holitas";
    size_t tamanio = strlen(string);
    log_trace(logger, "Enviando [%s]:%lu a %d", string, tamanio, socket);

    provider(socket, string, tamanio);
}

#define FILEMODE S_IRWXU | S_IRGRP | S_IROTH

void provideFileContent(int socket, t_provider provider) {
    int fd;
    struct stat st;
    char* data;
    char* archivo = "resrources/index.html";

    char cwd[1024];
    getcwd(cwd, 1024);
    log_debug(logger, "CWD: %s", cwd);


    if((fd = open(archivo, O_RDWR | O_APPEND | O_CREAT , FILEMODE)) < 0)
        log_error(logger, "%s | %s", "File Provider: open", strerror(errno));

    if(stat(archivo, &st) < 0)
        log_error(logger, "%s | %s", "File Provider: stat", strerror(errno));

    size_t tamanio = (size_t) st.st_size;
    if((data=mmap(NULL, tamanio, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
        log_error(logger, "%s | %s", "File Provider: mmap", strerror(errno));

    log_trace(logger, "Enviando el archivo [%s]:%lu a %d", archivo, tamanio, socket);

    provider(socket, data, tamanio);
}