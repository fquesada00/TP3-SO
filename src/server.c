#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#define PORT 8080
#define CTFS 3
int checkGivenAnswer(char *, char *);
int firstCTF(int);
int secondCTF(int);
int thirdCTF(int);
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, val_read;
    int opt = 1;
    struct sockaddr_in address;
    char buffer[1024] = {0};
    int addrlen = sizeof(address);
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket fd");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, &address, sizeof(address)) < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 1) == -1)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr_in *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    int ctfs = 0;
    char answers[] = {"hash1","hash2","hash3","hash4","hash5","hash6"};
    while (ctfs < CTFS)
    {
        switch (ctfs)
        {
        case 0:
            firstCTF(new_socket);
            //generalCTF(new_socket,answers[ctfs]);
            break;
        case 1:
            secondCTF(new_socket);
            //generalCTF(new_socket,answers[ctfs]);
            break;
        case 2:
            thirdCTF(new_socket);
            //generalCTF(new_socket,answers[ctfs]);
            break;
        default:
            break;
        }
        ctfs++;

    }
    val_read = read(new_socket, buffer, 1024);
    printf("%s\n", buffer);
    send(new_socket, "Hola soy el servidor!\n", strlen("Hola soy el servidor!\n"), 0);
    printf("Enviado!\n");
    return 0;
}

int checkGivenAnswer(char *answer, char *givenAnswer)
{
    if (answer == NULL && givenAnswer == NULL)
        return 1;
    char command[1024] = {0};
    char result[1024] = {0};
    FILE * res;
    sprintf(command, "echo -n \"%s\" | md5sum  | sed 's/  -//g'", givenAnswer);
    res = popen(command, "r");
    int n = fread(result, sizeof(char), 1024, res);
    result[n - 1] = 0;
    pclose(res);
    printf("%s vs %s y %d\n",answer, givenAnswer, strcmp(answer, givenAnswer));
    if (strcmp(answer, givenAnswer))
    {
        printf("Respuesta incorrecta: %s", givenAnswer);
        return 0;
    }
    return 1;
}

int generalCTF(int sv_fd, char * question, char * hash) {
    printf("%s\n",question);
    char ok = 0;
    do
    {
        char response[1024] = {0};
        read(sv_fd, response, 1024);
        ok = checkGivenAnswer(hash, response);
        sleep(2);
        printf("\n\n\n\n\n\n\n\n\n\n"); //VA ACA PORQUE SI NO SOLO LIMPIA CUANDO LE PEGAS
    }while (!ok);
    return 1;
}

int firstCTF(int sv_fd)
{
    printf("Bienvenido al primer CTF\n");
    char ok = 0;
    do
    {
        char response[1024] = {0};
        read(sv_fd, response, 1024);
        ok = checkGivenAnswer("uno", response);
    } while (!ok);
}

int secondCTF(int sv_fd)
{
    printf("Bienvenido al segundo CTF\n");
    char ok = 0;
    do
    {
        char response[1024] = {0};
        read(sv_fd, response, 1024);
        ok = checkGivenAnswer("dos", response);
    } while (!ok);
}

int thirdCTF(int sv_fd)
{
    printf("Bienvenido al tercer CTF\n");
    char ok = 0;
    do
    {
        char response[1024] = {0};
        read(sv_fd, response, 1024);
        ok = checkGivenAnswer("tres", response);
    } while (!ok);
}