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

    // transformar gerado de elem estado em um vetor para usar melhor o ponto

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

    // se ponto estiver na posição de um não terminal,
    // coloca as regras desse não terminal em regras
    for (int i = 0; i < (int)es.size(); i++)
    {
        if (es[i].posicao_ponto < es[i].gerado.size() &&
            this->nao_terminais.find(es[i].gerado[es[i].posicao_ponto]) != this->nao_terminais.end())
        {
            for (int j = 0; j < (int)this->ordem_regras.size(); j++)
            {
                if (this->ordem_regras[j].first == es[i].gerado[es[i].posicao_ponto])
                {
                    regras.push_back(ElemEstado(this->ordem_regras[j].first, this->ordem_regras[j].second, 0));
                }
            }
        }
    }

    // mostra as regras
    for (int i = 0; i < (int)regras.size(); i++)
    {
        cout << ".... mostrar regras 1 ...." << endl;
        // mostrar estado atual
        cout << this->estado_atual << " : ";
        cout << regras[i].gerador << " -> ";
        for (int j = 0; j < (int)regras[i].gerado.size(); j++)
        {
            if (j == regras[i].posicao_ponto)
            {
                cout << ". ";
            }
            cout << regras[i].gerado[j] << " ";
        }
        if (regras[i].posicao_ponto == regras[i].gerado.size())
        {
            cout << ". ";
        }
        cout << endl;
    }

    string current_state = this->estado_atual;

    // se o ponto estiver na posição de um não terminal,
    // colocar em automato um goto para o estado + 1, com este não terminal
    for (int i = 0; i < (int)regras.size(); i++)
    {
        if (regras[i].posicao_ponto < regras[i].gerado.size() &&
            this->nao_terminais.find(regras[i].gerado[regras[i].posicao_ponto]) != this->nao_terminais.end())
        {
            this->automato[current_state][regras[i].gerado[regras[i].posicao_ponto]] = "g" + to_string(stoi(current_state) + 1);

            // se tem um não terminal igual a esse em regras,
            // fazer um goto deste não terminal para o mesmo estado
            for (int j = 0; j < (int)regras.size(); j++)
            {
                if (regras[j].posicao_ponto == regras[i].posicao_ponto &&
                    regras[j].gerado[regras[j].posicao_ponto] == regras[i].gerado[regras[i].posicao_ponto])
                {
                    this->automato[current_state][regras[j].gerado[regras[j].posicao_ponto]] = "g" + to_string(stoi(current_state) + 1);
                }
            }

            // incrementa o estado atual
            this->estado_atual = to_string(stoi(current_state) + 1);
        }
    }

    // se o ponto estiver na posição de um terminal,
    // colocar em automato um shift para o estado + 1, com este terminal
    for (int i = 0; i < (int)regras.size(); i++)
    {
        if (regras[i].posicao_ponto < regras[i].gerado.size() &&
            this->terminais.find(regras[i].gerado[regras[i].posicao_ponto]) != this->terminais.end())
        {
            // se esse terminal for diferente de $
            if (regras[i].gerado[regras[i].posicao_ponto] != "$")
            {
                this->automato[current_state][regras[i].gerado[regras[i].posicao_ponto]] = "s" + to_string(stoi(current_state) + 1);

                // se estiver em regras um ponto na posição do mesmo terminal
                // fazer um shift deste para o mesmo do outro terminal
                for (int j = 0; j < (int)regras.size(); j++)
                {
                    if (regras[j].posicao_ponto == regras[i].posicao_ponto &&
                        regras[j].gerado[regras[j].posicao_ponto] == regras[i].gerado[regras[i].posicao_ponto])
                    {
                        this->automato[current_state][regras[j].gerado[regras[j].posicao_ponto]] = "s" + to_string(stoi(this->estado_atual) + 1);
                    }
                }

                this->estado_atual = to_string(stoi(this->estado_atual) + 1);
            }
            else
            {
                // se o ponto estiver na posição de $, colocar um accept
                this->automato[current_state]["$"] = "a";
            }
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
                if (this->automato[current_state].find(nao_terminal) == this->automato[current_state].end())
                {
                    this->automato[current_state][nao_terminal] = "r" + to_string(i);
                }
            }
        }
    }

    // avançar o ponto de cada regra
    for (int i = 0; i < (int)regras.size(); i++)
    {
        regras[i].posicao_ponto++;
    }

    // mostra as regras
    for (int i = 0; i < (int)regras.size(); i++)
    {
        cout << ".... mostrar regras 2 ...." << endl;
        // mostrar estado atual
        cout << this->estado_atual << " : ";
        cout << regras[i].gerador << " -> ";
        for (int j = 0; j < (int)regras[i].gerado.size(); j++)
        {
            if (j == regras[i].posicao_ponto)
            {
                cout << ". ";
            }
            cout << regras[i].gerado[j] << " ";
        }
        if (regras[i].posicao_ponto == regras[i].gerado.size())
        {
            cout << ". ";
        }
        cout << endl;
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
            // colocar estado atual na pilha
            pilha.push("estado" + this->estado_atual);
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
            // muda o estado atual para o estado do topo da pilha
            this->estado_atual = pilha.top().substr(6, pilha.top().size() - 6);
            // this->estado_atual = this->automato[this->estado_atual][regra.first];
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
            // se for o ultimo elemento, não coloca a virgula
            if (next(it2) == it->second.end())
            {
                cout << it2->first << " -> " << it2->second << " ";
                break;
            }
            cout << it2->first << " -> " << it2->second << ", ";
        }
        cout << "}" << endl;
    }
}