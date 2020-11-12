#include <stdio.h>
#include <string.h>

/*
    Programa que imprime por salida estandar la distancia de cada 
    caracter de un array a codificar, respecto a un caracter en 
    particular

    En este caso codificamos el array "ESTO ES UN EASTER EGG"
    ,asi este no salia al ejecutar strings, respecto al caracter 'A'

    Cabe aclarar que somos conscientes que es innecesario el hecho
    de imprimir por salida estandar y no guardarlo en un array de ints, 
    pero el problema es que de esa forma saldría el string en strings. 
    Entonces, la idea es ejecutar este programa por cada string a codificar.
    Para optimizarlo podria recibir el string por parametro directamente
    
    El unico proposito de tener en cuenta este programa es el de mostrar
    el mecanismo de codificacion utilizado
*/

int main()
{
    char msg[100] = "ESTO ES UN EASTER EGG";
    for (int i = 0; i < strlen("ESTO ES UN EASTER EGG"); i++)
    {
        printf("%d ;", msg[i] - 'A');
    }
    putchar('\n');
}