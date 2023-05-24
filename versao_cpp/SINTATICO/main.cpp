#include <iostream>
#include "headers/controller.h"

// compile and run
// g++ -o run ./source/*.cpp  *.cpp  && ./run

using namespace std;

int main()
{
    Controller controller("gramatica/gramatica.txt");
    controller.read_gramatica_file();
    // controller.make_nullable();
    // controller.make_firsts();
    // controller.make_follows();
    controller.make_automato();

    return 0;
}