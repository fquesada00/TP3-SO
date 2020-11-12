// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "ctfs.h"
#include "random.h"
#include "lib.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define CTFS 12
extern void hideme();
extern int nums[100];

//BORRAR EL ARRAY DE ANSWERS ANTES DE ENTREGAR
char *answers[CTFS] = {"entendido", "itba", "M4GFKZ289aku", "fk3wfLCm3QvS", "too_easy", ".RUN_ME", "K5n2UFfpFMUN", "BUmyYq5XxXGt", "u^v", "chin_chu_lan_cha", "gdb_rules", "normal"};
char *hashes[CTFS] = {"f959505ee0c9d7fb7d81a0904aa4e9f4", "244f7439f45f207f1eb89fb2344a4767", "d4daf850c3fcce947992440e3c17dd82", "53b04de7d6d99df86aa0289418f2b317", "ce0c1111d26e426e0ea7c1f58d5488fe", "752435d46843b72130c3b0b3bc1220d4", "d281db859d7ca31e15551150a10d20ad", "e09635a04dc73332ceb8f2488c7eea1a", "5473c71236bfb255256bc59958fb165a", "c2fb1566098f29ce6b5048fcd6aad77c", "869c4f21dcb4e24138d4a016ed000939", "fea087517c26fadd409bd4b9dc642555"};

void firstCTF()
{
    printf("Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\n\nEn este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\nAdemás tendrán que investigar otras preguntas para responder durante la defensa.\nEl desafío final consiste en crear un programa que se comporte igual que yo, es decir, que provea los mismos desafíos y que sea necesario hacer lo mismo para resolverlos. No basta con esperar la respuesta.\nAdemás, deberán implementar otro programa para comunicarse conmigo.\n\nDeberán estar atentos a los easter eggs.\n\nPara verificar que sus respuestas tienen el formato correcto respondan a este desafío con la palabra \'entendido\\n\'\n");
}

void secondCTF()
{
    printf("The Wire S1E5\n5295 888 6288\n");
}

void thirdCTF()
{
    printf("https://ibb.co/tc0Hb6w\n");
}

void forthCTF()
{
    printf("EBADF...\n\nwrite: Bad file descriptor\n");
    char buff[512] = {0};
    strcat(buff, "La respuesta es: ");
    strcat(buff, answers[3]);
    write(123, buff, strlen(buff));
}

void fifthCTF()
{
    printf("respuesta = strings:173\n");
}

void sixthCTF()
{
    printf(".text .fini .rodata ? .eh_frame_hdr .eh_frame .init_array\n");
    write(1, "b hideme", 0);
    hideme();
}

void seventhCTF()
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
}

void eigthCTF()
{
    printf("¿?\n\n\033[40;30mLa respuesta es BUmyYq5XxXGt\033[0m\n");
    char *buff = decrypt(nums, 'A', 21);
    printf("\033[8m%s\033[0m", buff);
    free(buff);
}

void ninthCTF()
{
    printf("Latexme\n\nSi\n\\mathrm{d}y = u^v{\\cdot}(v'{\\cdot}\\ln{(u)}+v{\\cdot}\\frac{u'}{u})\nentonces\ny = \n");
}

void tenthCTF()
{
    int n;
    printf("quine\n");
    FILE *res;
    res = popen("gcc quine.c -o quine", "r");
    if (pclose(res) == 0)
    {
        char result[1024] = {0};
        printf("¡Genial!, ya lograron meter un programa en quine.c, veamos si hacelo que corresponde.\n");
        res = popen("./quine | diff - quine.c", "r");
        n = fread(result, sizeof(char), 1024, res);
        if (n == 0)
        {
            pclose(res);
            printf("La respuesta es chin_chu_lan_cha");
            return;
        }
        pclose(res);
    }
    printf("Presiona ENTER para reintentar");
    return;
}

void eleventhCTF()
{
    printf("b gdbme y encontrá el valor mágico\n\nENTER para reintentar.\n");
    gdbme();
}

void twelfthCTF()
{
    printf("Me conoces\n\n");
    srand(time(NULL));
    double n;
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
}