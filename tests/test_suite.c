#include <commons/string.h>
#include "test_suite.h"

t_log *logger;
int tests_corridos = 0;

int prueba_de_pruebas() {
    _assert(true);
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