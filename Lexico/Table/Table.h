#include <stdbool.h>

#define MAX_TOKEN_SIZE 100

enum TokenType {
  ID = 0, Reserved, Number, Operator, None
};

bool isLetter(char c);
bool isDigit(char c);
int getTokenType(const char *token);

