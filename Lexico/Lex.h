#include "Table/Table.h"

void initLex(char *fileName, char *mode, bool *fileFound);
void finishLex();
int getToken(Token *token);
bool isEOF();
