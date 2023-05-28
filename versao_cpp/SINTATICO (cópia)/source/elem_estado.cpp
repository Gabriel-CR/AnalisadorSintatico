#include "../headers/elem_estado.h"

ElemEstado::ElemEstado(string gerador, string gerado, int posicao_ponto, int estado)
{
    this->gerador = gerador;
    this->gerado = Utils::split(gerado, " ");
    this->posicao_ponto = posicao_ponto;
    this->estado = estado;
}

string ElemEstado::to_string()
{
    string str = this->gerador + " -> ";
    for (int i = 0; i < (int)this->gerado.size(); i++)
    {
        if (i == this->posicao_ponto)
        {
            str += ". ";
        }
        str += this->gerado[i] + " ";
    }
    if (this->posicao_ponto == (int)this->gerado.size())
    {
        str += ". ";
    }
    return str;
}