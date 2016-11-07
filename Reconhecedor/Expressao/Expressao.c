#include <stdio.h>
#include <string.h>
#include "../../Lexico/Lex.h"
#include "../Data/Data.h"

enum Finish {Reject = -1, Accept = -2};
int finalStateList[7] = {3, 5, 12, 13, 14, 16, 21};
char *operators[13] = {">", "<", "<=", ">=", "=", "!=", "&", "||", "+", "-", "*", "/", "**"};
char *prioritaryOperators[7] = {"**", "=", "<", ">", "!=", "<=", ">="};
char *otherOperators[6] = {"+", "-", "*", "/", "||", "&"};

int getStateFrom();
int getStateFrom0();
int getStateFrom1();
int getStateFrom2();
int getStateFrom3();
int getStateFrom4();
int getStateFrom5();
int getStateFrom6();
int getStateFrom7();
int getStateFrom8();
int getStateFrom9();
int getStateFrom10();
int getStateFrom11();
int getStateFrom12();
int getStateFrom13();
int getStateFrom14();
int getStateFrom15();
int getStateFrom16();
int getStateFrom17();
int getStateFrom18();
int getStateFrom19();
int getStateFrom20();
int getStateFrom21();
int getStateFrom22();
int getStateFrom23();
int getStateFrom24();
bool isFinalState(int state);

bool isExpression() {
  int state = 0;

  while (1) {
    printf("  Estado: %d    Token: %s\n", state, getCurrentToken());
    switch (state) {
      case 0:
        state = getStateFrom0();
        break;
      case 1:
        state = getStateFrom1();
        break;
      case 2:
        state = getStateFrom2();
        break;
      case 3:
        state = getStateFrom3();
        break;
      case 4:
        state = getStateFrom4();
        break;
      case 5:
        state = getStateFrom5();
        break;
      case 6:
        state = getStateFrom6();
        break;
      case 7:
        state = getStateFrom7();
        break;
      case 8:
        state = getStateFrom8();
        break;
      case 9:
        state = getStateFrom9();
        break;
      case 10:
        state = getStateFrom10();
        break;
      case 11:
        state = getStateFrom11();
        break;
      case 12:
        state = getStateFrom12();
        break;
      case 13:
        state = getStateFrom13();
        break;
      case 14:
        state = getStateFrom14();
        break;
      case 15:
        state = getStateFrom15();
        break;
      case 16:
        state = getStateFrom16();
        break;
      case 17:
        state = getStateFrom17();
        break;
      case 18:
        state = getStateFrom18();
        break;
      case 19:
        state = getStateFrom19();
        break;
      case 20:
        state = getStateFrom20();
        break;
      case 21:
        state = getStateFrom21();
        break;
      case 22:
        state = getStateFrom22();
        break;
      case 23:
        state = getStateFrom23();
        break;
      case 24:
        state = getStateFrom24();
        break;
      default:
        printf("Automato de Expressao: estado fora do alcance!");
        break;
    }
    printf("  Estado depois: %d\n", state);
    if (state == Reject) {
      return false;
    }
    if (state == Accept) {
      return true;
    }

    if (!isFinalState(state)) {
      getNextToken();
    }
  }

  return false;
}

bool isFinalState(int state) {
  int i;

  for (i = 0; i < 9; i++) {
    if (finalStateList[i] == state) {
      return true;
    }
  }

  return false;
}

int getStateFrom0 () {
  if (isTokenEqual("-")) return 1;
  if (isTokenEqual("!")) return 2;
  if (isIdentifier()) return 3;
  if (isTokenEqual("(")) return 4;
  if (isNumber()) return 5;
  return Reject;
}

int getStateFrom1 () {
  if (isIdentifier()) return 3;
  if (isTokenEqual("(")) return 4;
  if (isNumber()) return 5;
  return Reject;
}

int getStateFrom2 () {
  if (isTokenEqual("!")) return 2;
  if (isIdentifier()) return 3;
  if (isTokenEqual("(")) return 4;
  if (isNumber()) return 5;
  return Reject;
}

int getStateFrom3 () {
  lookTokenAhead();
  if (isNextTokenOnList(operators, 13)) {
    getNextToken();
    return 1;
  }
  if (isNextTokenEqual("(")) {
    getNextToken();
    return 7;
  }
  if (isNextTokenEqual("[")) {
    getNextToken();
    return 6;
  }
  return Accept;
}

int getStateFrom4 () {
  if (isExpression()) return 10;
  return Reject;
}

int getStateFrom5() {
  lookTokenAhead();

  if (isNextTokenOnList(operators, 13)) {
    getNextToken();
    return 1;
  }

  return Accept;
}

