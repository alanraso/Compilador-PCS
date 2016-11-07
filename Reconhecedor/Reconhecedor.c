#include <stdio.h>
#include <string.h>
#include "../Lexico/Lex.h"
#include "Data/Data.h"
#include "Expressao/Expressao.h"

#define FILE_NAME "Reconhecedor/ENTRADA_DEV.txt"

void semantico_tbd() {
  printf("TODO\n");
}

/* *******************************
    Declaracao de funcoes
   ******************************* */


/* *******************************
    Automatos
   ******************************* */

bool isArrayIdentifier() {
  if (!isIdentifier()) {
    return false;
  }

  lookTokenAhead();
  if (!isNextTokenEqual("[")) {
    return true;
  } else {
    getNextToken();
  }

  getNextToken();
  if (!isExpression()) {
    return false;
  }

  getNextToken();
  if (!isTokenEqual("]")) {
    return false;
  }

  return true;
}

bool isVariableType() {
  char *types[4] = {"int", "bool", "pflut", "charact"};
  return isTokenOnList(types, 4);
}

bool isDeclarationCommand() {
  if (!isVariableType()) {
    return false;
  }

  getNextToken();
  if (!isArrayIdentifier()) {
    return false;
  }

  return true;
}

bool isChamadaFunc() {
  return true;
}

/* *******************************
    Main
   ******************************* */

int main() {
  bool fileFound;

  initData();
  initLex(FILE_NAME, "r", &fileFound);
  if(!fileFound) {
    printf("Erro ao abrir o arquivo! Terminando o programa...\n");
    return 0;
  }

  getNextToken();
  if (isDeclarationCommand()) {
    printf("FOI\n");
  } else {
    printf("NAO FOI\n");
  }

//  while(!feof(file)) {
//    getToken(file, &token);
//    if (isFunction() || isDeclarationCommand()) {
//      //Identified Function or Declaration
//    } else if (token.token[0] == -1) {
//        printf("Texto da linguagem aceito!");
//        return 0;
//    } else {
//      printf("Texto da linguagem incorreto!");
//      return 0;
//    }
//  }

  finishLex();

  return 0;
}

