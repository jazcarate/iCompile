#include "server.h"

#ifdef SINGLE_THREAD
    #define FORKED_RUN(doer) doer
#else
    #define FORKED_RUN(doer) \
        if (!fork()) {\
            close(sockfd);\
            doer;\
            close(new_fd);\
            exit(0);\
        }
#endif

extern t_log *logger;

void *get_in_addr(struct sockaddr *sa){
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void provide(int socket, void* data, size_t size){
    log_trace(logger, "------------- Mandando[%3d] -------------", size);
    log_trace(logger, "%*.s", size, data);
    log_trace(logger, "------------- ------------- -------------");


    if (send(socket, data, size, 0) == -1)
        log_error(logger, "%s | %s", "send", strerror(errno));
}

void serve(char *port, void(*run)(int, t_provider)){
    int sockfd = 0, new_fd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, port, &hints, &servinfo)) != 0) {
        log_error(logger, "getaddrinfo: %s\n", gai_strerror(rv));
        abort();
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            log_error(logger, "%s | %s", "server: socker", strerror(errno));
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                       sizeof(int)) == -1) {
            log_error(logger, "%s | %s", "setsockopt", strerror(errno));
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            log_error(logger, "%s | %s", "server: bind", strerror(errno));
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL)  {
        log_error(logger, "server: failed to bind");
        exit(1);
    }

    if (listen(sockfd, 10) == -1) {
        log_error(logger, "%s | %s", "server: listen", strerror(errno));
        exit(1);
    }

    log_trace(logger, "server: esperando conexiones...");

    while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            log_error(logger, "%s | %s", "server: accept", strerror(errno));
            continue;
        }

        inet_ntop(their_addr.ss_family,
                  get_in_addr((struct sockaddr *)&their_addr),
                  s, sizeof s);
        log_trace(logger, "server: se conecto %s", s);

        FORKED_RUN(
                run(new_fd, provide);
        )

        close(new_fd);  // parent doesn't need this
    }
}