#include <iostream>
#include "gramatica.h"
#include "first_follow.h"
#include "automato.h"

using namespace std;

class Controller
{
    Gramatica gramatica;
    FirstFollow first_follow;
    Automato automato;

public:
    Controller(string caminho);
    void make_nullable();
    void make_firsts();
    void make_follows();
    // void make_automato();
};