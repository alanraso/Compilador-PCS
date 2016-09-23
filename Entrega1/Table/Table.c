#include <stdio.h>
#include <stdbool.h>

#define TABLE_MAX_SIZE 100
#define TABLE_LINE_MAX_SIZE 20
#define TABLE_FILE_NAME "Table.txt"

char tokenTable[TABLE_MAX_SIZE][TABLE_LINE_MAX_SIZE];
int tableSize;

int convertStringToInt(char *number) {
    int i = 0, lenght = strlen(number), convertedNumber = 0, pot = 1;

    for(i = lenght - 1; i >= 0; i--) {
        convertedNumber = convertedNumber + pot*(number[i] - '0');
        pot = pot*10;
    }
    return convertedNumber;
}

void addTokenOnTable(char *line) {
    char *number = strtok(line, " ");
    char *token = strtok(strtok(NULL, " "), "\n");

    strcpy(tokenTable[convertStringToInt(number)], token);
}

void buildTable() {
  FILE *tableFile = fopen("TABLE_FILE_NAME", "r");
  char line[TABLE_LINE_MAX_SIZE];
  int count = 0;

  if (!tableFile) {
    printf("Erro ao ler o arquivo!");
  }

  while(fgets(line, TABLE_LINE_MAX_SIZE, tableFile) != NULL) {
     addTokenOnTable(&line);
     count++
  }

  size = count;
  fclose(tableFile);
}

bool hasOnTable(char *symbol) {
  int i;
  for (i = 0; i < size; i++) {
    if (tokenTable[i] == symbol) {
      return 1;
    }
  }
  return 0;
}
