#include <stdio.h>
#include<string.h>
#include "../Lexico/Lex.h"

#define FILE_NAME "Reconhecedor/ENTRADA.txt"

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
bool isBooleanExp(char *possibleFinalWords[], int size);
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
  printf("TODO\n");
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
  if (isTokenEqual(";") || isTokenEqual(")") || isTokenEqual("]")) {
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
  if(!isIdentifier() && !isTokenEqual("main")) {
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
    if (isFunctionCallCommand()) {
      getNextToken();
      if (!isTokenEqual(";")) {
        return false;
      }
      getNextToken();
    }
  }

  if (isIteraction() || isDeclarationCommand() || isAttribution(";") || isReturnCommand()) {
    getNextToken();
  } else if (!isConditional()) {
    return false;
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
  char *finalWords[1] = {")"};

  if (!isTokenEqual("se")) {
    return false;
  }

  getNextToken();
  if (!isTokenEqual("(")) {
    return false;
  }

  getNextToken();
  if (!isBooleanExp(finalWords, 1)) {
    return false;
  }

  getNextToken();
  if (!isTokenEqual("{")) {
    return false;
  }
  printf("A\n");
  getNextToken();
  if (!isCommandList()) {
    return false;
  }

  printf("C\n");
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

  if (!isArithmeticExp(beforeFinalWords, 0)) {
    return false;
  }

  if (isTokenOnList(beforeFinalWords, 4)) {
    getNextToken();
    if(!isArithmeticExp(beforeFinalWords, 0)) {
      return false;
    }
  }

  return true;
}

bool isFactor() {
  semantico_tbd();
  char *finalWords[1] = {")"};

  if (isMatrixIdentifier()) {
    return true;
  }

  if (isNumber() || isFunctionCallCommand()) {
    getNextToken();
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

bool isFactorBool() {
  semantico_tbd();
  char *finalWords[1] = {")"};

  if (isTokenEqual("(")) {
    getNextToken();
    if (isBooleanExp(finalWords, 1)) {
      getNextToken();
      return true;
    }
  }

  if (isTokenEqual("!")) {
    getNextToken();
  }

  if (!isComparison()) {
    return false;
  }

  return true;
}

bool isTermBool() {
  semantico_tbd();

  if (!isFactorBool()) {
    return false;
  }

  while (isTokenEqual("&")) {
    getNextToken();
    if (!isFactorBool()) {
      return false;
    }
  }

  return true;
}

bool isBooleanExp(char *possibleFinalWords[], int size) {
  semantico_tbd();

  if (!isTermBool()) {
    return false;
  }

  while (isTokenEqual("||")) {
    getNextToken();
    if (!isTermBool()) {
      return false;
    }
  }

  if (size != 0 && !isTokenOnList(possibleFinalWords, size)) {
    return false;
  }

  return true;
}

bool isExp(char *finalWords[], int size) {
  semantico_tbd();

  return isArithmeticExp(finalWords, size) || isBooleanExp(finalWords, size);
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
  char *finalWords[1] = {")"};

  if (!isTokenEqual("enquanto")) {
    return false;
  }

  getNextToken();
  if (!isTokenEqual("(")) {
    return false;
  }

  getNextToken();
  if (!isBooleanExp(finalWords, 1)) {
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
  char *finalWords[1] = {";"};

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
  if (!isBooleanExp(finalWords, 1)) {
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
  file = fopen(FILE_NAME, "r");

  if (!file) {
    printf("Erro ao ler arquivo!\n");
    return 0;
  }

  while(!feof(file)) {
    getToken(file, &token);
    if (isFunction() || isDeclarationCommand()) {
      //Identified Function or Declaration
    } else if (token.token[0] == -1) {
        printf("Texto da linguagem aceito!");
        return 0;
    } else {
      printf("Texto da linguagem incorreto!");
      return 0;
    }
  }

  fclose(file);
  return 0;
}

