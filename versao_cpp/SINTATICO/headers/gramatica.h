#ifndef GRAMATICA_H
#define GRAMATICA_H

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <fstream>
#include "utils.h"

using namespace std;

class Gramatica
{
    string caminho;
    map<string, vector<string>> gramatica;
    set<string> terminais;
    set<string> nao_terminais;

public:
    Gramatica(string caminho);
    void read_gramatica_file();
    void make_terminais();
    void make_nao_terminais();

    map<string, vector<string>> get_gramatica();
    set<string> get_terminais();
    set<string> get_nao_terminais();

    void print_gramatica();
};

#endif // GRAMATICA_H