#include <networking.h>

int main(int argc, char **argv)
{
    // Check arguments
    if (argc < 3)
    {
        printf("Usage: %s <host> <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Calculate ip and port
    in_addr_t server_ip = inet_addr(argv[1]);
    uint16_t server_port = htons(strtol(argv[2], NULL, 10));
    if (errno == EINVAL || errno == ERANGE)
    {
        printf("Invalid port number: %s\n", argv[2]);
        return EXIT_FAILURE;
    }

    // Create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Could not create socket");
        return EXIT_FAILURE;
    }

    // Connect to server
    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_port = server_port,
        .sin_addr = {.s_addr = server_ip},
        .sin_zero = {0}};

    connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    // Send and receive data
    while(1)
    {
        char buf[1024];
        fgets(buf, sizeof(buf), stdin);
        send(sockfd, buf, strlen(buf), 0);
        int n = recv(sockfd, buf, sizeof(buf), 0);
        buf[n] = '\0';
        printf("%s\n", buf);
    }

    return EXIT_SUCCESS;
}