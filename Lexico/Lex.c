#include <stdio.h>
#include <strings.h>
#include "Table/Table.h"

FILE *file;

void initLex(char *fileName, char *mode, bool *fileFound) {
  file = fopen(fileName, mode);
  *fileFound = file;
}

void finishLex() {
  fclose(file);
}

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

char lookAhead() {
  char c = fgetc(file);

  ungetc(c, file);
  return c;
}

bool isCompoundSymbol(const char current, char *token) {
    if (current == ':' && lookAhead(file) == '=') {
      fgetc(file);
      strcpy(token, ":=");
      return true;
    } else if (current == '|' && lookAhead(file) == '|') {
      fgetc(file);
      strcpy(token, "||");
      return true;
    } else if (current == '!' && lookAhead(file) == '=') {
      fgetc(file);
      strcpy(token, "!=");
      return true;
    } else if (current == '*' && lookAhead(file) == '*') {
      fgetc(file);
      strcpy(token, "**");
      return true;
    } else if ((current == '>' || current == '<') && lookAhead(file) == '=') {
      fgetc(file);
      char symbol[3] = {current, '=', 0};
      strcpy(token, symbol);
      return true;
    }

    return false;
}

void getToken(Token *tokenToReturn) {
  char current, possibleToken[MAX_TOKEN_SIZE], token[MAX_TOKEN_SIZE];
  int i = 0;

  while (!feof(file)) {
    current = fgetc(file);

    if (isDigit(current)) {
      possibleToken[i] = current; i++;
    } else if (current == '.' && isDigit(lookAhead())) {
      possibleToken[i] = current; i++;
    } else if (isLetter(current)) {
      possibleToken[i] = current; i++;
    } else if ((current == ' ' || current == '\n') && i == 0) {
      continue;
    } else if (i == 0 && isCompoundSymbol(current, token)) {
      break;
    } else if (current == '/' && lookAhead() == '*') {
      advanceLargeComment();
    } else if (current == '/' && lookAhead() == '/') {
      advanceLineComment();
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
}

bool isEOF() {
  return feof(file);
}
