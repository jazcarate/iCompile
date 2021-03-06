#include "webProvider_test.h"

#define UN_SOCKET 5531

int el_provider_estatico_devuelve_un_texto_estatico() {
    int argumentoSocket = 0;
    char *argumentoData = NULL;
    size_t argumentoSize = 0;

    void provide_de_mentira(int socket, void* data, size_t size){
        argumentoSocket = socket;
        argumentoData = string_duplicate(data);
        argumentoSize = size;
    }

    provideStaticContent(UN_SOCKET, provide_de_mentira);

    _assert(string_equals_ignore_case(argumentoData, "holitas"));
    _assert(argumentoSize == 7);
    _assert(argumentoSocket == UN_SOCKET);
    return 0;
}

int el_provider_de_paginas_devuelve_el_contenido_de_el_index_html(){
    int argumentoSocket = 0;
    char *argumentoData = NULL;
    size_t argumentoSize = 0;

    void provide_de_mentira(int socket, void* data, size_t size){
        argumentoSocket = socket;
        argumentoData = string_duplicate(data);
        argumentoSize = size;
    }

    provideFileContent(UN_SOCKET, provide_de_mentira);

    _assert(string_starts_with(argumentoData, "<html>"));
    _assert(string_ends_with(argumentoData, "</html>"));
    _assert(argumentoSocket == UN_SOCKET);
    return 0;
}