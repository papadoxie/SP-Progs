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

    while (1)
    {
        fprintf(stderr, "Server Started\n");

        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof client_addr;
        int client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_sockfd)
        {
            fprintf(stderr, "Client connected\n");
            fprintf(stderr, "Client IP: %s\n", inet_ntoa(client_addr.sin_addr));
            fprintf(stderr, "Client Port: %d\n", ntohs(client_addr.sin_port));

            while (1)
            {
                char buffer[1024];
                memset(buffer, 0, sizeof(buffer));

                int n = recv(client_sockfd, buffer, sizeof buffer, 0);
                buffer[n] = '\0';
                fprintf(stderr, "Received %d bytes: %s\n", n, buffer);

                FILE *file = fopen(buffer, "rb");
                if (file)
                {
                    char file_buffer[1 << 14];
                    memset(file_buffer, 0, sizeof(file_buffer));

                    while (1)
                    {
                        ssize_t n = fread(file_buffer, 1, sizeof file_buffer, file);
                        if (n <= 0)
                        {
                            break;
                        }
                        send(client_sockfd, file_buffer, n, 0);
                        memset(file_buffer, 0, sizeof(file_buffer));
                    }
                    fclose(file);
                }
                else
                {
                    fprintf(stderr, "File not found: %s\n", buffer);
                }
                break;
            }
            close(client_sockfd);
            fprintf(stderr, "Client disconnected\n");
        }
    }

    return EXIT_SUCCESS;
}