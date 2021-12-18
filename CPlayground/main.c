#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/param.h>
#include <stdlib.h>

#include "request.h"

int main(int argc, const char * argv[]) {

    // a get request
    Request *request = malloc(sizeof(Request));
    Request_init(request);
    char *content = "PUT /users?id=1 HTTP/1.1\r\nContent-Type: application/json\r\nAccept: application/json\r\nContent-Length: 2\r\n\r\na";
    RequestParsingState state = Request_receive(request, content, strlen(content));
    state = Request_receive(request, "b", strlen("b"));
    Request_debug_print(request);
    return 0;
}
