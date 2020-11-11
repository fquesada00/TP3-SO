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
    int socket_fd = 0, valread, opt = 1;
    struct sockaddr_in address;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
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
    if (connect(socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }
    int ctfs = 0;
    char *answers[12] = {"entendido", "itba", "M4GFKZ289aku", "fk3wfLCm3QvS", "too_easy", ".RUN_ME", "K5n2UFfpFMUN", "BUmyYq5XxXGt", "u^v", "chin_chu_lan_cha", "gdb_rules", "normal"};
    while (ctfs < CTFS)
    {
        send(socket_fd, answers[ctfs], strlen(answers[ctfs]),0);
        ctfs++;
        sleep(1);
    }
    //test_connection(socket_fd);
    return 0;
}

void test_connection(int socket_fd)
{
    char buffer[1024] = {0};
    send(socket_fd, "Hello from client", strlen("Hello from cliente"), 0);
    printf("Hello message sent\n");
    read(socket_fd, buffer, 1024);
    printf("%s\n", buffer);
}