#include "../headers/automato.h"

Automato::Automato()
{
}

vector<ElemEstado> Automato::closure(vector<ElemEstado> elem, int current_state)
{
    vector<ElemEstado> closure;
    for (int i = 0; i < (int)elem.size(); i++)
    {
        closure.push_back(elem[i]);
    }

    for (int i = 0; i < (int)closure.size(); i++)
    {
        if (closure[i].posicao_ponto < (int)closure[i].gerado.size() &&
            this->nao_terminais.find(closure[i].gerado[closure[i].posicao_ponto]) != this->nao_terminais.end())
        {
            // cria um novo ElemEstado para cada regra do não terminal
            for (int j = 0; j < (int)this->gramatica[closure[i].gerado[closure[i].posicao_ponto]].size(); j++)
            {
                ElemEstado novo(closure[i].gerado[closure[i].posicao_ponto], this->gramatica[closure[i].gerado[closure[i].posicao_ponto]][j], 0, current_state);

                // verifica se já não existe esse novo ElemEstado em closure
                bool existe = false;
                for (int k = 0; k < (int)closure.size(); k++)
                {
                    if (closure[k].gerador == novo.gerador &&
                        closure[k].gerado == novo.gerado &&
                        closure[k].posicao_ponto == novo.posicao_ponto)
                    {
                        existe = true;
                        break;
                    }
                }

                // se não existe, adiciona em closure
                if (!existe)
                {
                    closure.push_back(novo);
                }
            }
        }
    }

    // antes de retornar, verifico se já não existe esse estado no automato
    // se existe, não retorno
    // se não existe, retorno
    for (int i = 0; i < (int)closure.size(); i++)
    {
        if (closure[i].posicao_ponto == (int)closure[i].gerado.size())
        {
            // se já existe esse estado no automato, não retorno
            if (this->automato.find(current_state) != this->automato.end())
            {
                return vector<ElemEstado>();
            }
            // se não existe, retorno
            else
            {
                return closure;
            }
        }
    }

    return closure;
}

