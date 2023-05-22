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
    /*
     * Construtor da classe Gramatica
     */
    Gramatica();
    /*
    * Deve ser executado apos a leitura do arquivo de gramatica
    e cria o conjunto de nao terminais na gramatica
    * Usa como principio que os não terminais são aqueles que
    estão antes de -> na gramatica
    */
    void make_nao_terminais();
    /*
    * Deve ser executado apos a leitura do arquivo de gramatica
    e cria o conjunto de nao terminais na gramatica
    * Cria o conjunto de terminais na gramatica
    * Usa como principio que os não terminais são aqueles que
    não estão na lista de terminais
    */
    void make_terminais();

    // GETS e SETS
    map<string, vector<string>> get_gramatica();
    set<string> get_terminais();
    set<string> get_nao_terminais();

    void set_gramatica(map<string, vector<string>> gramatica);

    void print_gramatica();
};

#endif // GRAMATICA_H