#include <stdio.h>
#include<string.h>
#include "../Lexico/Lex.h"

#define FILE_NAME "Reconhecedor/ENTRADA_DEV.txt"

FILE *file;
Token token;

/* *******************************
    Declarações
   ******************************* */

bool isConditional();
bool isVariableType();
bool isCommandList();
bool isAttribution(char *finalWord);
bool isConditional();
bool isIteraction();
bool isFunctionCallCommand();
bool isReturnCommand();
bool isFactor();
bool isTerm();
bool isArithmeticExp(char *possibleFinalWords[], int size);
bool isBooleanExp();
bool isExp(char *finalWords[], int size);

bool isArgumentList();
bool isDeclarationParameter();
bool isParametersList();
void getNextToken();
bool isTokenEqual(char *word);
bool isTokenOnList(char *words[], int size);
bool isWhileCommand();
bool isForCommand();

void semantico_tbd() {
  //TODO: imprimir TODO
  //printf("TODO\n");
}

/* *******************************
    Funções derivadas dos autômatos
   ******************************* */

bool isIdentifier() {
  semantico_tbd();
  return token.type == ID;
}

bool isNumber() {
  semantico_tbd();
  return token.type == Number;
}

bool isMatrixIdentifier() {
  semantico_tbd();
  char *finalWords[1] = {"]"};

  if (!isIdentifier()) {
    return false;
  }

  getNextToken();
  if (isTokenEqual(";")) {
    return true;
  }
  if (!isTokenEqual("[")) {
    return false;
  }

  if (isArithmeticExp(finalWords, 1)) {
    getNextToken();
  }

  return true;
}

bool isDeclarationCommand() {
  semantico_tbd();

  if (token.type != Reserved || !isVariableType()) {
    return false;
  }

  getNextToken();
  if (!isMatrixIdentifier()) {
    return false;
  }

  if (!isTokenEqual(";")) {
    return false;
  }

  return true;
}

bool isFunction() {
  semantico_tbd();

  if (token.type != Reserved || !isTokenEqual("func")) {
    return false;
  }

  getNextToken();
  if(!isIdentifier()) {
    return false;
  }

  getNextToken();
  if (!isTokenEqual("(")) {
    return false;
  }

  getNextToken();
  if (!isArgumentList()) {
    return false;
  }

  getNextToken();
  if (!isTokenEqual("(")) {
    return false;
  }

  getNextToken();
  if (isVariableType()) {
    getNextToken();
  }
  if (!isTokenEqual(")")) {
    return false;
  }

  getNextToken();
  if (!isTokenEqual("{")) {
    return false;
  }

  getNextToken();

  if (!isCommandList()) {
    return false;
  }

  return true;
}

bool isCommandList() {
  semantico_tbd();

  if (isIdentifier()) {
    getNextToken();
  }

  if (isFunctionCallCommand()) {
    getNextToken();
    if (!isTokenEqual(";")) {
      return false;
    }
    getNextToken();
  } else if (isIteraction() || isConditional() || isDeclarationCommand() || isAttribution(";") || isReturnCommand()) {
    getNextToken();
  }

  if (isTokenEqual("}")) {
    return true;
  }

  return isCommandList();
}

bool isAttribution(char *finalWord) {
  semantico_tbd();
  char *finalWords[1] = {finalWord};

  if (!isTokenEqual(":=")) {
    return false;
  }

  getNextToken();
  if (!isExp(finalWords, 1)) {
    return false;
  }

  return true;
}

bool isConditional() {
  semantico_tbd();

  if (!isTokenEqual("se")) {
    return false;
  }

  getNextToken();
  if (!isTokenEqual("(")) {
    return false;
  }

  getNextToken();
  if (!isBooleanExp()) {
    return false;
  }

  getNextToken();
  if (!isTokenEqual(")")) {
    return false;
  }

  getNextToken();
  if (!isTokenEqual("{")) {
    return false;
  }

  getNextToken();
  if (!isCommandList()) {
    return false;
  }

  getNextToken();
  if (isTokenEqual("senao")) {
    getNextToken();
    if (isTokenEqual("{")) {
      getNextToken();
      if (!isCommandList()) {
        return false;
      }
    } else if (!isConditional()) {
      return false;
    }
  }
  return true;
}

bool isIteraction() {
  semantico_tbd();

  if (isWhileCommand()) {
    return true;
  }
  if (isForCommand()) {
    return true;
  }
  return false;
}

bool isFunctionCallCommand() {
  semantico_tbd();

  if (!isTokenEqual("(")) {
    return false;
  }

  getNextToken();
  if (!isParametersList()) {
    return false;
  }

  return true;
}

bool isReturnCommand() {
  semantico_tbd();
  char *finalWords[1] = {";"};

  if (!isTokenEqual("retorna")) {
    return false;
  }

  getNextToken();
  if (!isExp(finalWords, 1)) {
    return false;
  }

  return true;
}

