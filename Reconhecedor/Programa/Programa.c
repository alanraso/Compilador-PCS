#include <stdio.h>
#include <string.h>
#include "../../Lexico/Lex.h"
#include "../Data/Data.h"
#include "../Comando/Command.h"
#include "../Expressao/Expressao.h"
#include "../Semantico/Semantico.h"

int finalProgramState = 17;

bool isProgramFinalState(int state);

int getProgramStateFrom0();
int getProgramStateFrom2();
int getProgramStateFrom3();
int getProgramStateFrom6();
int getProgramStateFrom13();
int getProgramStateFrom14();
int getProgramStateFrom17();
int getProgramStateFrom18();
int getProgramStateFrom25();
int getProgramStateFrom26();
int getProgramStateFrom29();
int getProgramStateFrom30();
int getProgramStateFrom32();
int getProgramStateFrom34();
int getProgramStateFrom35();
int getProgramStateFrom36();

bool isProgram() {
  int state = 0;

  while (1) {
    switch(state) {
      case 0:
        state = getProgramStateFrom0();
        break;
      case 1:
        state = isIdentifier() ? 3 : Reject;
        break;
      case 2:
        state = getProgramStateFrom2();
        break;
      case 3:
        state = getProgramStateFrom3();
        break;
      case 4:
        state = isTokenEqual("(") ? 13 : Reject;
        break;
      case 5:
        state = isTokenEqual("(") ? 7 : Reject;
        break;
      case 6:
        state = getProgramStateFrom6();
        break;
      case 7:
        state = isTokenEqual(")") ? 8 : Reject;
        break;
      case 8:
        state = isTokenEqual("(") ? 10 : Reject;
        break;
      case 9:
        state = isTokenEqual("]") ? 3 : Reject;
        break;
      case 10:
        state = isTokenEqual(")") ? 11 : Reject;
        break;
      case 11:
        state = isTokenEqual("{") ? 12 : Reject;
        break;
      case 12:
        state = isCommand() ? 14 : Reject;
        break;
      case 13:
        state = getProgramStateFrom13();
        break;
      case 14:
        state = getProgramStateFrom14();
        break;
      case 15:
        state = isIdentifier() ? 30 : Reject;
        break;
      case 16:
        state = isTokenEqual("(") ? 18 : Reject;
        break;
      case 17:
        state = getProgramStateFrom17();
        break;
      case 18:
        state = getProgramStateFrom18();
        break;
      case 19:
        state = isIdentifier() ? 34 : Reject;
        break;
      case 20:
        state = isIdentifier() ? 23 : Reject;
        break;
      case 21:
        state = isTokenEqual(")") ? 22 : Reject;
        break;
      case 22:
        state = isTokenEqual("{") ? 24 : Reject;
        break;
      case 23:
        state = isTokenEqual("(") ? 25 : Reject;
        break;
      case 24:
        state = isCommand() ? 26 : Reject;
        break;
      case 25:
        state = getProgramStateFrom25();
        break;
      case 26:
        state = getProgramStateFrom26();
        break;
      case 27:
        state = isIdentifier() ? 32 : Reject;
        break;
      case 28:
        state = isTokenEqual("(") ? 29 : Reject;
        break;
      case 29:
        state = getProgramStateFrom29();
        break;
      case 30:
        state = getProgramStateFrom30();
        break;
      case 31:
        state = isVariableType() ? 15 : Reject;
        break;
      case 32:
        state = getProgramStateFrom32();
        break;
      case 33:
        state = isVariableType() ? 27 : Reject;
        break;
      case 34:
        state = getProgramStateFrom34();
        break;
      case 35:
        state = getProgramStateFrom35();
        break;
      case 36:
        state = getProgramStateFrom36();
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
    if (!isProgramFinalState(state)) {
      getNextToken();
      semantico_tbd();
    }
  }
}

bool isProgramFinalState(int state) {
  return state == 17;
}

int getProgramStateFrom0() {
  if (isVariableType()) return 1;
  if (isTokenEqual("func")) return 2;
  return Reject;
}

int getProgramStateFrom2() {
  if (isTokenEqual("main")) return 5;
  if (isIdentifier()) return 4;
  return Reject;
}

int getProgramStateFrom3() {
  if (isTokenEqual("[")) return 6;
  if (isTokenEqual(";")) return 0;
  return Reject;
}

int getProgramStateFrom6() {
  if (isTokenEqual("]")) return 3;
  if (isExpression()) return 9;
  return Reject;
}

int getProgramStateFrom13() {
  if (isTokenEqual(")")) return 16;
  if (isVariableType()) return 15;
  return Reject;
}

int getProgramStateFrom14() {
  if (isTokenEqual("}")) return 17;
  if (isCommand()) return 14;
  return Reject;
}

int getProgramStateFrom17() {
  lookTokenAhead();

  if (isNextTokenEqual("func")) {
    getNextToken();
    return 20;
  }

  if (isNextTokenVariableType()) {
    getNextToken();
    return 19;
  }

  return Accept;
}

int getProgramStateFrom18() {
  if (isTokenEqual(")")) return 22;
  if (isVariableType()) return 21;
  return Reject;
}

int getProgramStateFrom25() {
  if (isTokenEqual(")")) return 28;
  if (isVariableType()) return 27;
  return Reject;
}

int getProgramStateFrom26() {
  if (isTokenEqual("}")) return 0;
  if (isCommand()) return 26;
  return Reject;
}

int getProgramStateFrom29() {
  if (isTokenEqual(")")) return 11;
  if (isVariableType()) return 10;
  return Reject;
}

int getProgramStateFrom30() {
  if (isTokenEqual(",")) return 31;
  if (isTokenEqual(")")) return 16;
  return Reject;
}

int getProgramStateFrom32() {
  if (isTokenEqual(",")) return 33;
  if (isTokenEqual(")")) return 28;
  return Reject;
}


int getProgramStateFrom34() {
  if (isTokenEqual("[")) return 35;
  if (isTokenEqual(";")) return 17;
  return Reject;
}

int getProgramStateFrom35() {
  if (isTokenEqual("]")) return 34;
  if (isExpression()) return 36;
  return Reject;
}

int getProgramStateFrom36() {
  if (isTokenEqual("]")) return 34;
  return Reject;
}
