#include "s21_cat.h"

int main(int argc, char* argv[]) {
  int numberOfFlags = 0;
  catStruct newCat = {0};
  findFlag(argc, argv, &newCat);
  int optPos = optind;
  FILE* fp = NULL;
  while (optPos != argc) {
    if (argv[optPos][0] != '-') {
      if ((fp = fopen(argv[optPos], "r")) != NULL) {
        numberOfFlags = flagOpt(&newCat, fp);
        output(numberOfFlags, fp);
        fclose(fp);
      } else {
        fprintf(stderr, "cat: %s, No such file or directory\n", argv[optPos]);
      }
    }
    optPos++;
  }
  return 0;
}
