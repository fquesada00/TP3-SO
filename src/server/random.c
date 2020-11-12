// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "random.h"
#include <stdlib.h>
#include <time.h>
double randNormalize (void){
	return (rand() / ( (double)RAND_MAX + 1));
}
int randInt(int izq, int der){
	return (int)(randNormalize() * (der - izq + 1) + izq);
}
double randReal(double izq, double der){
	return (randNormalize() * (der - izq) + izq);

}
void randomize(void){
	srand((int)time(NULL));
}