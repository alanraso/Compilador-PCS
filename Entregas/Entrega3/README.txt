Para compilar o projeto do compilador até esta terceira entrega, é possível utilizar os seguintes comandos:

mingw32-gcc.exe -Wall -g -c Compilador-PCS\Reconhecedor\Reconhecedor.c -o obj\Debug\Reconhecedor\Reconhecedor.o
mingw32-g++.exe  -o bin\Debug\Compilador.exe obj\Debug\Lexico\Lex.o obj\Debug\Lexico\Table\Table.o obj\Debug\Reconhecedor\Reconhecedor.o   

Os comandos mingw32 podem variar dependendo do sistema operacional, mas é o comando do gcc normal. A pasta para a execução do comando é Compilador-PCS.

O arquivo executável será gerado em bin\Debug\Compilador.exe.
