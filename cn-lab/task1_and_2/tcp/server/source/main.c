#include <networking.h>
#include <aes.h>

int main(void)
{
    // Initialize AES
    struct AES_ctx ctx;
    uint8_t key[] = "0123456789abcdef";
    AES_init_ctx(&ctx, key);

    // Create new TCP Socket
    int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sockfd < 0)
    {
        perror("Could not create socket");
        return EXIT_FAILURE;
    }

    // Set socket options
    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(SERVER_PORT),
        .sin_addr = {.s_addr = INADDR_ANY},
        .sin_zero = {0}};

    // Bind socket to port
    if (bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Could not bind socket");
        return EXIT_FAILURE;
    }

    // Listen for connections
    if (listen(server_sockfd, MAX_CLIENTS) < 0)
    {
        perror("Could not listen on socket");
        return EXIT_FAILURE;
    }

    // Accept connections
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
                char buffer[AES_BLOCKLEN];
                memset(buffer, 0, AES_BLOCKLEN);

                int n = recv(client_sockfd, buffer, AES_BLOCKLEN, 0);
                fprintf(stderr, "Received %d bytes:", n);
                fwrite(buffer, 1, AES_BLOCKLEN, stderr);
                fprintf(stderr, "\n");

                AES_ECB_decrypt(&ctx, (uint8_t *)buffer);
                buffer[AES_BLOCKLEN - 1] = '\0';

                n = send(client_sockfd, buffer, n, 0);
                fprintf(stderr, "Sent %d bytes: %s\n", n, buffer);
                if (!n)
                {
                    break;
                }
            }
            close(client_sockfd);
            fprintf(stderr, "Client disconnected\n");
        }
    }

    return EXIT_SUCCESS;
}