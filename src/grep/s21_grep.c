#include "s21_grep.h"

void parser(int argc, char* argv[], grepStruct* newGrep) {
  int opt = 0;
  while ((opt = getopt(argc, argv, optionsString)) != -1) {
    flagReader(opt, newGrep);
  }
  int i = 0;
  while (optind != argc) {
    if (argv[optind][i] == '-') {
      i++;
      while (argv[optind][i] != '\0') {
        flagReader(argv[optind][i], newGrep);
        i++;
      }
      i = 0;
    }
    optind++;
  }
}

void flagReader(int opt, grepStruct* newGrep) {
  switch (opt) {
    case 'e':
      newGrep->e = 1;
      break;
    case 'i':
      newGrep->i = 1;
      break;
    case 'v':
      newGrep->v = 1;
      break;
    case 'c':
      newGrep->c = 1;
      break;
    case 'l':
      newGrep->l = 1;
      break;
    case 'n':
      newGrep->n = 1;
      break;
    case 'h':
      newGrep->h = 1;
      break;
    case 's':
      newGrep->s = 1;
      break;
    case 'f':
      newGrep->f = 1;
      break;
    case 'o':
      newGrep->o = 1;
      break;
  }
}

void flagOpt(FILE* fp, grepStruct* newGrep, char* pat, int* counter,
             char* pattern1[]) {
  if (newGrep->v == 1) {
    sovmFuncSVE(newGrep, fp, counter, pat, pattern1);
  } else if (newGrep->v == 0) {
    sovmFuncBezVSE(newGrep, fp, counter, pat, pattern1);
  }
}

int fileNum(int argc, char* argv[]) {
  int counter = 0;
  int optPos = 1;
  FILE* fp;
  while (optPos != argc) {
    if ((fp = fopen(argv[optPos], "r")) != NULL && argv[optPos][0] != '.') {
      // printf("%s", argv[optPos]);
      counter++;
      fclose(fp);
    }
    optPos++;
  }
  return counter;
}

void patternFind(int argc, char* argv[], grepStruct* newGrep, FILE* fp,
                 int* counter, char* pat) {
  char pattern[BUFFER_SIZE] = " ";
  char pattern1[100][BUFFER_SIZE] = {0};
  int optPos = 0, ccount = 0, y = 0, s = 0, a = 0;
  char* ePattern[BUFFER_SIZE] = {0};
  FILE* fp1 = NULL;
  if (newGrep->f == 1) {
    a = patternF(fp1, argc, argv, pattern, fp, pattern1, ePattern, y, s);
  }
  while (optPos != argc) {
    if (newGrep->e == 0 && ccount == 0) {
      if (argv[1][0] == '-') {
        ePattern[a] = argv[2];
        a++;
      } else if (argv[1][0] != '-') {
        ePattern[a] = argv[1];
        a++;
      }
    } else if (newGrep->e == 1 && ccount == 0) {
      for (int i = 1; i < argc; i++) {
        int j = 1;
        while (argv[i][j] != '\0') {
          if (argv[i][0] == '-' && argv[i][j] == 'e' &&
              argv[i][j + 1] == '\0') {
            ePattern[a] = argv[i + 1];
            a++;
          }
          j++;
        }
      }
    }
    optPos++;
    ccount++;
  }
  flagOpt(fp, newGrep, pat, counter, ePattern);
  optPos++;
}

