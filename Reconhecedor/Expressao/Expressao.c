#include <stdio.h>
#include <string.h>
#include "../../Lexico/Lex.h"
#include "../Data/Data.h"

int finalExpressionStateList[3] = {2, 4, 10};
char *operators[13] = {">", "<", "<=", ">=", "=", "!=", "&", "||", "+", "-", "*", "/", "**"};

int getExpressionStateFrom0();
int getExpressionStateFrom1();
int getExpressionStateFrom2();
int getExpressionStateFrom3();
int getExpressionStateFrom4();
int getExpressionStateFrom5();
int getExpressionStateFrom6();
int getExpressionStateFrom7();
int getExpressionStateFrom8();
int getExpressionStateFrom9();
int getExpressionStateFrom10();
int getExpressionStateFrom11();
bool isExpressionFinalState(int state);

bool isExpression() {
  int state = 0;

  while (1) {
    switch (state) {
      case 0:
        state = getExpressionStateFrom0();
        break;
      case 1:
        state = getExpressionStateFrom1();
        break;
      case 2:
        state = getExpressionStateFrom2();
        break;
      case 3:
        state = getExpressionStateFrom3();
        break;
      case 4:
        state = getExpressionStateFrom4();
        break;
      case 5:
        state = getExpressionStateFrom5();
        break;
      case 6:
        state = getExpressionStateFrom6();
        break;
      case 7:
        state = getExpressionStateFrom7();
        break;
      case 8:
        state = getExpressionStateFrom8();
        break;
      case 9:
        state = getExpressionStateFrom9();
        break;
      case 10:
        state = getExpressionStateFrom10();
        break;
      case 11:
        state = getExpressionStateFrom11();
        break;
      default:
        printf("Automato de Expressao: estado fora do alcance!");
        break;
    }

    if (state == Reject) {
      return false;
    }
    if (state == Accept) {
      return true;
    }

    if (!isExpressionFinalState(state)) {
      getNextToken();
    }
  }

  return false;
}

bool isExpressionFinalState(int state) {
  int i;

  for (i = 0; i < 3; i++) {
    if (finalExpressionStateList[i] == state) {
      return true;
    }
  }

  return false;
}

int getExpressionStateFrom0() {
  if (isTokenEqual("-")) return 1;
  if (isTokenEqual("!")) return 1;
  if (isIdentifier()) return 2;
  if (isTokenEqual("(")) return 3;
  if (isNumber()) return 4;
  return Reject;
}

int getExpressionStateFrom1() {
  if (isTokenEqual("!")) return 1;
  if (isIdentifier()) return 2;
  if (isTokenEqual("(")) return 3;
  if (isNumber()) return 4;
  return Reject;
}

int getExpressionStateFrom2() {
  lookTokenAhead();

  if (isNextTokenEqual("-") || isNextTokenEqual("!") || isNextTokenOnList(operators, 13)) {
    getNextToken();
    return 1;
  }
  if (isNextTokenIdentifier()) {
    getNextToken();
    return 2;
  }
  if (isNextTokenEqual("[")) {
    getNextToken();
    return 5;
  }
  if (isNextTokenEqual("(")) {
    getNextToken();
    return 6;
  }
  if (isNextTokenNumber()) {
    getNextToken();
    return 4;
  }

  return Accept;
}

int getExpressionStateFrom3() {
  if (isExpression()) return 11;
  return Reject;
}

int getExpressionStateFrom4() {
  lookTokenAhead();

  if (isNextTokenEqual("-") || isNextTokenEqual("!") || isNextTokenOnList(operators, 13)) {
    getNextToken();
    return 1;
  }
  if (isNextTokenIdentifier()) {
    getNextToken();
    return 2;
  }
  if (isNextTokenEqual("[")) {
    getNextToken();
    return 5;
  }
  if (isNextTokenEqual("(")) {
    getNextToken();
    return 3;
  }
  if (isNextTokenNumber()) {
    getNextToken();
    return 4;
  }

  return Accept;
}

int getExpressionStateFrom5() {
  if (isExpression()) return 9;
  if (isTokenEqual("[")) return 10;
  return Reject;
}

int getExpressionStateFrom6() {
  if (isExpression()) return 7;
  if (isTokenEqual(")")) return 4;
  return Reject;
}

int getExpressionStateFrom7() {
  if (isTokenEqual(",")) return 8;
  if (isTokenEqual(")")) return 4;
  return Reject;
}

int getExpressionStateFrom8() {
  if (isExpression()) return 7;
  return Reject;
}

int getExpressionStateFrom9() {
  if (isTokenEqual("]")) return 10;
  return Reject;
}

int getExpressionStateFrom10() {
  lookTokenAhead();

  if (isNextTokenEqual("-") || isNextTokenEqual("!") || isNextTokenOnList(operators, 13)) {
    getNextToken();
    return 1;
  }
  if (isNextTokenIdentifier()) {
    getNextToken();
    return 2;
  }
  if (isNextTokenEqual("[")) {
    getNextToken();
    return 5;
  }
  if (isNextTokenEqual("(")) {
    getNextToken();
    return 3;
  }
  if (isNextTokenNumber()) {
    getNextToken();
    return 4;
  }

  return Accept;
}

int getExpressionStateFrom11() {
  if (isTokenEqual(")")) return 4;
  return Reject;
}
