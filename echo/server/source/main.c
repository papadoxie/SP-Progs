#include <networking.h>

int main(void)
{
    int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sockfd < 0)
    {
        perror("Could not create socket");
        return EXIT_FAILURE;
    }

    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(SERVER_PORT),
        .sin_addr = {.s_addr = INADDR_ANY},
        .sin_zero = {0}};

    if (bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Could not bind socket");
        return EXIT_FAILURE;
    }
    
    if (listen(server_sockfd, MAX_CLIENTS) < 0)
    {
        perror("Could not listen on socket");
        return EXIT_FAILURE;
    }

    while(1)
    {
        fprintf(stderr, "Server Started\n");

        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof client_addr;
        int client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_sockfd)
        {
            fprintf(stderr, "Client connected\n");
            char buffer[1024];
            int n = read(client_sockfd, buffer, sizeof buffer);
            fprintf(stderr, "Received %d bytes: %s\n", n, buffer);
            n = write(client_sockfd, buffer, n);
            fprintf(stderr, "Sent %d bytes\n", n);
            close(client_sockfd);
            fprintf(stderr, "Client disconnected\n");
        }
    }

    return EXIT_SUCCESS;
}