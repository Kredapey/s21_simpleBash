// henrietr 2022
#include "s21_cat.h"

int flagOpt(catStruct* newCat, FILE* fp) {
  int counter = 0;
  FILE* tester = NULL;
  FILE* tester1 = NULL;
  if (newCat->s == 1) {
    sFlagDec(fp, tester);
    counter++;
  }
  if (newCat->t == 1) {
    tFlagDec(fp, tester, tester1, &counter);
    counter++;
  }
  if (newCat->b == 1) {
    bFlagDec(fp, tester, tester1, &counter);
    counter++;
  }
  if (newCat->n == 1) {
    if (newCat->b != 1) {
      nFlagDec(fp, tester, tester1, &counter);
      counter++;
    }
  }
  if (newCat->e == 1) {
    eFlagDec(fp, tester, tester1, &counter);
    counter++;
  }
  if (newCat->v == 1) {
    vFlagDec(fp, tester, tester1, &counter);
    counter++;
  }
  return counter;
}

void findFlag(int argc, char* argv[], catStruct* newCat) {
  int opt = 0;
  int optionIndex = 0;
  optind = 1;
#ifdef unix
  char* optStr = "bvnseEtT";
#else
  char* optStr = "+bvnseEtT";
#endif
  while ((opt = getopt_long(argc, argv, optStr, longOptions, &optionIndex)) !=
         -1) {
    switch (opt) {
      case 'b':
        newCat->b = 1;
        break;
      case 'v':
        newCat->v = 1;
        break;
      case 'n':
        newCat->n = 1;
        break;
      case 's':
        newCat->s = 1;
        break;
      case 'e':
        newCat->e = 1;
        newCat->v = 1;
        break;
      case 'E':
        newCat->e = 1;
        break;
      case 't':
        newCat->t = 1;
        newCat->v = 1;
        break;
      case 'T':
        newCat->t = 1;
        break;
    }
  }
}

void sFunc(FILE* fp, FILE* tester) {
  int counter = 0;
  int startCounter = 0;
  char nxt = ' ';
  char ch = ' ';
  while ((ch = fgetc(fp)) != EOF) {
    if (startCounter == 0) {
      counter = 1;
    }
    if (ch == '\n') {
      if (counter <= 1) {
        fprintf(tester, "\n");
        counter++;
      } else if (counter > 1) {
        do {
          nxt = fgetc(fp);
          counter++;
        } while (nxt == '\n');
        if (nxt != '\n') {
          fprintf(tester, "%c", nxt);
        }
        counter = 0;
      }
    } else {
      fprintf(tester, "%c", ch);
      counter = 0;
    }
    startCounter++;
  }
}

void bFunc(FILE* fp, FILE* tester) {
  int counter = 1;
  int strCounter = 1;
  char ch = ' ';
  while ((ch = fgetc(fp)) != EOF) {
    if (ch == '\n') {
      fprintf(tester, "%c", ch);
      counter = 1;
    } else if (counter == 1 && ch != '\n') {
      fprintf(tester, "%6d\t", strCounter);
      strCounter++;
      fprintf(tester, "%c", ch);
      counter = 0;
    } else {
      fprintf(tester, "%c", ch);
    }
  }
}

void nFunc(FILE* fp, FILE* tester) {
  int counter = 0;
  int strCounter = 1;
  char ch = ' ';
  while ((ch = fgetc(fp)) != EOF) {
    if (ch == '\n' && counter == 0) {
      fprintf(tester, "%6d\t", strCounter);
      strCounter++;
      fprintf(tester, "%c", ch);
    } else if (ch != '\n' && counter == 0) {
      fprintf(tester, "%6d\t", strCounter);
      strCounter++;
      fprintf(tester, "%c", ch);
      counter = 1;
    } else if (ch == '\n' && counter == 1) {
      fprintf(tester, "%c", ch);
      counter = 0;
    } else {
      fprintf(tester, "%c", ch);
    }
  }
}

void eFunc(FILE* fp, FILE* tester) {
  char ch = ' ';
  while ((ch = fgetc(fp)) != EOF) {
    if (ch == '\n') {
      fprintf(tester, "$");
      fprintf(tester, "%c", ch);
    } else {
      fprintf(tester, "%c", ch);
    }
  }
}

void tFunc(FILE* fp, FILE* tester) {
  char ch = ' ';
  while ((ch = fgetc(fp)) != EOF) {
    if (ch == '\t') {
      fprintf(tester, "^I");
    } else {
      fprintf(tester, "%c", ch);
    }
  }
}

