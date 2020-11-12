// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "lib.h"
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
extern int nums[100];

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

void progressBar()
{
    char t[22] = {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'};
    t[21] = 0;
    int i;
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