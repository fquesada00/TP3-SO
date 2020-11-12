// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8080
#define CTFS 12

int main(int argc, char const *argv[])
{
    int socket_fd = 0;
    struct sockaddr_in address;
    int server_fd;
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket fd");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0)
    {
        perror("not supported address");
        exit(EXIT_FAILURE);
    }
    if ((server_fd = connect(socket_fd, (struct sockaddr *)&address, sizeof(address))) < 0)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }
    size_t n = 0;
    char *response = NULL, done = 0;
    FILE *client_file = fdopen(0, "r");
    if (client_file == NULL)
    {
        perror("fdopen");
        exit(EXIT_FAILURE);
    }
    puts("\n\nBienvenidos al cliente de ositOS.\n\nPara mandar input al servidor, escriban el texto con la respuesta que crean correcta y presionen enter.\n\nPara salir del cliente, escriban la palabra \'quit\' seguida de cualquier caracter (o ninguno).\n\n");
    while (!done)
    {
        if (getline(&response, &n, client_file) == -1)
        {
            free(response);
            close(socket_fd);
            close(server_fd);
            perror("getline");
            exit(EXIT_FAILURE);
        }
        if (!strncmp(response, "quit",4))
        {
            done = 1;
            continue;
        }
        printf("%s\n", response);
        send(socket_fd, response, strlen(response), 0);
    }
    free(response);
    close(socket_fd);
    close(server_fd);
    return 0;
}