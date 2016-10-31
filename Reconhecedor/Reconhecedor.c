#include <stdio.h>
#include "../Lexico/Lex.h"

#define FILE_NAME "Reconhecedor/ENTRADA.txt"

int main() {
  char token[100]; int type;
  FILE *file = fopen(FILE_NAME, "r");

  printf("Tipos -> 0 - Identificador, 1 - Palavra reservada, 2 - Numero, 3 - Sinal, 4 - Nenhum\n\n");
  printf("Token                        Tipo\n");

  while(!feof(file)) {
    type = getToken(file, token);
    printToken(token, type);
  }

  fclose(file);
  return 0;
}