int getStateFrom6() {
  if (isExpression()) return 11;
  if (isTokenEqual("]")) return 12;
  return Reject;
}

int getStateFrom7() {
  if (isExpression()) return 8;
  if (isTokenEqual(")")) return 5;
  return Reject;
}

int getStateFrom8() {
  if (isTokenEqual(",")) return 9;
  if (isTokenEqual(")")) return 5;
  return Reject;
}

int getStateFrom9() {
  if (isExpression()) return 8;
  return Reject;
}

int getStateFrom10() {
  if (isTokenEqual(")")) return 13;
  return Reject;
}

int getStateFrom11() {
  if (isTokenEqual("]")) return 12;
  return Reject;
}

int getStateFrom12() {
  lookTokenAhead();
  if (isNextTokenOnList(operators, 13)) {
    getNextToken();
    return 1;
  }
  if (isNextTokenEqual("[")) {
    getNextToken();
    return 6;
  }
  return Accept;
}

int getStateFrom13() {
  lookTokenAhead();

  if (isNextTokenIdentifier()){
    getNextToken();
    return 14;
  }
  if (isNextTokenEqual("(")) {
    getNextToken();
    return 4;
  }
  if (isNextTokenNumber()) {
    getNextToken();
    return 13;
  }
  if (isNextTokenOnList(prioritaryOperators, 7)) {
    getNextToken();
    return 15;
  }
  if (isNextTokenOnList(otherOperators, 6)) {
    getNextToken();
    return 1;
  }

  return Accept;
}

int getStateFrom14() {
  lookTokenAhead();

  if (isNextTokenIdentifier()) {
    getNextToken();
    return 14;
  }
  if (isNextTokenEqual("[")) {
    getNextToken();
    return 17;
  }
  if (isNextTokenEqual("(")) {
    getNextToken();
    return 22;
  }
  if (isNextTokenNumber()) {
    getNextToken();
    return 13;
  }
  if (isNextTokenOnList(prioritaryOperators, 7)) {
    getNextToken();
    return 15;
  }
  if (isNextTokenOnList(otherOperators, 6)) {
    getNextToken();
    return 1;
  }

  return Accept;
}

int getStateFrom15() {
  if (isTokenEqual("(")) return 4;
  if (isNumber()) return 5;
  if (isIdentifier()) return 16;
  return Reject;
}

int getStateFrom16() {
  lookTokenAhead();

  if (isNextTokenIdentifier()) {
    getNextToken();
    return 14;
  }
  if (isNextTokenEqual("[")) {
    getNextToken();
    return 17;
  }
  if (isNextTokenEqual("(")) {
    getNextToken();
    return 18;
  }
  if (isNextTokenNumber()) {
    getNextToken();
    return 13;
  }
  if (isNextTokenOnList(prioritaryOperators, 7)) {
    getNextToken();
    return 15;
  }
  if (isNextTokenOnList(otherOperators, 6)) {
    getNextToken();
    return 1;
  }

  return Accept;
}

int getStateFrom17() {
  if (isTokenEqual("]")) return 21;
  if (isExpression()) return 20;
  return Reject;
}

int getStateFrom18() {
  if (isTokenEqual(")")) return 5;
  if (isExpression()) return 19;
  return Reject;
}

int getStateFrom19() {
  if (isTokenEqual(",")) return 9;
  if (isTokenEqual(")")) return 13;
  return Reject;
}

int getStateFrom20() {
  if (isTokenEqual("]")) return 21;
  return Reject;
}

int getStateFrom21() {
  lookTokenAhead();

  if (isNextTokenIdentifier()) {
    getNextToken();
    return 14;
  }
  if (isNextTokenEqual("[")) {
    getNextToken();
    return 17;
  }
  if (isNextTokenEqual("(")) {
    getNextToken();
    return 4;
  }
  if (isNextTokenNumber()) {
    getNextToken();
    return 13;
  }
  if (isNextTokenOnList(prioritaryOperators, 7)) {
    getNextToken();
    return 15;
  }
  if (isNextTokenOnList(otherOperators, 6)) {
    getNextToken();
    return 1;
  }

  return Accept;
}

int getStateFrom22() {
  if (isExpression()) return 23;
  if (isTokenEqual(")")) return 13;
  return Reject;
}

int getStateFrom23() {
  if (isTokenEqual(",")) return 24;
  if (isTokenEqual(")")) return 13;
  return Reject;
}

int getStateFrom24() {
  if (isExpression()) return 23;
  return Reject;
}
