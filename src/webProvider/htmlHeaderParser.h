#ifndef ICOMPILE_HTMLHEADERPARSER_H
#define ICOMPILE_HTMLHEADERPARSER_H

#include <commons/string.h>
#include <commons/log.h>

#include <stdlib.h>

    typedef enum {
        HTMLMethod_GET
    } e_METHOD;

    typedef struct {
        char* direction;
        e_METHOD method;
    } t_HTMLAction;

    t_HTMLAction getHTMLAction(char* HTMLRequest);

#endif //ICOMPILE_HTMLHEADERPARSER_H
