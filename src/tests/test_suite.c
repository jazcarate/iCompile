#include <commons/string.h>
#include "test_suite.h"

#define FAIL() printf("\nFallo en %s() line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define _verify(test) do { int r=test(); tests_corridos++; if(r) return r; } while(0)

t_log *logger;
int tests_corridos = 0;

int prueba_de_pruebas() {
    _assert(true);
    return 0;
}

#define UN_SOCKET 5531

int servirEstatico(){
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

int todos_los_tests() {
    _verify(prueba_de_pruebas);
    _verify(servirEstatico);
    return 0;
}

int run_test_suite() {

    logger = log_create("test.log", "iCompileTest", false, LOG_LEVEL_WARNING);

    int result = todos_los_tests();
    if (result == 0)
        printf("Ok\n");
    printf("Tests corridos: %d\n", tests_corridos);

    return result != 0;
}