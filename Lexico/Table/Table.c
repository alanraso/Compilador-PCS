#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Table.h"

#define TABLE_MAX_SIZE 200
#define TABLE_LINE_MAX_SIZE 50
#define TABLE_FILE_PATH "Lexico/Table/Table.txt"

Token tokenTable[TABLE_MAX_SIZE];
int tableSize = 0;

bool isLetter(char c) {
  return c >= 'A' && c <= 'z';
}

bool isDigit(char c) {
  return c >= '0' && c <= '9';
}

void addTokenOnTable(char *line, int count) {
  char *token = strtok(line, " ");
  char *number = strtok(strtok(NULL, " "), "\n");

  strcpy(tokenTable[count].token, token);
  tokenTable[count].type = number[0] - '0';
}

void buildTable() {
  FILE *tableFile;
  char line[TABLE_LINE_MAX_SIZE];
  int count = 0;
  tableFile = fopen(TABLE_FILE_PATH, "r");

  if (!tableFile) {
    printf("Erro ao ler o arquivo!");
  }

  // Ignorar primeiras duas linha
  fgets(line, TABLE_LINE_MAX_SIZE, tableFile);
  fgets(line, TABLE_LINE_MAX_SIZE, tableFile);

  while(fgets(line, TABLE_LINE_MAX_SIZE, tableFile) != NULL) {
    addTokenOnTable(line, count);
    count++;
  }

  tableSize = count;
  fclose(tableFile);
}

int getTokenType(const char *token) {
  int i; char firstChar = token[0];

  if (tableSize == 0) {
    buildTable();
  }

  if (isDigit(firstChar) || (firstChar == '.' && isDigit(token[1]))) {
    return Number;
  }

  for (i = 0; i < tableSize; i++) {
    Token tokenFromTable = tokenTable[i];
    //printf("%s\n", token);
    if (strcmp(tokenFromTable.token, token) == 0) {
      return tokenFromTable.type;
    }
  }

  if (isLetter(firstChar)) {
    return ID;
  }

  return None;
}
