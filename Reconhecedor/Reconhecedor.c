#include <stdio.h>
#include <string.h>
#include "../Lexico/Lex.h"
#include "Data/Data.h"
#include "Programa/Programa.h"

#define FILE_NAME "Reconhecedor/ENTRADA.txt"

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
    printf("\nTexto da linguagem aceito!");
  } else {
    printf("\nTexto da linguagem nao aceito!");
  }

  finishLex();

  return 0;
}

