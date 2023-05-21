#include <iostream>
#include "headers/soma.h"
#include "headers/gramatica.h"
#include "headers/controller.h"

// compile and run
// g++ -o run ./source/*.cpp  *.cpp  && ./run

using namespace std;

int main()
{
    Controller controller("gramatica/gramatica.txt");
    controller.make_nullable();
    controller.make_firsts();
    controller.make_follows();
    // controller.make_automato();

    return 0;
}