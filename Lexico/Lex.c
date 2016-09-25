#include <stdio.h>
#include <strings.h>
#include "Table/Table.h"

#define FILE_NAME "ExTest.car"

void advanceLargeComment(FILE *file) {
  char symbols[3];
  symbols[1] = ' '; symbols[2] = 0;

  while (strcmp(symbols, "*/") != 0) {
    symbols[0] = symbols[1];
    symbols[1] = fgetc(file);
  }
}

void advanceLineComment(FILE *file) {
  char symbol = 0;

  while (symbol != '\n') {
    symbol = fgetc(file);
  }
}

void reset(char *stringToReset) {
  int i;
  for (i = 0; i < MAX_TOKEN_SIZE; i++) {
    stringToReset[i] = 0;
  }
}

void getToken(FILE *file, char *token) {
  char possibleToken[MAX_TOKEN_SIZE];
  int i = 0;

  while (!feof(file)) {
    char current = fgetc(file);

    char currentString[2];
    currentString[1] = 0;
    currentString[0] = current;

    possibleToken[i+1] = 0;

    if (current == '/') {
      possibleToken[i] = current;
      current = fgetc(file);
      if (current == '/') {
        advanceLineComment(file);
      } else if (current == '*') {
        advanceLargeComment(file);
      } else {
        strcpy(token, possibleToken);
        return;
      }
      reset(possibleToken);
      i = 0;
    } else if (current == ' ' || current == '\n') {
      if (i == 0) {
        continue;
      } else {
        strcpy(token, possibleToken);
        return;
      }
    } else if (hasOnTable(possibleToken) == true) {
      strcpy(token, possibleToken);
      return;
    } else if (hasOnTable(currentString) == true) {
        if (i != 0) {
          ungetc(current, file);
          strcpy(token, possibleToken);
          return;
        } else {
          token[0] = current;
          token[1] = 0;
          return;
        }
    } else if (i > 100) {
      reset(possibleToken);
      i = 0;
    } else {
      possibleToken[i] = current;
      i++;
    }
  }

}

int main() {
  char token[100];
  FILE *file = fopen(FILE_NAME, "r");
  buildTable();

  while(!feof(file)) {
    getToken(file, token);
    printf("%s\n", token);
    reset(token);
  }

  fclose(file);
  return 0;
}

