#include <stdio.h>
#include "./Table/Table.h"

#define FILE_NAME "ExTest.car"

bool isOnComment(char *symbol, bool *isOnLargeComment, bool *isOnLineComment) {
  if (*isOnLargeComment && symbol[0] == '*' && symbol[1] == '/') {
    *isOnLargeComment = false;
  } else if (!*isOnLargeComment && symbol[0] == '/' && symbol[1] == '*') {
    *isOnLargeComment = true;
  }

  if (*isOnLineComment && symbol[1] == '\n') {
    *isOnLineComment = false;
  } else if (!*isOnLineComment && symbol[0] == '/' && symbol[1] == '/') {
    *isOnLineComment = true;
  }

  return *isOnLargeComment || *isOnLineComment;
}

bool shouldContinue(char *symbol, bool *isOnLargeComment, bool *isOnLineComment) {
    if (symbol[0] == ' ') {
      return true;
    }

    if (isOnComment(symbol, isOnLargeComment, isOnLineComment)) {
      return true;
    }

    if (symbol[0] == '\n') {
      return true;
    }

    return false;
}

void getTokens() {
  FILE *file = fopen(FILE_NAME, "r");
  char symbol[3];
  bool isOnLargeComment = false, isOnLineComment = false;

  int i = 0;
  char lido[1000];

  symbol[1] = ' ';
  while (!feof(file)) {
    symbol[0] = symbol[1];
    symbol[1] = fgetc(file);

    lido[i] = symbol[1];
    i++;
    //printf("\n\nLido ate agora: %s", lido);

    if(shouldContinue(symbol, &isOnLargeComment, &isOnLineComment)) {
        continue;
    }
  }
}

int main() {
  getTokens();
  return 0;
}
