#include <iostream>
#include "headers/controller.h"

// compile and run
// g++ -o run ./source/*.cpp  *.cpp  && ./run

using namespace std;

// recebe argumentos para o programa
int main(int argc, char *argv[])
{
    /*
    Coloque a gramática no arquivo gramatica.txt
    a gramática deve estar no seguinte formato:
        S -> A $
        A -> a B
        B -> a
    Para o uso do autômato, não está definido operações com epsilon, então,
    não coloque epsilon na gramática, por favor. No caso do calculo de firsts e follows,
    epsilon é representado por eps.
    */
    Controller controller("gramatica/gramatica.txt");
    controller.read_gramatica_file();

    // se argumento for ff, faz firsts e follows
    /*
    Para usar o firsts e follows, não é necessário passar o argumento ff
    Exemplo:
        ./run ff

    */
    if (argc > 1 && string(argv[1]) == "ff")
    {
        controller.make_nullable();
        controller.make_firsts();
        controller.make_follows();
    }
    // se argumento for aut, faz automato
    /*
    Para usar o autômato, é necessário passar a palavra como argumento
    Exemplo:
        ./run aut "print ( id )"
    Como no exemplo acima, a palavra deve estar entre aspas e cada token deve estar separado por espaço
    Repare também que não se coloca $ no final da palavra, esta ação fica a cargo do programa
    */
    else if (argc > 1 && string(argv[1]) == "aut")
    {
        // pega a palavra do argumento,
        // palavra passada como argumento deve estar entre aspas
        // [ATENÇÃO] o código coloca $ no final da palavra, por isso,
        // não é necessário colocar $ no final da palavra passado como argumento

        if (argv[2] == NULL)
        {
            cout << "[ERRO] palavra não passada como argumento" << endl;
            controller.menu();
            return 0;
        }

        string palavra = string(argv[2]);

        // mostra o autômato se o terceiro argumento for sa
        if (argc > 2 && string(argv[3]) == "sa")
            controller.make_automato(palavra, true);
        else
            controller.make_automato(palavra, false);
    }
    // se não tiver argumento, mostra menu
    else
    {
        controller.menu();
    }

    return 0;
}