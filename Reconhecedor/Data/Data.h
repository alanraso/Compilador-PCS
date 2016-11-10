enum Finish {Reject = -1, Accept = -2};

void initData();
bool isNumber();
bool isIdentifier();
void getNextToken();
bool isTokenEqual(char *word);
bool isTokenOnList(char *wordList[], int size);
bool isVariableType();
char *getCurrentToken();

void lookTokenAhead();
bool isNextTokenVariableType();
bool isNextTokenIdentifier();
bool isNextTokenNumber();
bool isNextTokenEqual(char *word);
bool isNextTokenOnList(char *wordList[], int size);

