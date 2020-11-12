// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>
#include "random.h"
#include "ctfs.h"
#include "lib.h"
#include "server.h"
#define PORT 8080
#define CTFS 12
#define MD5_LENGTH 32
extern char *hashes[CTFS];
//CODIFICACION "ESTO ES UN EASTER EGG" BASADA EN distance.c
int nums[100] = {4, 18, 19, 14, -33, 4, 18, -33, 20, 13, -33, 4, 0, 18, 19, 4, 17, -33, 4, 6, 6};

void *challenges[CTFS] = {firstCTF, secondCTF, thirdCTF, forthCTF, fifthCTF, sixthCTF, seventhCTF, eigthCTF, ninthCTF, tenthCTF, eleventhCTF, twelfthCTF};
char *questions[CTFS] = {"¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?", "¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?", "¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? ¿Por qué?", "¿Qué útil abstracción es utilizada para comunicarse con sockets? ¿se puede utilizar read(2) y write(2) para operar?", "¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?", "Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. ¿Qué conviene más?", "¿Cómo se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?", "¿Qué aplicaciones se pueden utilizar para ver el tráfico por la red?", "sockets es un mecanismo de IPC. ¿Qué es más eficiente entre sockets y pipes?", "¿Cuáles son las características del protocolo SCTP?", "¿Qué es un RFC?", "¿Fue divertido?"};
char easy[] = "too_easy";

int main(int argc, char const *argv[])
{
    int server_fd, client_fd;
    int opt = 1;
    struct sockaddr_in *address = malloc(sizeof(struct sockaddr_in));
    if (address == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    int addrlen = sizeof(*address);
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

    address->sin_family = AF_INET;
    address->sin_port = htons(PORT);
    address->sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (const struct sockaddr *)address, sizeof(*address)) < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 1) == -1)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((client_fd = accept(server_fd, (struct sockaddr *)address, (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    generalCTF(client_fd);
    printf("\n\nFelicitaciones, finalizaron el juego. Ahora deberán implementar el servidor que se comporte como el servidor provisto");
    printf("\033[1;1H\033[2J");
    close(server_fd);
    close(client_fd);
    free(address);
    return 0;
}

int checkGivenAnswer(char *hash, char *givenAnswer)
{
    if (givenAnswer == NULL)
        return 0;
    givenAnswer[strlen(givenAnswer) - 1] = 0;
    char command[1024] = {0};
    char result[1024] = {0};
    FILE *res;
    sprintf(command, "echo -n \"%s\" | md5sum  | sed 's/  -//g'", givenAnswer);
    res = popen(command, "r");
    fread(result, sizeof(char), 1024, res);
    pclose(res);
    progressBar();
    if (strncmp(hash, result, MD5_LENGTH) != 0)
    {
        printf("Respuesta incorrecta: %s", givenAnswer);
        fflush(stdout);
        sleep(1);
        printf("\r");
        return 0;
    }
    return 1;
}

int generalCTF(int client_fd)
{
    char ok = 0;
    char *response = NULL;
    int ctfs = 0;
    size_t n = 0;
    int aux = dup(client_fd);
    FILE *client_file = fdopen(aux, "r");
    if (client_file == NULL)
    {
        perror("fdopen");
        exit(EXIT_FAILURE);
    }
    void (*challenge)();
    while (ctfs < CTFS)
    {
        challenge = (void (*)())challenges[ctfs];
        do
        {
            printf("\033[1;1H\033[2J");
            printf("------------- DESAFIO -------------\n");
            challenge();
            printf("\n\n----- PREGUNTA PARA INVESTIGAR -----\n");
            printf("%s\n", questions[ctfs]);
            if (getline(&response, &n, client_file) == -1)
            {
                free(response);
                perror("getline");
                exit(EXIT_FAILURE);
            }
            if (strcmp(response, "ositOS\n") == 0)
            {
                ositoCarinoso();
            }
            else
            {
                ok = checkGivenAnswer(hashes[ctfs], response);
            }
        } while (!ok);
        ctfs++;
        ok = 0;
    }
    free(response);
    fclose(client_file);
    return 1;
}