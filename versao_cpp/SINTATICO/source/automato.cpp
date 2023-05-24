#include "../headers/automato.h"

Automato::Automato()
{
}

void Automato::make_automato(vector<ElemEstado> es)
{
    // this->automato["1"]["A"] = "g2"; // goto 2
    // this->automato["1"]["a"] = "s3"; // shift 3

    // this->automato["2"]["$"] = "a"; // aceita

    // this->automato["3"]["a"] = "r2"; // reduce pela regra 2

    /*
    1 : { A -> g2, a -> s3, }
    2 : { $ -> a, }
    3 : { a -> r2, }
    */

    vector<ElemEstado> regras;
    // coloca as regras de es em regras
    for (int i = 0; i < (int)es.size(); i++)
    {
        // se a regra não for sofre uma redução
        if (es[i].posicao_ponto < es[i].gerado.size())
        {
            regras.push_back(es[i]);
        }
    }

    // se ponto estiver antes de um não terminal,
    // coloca as regras desse não terminal em regras
    for (int i = 0; i < (int)es.size(); i++)
    {
        if (es[i].posicao_ponto < es[i].gerado.size() &&
            this->nao_terminais.find(es[i].gerado.substr(es[i].posicao_ponto, 1)) != this->nao_terminais.end())
        {
            for (string regra : this->gramatica[es[i].gerado.substr(es[i].posicao_ponto, 1)])
            {
                regras.push_back(ElemEstado(es[i].gerado.substr(es[i].posicao_ponto, 1), regra, 0));
            }
        }
    }

    string current_state = this->estado_atual;

    // se o ponto estiver na posição de um não terminal,
    // colocar em automato um goto para o estado + 1, com este não terminal
    for (int i = 0; i < (int)regras.size(); i++)
    {
        if (regras[i].posicao_ponto < regras[i].gerado.size() &&
            this->nao_terminais.find(regras[i].gerado.substr(regras[i].posicao_ponto, 1)) != this->nao_terminais.end())
        {
            this->automato[current_state][regras[i].gerado.substr(regras[i].posicao_ponto, 1)] = "g" + to_string(stoi(current_state) + 1);
            // se estiver em regras um ponto antes do mesmo não terminal
            // fazer um goto deste para o mesmo do outro não terminal
            for (int j = 0; j < (int)regras.size(); j++)
            {
                if (regras[j].posicao_ponto == regras[i].posicao_ponto &&
                    regras[j].gerado.substr(regras[j].posicao_ponto, 1) == regras[i].gerado.substr(regras[i].posicao_ponto, 1))
                {
                    this->automato[current_state][regras[j].gerado.substr(regras[j].posicao_ponto, 1)] = "g" + to_string(stoi(this->estado_atual) + 1);
                }
            }
            this->estado_atual = to_string(stoi(this->estado_atual) + 1);
        }
    }

    // se o ponto estiver na posição de um terminal,
    // colocar em automato um shift para o estado + 1, com este terminal
    for (int i = 0; i < (int)regras.size(); i++)
    {
        if (regras[i].posicao_ponto < regras[i].gerado.size() &&
            this->terminais.find(regras[i].gerado.substr(regras[i].posicao_ponto, 1)) != this->terminais.end())
        {
            this->automato[current_state][regras[i].gerado.substr(regras[i].posicao_ponto, 1)] = "s" + to_string(stoi(current_state) + 1);

            // se estiver em regras um ponto antes do mesmo terminal
            // fazer um shift deste para o mesmo do outro terminal
            for (int j = 0; j < (int)regras.size(); j++)
            {
                if (regras[j].posicao_ponto == regras[i].posicao_ponto &&
                    regras[j].gerado.substr(regras[j].posicao_ponto, 1) == regras[i].gerado.substr(regras[i].posicao_ponto, 1))
                {
                    this->automato[current_state][regras[j].gerado.substr(regras[j].posicao_ponto, 1)] = "s" + to_string(stoi(this->estado_atual) + 1);
                }
            }

            this->estado_atual = to_string(stoi(this->estado_atual) + 1);
        }
    }

    // se o ponto estiver no final da regra, colocar em automato um reduce
    // em cada não terminal da gramatica
    for (int i = 0; i < (int)regras.size(); i++)
    {
        if (regras[i].posicao_ponto == regras[i].gerado.size())
        {
            for (string nao_terminal : this->nao_terminais)
            {
                this->automato[this->estado_atual][nao_terminal] = "r" + to_string(i + 1);
            }

            // remove esta regra de regras
            regras.erase(regras.begin() + i);
        }
    }

    // se o ponto estiver antes de $ (fim de palavra), colocar em automato um accept
    for (int i = 0; i < (int)regras.size(); i++)
    {
        if (regras[i].posicao_ponto == regras[i].gerado.size() - 1 &&
            regras[i].gerado.substr(regras[i].posicao_ponto, 1) == "$")
        {
            this->automato[this->estado_atual]["$"] = "a";
            // remove esta regra de regras
            regras.erase(regras.begin() + i);
        }
    }

    // avançar o ponto de cada regra
    for (int i = 0; i < (int)regras.size(); i++)
    {
        regras[i].posicao_ponto += 2;
    }

    // aumentar o estado atual
    this->estado_atual = to_string(stoi(current_state) + 1);

    // chamada recursiva
    // se regras não estiver vazio
    if (!regras.empty())
    {
        this->make_automato(regras);
    }
}

bool Automato::test_word(string word)
{
    cout << "Testando palavra: " << word << endl;
    this->estado_atual = "1";
    int i = 0;

    stack<string> pilha;

    while (true)
    {
        map<string, string> estado = this->automato[this->estado_atual];
        string simbolo = word.substr(i, 1);
        string acao = estado[simbolo];

        // se a ação for shift
        if (acao[0] == 's')
        {
            // empilha o simbolo
            pilha.push(simbolo);
            // muda o estado atual
            this->estado_atual = acao.substr(1, acao.size() - 1);
            // incrementa o contador
            i++;
        }
        // se acao for accept
        else if (acao == "a")
        {
            cout << "Palavra aceita!" << endl;
            return true;
        }
        // se acao for reduce
        else if (acao[0] == 'r')
        {
            // pega a regra
            pair<string, string> regra = this->ordem_regras[stoi(acao.substr(1, acao.size() - 1)) - 1];
            // desempilha o tamanho da regra
            for (int j = 0; j < (int)regra.second.size(); j++)
            {
                pilha.pop();
            }
            // empilha o não terminal
            pilha.push(regra.first);
            // muda o estado atual
            this->estado_atual = this->automato[this->estado_atual][regra.first];
        }
        // se acao for goto
        else if (acao[0] == 'g')
        {
            // muda o estado atual
            this->estado_atual = acao.substr(1, acao.size() - 1);
        }
        else
        {
            cout << "Palavra não aceita!" << endl;
            return false;
        }
    }
}

void Automato::set_gramatica(map<string, vector<string>> gramatica)
{
    this->gramatica = gramatica;
}

void Automato::set_ordem_regras(vector<pair<string, string>> ordem_regras)
{
    this->ordem_regras = ordem_regras;
}

void Automato::set_terminais(set<string> terminais)
{
    this->terminais = terminais;
}

void Automato::set_nao_terminais(set<string> nao_terminais)
{
    this->nao_terminais = nao_terminais;
}

void Automato::print_automato()
{
    cout << "Automato: " << endl;
    for (auto it = this->automato.begin(); it != this->automato.end(); it++)
    {
        cout << it->first << " : { ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            cout << it2->first << " -> " << it2->second << ", ";
        }
        cout << "}" << endl;
    }
}