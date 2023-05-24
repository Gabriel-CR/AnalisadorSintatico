#ifndef AUTOMATO_H
#define AUTOMATO_H

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <stack>
#include <string>

#include "gramatica.h"
#include "elem_estado.h"

using namespace std;

class Automato
{
    map<string, map<string, string>> automato;
    string estado_atual = "1";

    map<string, vector<string>> gramatica;
    vector<pair<string, string>> ordem_regras;
    set<string> terminais;
    set<string> nao_terminais;

public:
    Automato();

    void make_automato(vector<ElemEstado> es);
    void make_automato_iterativo(ElemEstado es);
    bool test_word(string word);

    void set_gramatica(map<string, vector<string>> gramatica);
    void set_ordem_regras(vector<pair<string, string>> ordem_regras);
    void set_terminais(set<string> terminais);
    void set_nao_terminais(set<string> nao_terminais);

    void print_automato();
};

#endif // AUTOMATO_H