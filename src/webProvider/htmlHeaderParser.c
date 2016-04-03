#include "htmlHeaderParser.h"

extern t_log *logger;

t_HTMLAction getHTMLAction(char* HTMLRequest){
    log_trace(logger, "------------- Obtenido -------------");
    log_trace(logger, HTMLRequest);
    log_trace(logger, "------------- -------- -------------");

    char** header = string_split(HTMLRequest, " ");
    t_HTMLAction ret;


    if(string_starts_with(header[0], "GET")){
        ret.method = HTMLMethod_GET;
    if( string_equals_ignore_case(header[1], "/" ) )
        header[1] = string_duplicate("/index.html");
        log_trace(logger, "Tratando de acceder a: [%s]", header[1]+1);
        ret.direction = string_duplicate(header[1]);
    } else {
        exit(0);
    }
    return ret;
}

