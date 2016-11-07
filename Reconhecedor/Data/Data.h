void initData();
bool isNumber();
bool isIdentifier();
void getNextToken();
bool isTokenEqual(char *word);
bool isTokenOnList(char *wordList[], int size);
void lookTokenAhead();
bool isNextTokenIdentifier();
bool isNextTokenNumber();
bool isNextTokenEqual(char *word);
bool isNextTokenOnList(char *wordList[], int size);

char *getCurrentToken();

