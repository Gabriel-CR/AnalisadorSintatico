#ifndef AUTOMATO_H
#define AUTOMATO_H

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <string>

#include "gramatica.h"
#include "elem_estado.h"
#include "elem_pilha.h"

using namespace std;

class Automato
{
    map<int, map<string, string>> automato;
    map<string, vector<string>> gramatica;
    vector<pair<string, string>> ordem_regras;
    set<string> terminais;
    set<string> nao_terminais;

    // memoriza a primeira regra de cada estado
    map<int, string> mem_regra;

public:
    Automato();

    vector<ElemEstado> closure(vector<ElemEstado> elem, int current_state);
    void goto_(vector<ElemEstado> elem, int current_state);
    /*
    Forma o automato a partir de um elemento inicial
    @param elem_inicial: primeira regra da gramatica
    */
    void make_automato(ElemEstado elem_inicial);
    /*
    Testa uma dada palavra com base no autômato feito no método make_automato
    @param word: palavra a ser testada
    */
    bool test_word(string word);

    // SETTERS
    void set_gramatica(map<string, vector<string>> gramatica);
    void set_ordem_regras(vector<pair<string, string>> ordem_regras);
    void set_terminais(set<string> terminais);
    void set_nao_terminais(set<string> nao_terminais);

    /*
    Imprime o autômato
    Mostra o estad e cada ação que ele pode tomar com cada símbolo
    */
    void print_automato();
};

#endif // AUTOMATO_H