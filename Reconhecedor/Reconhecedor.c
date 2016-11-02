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
bool isAttribution();
bool isConditional();
bool isIteraction();
bool isFunctionCallCommand();
bool isReturnCommand();
bool isArithmeticExp();
bool isBooleanExp();
bool isExp();

bool isArgumentList();
bool isDeclarationParameter();
bool isParametersList();
void getNextToken();
bool isTokenEqual(char *word);
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
  if (isArithmeticExp()) {
    getNextToken();
  }
  if (!isTokenEqual("]")) {
    return false;
  }

  getNextToken();
  if (!isTokenEqual(";")) {
    return false;
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
  printf("Comecou\n");
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

  if (isReturnCommand() || isFunctionCallCommand() || isAttribution()) {
    getNextToken();
    if (!isTokenEqual(";")) {
      return false;
    }
    getNextToken();
  } else if (isIteraction() || isConditional() || isDeclarationCommand()) {
    getNextToken();
  }

  if (isTokenEqual("}")) {
    return true;
  }

  return isCommandList();
}

bool isAttribution() {
  semantico_tbd();

  if (!isTokenEqual(":=")) {
    return false;
  }

  getNextToken();
  if (!isExp()) {
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

  if (!isTokenEqual("retorna")) {
    return false;
  }

  getNextToken();
  if (!isExp()) {
    return false;
  }

  return true;
}

bool isComparison() {
  semantico_tbd();

  if (!isArithmeticExp()) {
    return false;
  }

  getNextToken();
  if (!isTokenEqual(">") && !isTokenEqual("<") && !isTokenEqual("=") && !isTokenEqual("!=")) {
    return false;
  }

  getNextToken();
  if (!isArithmeticExp()) {
    return false;
  }

  return true;
}

bool isArithmeticExp() {
  semantico_tbd();

  //TODO: do
  return isNumber();
}

bool isBooleanExp() {
  semantico_tbd();

  //TODO: do
  if (!isTokenEqual("comp")) {
    return false;
  }
  return true;
}

bool isExp() {
  semantico_tbd();

  //TODO: do
  if (!isNumber()) {
    return false;
  }
  return true;
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

bool isVariableType() {
  return isTokenEqual("int") || isTokenEqual("bool") || isTokenEqual("pflut") || isTokenEqual("caract");
}

bool isIsolatedAttribuition() {
  getNextToken();
  return isAttribution();
}

bool isIsolatedFunctionCall() {
  getNextToken();
  return isFunctionCallCommand();
}

bool isParametersList() {
  while(!isTokenEqual(")")) {
    if (!isExp()) {
      return false;
    }

    getNextToken();
    if (isTokenEqual(",")) {
      getNextToken();
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
  if (!isIsolatedAttribuition()) {
    return false;
  }

  getNextToken();
  if (!isTokenEqual(";")) {
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
  if (!isIsolatedAttribuition()) {
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

/* *******************************
    Main
   ******************************* */

int main() {
  file = fopen(FILE_NAME, "r"); int i;

  if (!file) {
    printf("Erro ao ler arquivo!\n");
    return 0;
  }

  for (i = 0; i < 2; i ++) {
    getToken(file, &token);
    if (isFunction()) {
      printf("Funcao!\n");
    } else if (isDeclarationCommand()) {
      printf("Declaracao!\n");
    } else {
      printf("Fodeu!\n");
    }
  }

//  while(!feof(file)) {
//
//  }

  fclose(file);
  return 0;
}

