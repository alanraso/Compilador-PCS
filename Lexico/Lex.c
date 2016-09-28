#include <stdio.h>
#include <strings.h>
#include "Table/Table.h"

#define FILE_NAME "ENTRADA.txt"

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

char lookAhead(FILE *file) {
  char c = fgetc(file);

  ungetc(c, file);
  return c;
}

bool isCompoundSymbol(FILE *file, const char current, char *token) {
    if (current == ':' && lookAhead(file) == '=') {
      fgetc(file);
      strcpy(token, ":=");
      return true;
    } else if (current == '|' && lookAhead(file) == '|') {
      fgetc(file);
      strcpy(token, "||");
      return true;
    }

    return false;
}

int getToken(FILE *file, char *token) {
  char current, possibleToken[100];
  int i = 0;

  while (!feof(file)) {
    current = fgetc(file);

    if (isDigit(current)) {
      possibleToken[i] = current; i++;
    } else if (current == '.' && isDigit(lookAhead(file))) {
      possibleToken[i] = current; i++;
    } else if (isLetter(current)) {
      possibleToken[i] = current; i++;
    } else if ((current == ' ' || current == '\n') && i == 0) {
      continue;
    } else if (isCompoundSymbol(file, current, token)) {
      break;
    } else if (current == '/' && lookAhead(file) == '*') {
      advanceLargeComment(file);
    } else if (current == '/' && lookAhead(file) == '/') {
      advanceLineComment(file);
    } else if (i != 0) {
      ungetc(current, file);
      possibleToken[i] = 0;
      strcpy(token, possibleToken);
      break;
    } else {
      token[0] = current;
      token[1] = 0;
      break;
    }
  }

  return getTokenType(token);
}

void reset(char *stringToReset) {
  int i;
  for (i = 0; i < MAX_TOKEN_SIZE; i++) {
    stringToReset[i] = 0;
  }
}

void printToken(const char *token, int type) {
  if (token[0] == EOF) {
    return;
  }

  int i;
  printf("%s", token);
  for (i = 0; i < 30 - strlen(token); i++) {
    printf(" ");
  }
  printf("%d\n", type);
}

int main() {
  char token[100]; int type;
  FILE *file = fopen(FILE_NAME, "r");

  printf("Tipos -> 0 - Identificador, 1 - Palavra reservada, 2 - Numero, 3 - Sinal, 4 - Nenhum\n\n");
  printf("Token                        Tipo\n");
  while(!feof(file)) {
    type = getToken(file, token);
    printToken(token, type);
    reset(token);
  }

  fclose(file);
  return 0;
}

