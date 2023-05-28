#include <iostream>
#include "gramatica.h"
#include "first_follow.h"
#include "automato.h"
#include "elem_estado.h"

using namespace std;

class Controller
{
    string caminho;
    Gramatica gramatica;
    vector<pair<string, string>> ordem_regras;
    FirstFollow first_follow;
    Automato automato;

public:
    Controller(string caminho);

    void menu();

    void read_gramatica_file();
    void make_gramatica(map<string, vector<string>> gramatica);
    void make_nullable();
    void make_firsts();
    void make_follows();
    void make_automato(string palavra);
};