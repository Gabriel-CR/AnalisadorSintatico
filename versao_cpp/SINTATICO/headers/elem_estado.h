#ifndef ELEM_ESTADO_H
#define ELEM_ESTADO_H

#include <iostream>
#include "utils.h"

using namespace std;

class ElemEstado
{
public:
    string gerador;
    vector<string> gerado;
    int posicao_ponto;
    ElemEstado(string gerador, string gerado, int posicao_ponto);
};

#endif // ELEM_ESTADO_H