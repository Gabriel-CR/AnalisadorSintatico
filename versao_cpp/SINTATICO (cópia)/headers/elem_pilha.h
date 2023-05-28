#ifndef ELEM_PILHA_H
#define ELEM_PILHA_H

#include <iostream>
#include <vector>

using namespace std;

class ElemPilha
{
public:
    ElemPilha(string token, int estado);
    string token;
    int estado;
};

#endif // ELEM_PILHA_H