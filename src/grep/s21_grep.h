#ifndef S_21_GREP_H
#define S_21_GREP_H

#include <getopt.h>
#include <math.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 2048
#define optionsString "eivclnhsf:o"

typedef struct grepStruct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} grepStruct;

void flagReader(int opt, grepStruct* newGrep);
void parser(int argc, char* argv[], grepStruct* newGrep);
void flagOpt(FILE* fp, grepStruct* newGrep, char* pat, int* counter,
             char* pattern1[]);
void def(char* pattern, FILE* fp, int* counter, char* argv,
         grepStruct* newGrep);
int fileNum(int argc, char* argv[]);
void patternFind(int argc, char* argv[], grepStruct* newGrep, FILE* fp,
                 int* counter, char* pat);
char* patPrev(char* pattern, int turn);
void sovmFuncBezVSE(grepStruct* newGrep, FILE* fp, int* counter, char* argv,
                    char* pattern[]);
void sovmFuncSVE(grepStruct* newGrep, FILE* fp, int* counter, char* argv,
                 char* pattern[]);
int patternF(FILE* fp1, int argc, char* argv[], char* pattern, FILE* fp,
             char pattern1[100][BUFFER_SIZE], char* ePattern[], int y, int s);
void sVEDec(grepStruct* newGrep, int count, char* argv, int strCount);
void oFunc(char* buffer, char* pattern[], int j);
void decider(int count, grepStruct* newGrep, char* argv, int strNum,
             char* buffer, char* pattern[], int j);
void bezVEDec(grepStruct* newGrep, int count, char* argv, int someCount);
void nFinder(grepStruct* newGrep, char* buffer);
void nFinderBezV(grepStruct* newGrep, char* buffer);
void deciderForV(int count, grepStruct* newGrep, char* argv, int strNum,
                 char* buffer);

#endif  // S_21_GREP_H
