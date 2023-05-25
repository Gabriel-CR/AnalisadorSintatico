#include "../headers/elem_estado.h"

ElemEstado::ElemEstado(string gerador, string gerado, int posicao_ponto, int estado)
{
    this->gerador = gerador;
    this->gerado = Utils::split(gerado, " ");
    this->posicao_ponto = posicao_ponto;
    this->estado = estado;
}