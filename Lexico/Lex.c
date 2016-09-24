#include <stdio.h>
#include <strings.h>
#include "Table/Table.h"

#define FILE_NAME "ExTest.car"

FILE *file;

void advanceLargeComment() {
  char symbols[3];
  symbols[1] = ' '; symbols[2] = 0;

  while (strcmp(symbols, "*/") != 0) {
    symbols[0] = symbols[1];
    symbols[1] = fgetc(file);
  }
}

void advanceLineComment() {
  char symbol = 0;

  while (symbol != '\n') {
    symbol = fgetc(file);
  }
}

void getToken() {
  file = fopen(FILE_NAME, "r");
  char symbols[3]; symbols[2] = 0;
  char possibleToken[100];
  int i = 0;

  while (!feof(file)) {
    char current = fgetc(file);

    symbols[0] = symbols[1];
    symbols[1] = current;

    if (strcmp(symbols, "/*") == 0) {
      advanceLargeComment();
    } else if (strcmp(symbols, "//") == 0) {
      advanceLineComment();
    } else if (current == ' ' || current == '\n') {
      continue;
    } else {
        printf("%c", current);
    }

  }
}

int main() {
  getToken();
  return 0;
}

