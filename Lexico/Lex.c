#include <stdio.h>
#include <strings.h>
#include "Table/Table.h"

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

void getToken(FILE *file, Token *tokenToReturn) {
  char current, possibleToken[MAX_TOKEN_SIZE], token[MAX_TOKEN_SIZE];
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

  strcpy(tokenToReturn->token, token);
  tokenToReturn->type = getTokenType(token);
  printf("Get Token: %s / tipo: %d\n", tokenToReturn->token, tokenToReturn->type);
}
