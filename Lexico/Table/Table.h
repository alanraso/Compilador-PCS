#include <stdbool.h>

#define MAX_TOKEN_SIZE 100

enum TokenType {
  ID = 0, Reserved, Number, Operator, None
};

typedef struct Token {
  char token[MAX_TOKEN_SIZE];
  int type;
} Token;

bool isLetter(char c);
bool isDigit(char c);
int getTokenType(const char *token);

