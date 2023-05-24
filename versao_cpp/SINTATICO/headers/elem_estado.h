#ifndef ELEM_ESTADO_H
#define ELEM_ESTADO_H

#include <iostream>

using namespace std;

class ElemEstado
{
public:
    string gerador;
    string gerado;
    int posicao_ponto;
    ElemEstado(string gerador, string gerado, int posicao_ponto);
};

#endif // ELEM_ESTADO_H