void sovmFuncSVE(grepStruct* newGrep, FILE* fp, int* counter, char* argv,
                 char* pattern[]) {
  regex_t re;
  char buffer[BUFFER_SIZE] = " ";
  int count = 0, j = 0, t = 0, strNum = 0, someCount = 0, strCount = 0,
      iFlag = 0, lastStr = 0, lastStr1 = 0;
  count = *counter;
  if (newGrep->i == 1) {
    iFlag = REG_ICASE;
  }
  while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
    someCount = 0;
    strNum++;
    j = 0;
    while (pattern[j] != NULL) {
      t = regcomp(&re, pattern[j], iFlag);
      if (t == 0) {
        if (regexec(&re, buffer, 0, NULL, 0) != 0) {
          someCount++;
          lastStr = strNum;
        }
      }
      j++;
      regfree(&re);
    }
    if (someCount == j) {
      strCount++;
      lastStr1 = strNum;
      if (newGrep->f == 1) {
        count = *counter - 1;
      }
      deciderForV(count, newGrep, argv, strNum, buffer);
    }
  }
  sVEDec(newGrep, count, argv, strCount);
  if (lastStr == lastStr1 && buffer[0] != '\n') {
    nFinderBezV(newGrep, buffer);
  }
}

void sovmFuncBezVSE(grepStruct* newGrep, FILE* fp, int* counter, char* argv,
                    char* pattern[]) {
  regex_t re = {0};
  int iFlag = 0, t = 0, j = 0, strNum = 0, count = 0, score = 0, someCount = 0,
      lastStr = 0;
  char buffer[BUFFER_SIZE] = " ";
  count = *counter;
  if (newGrep->i == 1) {
    iFlag = REG_ICASE;
  }
  while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
    score = 0;
    strNum++;
    j = 0;
    while (pattern[j] != NULL) {
      t = regcomp(&re, pattern[j], iFlag);
      if (t == 0) {
        if (regexec(&re, buffer, 0, NULL, 0) == 0) {
          lastStr = strNum;
          if (score == 0) {
            if (pattern[j][0] == '.') {
              if (buffer[0] != '\n') {
                someCount++;
              }
            } else {
              someCount++;
            }
            if (newGrep->f == 1) {
              count = *counter - 1;
            }
            decider(count, newGrep, argv, strNum, buffer, pattern, j);
          }
          score++;
        }
      }
      regfree(&re);
      j++;
    }
  }
  bezVEDec(newGrep, count, argv, someCount);
  if (lastStr == strNum && buffer[0] != '\n') nFinder(newGrep, buffer);
}

int patternF(FILE* fp1, int argc, char* argv[], char* pattern, FILE* fp,
             char pattern1[100][BUFFER_SIZE], char* ePattern[], int y, int s) {
  int numb = 0;
  for (int i = 0; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] == 'f') {
      if ((fp1 = fopen(argv[i + 1], "r")) != NULL) {
        numb = i + 1;
      } else {
        fprintf(stderr, "%s: No such file or directory\n", argv[i + 1]);
        return s;
      }
      fclose(fp1);
    }
  }
  fp1 = fopen(argv[numb], "r");
  while (fgets(pattern, BUFFER_SIZE, fp1) != NULL) {
    if (pattern[0] == '\n') {
      while (fgets(pattern, BUFFER_SIZE, fp) != NULL) {
        fprintf(stdout, "%s", pattern);
      }
      return s;
    }
  }
  fclose(fp1);
  fp1 = fopen(argv[numb], "r");
  while (fgets(pattern, BUFFER_SIZE, fp1) != NULL) {
    int i = 0;
    while (pattern[i] != '\0') {
      if (pattern[i] != '\n') {
        pattern1[y][i] = pattern[i];
      }
      if (i == 0 && pattern[i] == '\n') {
        pattern1[y][i] = pattern[i];
      }
      i++;
    }
    ePattern[s] = pattern1[y];
    s++;
    y++;
  }
  fclose(fp1);
  return s;
}

void sVEDec(grepStruct* newGrep, int count, char* argv, int strCount) {
  if (newGrep->c == 1) {
    if (count > 1 && newGrep->h == 0) {
      fprintf(stdout, "%s:", argv);
    }
    if (newGrep->l == 0) {
      fprintf(stdout, "%d\n", strCount);
    } else if (newGrep->l == 1 && strCount > 0) {
      fprintf(stdout, "1\n");
    } else {
      fprintf(stdout, "0\n");
    }
  }
  if (strCount > 0 && newGrep->l == 1) {
    fprintf(stdout, "%s\n", argv);
  }
}

