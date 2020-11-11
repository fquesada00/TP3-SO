#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>
#include "random.h"
#define PORT 8080
#define CTFS 12
#define MD5_LENGTH 32
int nums[100] = {4, 18, 19, 14, -33, 4, 18, -33, 20, 13, -33, 4, 0, 18, 19, 4, 17, -33, 4, 6, 6};
char easy[] = "too_easy";
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
void progressBar();
void ositoCarinoso();

char *hashes[CTFS] = {"f959505ee0c9d7fb7d81a0904aa4e9f4", "244f7439f45f207f1eb89fb2344a4767", "d4daf850c3fcce947992440e3c17dd82", "53b04de7d6d99df86aa0289418f2b317", "ce0c1111d26e426e0ea7c1f58d5488fe", "752435d46843b72130c3b0b3bc1220d4", "d281db859d7ca31e15551150a10d20ad", "e09635a04dc73332ceb8f2488c7eea1a", "5473c71236bfb255256bc59958fb165a", "c2fb1566098f29ce6b5048fcd6aad77c", "869c4f21dcb4e24138d4a016ed000939", "fea087517c26fadd409bd4b9dc642555"};
int (*challenges[CTFS])() = {firstCTF, secondCTF, thirdCTF, forthCTF, fifthCTF, sixthCTF, seventhCTF, eigthCTF, ninthCTF, tenthCTF, eleventhCTF, twelfthCTF};
char *questions[CTFS] = {"¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?", "¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?", "¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? ¿Por qué?", "¿Qué útil abstracción es utilizada para comunicarse con sockets? ¿se puede utilizar read(2) y write(2) para operar?", "¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?", "Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. ¿Qué conviene más?", "¿Cómo se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?", "¿Qué aplicaciones se pueden utilizar para ver el tráfico por la red?", "sockets es un mecanismo de IPC. ¿Qué es más eficiente entre sockets y pipes?", "¿Cuáles son las características del protocolo SCTP?", "¿Qué es un RFC?", "¿Fue divertido?"};
//BORRAR EL ARRAY DE ANSWERS ANTES DE ENTREGAR
char *answers[CTFS] = {"entendido", "itba", "M4GFKZ289aku", "fk3wfLCm3QvS", "too_easy", ".RUN_ME", "K5n2UFfpFMUN", "BUmyYq5XxXGt", "u^v", "chin_chu_lan_cha", "gdb_rules", "normal"};

