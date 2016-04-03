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
    _verify(el_provider_estatico_devuelve_un_texto_estatico);
    _verify(el_provider_de_paginas_devuelve_el_contenido_de_el_index_html);

    _verify(si_llega_un_header_de_get_a_una_direccion_el_parser_lo_entiende);
    return 0;
}

int run_test_suite() {

    logger = log_create("test.log", "iCompileTest", false, LOG_LEVEL_WARNING);

    int result = todos_los_tests();
    if (result == 0)
        printf("\nOk");
    printf("\nTests corridos: %d", tests_corridos);

    return result != 0;
}