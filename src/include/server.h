#ifndef _SERVER_H_
#define _SERVER_H_
int checkGivenAnswer(char *hash, char *givenAnswer);
int generalCTF(int client_fd, char *hash, int (*challenge)(), char *question);
#endif