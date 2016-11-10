#include <stdio.h>
#include <string.h>
#include "../Lexico/Lex.h"
#include "Data/Data.h"
#include "Expressao/Expressao.h"
#include "Comando/Command.h"
#include "Programa/Programa.h"

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
  if (isProgram()) {
    printf("FOI!\n");
  } else {
    printf("NAO FOI!\n");
  }

  finishLex();

  return 0;
}

