#ifndef AUTOMATO_H
#define AUTOMATO_H

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include "gramatica.h"

using namespace std;

class Automato
{
    map<string, map<string, string>> automato;
    map<string, vector<string>> gramatica;
    set<string> terminais;
    set<string> nao_terminais;

public:
    Automato();
    void make_automato();

    void set_gramatica(map<string, vector<string>> gramatica);
    void set_terminais(set<string> terminais);
    void set_nao_terminais(set<string> nao_terminais);

    void print_automato();
};

#endif // AUTOMATO_H