#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>
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
    //BORRAR EL ARRAY DE ANSWERS ANTES DE ENTREGAR
    char *answers[CTFS] = {"entendido", "itba", "M4GFKZ289aku", "fk3wfLCm3QvS", "too_easy", ".RUN_ME", "K5n2UFfpFMUN", "BUmyYq5XxXGt", "u^v", "chin_chu_lan_cha", "gdb_rules", "normal"};
    char *hashes[CTFS] = {"f959505ee0c9d7fb7d81a0904aa4e9f4", "244f7439f45f207f1eb89fb2344a4767", "d4daf850c3fcce947992440e3c17dd82", "53b04de7d6d99df86aa0289418f2b317", "ce0c1111d26e426e0ea7c1f58d5488fe", "752435d46843b72130c3b0b3bc1220d4", "d281db859d7ca31e15551150a10d20ad", "e09635a04dc73332ceb8f2488c7eea1a", "5473c71236bfb255256bc59958fb165a", "c2fb1566098f29ce6b5048fcd6aad77c", "869c4f21dcb4e24138d4a016ed000939", "fea087517c26fadd409bd4b9dc642555"};
    int (*foos[CTFS])() = {firstCTF, secondCTF, thirdCTF, forthCTF, fifthCTF, sixthCTF, seventhCTF, eigthCTF, ninthCTF, tenthCTF, eleventhCTF, twelfthCTF};
    char *questions[CTFS] = {"¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?", "¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?", "¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? ¿Por qué?", "¿Qué útil abstracción es utilizada para comunicarse con sockets? ¿se puede utilizar read(2) y write(2) para operar?", "¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?", "Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. ¿Qué conviene más?", "¿Cómo se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?", "¿Qué aplicaciones se pueden utilizar para ver el tráfico por la red?", "sockets es un mecanismo de IPC. ¿Qué es más eficiente entre sockets y pipes?", "¿Cuáles son las características del protocolo SCTP?", "¿Qué es un RFC?", "¿Fue divertido?"};
    while (ctfs < CTFS)
    {
        generalCTF(new_socket, hashes[ctfs], foos[ctfs], questions[ctfs]);
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
        return 0;
    char command[1024] = {0};
    char result[1024] = {0};
    FILE *res;
    sprintf(command, "echo -n \"%s\" | md5sum  | sed 's/  -//g'", givenAnswer);
    res = popen(command, "r");
    int n = fread(result, sizeof(char), 1024, res);
    pclose(res);
    if (strncmp(hash, result, MD5_LENGTH))
    {
        printf("Respuesta incorrecta: %s", givenAnswer);
        return 0;
    }
    return 1;
}

int generalCTF(int sv_fd, char *hash, int (*foo)(), char *question)
{
    char ok = 0;
    do
    {
        printf("------------- DESAFIO -------------\n");
        foo();
        printf("\n\n----- PREGUNTA PARA INVESTIGAR -----\n");
        printf("%s\n", question);
        char response[1024] = {0};
        read(sv_fd, response, 1024);
        ok = checkGivenAnswer(hash, response);
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); //VA ACA PORQUE SI NO SOLO LIMPIA CUANDO LE PEGAS
    } while (!ok);
    return 1;
}

int firstCTF()
{
    printf("Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\n\nEn este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\nAdemás tendrán que investigar otras preguntas para responder durante la defensa.\nAdemás tendrán que investigar otras preguntas para responder durante la defensa.\nEl desafío final consiste en crear un programa que se comporte igual que yo, es decir, que provea los mismos desafíos y que sea necesario hacer lo mismo para resolverlos. No basta con esperar la respuesta.\nAdemás, deberán implementar otro programa para comunicarse conmigo.\n\nDeberán estar atentos a los easter eggs.\n\nPara verificar que sus respuestas tienen el formato correcto respondan a este desafío con la palabra \'entendido\\n\'\n");
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
    //FALTA LA LOGICA
    printf("Filter error\n");
    return 1;
}

int eigthCTF()
{
    //FALTA SOMBREAR EL DISPLAY
    printf("¿?\n\nLa respuesta es BUmyYq5XxXGt\n");
    return 1;
}

int ninthCTF()
{
    printf("Latexme\n\nSi\n\\mathrm{d}y = u^v{\\cdot}(v'{\\cdot}\\ln{(u)}+v{\\cdot}\\frac{u'}{u})\nentonces\ny = \n");
    return 1;
}

int tenthCTF()
{
    //FALTA LA LOGICA
    printf("quine\n");
    return 1;
}

void gdbme()
{
    if (getpid() == 0x12345678)
    {
        printf("La respuesta es gdb_rules\n");
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
    //FALTA LA GENERACION DE PUNTOS RANDOM CON COS Y LOG
    printf("Me conoces\n\n");
    srand(time(NULL));
    double n = 0.0;
    for (int i = 0, k; i < 300; i++)
    {
        if (i % 3 == 0)
        {
            n = ((double)rand() / RAND_MAX) - 0.5;
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

void too_easy(){};