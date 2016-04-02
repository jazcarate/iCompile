#include <commons/string.h>

#include "tests/test_suite.h"

t_log *logger;

int main(int argc, char **argv){
    if(argc > 1 && string_equals_ignore_case(argv[1], "-t")){
        return run_test_suite();
    }

    logger = log_create("log.txt", "iCompile", true, LOG_LEVEL_TRACE);
    char *port = (argc > 2 && NULL != argv[2]) ? argv[2] : "3333";

    serve(port, provideFileContent);
    return 0;
}

