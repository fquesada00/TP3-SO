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
    if ((server_fd =connect(socket_fd, (struct sockaddr *)&address, sizeof(address))) < 0)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }
    int ctfs = 0;
    char *answers[12] = {"entendido\n", "itba\n", "M4GFKZ289aku\n", "fk3wfLCm3QvS\n", "too_easy\n", ".RUN_ME\n", "K5n2UFfpFMUN\n", "BUmyYq5XxXGt\n", "u^v\n", "chin_chu_lan_cha\n", "gdb_rules\n", "normal\n"};
    while (ctfs < CTFS)
    {
        send(socket_fd, answers[ctfs], strlen(answers[ctfs]),0);
        ctfs++;
        sleep(1);
    }
    close(socket_fd);
    close(server_fd);
    return 0;
}