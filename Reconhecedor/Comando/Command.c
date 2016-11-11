#include <stdio.h>
#include <string.h>
#include "../../Lexico/Lex.h"
#include "../Data/Data.h"
#include "../Expressao/Expressao.h"
#include "../Semantico/Semantico.h"

int finalCommandStateList[2] = {10, 41};

int getCommandStateFrom0();
int getCommandStateFrom2();
int getCommandStateFrom3();
int getCommandStateFrom7();
int getCommandStateFrom9();
int getCommandStateFrom11();
int getCommandStateFrom12();
int getCommandStateFrom18();
int getCommandStateFrom20();
int getCommandStateFrom22();
int getCommandStateFrom24();
int getCommandStateFrom25();
int getCommandStateFrom31();
int getCommandStateFrom33();
int getCommandStateFrom40();
int getCommandStateFrom41();
int getCommandStateFrom42();

bool isCommandFinalState(int state);

bool isCommand() {
  int state = 0;

  while (1) {
    switch(state) {
      case 0:
        state = getCommandStateFrom0();
        break;
      case 1:
        state = isIdentifier() ? 7 : Reject;
        break;
      case 2:
        state = getCommandStateFrom2();
        break;
      case 3:
        state = getCommandStateFrom3();
        break;
      case 4:
        state = isTokenEqual("(") ? 35 : Reject;
        break;
      case 5:
        state = isTokenEqual("(") ? 26 : Reject;
        break;
      case 6:
        state = isTokenEqual("(") ? 8 : Reject;
        break;
      case 7:
        state = getCommandStateFrom7();
        break;
      case 8:
        state = isIdentifier() ? 11 : Reject;
        break;
      case 9:
        state = getCommandStateFrom9();
        break;
      case 10:
        state = Accept;
        break;
      case 11:
        state = getCommandStateFrom11();
        break;
      case 12:
        state = getCommandStateFrom12();
        break;
      case 13:
        state = isExpression() ? 15 : Reject;
        break;
      case 14:
        state = isTokenEqual("]") ? 7 : Reject;
        break;
      case 15:
        state = isTokenEqual(";") ? 16 : Reject;
        break;
      case 16:
        state = isExpression() ? 17 : Reject;
        break;
      case 17:
        state = isTokenEqual(";") ? 21 : Reject;
        break;
      case 18:
        state = getCommandStateFrom18();
        break;
      case 19:
        state = isExpression() ? 23 : Reject;
        break;
      case 20:
        state = getCommandStateFrom20();
        break;
      case 21:
        state = isIdentifier() ? 24 : Reject;
        break;
      case 22:
        state = getCommandStateFrom22();
        break;
      case 23:
        state = isTokenEqual(";") ? 10 : Reject;
        break;
      case 24:
        state = getCommandStateFrom24();
        break;
      case 25:
        state = getCommandStateFrom25();
        break;
      case 26:
        state = isExpression() ? 28 : Reject;
        break;
      case 27:
        state = isExpression() ? 22 : Reject;
        break;
      case 28:
        state = isTokenEqual(")") ? 29 : Reject;
        break;
      case 29:
        state = isTokenEqual("{") ? 30 : Reject;
        break;
      case 30:
        state = isCommand() ? 31 : Reject;
        break;
      case 31:
        state = getCommandStateFrom31();
        break;
      case 32:
        state = isTokenEqual("]") ? 33 : Reject;
        break;
      case 33:
        state = getCommandStateFrom33();
        break;
      case 34:
        state = isTokenEqual("]") ? 24 : Reject;
        break;
      case 35:
        state = isExpression() ? 37 : Reject;
        break;
      case 36:
        state = isTokenEqual("]") ? 11 : Reject;
        break;
      case 37:
        state = isTokenEqual(")") ? 38 : Reject;
        break;
      case 38:
        state = isTokenEqual("{") ? 39 : Reject;
        break;
      case 39:
        state = isCommand() ? 40 : Reject;
        break;
      case 40:
        state = getCommandStateFrom40();
        break;
      case 41:
        state = getCommandStateFrom41();
        break;
      case 42:
        state = getCommandStateFrom42();
        break;
      default:
        printf("Automato de Comando: Estado nao alcancavel!");
        return false;
        break;
    }

    if (state == Reject) {
      return false;
    }
    if (state == Accept) {
      return true;
    }

    if (!isCommandFinalState(state)) {
      getNextToken();
      semantico_tbd();
    }
  }
}

bool isCommandFinalState(int state) {
  return state == finalCommandStateList[0] || state == finalCommandStateList[1];
}

int getCommandStateFrom0() {
  if (isTokenEqual("retorna")) return 3;
  if (isTokenEqual("se")) return 4;
  if (isTokenEqual("enquanto")) return 5;
  if (isTokenEqual("para")) return 6;
  if (isVariableType()) return 1;
  if (isIdentifier()) return 2;
  return Reject;
}

int getCommandStateFrom2() {
  if (isTokenEqual("[")) return 18;
  if (isTokenEqual(":=")) return 19;
  if (isTokenEqual("(")) return 20;
  return Reject;
}

int getCommandStateFrom3() {
  if (isTokenEqual(";")) return 10;
  if (isExpression()) return 23;
  return Reject;
}

int getCommandStateFrom7() {
  if (isTokenEqual("[")) return 9;
  if (isTokenEqual(";")) return 10;
  return Reject;
}

int getCommandStateFrom9() {
  if (isTokenEqual("]")) return 7;
  if (isExpression()) return 14;
  return Reject;
}

int getCommandStateFrom11() {
  if (isTokenEqual("[")) return 12;
  if (isTokenEqual(":=")) return 13;
  return Reject;
}

int getCommandStateFrom12() {
  if (isTokenEqual("]")) return 11;
  if (isExpression()) return 38;
  return Reject;
}

int getCommandStateFrom18() {
  if (isTokenEqual("]")) return 33;
  if (isExpression()) return 32;
  return Reject;
}

int getCommandStateFrom20() {
  if (isTokenEqual(")")) return 23;
  if (isExpression()) return 22;
  return Reject;
}

int getCommandStateFrom22() {
  if (isTokenEqual(",")) return 27;
  if (isTokenEqual(")")) return 23;
  return Reject;
}

int getCommandStateFrom24() {
  if (isTokenEqual("[")) return 25;
  if (isTokenEqual(":=")) return 26;
  return Reject;
}

int getCommandStateFrom25() {
  if (isTokenEqual("]")) return 24;
  if (isExpression()) return 34;
  return Reject;
}

int getCommandStateFrom31() {
  if (isTokenEqual("}")) return 10;
  if (isCommand()) return 31;
  return Reject;
}

int getCommandStateFrom33() {
  if (isTokenEqual("[")) return 18;
  if (isTokenEqual(":=")) return 19;
  return Reject;
}

int getCommandStateFrom40() {
  if (isTokenEqual("}")) return 41;
  if (isCommand()) return 40;
  return Reject;
}

int getCommandStateFrom41() {
  lookTokenAhead();

  if (isNextTokenEqual("senao")) {
    getNextToken();
    return 42;
  }

  return Accept;
}

int getCommandStateFrom42() {
  if (isTokenEqual("se")) return 4;
  if (isTokenEqual("{")) return 30;
  return Reject;
}
