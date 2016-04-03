#include "webProvider.h"

extern t_log *logger;

void provideStaticContent(int socket, t_provider provider){
    char* string = "holitas";
    size_t tamanio = strlen(string);
    log_trace(logger, "Enviando [%s]:%lu a %d", string, tamanio, socket);

    provider(socket, string, tamanio);
}

#define FILEMODE S_IRWXU | S_IRGRP | S_IROTH
void* mapFile(char* path, size_t* tamanio){
    int fd;
    struct stat st;
    char* data;
    char* archivo = path;

    char cwd[1024];
    getcwd(cwd, 1024);
    log_debug(logger, "CWD: %s", cwd);


    if((fd = open(archivo, O_RDWR | O_APPEND | O_CREAT , FILEMODE)) < 0)
        log_error(logger, "%s | %s", "File Provider: open", strerror(errno));

    if(stat(archivo, &st) < 0)
        log_error(logger, "%s | %s", "File Provider: stat", strerror(errno));

    *tamanio = (size_t) st.st_size;
    if((data=mmap(NULL, *tamanio, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
        log_error(logger, "%s | %s", "File Provider: mmap", strerror(errno));

    return data;
}


void provideFileContent(int socket, t_provider provider) {

    char *archivo = "resrources/index.html";
    size_t tamanio = 0;
    void *data = mapFile(archivo, &tamanio);
    log_trace(logger, "Enviando el archivo [%s]:%lu a %d", archivo, tamanio, socket);

    provider(socket, data, tamanio);
}

void provideFileContentAware(int socket, t_provider provider) {
    int buff_size = 40;
    char buf[buff_size];
    ssize_t recved;

    if((recved = recv(socket, buf, buff_size, 0)) < 0){
        log_error(logger, "%s | %s", "File Provider: recv", strerror(errno));
    }

    t_HTMLAction action = getHTMLAction(buf);

    if( action.method == HTMLMethod_GET ){
        char *archivo = string_from_format("resrources%s", action.direction );
        size_t tamanio = 0;
        void *data = mapFile(archivo, &tamanio);

        if(data == NULL){
            data = "404, no se encontro";
        }
        log_trace(logger, "Enviando el archivo [%s]:%lu a %d", archivo, tamanio, socket);

        provider(socket, data, tamanio);
    }


}