bool isComparison() {
  semantico_tbd();
  char *beforeFinalWords[4] = {">", "<", "=", "!="};
  char *afterFinalWords[1] = {""};

  if (!isArithmeticExp(beforeFinalWords, 4)) {
    return false;
  }

  getNextToken();
  if (!isArithmeticExp(afterFinalWords, 0)) {
    return false;
  }

  return true;
}

bool isFactor() {
  semantico_tbd();
  char *finalWords[1] = {")"};

  if (isNumber() || isFunctionCallCommand()) {
    getNextToken();
  } else if (!isMatrixIdentifier()) {
    return false;
  } else if (isTokenEqual("(")) {
    getNextToken();
    if (!isArithmeticExp(finalWords, 1)) {
      return false;
    }
  }

  return true;
}

bool isTerm() {
  semantico_tbd();

  if (!isFactor()) {
    return false;
  }

  while (isTokenEqual("*") || isTokenEqual("/")) {
    getNextToken();
    if (!isFactor()) {
      return false;
    }
  }

  return true;
}

bool isArithmeticExp(char *possibleFinalWords[], int size) {
  semantico_tbd();

  if (!isTerm()) {
    return false;
  }

  while (isTokenEqual("+") || isTokenEqual("-")) {
    getNextToken();
    if (!isTerm()) {
      return false;
    }
  }

  if (size != 0 && !isTokenOnList(possibleFinalWords, size)) {
    return false;
  }

  return true;
}

bool isTermBool() {
  if (!isMatrixIdentifier() && !isComparison()) {
    return false;
  }

  return true;
}

bool isBooleanExp() {
  semantico_tbd();

  return isTokenEqual("cond");
}

bool isExp(char *finalWords[], int size) {
  semantico_tbd();

  return isArithmeticExp(finalWords, size) || isBooleanExp();
}

/* *******************************
    Funções auxiliares
   ******************************* */

void getNextToken() {
  getToken(file, &token);
}

bool isTokenEqual(char *word) {
  return strcmp(token.token, word) == 0;
}

bool isTokenOnList(char *words[], int size) {
  int i;

  for (i = 0; i < size; i++) {
    if (isTokenEqual(words[i])) {
      return true;
    }
  }

  return false;
}

bool isVariableType() {
  return isTokenEqual("int") || isTokenEqual("bool") || isTokenEqual("pflut") || isTokenEqual("caract");
}

bool isIsolatedFunctionCall() {
  getNextToken();
  return isFunctionCallCommand();
}

bool isParametersList() {
  char *finalWords[2] = {",", ")"};

  while(!isTokenEqual(")")) {
    if (!isExp(finalWords, 2)) {
      return false;
    }
  }
  return true;
}

bool isArgument() {
  if (!isVariableType()) {
    return false;
  }

  getNextToken();
  if (!isIdentifier()) {
    return false;
  }
  return true;
}

bool isArgumentList() {
  while (!isTokenEqual(")")) {
    if (!isArgument()) {
      return false;
    }

    getNextToken();
    if (isTokenEqual(",")) {
      getNextToken();
    }
  }
  return true;
}

bool isWhileCommand() {
  if (!isTokenEqual("enquanto")) {
    return false;
  }

  getNextToken();
  if (!isTokenEqual("(")) {
    return false;
  }

  getNextToken();
  if (!isBooleanExp()) {
    return false;
  }

  getNextToken();
  if (!isTokenEqual(")")) {
    return false;
  }

  getNextToken();
  if (!isTokenEqual("{")) {
    return false;
  }

  getNextToken();
  if (!isCommandList()) {
    return false;
  }

  return true;
}

bool isForCommand() {
  if (!isTokenEqual("para")) {
    return false;
  }

  getNextToken();
  if (!isTokenEqual("(")) {
    return false;
  }

  getNextToken();
  if (!isIdentifier()) {
    return false;
  }

  getNextToken();
  if (!isAttribution(";")) {
    return false;
  }

  getNextToken();
  if (!isBooleanExp()) {
    return false;
  }

  getNextToken();
  if (!isTokenEqual(";")) {
    return false;
  }

  getNextToken();
  if (!isIdentifier()) {
    return false;
  }

  getNextToken();
  if (!isAttribution(")")) {
    return false;
  }

  getNextToken();
  if (!isTokenEqual("{")) {
    return false;
  }

  getNextToken();
  if (!isCommandList()) {
    return false;
  }

  return true;
}

/* *******************************
    Main
   ******************************* */

int main() {
  file = fopen(FILE_NAME, "r"); int i;

  if (!file) {
    printf("Erro ao ler arquivo!\n");
    return 0;
  }

  for(i = 0; i < 2; i ++) {
    getToken(file, &token);
    if (isFunction()) {
      printf("Funcao!\n");
    } else if (isDeclarationCommand()) {
      printf("Declaracao!\n");
    } else {
      printf("Deu ruim!\n");
    }
  }

//  while(!feof(file)) {
//
//  }

  fclose(file);
  return 0;
}

