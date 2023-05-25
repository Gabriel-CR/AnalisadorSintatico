#include "../headers/automato.h"

Automato::Automato()
{
}

void Automato::make_automato_iterativo(ElemEstado elem_inicial)
{
    queue<ElemEstado> fila;
    fila.push(elem_inicial);

    vector<ElemEstado> regras;
    int current_state = 1;
    int temp_state = 1;

    // enquanto a fila não estiver vazia
    while (!fila.empty())
    {
        temp_state = current_state;

        // tirar da fila e colcar em regras enquando o estado do ElemEstado for o mesmo
        while (!fila.empty() && fila.front().estado == current_state)
        {
            regras.push_back(fila.front());
            fila.pop();

            // mostra estado elemento que está sendo tirado da fila
            cout << ".... retirando ...." << endl;
            cout << current_state << " : ";
            cout << regras[regras.size() - 1].gerador << " -> ";
            for (int j = 0; j < (int)regras[regras.size() - 1].gerado.size(); j++)
            {
                if (j == regras[regras.size() - 1].posicao_ponto)
                {
                    cout << ". ";
                }
                cout << regras[regras.size() - 1].gerado[j] << " ";
            }
            if (regras[regras.size() - 1].posicao_ponto == (int)regras[regras.size() - 1].gerado.size())
            {
                cout << ". ";
            }
            cout << endl;
        }

        // se . na posição de NT, adiciona as regras deste NT em regras
        for (int i = 0; i < (int)regras.size(); i++)
        {
            if (regras[i].posicao_ponto < (int)regras[i].gerado.size() &&
                this->nao_terminais.find(regras[i].gerado[regras[i].posicao_ponto]) != this->nao_terminais.end())
            {
                // adiciona as regras deste NT em regras
                for (int j = 0; j < (int)this->gramatica[regras[i].gerado[regras[i].posicao_ponto]].size(); j++)
                {
                    ElemEstado novo(regras[i].gerado[regras[i].posicao_ponto], this->gramatica[regras[i].gerado[regras[i].posicao_ponto]][j], 0, temp_state);
                    regras.push_back(novo);
                }
            }
        }

        // mostra as regras
        for (int i = 0; i < (int)regras.size(); i++)
        {
            cout << ".... mostrar regras 1 ...." << endl;
            // mostrar estado atual
            cout << current_state << " : ";
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

        // [shift] se . na posição de Terminal != $, coloca um shift em automato
        for (int i = 0; i < (int)regras.size(); i++)
        {
            if (regras[i].posicao_ponto < (int)regras[i].gerado.size() &&
                this->terminais.find(regras[i].gerado[regras[i].posicao_ponto]) != this->terminais.end() &&
                regras[i].gerado[regras[i].posicao_ponto] != "$")
            {
                this->automato[current_state][regras[i].gerado[regras[i].posicao_ponto]] = "s" + to_string(temp_state + 1);

                // avança o ponto e estado
                // coloca essa regra modificada na fila
                regras[i].posicao_ponto++;
                regras[i].estado = temp_state + 1;
                fila.push(regras[i]);

                // verifica se não tem um terminal igual a este que vai para o mesmo estado
                for (int j = 0; j < (int)regras.size(); j++)
                {
                    if (regras[j].posicao_ponto < (int)regras[j].gerado.size() &&
                        this->terminais.find(regras[j].gerado[regras[j].posicao_ponto]) != this->terminais.end() &&
                        regras[j].gerado[regras[j].posicao_ponto] != "$" &&
                        regras[j].gerado[regras[j].posicao_ponto] == regras[i].gerado[regras[i].posicao_ponto] &&
                        regras[j].estado == regras[i].estado)
                    {
                        // se tiver, faz o mesmo processo de cima
                        this->automato[current_state][regras[j].gerado[regras[j].posicao_ponto]] = "s" + to_string(temp_state);

                        regras[j].posicao_ponto++;
                        regras[j].estado = temp_state + 1;
                        fila.push(regras[j]);

                        // apaga a regra antiga de regras
                        regras.erase(regras.begin() + j);
                    }
                }

                // apaga a regra antiga de regras
                regras.erase(regras.begin() + i);

                temp_state++;
            }
        }

        // [goto] se . na posição de Não Terminal, coloca um goto em automato
        for (int i = 0; i < (int)regras.size(); i++)
        {
            if (regras[i].posicao_ponto < (int)regras[i].gerado.size() && this->nao_terminais.find(regras[i].gerado[regras[i].posicao_ponto]) != this->nao_terminais.end())
            {
                this->automato[current_state][regras[i].gerado[regras[i].posicao_ponto]] = "g" + to_string(temp_state + 1);

                // avança o ponto e estado
                // coloca essa regra modificada na fila
                regras[i].posicao_ponto++;
                regras[i].estado = temp_state + 1;
                fila.push(regras[i]);

                // verifica se não tem um não terminal igual a este que vai para o mesmo estado
                for (int j = 0; j < (int)regras.size(); j++)
                {
                    if (regras[j].posicao_ponto < (int)regras[j].gerado.size() &&
                        this->nao_terminais.find(regras[j].gerado[regras[j].posicao_ponto]) != this->nao_terminais.end() &&
                        regras[j].gerado[regras[j].posicao_ponto] == regras[i].gerado[regras[i].posicao_ponto] &&
                        regras[j].estado == regras[i].estado)
                    {
                        // se tiver, faz o mesmo processo de cima
                        this->automato[current_state][regras[j].gerado[regras[j].posicao_ponto]] = "g" + to_string(temp_state);

                        regras[j].posicao_ponto++;
                        regras[j].estado = temp_state + 1;
                        fila.push(regras[j]);

                        // apaga a regra antiga de regras
                        regras.erase(regras.begin() + j);
                    }
                }

                // apaga a regra antiga de regras
                regras.erase(regras.begin() + i);

                temp_state++;
            }
        }

        // [reduce] se . no fim da palavra, coloca um reduce em todos os terminais
        for (int i = 0; i < (int)regras.size(); i++)
        {
            if (regras[i].posicao_ponto == (int)regras[i].gerado.size())
            {
                // coloca um reduce em todos os terminais
                for (auto it = this->terminais.begin(); it != this->terminais.end(); it++)
                {
                    // usar ordem das regras para saber qual regra usar
                    for (int j = 0; j < this->ordem_regras.size(); j++)
                    {
                        if (this->ordem_regras[j].first == regras[i].gerador && this->ordem_regras[j].second == Utils::join(regras[i].gerado, " "))
                        {
                            this->automato[current_state][*it] = "r" + to_string(j + 1);
                        }
                    }
                }

                // apagar a regra antiga de regras
                regras.erase(regras.begin() + i);
            }
        }

        // [accept] se . na posição de $, coloca um accept em automato
        for (int i = 0; i < (int)regras.size(); i++)
        {
            if (regras[i].posicao_ponto < (int)regras[i].gerado.size() && regras[i].gerado[regras[i].posicao_ponto] == "$")
            {
                this->automato[current_state]["$"] = "a";
            }

            // apagar a regra antiga de regras
            regras.erase(regras.begin() + i);
        }

        // atualiza o estado atual
        current_state++;
    }
}

bool Automato::test_word(string word)
{
    cout << "Testando palavra: " << word << endl;
    int estado_atual = 1;
    int i = 0;

    stack<string> pilha;

    while (true)
    {
        map<string, string> estado = this->automato[estado_atual];
        string simbolo = word.substr(i, 1);
        string acao = estado[simbolo];

        // se a ação for shift
        if (acao[0] == 's')
        {
            // empilha o simbolo
            pilha.push(simbolo);
            // muda o estado atual
            estado_atual = stoi(acao.substr(1, acao.size() - 1));
            // colocar estado atual na pilha
            pilha.push("estado" + to_string(estado_atual));
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
            estado_atual = stoi(pilha.top().substr(6, pilha.top().size() - 6));
            // this->estado_atual = this->automato[this->estado_atual][regra.first];
        }
        // se acao for goto
        else if (acao[0] == 'g')
        {
            // muda o estado atual
            estado_atual = stoi(acao.substr(1, acao.size() - 1));
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