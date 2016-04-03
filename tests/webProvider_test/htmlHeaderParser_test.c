#include <htmlHeaderParser.h>
#include "htmlHeaderParser_test.h"

int si_llega_un_header_de_get_a_una_direccion_el_parser_lo_entiende() {
    char* testRequest = "GET / HTTP 1.1"
            "\nContent-type:'application/json'";

    t_HTMLAction action = getHTMLAction(testRequest);

    _assert(string_equals_ignore_case(action.direction, "/index.html"));
    _assert(action.method == HTMLMethod_GET);
    return 0;
}
