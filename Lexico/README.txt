Para compilar o projeto do analisador léxico, utilize os três comandos:

mingw32-gcc.exe -Wall -g -c C:\Alan\Compiladores\Compilador-PCS\Lexico\Lex.c -o obj\Debug\Lex.o
mingw32-gcc.exe -Wall -g -c C:\Alan\Compiladores\Compilador-PCS\Lexico\Table\Table.c -o obj\Debug\Table\Table.o
mingw32-g++.exe -o bin\Debug\Lexico.exe obj\Debug\Lex.o obj\Debug\Table\Table.o

O comando "mingw32-gcc.exe" é setado para o Windows, mas é o compilador gcc.
O programa Lexico.exe será criado na pasta bin\Debug.