void vFunc(FILE* fp, FILE* tester) {
  char ch = ' ';
  while ((ch = fgetc(fp)) != EOF) {
    if (ch >= 0 && ch <= 31 && ch != '\n' && ch != '\t') {
      fprintf(tester, "^%c", ch + 64);
    } else if (ch == 127) {
      fprintf(tester, "^%c", ch - 64);
    } else {
      fprintf(tester, "%c", ch);
    }
  }
}

void output(int num, FILE* fp) {
  char ch = ' ';
  FILE* tester = NULL;
  FILE* tester1 = NULL;
  if (num == 1 || num == 3 || num == 5) {
    tester = fopen("test.txt", "r");
    while ((ch = fgetc(tester)) != EOF) {
      fprintf(stdout, "%c", ch);
    }
    fclose(tester);
  } else if (num == 2 || num == 4) {
    tester1 = fopen("test1.txt", "r");
    while ((ch = fgetc(tester1)) != EOF) {
      fprintf(stdout, "%c", ch);
    }
    fclose(tester1);
  } else if (num == 0) {
    while ((ch = fgetc(fp)) != EOF) {
      fprintf(stdout, "%c", ch);
    }
  }
}

void sFlagDec(FILE* fp, FILE* tester) {
  tester = fopen("test.txt", "w+");
  sFunc(fp, tester);
  fclose(tester);
}

void tFlagDec(FILE* fp, FILE* tester, FILE* tester1, int* counter) {
  if (*counter == 0) {
    tester = fopen("test.txt", "w+");
    tFunc(fp, tester);
    fclose(tester);
  } else {
    tester = fopen("test.txt", "r");
    tester1 = fopen("test1.txt", "w+");
    tFunc(tester, tester1);
    fclose(tester);
    fclose(tester1);
  }
}

void bFlagDec(FILE* fp, FILE* tester, FILE* tester1, int* counter) {
  if (*counter == 0) {
    tester = fopen("test.txt", "w+");
    bFunc(fp, tester);
    fclose(tester);
  } else if (*counter == 1 || *counter == 3 || *counter == 5) {
    tester = fopen("test.txt", "r");
    tester1 = fopen("test1.txt", "w+");
    bFunc(tester, tester1);
    fclose(tester);
    fclose(tester1);
  } else {
    tester1 = fopen("test1.txt", "r");
    tester = fopen("test.txt", "w+");
    bFunc(tester1, tester);
    fclose(tester1);
    fclose(tester);
  }
}

void nFlagDec(FILE* fp, FILE* tester, FILE* tester1, int* counter) {
  if (*counter == 0) {
    tester = fopen("test.txt", "w+");
    nFunc(fp, tester);
    fclose(tester);
  } else if (*counter == 1 || *counter == 3 || *counter == 5) {
    tester = fopen("test.txt", "r");
    tester1 = fopen("test1.txt", "w+");
    nFunc(tester, tester1);
    fclose(tester);
    fclose(tester1);
  } else {
    tester1 = fopen("test1.txt", "r");
    tester = fopen("test.txt", "w+");
    nFunc(tester1, tester);
    fclose(tester1);
    fclose(tester);
  }
}

void eFlagDec(FILE* fp, FILE* tester, FILE* tester1, int* counter) {
  if (*counter == 0) {
    tester = fopen("test.txt", "w+");
    eFunc(fp, tester);
    fclose(tester);
  } else if (*counter == 1 || *counter == 3 || *counter == 5) {
    tester = fopen("test.txt", "r");
    tester1 = fopen("test1.txt", "w+");
    eFunc(tester, tester1);
    fclose(tester);
    fclose(tester1);
  } else {
    tester1 = fopen("test1.txt", "r");
    tester = fopen("test.txt", "w+");
    eFunc(tester1, tester);
    fclose(tester1);
    fclose(tester);
  }
}

void vFlagDec(FILE* fp, FILE* tester, FILE* tester1, int* counter) {
  if (*counter == 0) {
    tester = fopen("test.txt", "w+");
    vFunc(fp, tester);
    fclose(tester);
  } else if (*counter == 1 || *counter == 3 || *counter == 5) {
    tester = fopen("test.txt", "r");
    tester1 = fopen("test1.txt", "w+");
    vFunc(tester, tester1);
    fclose(tester);
    fclose(tester1);
  } else {
    tester1 = fopen("test1.txt", "r");
    tester = fopen("test.txt", "w+");
    vFunc(tester1, tester);
    fclose(tester1);
    fclose(tester);
  }
}
