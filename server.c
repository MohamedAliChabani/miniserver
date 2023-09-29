#include "server.h"
#include "http_utils.h"

int sockfd;

void exit_at_ctrl_c(int sig)
{
    // Closing the server socket
    if (close(sockfd) < 0)
        handle_error("Could not close communication");
    exit(EXIT_SUCCESS);
}

void init_server()
{
    struct sockaddr_in server_info = {0};
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(PORT);

    socklen_t server_info_len = sizeof(server_info);

    // Creating the socket
    sockfd = socket(AF_INET, SOCK_STREAM,0);
    if (sockfd < 0)
        handle_error("Could not create socket");
    
    // Binding the socket to an addr and a port
    if (bind(sockfd, (struct sockaddr *) &server_info, server_info_len) < 0)
        handle_error("Could not bind the communication to an address and port");

    // Listening for incoming connections
    if (listen(sockfd, 5) < 0)
        handle_error("Could not accept communication requests");
}

int main(void)
{
    init_server();

    struct sockaddr_in client_info = {0};
    socklen_t client_info_len = sizeof(client_info);

    while (1) {
        // Accepting connections
        printf("Waiting for connections\n");

        int clientfd = accept(sockfd, (struct sockaddr *) &client_info, &client_info_len);
        if (clientfd < 0)
            handle_error("Could not accept communication");

        // Reading message
        char http_request[BUFFSIZE];
        if (recv(clientfd, (void *)http_request, BUFFSIZE, 0) < 0)
            handle_error("Could not read request");
        printf("HTTP Request:\n%s\n", http_request);

        // Sending message
        char http_response[BUFFSIZE];
        generate_http_response("index.html", http_response);

        if (send(clientfd, (void *) http_response, strlen(http_response), 0) < 0)
            handle_error("Could not send response");
        printf("Response sent successfully\n\n");

        // Closing the client socket
        close(clientfd);

        printf("---------------------------------------------\n");
    }


    return EXIT_SUCCESS;
}
