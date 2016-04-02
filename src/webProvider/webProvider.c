#include "webProvider.h"

extern t_log *logger;

void provideStaticContent(int socket, t_provider provider){
    char* string = "holitas";
    size_t tamanio = strlen(string);
    log_trace(logger, "Enviando [%s]:%lu a %d", string, tamanio, socket);

    provider(socket, string, tamanio);
}