void oFunc(char* buffer, char* pattern[], int j) {
  int s = 0;
  char *t = " ", *st = " ";
  st = buffer;
  int c = 0;
  while (1) {
    t = strstr(st, pattern[j]);
    if (!t) break;
    c++;
    st = t + 1;
    if (st[0] == '\0') break;
  }
  if (c == 1) {
    while (pattern[j][s] != '\0') {
      if (pattern[j][s] != '^') {
        fprintf(stdout, "%c", pattern[j][s]);
      }
      s++;
    }
  } else {
    int ev = 0;
    do {
      while (pattern[j][s] != '\0') {
        if (pattern[j][s] != '^') {
          fprintf(stdout, "%c", pattern[j][s]);
        }
        s++;
      }
      if (c == 0) {
        c = 1;
      } else {
        if (ev + 1 != c) {
          fprintf(stdout, "\n");
        }
      }
      ev++;
      s = 0;
    } while (ev != c);
  }
  fprintf(stdout, "\n");
}

void decider(int count, grepStruct* newGrep, char* argv, int strNum,
             char* buffer, char* pattern[], int j) {
  if (count > 1 && newGrep->h == 0 && newGrep->c == 0 && newGrep->l == 0) {
    fprintf(stdout, "%s:", argv);
  }
  if (newGrep->n == 1 && newGrep->c == 0 && newGrep->l == 0) {
    fprintf(stdout, "%d:", strNum);
  }
  if (newGrep->o == 1 && newGrep->c == 0 && newGrep->l == 0) {
    oFunc(buffer, pattern, j);
  }
  if (newGrep->c == 0 && newGrep->l == 0 && newGrep->o == 0) {
    fprintf(stdout, "%s", buffer);
  }
}

void bezVEDec(grepStruct* newGrep, int count, char* argv, int someCount) {
  if (newGrep->c == 1) {
    if (count > 1 && newGrep->h == 0) {
      fprintf(stdout, "%s:", argv);
    }
    if (newGrep->l == 0) {
      fprintf(stdout, "%d\n", someCount);
    } else if (newGrep->l == 1 && someCount > 0) {
      fprintf(stdout, "1\n");
    } else {
      fprintf(stdout, "0\n");
    }
  }
  if (someCount > 0 && newGrep->l == 1) {
    fprintf(stdout, "%s\n", argv);
  }
}

void nFinder(grepStruct* newGrep, char* buffer) {
  if (newGrep->c == 0 && newGrep->l == 0 && newGrep->v == 0 &&
      newGrep->o == 0) {
    int z = 0;
    while (buffer[z] != '\0') {
      if (buffer[z + 1] == '\0' && buffer[0] != '\n') {
        if (buffer[z] != '\n') {
          fprintf(stdout, "\n");
        }
      }
      z++;
    }
  }
}

void nFinderBezV(grepStruct* newGrep, char* buffer) {
  if (newGrep->c == 0 && newGrep->l == 0) {
    int z = 0;
    while (buffer[z] != '\0') {
      if (buffer[z + 1] == '\0' && buffer[0] != '\n') {
        if (buffer[z] != '\n') {
          fprintf(stdout, "\n");
        }
      }
      z++;
    }
  }
}

void deciderForV(int count, grepStruct* newGrep, char* argv, int strNum,
                 char* buffer) {
  if (count > 1 && newGrep->h == 0 && newGrep->c == 0 && newGrep->l == 0) {
    fprintf(stdout, "%s:", argv);
  }
  if (newGrep->n == 1 && newGrep->c == 0 && newGrep->l == 0) {
    fprintf(stdout, "%d:", strNum);
  }
  if ((newGrep->o == 1 || newGrep->o == 0) && newGrep->c == 0 &&
      newGrep->l == 0) {
    fprintf(stdout, "%s", buffer);
  }
}
