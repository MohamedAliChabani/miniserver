#include "http_utils.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void generate_http_response(const char *filename, char *http_response)
{
    FILE *home_page = fopen("index.html", "rb");
    if (home_page != NULL) {
        char file_buffer[BUFFSIZE];
        fread(file_buffer, BUFFSIZE, 1, home_page);
        snprintf(http_response, BUFFSIZE, "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %zu\n\n%s", strlen(file_buffer), file_buffer);
        fclose(home_page);
    }
    else {
        strcpy(http_response, "HTTP/1.1 404 Not Found\n\nPage Not Found");
    }
}
