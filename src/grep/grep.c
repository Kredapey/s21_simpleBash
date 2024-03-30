#include "s21_grep.h"

int main(int argc, char* argv[]) {
  grepStruct newGrep = {0};
  FILE* fp = NULL;
  int fileCounter = 0;
  int counter = fileNum(argc, argv);
  parser(argc, argv, &newGrep);
  int optPos = 1;
  while (optPos != argc) {
    if (argv[optPos][0] != '-') {
      if ((fp = fopen(argv[optPos], "r")) != NULL &&
          (argv[optPos - 1][0] != '-' && argv[optPos - 1][1] != 'f')) {
        patternFind(argc, argv, &newGrep, fp, &counter, argv[optPos]);
        fclose(fp);
      }
    } else if (fp == NULL && newGrep.s == 0 && argv[optPos][0] != '-') {
      fprintf(stderr, "grep: %s: No such file or directory", argv[optPos]);
      fclose(fp);
    }
    if ((fp = fopen(argv[optPos], "r")) != NULL && argv[optPos - 1][0] == '-' &&
        argv[optPos - 1][1] != 'f' && argv[optPos - 1][1] != 'e') {
      fileCounter++;
      patternFind(argc, argv, &newGrep, fp, &counter, argv[optPos]);
      fclose(fp);
    }
    optPos++;
  }
  return 0;
}