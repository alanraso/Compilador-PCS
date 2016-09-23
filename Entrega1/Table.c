#include <stdio.h>

#define TABLE_MAX_SIZE 100
#define TABLE_LINE_MAX_SIZE 20
#define TABLE_FILE_NAME "Table.txt"

char tokenTable[TABLE_MAX_SIZE][TABLE_LINE_MAX_SIZE];

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
  FILE *tableFile;
  char line[TABLE_LINE_MAX_SIZE];
  tableFile = fopen("./table.txt", "r");

  if (!tableFile) {
    printf("Erro ao ler o arquivo!");
  }

  while(fgets(line, TABLE_LINE_MAX_SIZE, tableFile) != NULL) {
     addTokenOnTable(&line);
  }
}
