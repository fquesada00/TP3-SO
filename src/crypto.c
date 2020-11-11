#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*
    Este programa encripta y decripta un unico mensaje
    mediante el algoritmo RSA.

    Link: http://www.trytoprogram.com/c-examples/c-program-to-encrypt-and-decrypt-string/#:~:text=from%20ASCII%20value.-,Example%3A%20C%20program%20to%20encrypt%20and%20decrypt%20the%20string%20using,to%20decrypt%20the%20encrypted%20message.
*/

int x, y, n, t, i, flag;
long int e[50], d[50], temp[50], j, m[50], en[50];
char msg[100];
int nums[100] = {4, 18, 19, 14, -33, 4, 18, -33, 20, 13, -33, 4, 0, 18, 19, 4, 17, -33, 4, 6, 6};
int prime(long int);
void encryption_key();
long int cd(long int);
void encrypt();
char* decrypt();

int main()
{
  //PRIMER NRO PRIMO
  x = 3;
  flag = prime(x);
  if (flag == 0)
  {
    exit(0);
  }
  //SEGUNDO NRO PRIMO
  y = 23;
  flag = prime(y);
  if (flag == 0 || x == y)
  {
    exit(0);
  }

  /*Pasos: 
            - correr el script "distance.c" para calcular la distancia
    del ascii de la 'A' a cada letra (es indiferente si el string
    esta en mayuscula o minuscula)
            - cargar el resultado de los numeros en el string de nums
    (es importante el signo negativo)
    */

  //ACA SE ENCRIPTA EL MENSAJE "ESTO ES UN EASTER EGG"
  for (int i = 0; i < 21; i++)
  {
    msg[i] = 'A' + nums[i];
  }
  for (i = 0; msg[i] != '\0'; i++)
    m[i] = msg[i];
  n = x * y;
  t = (x - 1) * (y - 1);
  encryption_key();
  encrypt();
  decrypt();
  return 0;
}
int prime(long int pr)
{
  int i;
  j = sqrt(pr);
  for (i = 2; i <= j; i++)
  {
    if (pr % i == 0)
      return 0;
  }
  return 1;
}

//function to generate encryption key
void encryption_key()
{
  int k;
  k = 0;
  for (i = 2; i < t; i++)
  {
    if (t % i == 0)
      continue;
    flag = prime(i);
    if (flag == 1 && i != x && i != y)
    {
      e[k] = i;
      flag = cd(e[k]);
      if (flag > 0)
      {
        d[k] = flag;
        k++;
      }
      if (k == 99)
        break;
    }
  }
}
long int cd(long int a)
{
  long int k = 1;
  while (1)
  {
    k = k + t;
    if (k % a == 0)
      return (k / a);
  }
}

//function to encrypt the message
void encrypt()
{
  long int pt, ct, key = e[0], k, len;
  i = 0;
  len = strlen(msg);
  while (i != len)
  {
    pt = m[i];
    pt = pt - 96;
    k = 1;
    for (j = 0; j < key; j++)
    {
      k = k * pt;
      k = k % n;
    }
    temp[i] = k;
    ct = k + 96;
    en[i] = ct;
    i++;
  }
  en[i] = -1;
}

//function to decrypt the message
char* decrypt()
{
  long int pt, ct, key = d[0], k;
  i = 0;
  while (en[i] != -1)
  {
    ct = temp[i];
    k = 1;
    for (j = 0; j < key; j++)
    {
      k = k * ct;
      k = k % n;
    }
    pt = k + 96;
    m[i] = pt;
    i++;
  }
  m[i] = '\0';
  return m;
}