int main(int argc, char const *argv[])
{
    int server_fd, client_fd, val_read;
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
    if ((client_fd = accept(server_fd, (struct sockaddr_in *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    int ctfs = 0;
    while (ctfs < CTFS)
    {
        generalCTF(client_fd, hashes[ctfs], challenges[ctfs], questions[ctfs]);
        ctfs++;
    }
    printf("Felicitaciones, finalizaron el juego. Ahora deberán implementar el servidor que se comporte como el servidor provisto");
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

char *decrypt(int n[], char c, int size)
{
    char *buff = malloc(size + 1);
    for (int i = 0; i < size; i++)
    {
        buff[i] = c + n[i];
    }
    buff[size] = '\0';
    return buff;
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
    char *msg = decrypt(nums, 'A', 21);
    free(msg);
    progressBar();
    if (strncmp(hash, result, MD5_LENGTH))
    {
        printf("Respuesta incorrecta: %s", givenAnswer);
        fflush(stdout);
        sleep(1);
        printf("\r");
        return 0;
    }
    return 1;
}

void ositoCarinoso()
{
    printf("\033[1;1H\033[2J");
    char *buff = decrypt(nums, 'A', 21);
    printf("%s\n", buff);
    free(buff);
    write(1, "¿Como se llama nuestro SO del TP2?\nMiren mas abajo", 0);
    printf("   _     _   \n");
    printf("  (c).-.(c)  \n");
    printf("   / ._. \\  \n");
    printf(" __\\( Y )/__\n");
    printf("(_.-/'-'\\-._)\n");
    printf("   || o ||   \n");
    printf(" _.' `-' '._ \n");
    printf("(.-./`-'\\.-.)\n");
    printf(" `-'     `-' \n");
    usleep(100000);
    printf("\033[1;1H\033[2J");
}

int generalCTF(int client_fd, char *hash, int (*challenge)(), char *question)
{
    char ok = 0;
    char *response;
    int n;
    FILE *client_file = fdopen(client_fd, "r");
    if (client_file == NULL)
    {
        perror("fdopen");
        exit(EXIT_FAILURE);
    }
    do
    {
        printf("\033[1;1H\033[2J");
        printf("------------- DESAFIO -------------\n");
        challenge();
        printf("\n\n----- PREGUNTA PARA INVESTIGAR -----\n");
        printf("%s\n", question);
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
            ok = checkGivenAnswer(hash, response);
        }

    } while (!ok);
    return 1;
}

void progressBar()
{
    char t[22] = {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'};
    t[21] = 0;
    int i = 0;
    for (int j = 0; j <= 100; j++)
    {
        i = j / 5;
        t[i] = '#';
        printf("[%s] %%%d", t, j);
        printf("\r");
        fflush(stdout);
        usleep(10000);
    }
    printf("\n");
}

int firstCTF()
{
    printf("Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\n\nEn este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\nAdemás tendrán que investigar otras preguntas para responder durante la defensa.\nEl desafío final consiste en crear un programa que se comporte igual que yo, es decir, que provea los mismos desafíos y que sea necesario hacer lo mismo para resolverlos. No basta con esperar la respuesta.\nAdemás, deberán implementar otro programa para comunicarse conmigo.\n\nDeberán estar atentos a los easter eggs.\n\nPara verificar que sus respuestas tienen el formato correcto respondan a este desafío con la palabra \'entendido\\n\'\n");
    return 1;
}

int secondCTF()
{
    printf("The Wire S1E5\n5295 888 6288\n");
    return 1;
}

int thirdCTF()
{
    printf("https://ibb.co/tc0Hb6w\n");
    return 1;
}

int forthCTF()
{
    printf("EBADF...\n\nwrite: Bad file descriptor\n");
    char buff[512] = {0};
    strcat(buff, "La respuesta es: ");
    strcat(buff, answers[3]);
    write(123, buff, strlen(buff));
    return 1;
}

int fifthCTF()
{
    //CAMBIAR SEGUN INDICADO
    printf("respuesta = strings:277\n");
    return 1;
}

int sixthCTF()
{
    //CAMBIAR SEGUN INDICADO
    printf(".data .bss .comment ? .shstrtab .symtab .strtab\n");
    return 1;
}

int seventhCTF()
{
    char ans[512] = {0};
    strcat(ans, "La respuesta es: ");
    strcat(ans, answers[6]);
    printf("Filter error\n\n");
    int len = strlen(ans);
    for (int i = 0; i < len; i++)
    {
        write(1, ans + i, 1);
        for (int j = 0; j < randInt(1, 6); j++)
        {
            int c[2] = {0};
            c[0] = randInt(33, 125);
            write(2, c, 1);
        }
    }
    putchar('\n');
    //TODO FRAN
    return 1;
}

int eigthCTF()
{
    printf("¿?\n\n\033[40;30mLa respuesta es BUmyYq5XxXGt\033[0m\n");
    char *buff = decrypt(nums, 'A', 21);
    printf("\033[8m%s\033[0m", buff);
    free(buff);
    return 1;
}

int ninthCTF()
{
    printf("Latexme\n\nSi\n\\mathrm{d}y = u^v{\\cdot}(v'{\\cdot}\\ln{(u)}+v{\\cdot}\\frac{u'}{u})\nentonces\ny = \n");
    return 1;
}

int tenthCTF()
{
    char command[1024] = {0};
    char result[1024] = {0};
    int n;
    printf("quine\n");
    FILE *res;
    res = popen("gcc quine.c -o quine", "r");
    if (pclose(res) == 0)
    {
        printf("¡Genial!, ya lograron meter un programa en quine.c, veamos si hacelo que corresponde.");
        res = popen("./quine | diff - quine.c", "r");
        n = fread(result, sizeof(char), 1024, res);
        if (n == 0)
            return 1;
        result[n - 1] = 0;
    }
    else
        perror("gcc");
    return 1;
}

void gdbme()
{
    if (getpid() == 0x12345678)
    {
        printf("La respuesta es gdb_rules\n");
    }
    if (getpid() == 0x87654321)
    {
        char *buff = decrypt(nums, 'A', 21);
        printf("%s\n", buff);
        free(buff);
    }
}

int eleventhCTF()
{
    printf("b gdbme y encontrá el valor mágico\n\nENTER para reintentar.\n");
    gdbme();
    return 1;
}

int twelfthCTF()
{
    printf("Me conoces\n\n");
    srand(time(NULL));
    double n = 0.0;
    int sequence = randInt(1, 3);
    for (int i = 0, k; i < 400; i++)
    {
        if (i % 4 == 0)
        {
            n = ((double)rand() / RAND_MAX) - 0.5;
        }
        else if (i % sequence == 0)
        {
            n = randReal(0.7, 2.1);
        }
        else
        {
            n = ((double)rand() / RAND_MAX) * 0.2;
        }
        k = rand() & 0x1;
        if (k)
            n *= -1;
        printf("%g ", n);
    }
    return 1;
}