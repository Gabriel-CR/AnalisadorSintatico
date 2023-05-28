#ifndef FIRST_FOLLOW_H
#define FIRST_FOLLOW_H

#include "gramatica.h"

class FirstFollow
{
    map<string, vector<string>> gramatica;
    set<string> terminais;
    set<string> nao_terminais;

    map<string, set<string>> firsts;
    map<string, set<string>> follows;

public:
    FirstFollow();

    bool nullable(string nao_terminal);
    set<string> first(string nao_terminal);
    set<string> follow(string nao_terminal);

    void set_gramatica(map<string, vector<string>> gramatica);
    void set_terminais(set<string> terminais);
    void set_nao_terminais(set<string> nao_terminais);
};

#endif // SOMA_H