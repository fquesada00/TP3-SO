#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#define PORT 8080
#define CTFS 12
#define MD5_LENGTH 32

int firstCTF();
int secondCTF();
int thirdCTF();
int forthCTF();
int fifthCTF();
int sixthCTF();
int seventhCTF();
int eigthCTF();
int ninthCTF();
int tenthCTF();
int eleventhCTF();
int twelfthCTF();

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
    char *answers[12] = {"entendido", "itba", "M4GFKZ289aku", "fk3wfLCm3QvS", "too_easy", ".RUN_ME", "K5n2UFfpFMUN", "BUmyYq5XxXGt", "u^v", "chin_chu_lan_cha", "gdb_rules", "normal"};
    char *hashes[12] = {"f959505ee0c9d7fb7d81a0904aa4e9f4","244f7439f45f207f1eb89fb2344a4767","d4daf850c3fcce947992440e3c17dd82","53b04de7d6d99df86aa0289418f2b317","ce0c1111d26e426e0ea7c1f58d5488fe","752435d46843b72130c3b0b3bc1220d4","d281db859d7ca31e15551150a10d20ad","e09635a04dc73332ceb8f2488c7eea1a","5473c71236bfb255256bc59958fb165a","c2fb1566098f29ce6b5048fcd6aad77c","869c4f21dcb4e24138d4a016ed000939","fea087517c26fadd409bd4b9dc642555"};
    int (*foos[12])() = {firstCTF, secondCTF, thirdCTF, forthCTF, fifthCTF, sixthCTF, seventhCTF, eigthCTF, ninthCTF, tenthCTF, eleventhCTF, twelfthCTF};
    while (ctfs < CTFS)
    {
        generalCTF(new_socket, hashes[ctfs], foos[ctfs]);
        ctfs++;
    }
    //test_connection(new_socket);
    return 0;
}

void test_connection(int socket_fd)
{
    char buffer[1024] = {0};
    read(socket_fd, buffer, 1024);
    printf("%s\n", buffer);
    send(socket_fd, "Hola soy el servidor!\n", strlen("Hola soy el servidor!\n"), 0);
    printf("Enviado!\n");
}

int checkGivenAnswer(char *hash, char *givenAnswer)
{
    if (givenAnswer == NULL)
        return 1;
    char command[1024] = {0};
    char result[1024] = {0};
    FILE *res;
    sprintf(command, "echo -n \"%s\" | md5sum  | sed 's/  -//g'", givenAnswer);
    res = popen(command, "r");
    int n = fread(result, sizeof(char), 1024, res);
    pclose(res);
    char ok = 1;
    if (strncmp(hash, result, MD5_LENGTH))
    {
        printf("Respuesta incorrecta: ");
        ok = 0;
    }
    printf("%s\n", givenAnswer);
    return ok;
}

int generalCTF(int sv_fd, char *hash, int (*foo)())
{
    char ok = 0;
    do
    {
        foo();
        char response[1024] = {0};
        read(sv_fd, response, 1024);
        ok = checkGivenAnswer(hash, response);
        printf("\n\n\n\n\n\n\n\n\n\n"); //VA ACA PORQUE SI NO SOLO LIMPIA CUANDO LE PEGAS
    } while (!ok);
    return 1;
}

int firstCTF()
{
    printf("Bienvenido al primer CTF\n");
    return 1;
}

int secondCTF()
{
    printf("Bienvenido al segundo CTF\n");
    return 1;
}

int thirdCTF()
{
    printf("Bienvenido al tercer CTF\n");
    return 1;
}

int forthCTF()
{
    printf("Bienvenido al cuarto CTF\n");
    return 1;
}

int fifthCTF()
{
    printf("Bienvenido al quinto CTF\n");
    return 1;
}

int sixthCTF()
{
    printf("Bienvenido al sexto CTF\n");
    return 1;
}

int seventhCTF()
{
    printf("Bienvenido al septimo CTF\n");
    return 1;
}

int eigthCTF()
{
    printf("Bienvenido al octavo CTF\n");
    return 1;
}

int ninthCTF()
{
    printf("Bienvenido al noveno CTF\n");
    return 1;
}

int tenthCTF()
{
    printf("Bienvenido al decimo CTF\n");
    return 1;
}

int eleventhCTF()
{
    printf("Bienvenido al onceavo CTF\n");
    return 1;
}

int twelfthCTF()
{
    printf("Bienvenido al doceavo CTF\n");
    return 1;
}