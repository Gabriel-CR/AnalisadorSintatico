#include "../headers/elem_estado.h"

ElemEstado::ElemEstado(string gerador, string gerado, int posicao_ponto)
{
    this->gerador = gerador;
    this->gerado = gerado;
    this->posicao_ponto = posicao_ponto;
}