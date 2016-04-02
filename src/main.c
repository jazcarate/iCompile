#include <stdlib.h>
#include <memory.h>
#include <commons/string.h>

#include "tests/test_suite.h"
#include "server/server.h"

int main(int argc, char **argv){
    if(argc > 1 && string_equals_ignore_case(argv[1], "-t")){
        return run_test_suite();
    }

    int port = (argc > 2 && NULL != argv[2]) ? atoi(argv[2]) : 333;

    return serve(port);
}

