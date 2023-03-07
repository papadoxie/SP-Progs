#include <networking.h>
#include <aes.h>

int main(int argc, char **argv)
{
    // Check arguments
    if (argc < 4)
    {
        printf("Usage: %s <host> <port> <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Open file for reading
    FILE *file = fopen(argv[3], "rb");
    if (!file)
    {
        perror("fopen");
        return EXIT_FAILURE;
    }
    
    //Initialize AES
    struct AES_ctx ctx;
    uint8_t key[] = "0123456789abcdef";
    AES_init_ctx(&ctx, key);

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

    connect(sockfd, (struct sockaddr *)&server_addr, sizeof server_addr);

    // Send and receive data
    while(1)
    {
        char send_buf[AES_BLOCKLEN];
        char recv_buf[AES_BLOCKLEN];
        memset(send_buf, 0, AES_BLOCKLEN);
        memset(recv_buf, 0, AES_BLOCKLEN);

        fgets(send_buf, AES_BLOCKLEN, file);
        if (feof(file))
        {
            break;
        }

        AES_ECB_encrypt(&ctx, (uint8_t *)send_buf);
        send(sockfd, send_buf, AES_BLOCKLEN, 0);
        
        recv(sockfd, recv_buf, AES_BLOCKLEN, 0);
        printf("%s", recv_buf);
    }

    fclose(file);
    return EXIT_SUCCESS;
}