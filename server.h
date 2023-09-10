#ifndef SERVER_H_
#define SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#define handle_error(msg) \
   do {fprintf(stderr, "%s: %s\n", (msg), strerror(errno)); exit(EXIT_FAILURE); } while (0)

#define PORT 9090
#define BUFFSIZE 30000

#endif // SERVER_H_
