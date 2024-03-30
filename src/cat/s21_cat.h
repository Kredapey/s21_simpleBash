#ifndef S_21_CAT_H
#define S_21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct catStruct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} catStruct;

static struct option const longOptions[] = {{"number-nonblank", 0, 0, 'b'},
                                            {"number", 0, 0, 'n'},
                                            {"squeeze-blank", 0, 0, 's'},
                                            {NULL, 0, NULL, 0}};

void findFlag(int argc, char* argv[], catStruct* newCat);
int flagOpt(catStruct* newCat, FILE* fp);
void sFunc(FILE* fp, FILE* tester);
void tFunc(FILE* fp, FILE* tester);
void eFunc(FILE* fp, FILE* tester);
void bFunc(FILE* fp, FILE* tester);
void nFunc(FILE* fp, FILE* tester);
void vFunc(FILE* fp, FILE* tester);
void output(int num, FILE* fp);
void sFlagDec(FILE* fp, FILE* tester);
void tFlagDec(FILE* fp, FILE* tester, FILE* tester1, int* counter);
void eFlagDec(FILE* fp, FILE* tester, FILE* tester1, int* counter);
void bFlagDec(FILE* fp, FILE* tester, FILE* tester1, int* counter);
void nFlagDec(FILE* fp, FILE* tester, FILE* tester1, int* counter);
void vFlagDec(FILE* fp, FILE* tester, FILE* tester1, int* counter);

#endif  // S_21_CAT_H
