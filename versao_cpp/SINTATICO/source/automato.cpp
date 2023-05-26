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
        // atualiza current_state
        current_state = fila.front().estado;
        temp_state = current_state;

        // tirar da fila e colcar em regras enquando o estado do ElemEstado for o mesmo
        while (!fila.empty() && fila.front().estado == current_state)
        {
            regras.push_back(fila.front());
            fila.pop();

            // mostra estado elemento que está sendo tirado da fila
            /*cout << ".... retirando ...." << endl;
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
            // mostrar estado registrado no elemento
            cout << " , " << regras[regras.size() - 1].estado << endl;
            cout << "..................." << endl;*/
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
        /*for (int i = 0; i < (int)regras.size(); i++)
        {
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
        cout << endl;*/

        // [shift] se . na posição de Terminal != $, coloca um shift em automato
        for (int i = 0; i < (int)regras.size(); i++)
        {
            if (regras[i].posicao_ponto < (int)regras[i].gerado.size() &&
                this->terminais.find(regras[i].gerado[regras[i].posicao_ponto]) != this->terminais.end() &&
                regras[i].gerado[regras[i].posicao_ponto] != "$")
            {
                // vai para o estado do ultimo elemento da fila + 1
                int temp = fila.back().estado;

                this->automato[current_state][regras[i].gerado[regras[i].posicao_ponto]] = "s" + to_string(temp + 1);

                // avança o ponto e estado
                // coloca essa regra modificada na fila
                regras[i].posicao_ponto++;
                regras[i].estado = temp + 1;
                fila.push(regras[i]);

                // verifica se não tem um terminal igual a este que vai para o mesmo estado
                for (int j = 0; j < (int)regras.size(); j++)
                {
                    if (regras[j].posicao_ponto < (int)regras[j].gerado.size() &&
                        this->terminais.find(regras[j].gerado[regras[j].posicao_ponto]) != this->terminais.end() &&
                        regras[j].gerado[regras[j].posicao_ponto] != "$" &&
                        regras[j].gerado[regras[j].posicao_ponto] != regras[i].gerado[regras[i].posicao_ponto] &&
                        regras[j].estado == regras[i].estado)
                    {
                        // se tiver, faz o mesmo processo de cima
                        this->automato[current_state][regras[j].gerado[regras[j].posicao_ponto]] = "s" + to_string(temp);

                        regras[j].posicao_ponto++;
                        regras[j].estado = temp + 1;
                        fila.push(regras[j]);

                        // apaga a regra antiga de regras
                        regras.erase(regras.begin() + j);
                    }
                }

                // apaga a regra antiga de regras
                regras.erase(regras.begin() + i);

                // incrementa o estado temporário
                temp_state += 1;
            }
        }

        // [ERRO AQUI]
        // [goto] se . na posição de Não Terminal, coloca um goto em automato
        for (int i = 0; i < (int)regras.size(); i++)
        {
            if (regras[i].posicao_ponto < (int)regras[i].gerado.size() && this->nao_terminais.find(regras[i].gerado[regras[i].posicao_ponto]) != this->nao_terminais.end())
            {
                // vai para o estado do ultimo elemento da fila + 1
                int temp = fila.back().estado;

                this->automato[current_state][regras[i].gerado[regras[i].posicao_ponto]] = "g" + to_string(temp + 1);

                // avança o ponto e estado
                // coloca essa regra modificada na fila
                regras[i].posicao_ponto++;
                regras[i].estado = temp + 1;
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
                        this->automato[current_state][regras[j].gerado[regras[j].posicao_ponto]] = "g" + to_string(temp);

                        regras[j].posicao_ponto++;
                        regras[j].estado = temp + 1;
                        fila.push(regras[j]);

                        // apaga a regra antiga de regras
                        regras.erase(regras.begin() + j);
                    }
                }

                // apaga a regra antiga de regras
                regras.erase(regras.begin() + i);

                temp_state += 1;
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
                    for (int j = 0; j < (int)this->ordem_regras.size(); j++)
                    {
                        if (this->ordem_regras[j].first == regras[i].gerador && this->ordem_regras[j].second == Utils::join(regras[i].gerado, " "))
                        {
                            this->automato[current_state][*it] = "r" + to_string(j);
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
    }
}

bool Automato::test_word(string word)
{
    cout << "Testando palavra: " << word << endl;
    int estado_atual = 1;
    int i = 0;

    vector<string> palavra = Utils::split(word, " ");

    stack<string> pilha;

    while (true)
    {
        string simbolo = palavra[i];
        string acao = this->automato[estado_atual][simbolo];

        // se no topo da pilha tem um não terminal
        // alterar acao
        if (!pilha.empty() && this->nao_terminais.find(pilha.top()) != this->nao_terminais.end())
        {
            acao = this->automato[estado_atual][pilha.top()];
            pilha.pop();
        }

        cout << "Estado atual: " << estado_atual << endl;
        cout << "Simbolo: " << simbolo << endl;
        cout << "Acao: " << acao << endl;

        // [shift] se ação for shift,
        // empilha estado atual e simbolo
        // vai para o estado da ação
        if (acao[0] == 's')
        {
            pilha.push("estado " + to_string(estado_atual));
            pilha.push(simbolo);

            estado_atual = stoi(acao.substr(1, acao.size() - 1));
            i++;
        }

        // [reduce] se ação for reduce,
        // desempilha o tamanho da regra
        // desempilha o estado
        else if (acao[0] == 'r')
        {
            int tamanho_regra = Utils::split(this->ordem_regras[stoi(acao.substr(1, acao.size() - 1))].second, " ").size();
            cout << "Tamanho da regra: " << tamanho_regra << endl;

            for (int j = 0; j < tamanho_regra; j++)
            {
                pilha.pop();
            }

            estado_atual = stoi(pilha.top().substr(7, pilha.top().size() - 7));
            pilha.pop();

            string nao_terminal = this->ordem_regras[stoi(acao.substr(1, acao.size() - 1))].first;
            cout << "Nao terminal: " << nao_terminal << endl;

            pilha.push(nao_terminal);
        }

        // [goto] se ação for goto,
        // vai para o estado da ação
        else if (acao[0] == 'g')
        {
            estado_atual = stoi(acao.substr(1, acao.size() - 1));
        }

        // [accept] se ação for accept,
        // aceita a palavra
        else if (acao[0] == 'a')
        {
            cout << "Palavra aceita!" << endl;
            return true;
        }

        // [error] se ação for error,
        // rejeita a palavra
        else
        {
            cout << "Palavra rejeitada!" << endl;
            return false;
        }

        // mostrar pilha
        cout << "Pilha: ";
        stack<string> pilha_aux = pilha;
        while (!pilha_aux.empty())
        {
            cout << pilha_aux.top() << " ";
            pilha_aux.pop();
        }
        cout << endl;
    }

    return false;
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