void Automato::make_automato(ElemEstado elem_inicial)
{
    queue<ElemEstado> fila;
    fila.push(elem_inicial);

    vector<ElemEstado> regras;
    int current_state = 1;
    int temp_state = 1;

    vector<vector<ElemEstado>> regras_verify;

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
        }

        vector<ElemEstado> temp = this->closure(regras, current_state);

        // verifica se essas regras já não foram processadas
        // faz isso verificando regras_verify
        bool existe = false;
        for (int i = 0; i < (int)regras_verify.size(); i++)
        {
            for (int j = 0; j < (int)regras_verify[i].size(); j++)
            {
                if (regras_verify[i][j].gerador == temp[j].gerador &&
                    regras_verify[i][j].gerado == temp[j].gerado &&
                    regras_verify[i][j].posicao_ponto == temp[j].posicao_ponto)
                {
                    existe = true;

                    // se existe, faz a transição goto ou shift
                    // se o ponto esta na posição de um NT, faz goto para o estado que possui esse NT
                    if (temp[j].posicao_ponto < (int)temp[j].gerado.size() &&
                        this->nao_terminais.find(temp[j].gerado[temp[j].posicao_ponto]) != this->nao_terminais.end())
                    {
                        this->automato[current_state][temp[j].gerado[temp[j].posicao_ponto]] = "g" + to_string(regras_verify[i][j].estado + 1);
                    }

                    // se o ponto esta na posição de um T, faz shift para o estado que possui esse T
                    else if (temp[j].posicao_ponto < (int)temp[j].gerado.size() &&
                             this->terminais.find(temp[j].gerado[temp[j].posicao_ponto]) != this->terminais.end())
                    {
                        this->automato[current_state][temp[j].gerado[temp[j].posicao_ponto]] = "s" + to_string(regras_verify[i][j].estado + 1);
                    }
                }
            }

            if (existe)
            {
                break;
            }
        }

        // se não existe, adiciona em regras_verify e em regras
        if (!existe)
        {
            regras_verify.push_back(temp);
            for (int i = 0; i < (int)temp.size(); i++)
            {
                regras.push_back(temp[i]);
            }

            // remove regras repetidas
            for (int i = 0; i < (int)regras.size(); i++)
            {
                for (int j = i + 1; j < (int)regras.size(); j++)
                {
                    if (regras[i].gerador == regras[j].gerador &&
                        regras[i].gerado == regras[j].gerado &&
                        regras[i].posicao_ponto == regras[j].posicao_ponto)
                    {
                        regras.erase(regras.begin() + j);
                        j--;
                    }
                }
            }
        }

        // mostrar regras
        // cout << "Regras: " << endl;
        // for (int i = 0; i < (int)regras.size(); i++)
        // {
        //     cout << regras[i].to_string() << endl;
        // }

        // // mostrar fila
        // cout << "Fila: " << endl;
        // queue<ElemEstado> temp_fila = fila;
        // while (!temp_fila.empty())
        // {
        //     cout << temp_fila.front().to_string() << endl;
        //     temp_fila.pop();
        // }

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

                // mostrar a regra que foi apagada
                // cout << "Regra apagada: " << regras[i].to_string() << endl;

                // apaga a regra antiga de regras
                regras.erase(regras.begin() + i);

                // incrementa o estado temporário
                temp_state += 1;
            }
        }

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
    stack<ElemPilha> pilha;

    // coloca o estado inicial na pilha
    pilha.push(ElemPilha("$", 1));

    int posicao_palavra = 0;
    int estado_atual = 1;
    string acao;

    while (true)
    {
        // estado_atual = pilha.top().estado;

        // converter char para string
        string caractere(1, word[posicao_palavra]);
        acao = this->automato[estado_atual][caractere];

        if (acao[0] == 's')
        {
            // coloca o estado e a palavra na pilha
            string e(1, word[posicao_palavra]);
            pilha.push(ElemPilha(e, stoi(string(1, acao[1]))));

            // incrementa a posição da palavra
            posicao_palavra += 2;

            // muda o estado atual
            string x(1, acao[1]);
            estado_atual = stoi(x);
        }
        else if (acao[0] == 'r')
        {
            // pega a regra
            string regra = this->ordem_regras[stoi(string(1, acao[1]))].second;
            // cout << "regra: " << regra << endl;

            // pega o tamanho da regra
            int tamanho_regra = Utils::split(regra, " ").size();

            // desempilha o tamanho da regra
            for (int i = 0; i < tamanho_regra; i++)
            {
                pilha.pop();
            }

            // pega o estado do topo da pilha
            estado_atual = pilha.top().estado;
            // cout << "estado atual: " << estado_atual << endl;

            // pega o não terminal do topo da pilha
            string nao_terminal = this->ordem_regras[stoi(string(1, acao[1]))].first;
            // cout << "nao terminal: " << nao_terminal << endl;

            // faz o goto
            acao = this->automato[estado_atual][nao_terminal];
            estado_atual = stoi(string(1, acao[1]));
            // cout << "estado atual: " << estado_atual << endl;

            // coloca o estado e o não terminal na pilha
            pilha.push(ElemPilha(nao_terminal, estado_atual));
        }
        else if (acao[0] == 'a')
        {
            cout << "Aceito" << endl;
            return true;
        }
        else
        {
            cout << "Erro sintatico" << endl;
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
    std::cout << "Automato: " << endl;
    for (auto it = this->automato.begin(); it != this->automato.end(); it++)
    {
        std::cout << it->first << " : { ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            // se for o ultimo elemento, não coloca a virgula
            if (next(it2) == it->second.end())
            {
                std::cout << it2->first << " -> " << it2->second << " ";
                break;
            }
            std::cout << it2->first << " -> " << it2->second << ", ";
        }
        std::cout << "}" << endl;
    }
}