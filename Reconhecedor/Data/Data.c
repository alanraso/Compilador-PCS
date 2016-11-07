#include <string.h>
#include <stdio.h>
#include "../../Lexico/Lex.h"

#define FILE_NAME "Reconhecedor/ENTRADA_DEV.txt"

/* *******************************
    Fun��es Auxiliares
   ******************************* */

Token token;
Token lookAheadToken;

void initData() {
  lookAheadToken.type = -1;
}

bool isNumber() {
  return token.type == Number;
}

bool isIdentifier() {
  return token.type == ID;
}

void getNextToken() {
  if (lookAheadToken.type == -1) {
    getToken(&token);
  } else {
    token = lookAheadToken;
    lookAheadToken.type = -1;
  }
  printf("Token: %s -> tipo: %d\n", token.token, token.type);
}

bool isTokenEqual(char *word) {
  return strcmp(token.token, word) == 0;
}

bool isTokenOnList(char *wordList[], int size) {
  int i;

  for (i = 0; i < size; i ++) {
    if (isTokenEqual(wordList[i])) {
      return true;
    }
  }

  return false;
}

void lookTokenAhead() {
  getToken(&lookAheadToken);
}

bool isNextTokenIdentifier() {
  return lookAheadToken.type == ID;
}

bool isNextTokenNumber() {
  return lookAheadToken.type == Number;
}

bool isNextTokenEqual(char *word) {
  return strcmp(word, lookAheadToken.token) == 0;
}

bool isNextTokenOnList(char *wordList[], int size) {
  int i;

  for (i = 0; i < size; i++) {
    if (strcmp(wordList[i], lookAheadToken.token) == 0) {
      return true;
    }
  }

  return false;
}

char *getCurrentToken() {
  return token.token;
}
