#include "test_suite.h"

#define FAIL() printf("\nFallo en %s() line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define _verify(test) do { int r=test(); tests_corridos++; if(r) return r; } while(0)

int tests_corridos = 0;

int prueba_de_pruebas() {
    _assert(true);
    return 0;
}

int todos_los_tests() {
    _verify(prueba_de_pruebas);
    return 0;
}

int run_test_suite() {
    int result = todos_los_tests();
    if (result == 0)
        printf("Ok\n");
    printf("Tests corridos: %d\n", tests_corridos);

    return result != 0;
}