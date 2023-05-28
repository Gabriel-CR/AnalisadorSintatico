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

    return closure;
}

void mostrar_regras(vector<ElemEstado> elem)
{
    for (int i = 0; i < (int)elem.size(); i++)
    {
        cout << elem[i].gerador << " -> ";
        for (int j = 0; j < (int)elem[i].gerado.size(); j++)
        {
            if (j == elem[i].posicao_ponto)
            {
                cout << ". ";
            }
            cout << elem[i].gerado[j] << " ";
        }
        if (elem[i].posicao_ponto == (int)elem[i].gerado.size())
        {
            cout << ". ";
        }
        cout << endl;
    }
}

void Automato::goto_(vector<ElemEstado> elem, int current_state)
{
    int estado_atual = current_state;

    // para cada elemento, faz o goto
    for (int i = 0; i < (int)elem.size(); i++)
    {
        // [goto] se o ponto está na posição de um não terminal
        if (elem[i].posicao_ponto < (int)elem[i].gerado.size() &&
            this->nao_terminais.find(elem[i].gerado[elem[i].posicao_ponto]) != this->nao_terminais.end())
        {
            // cout << "nao terminal " << current_state << endl;
            this->automato[current_state][elem[i].gerado[elem[i].posicao_ponto]] = "g" + to_string(estado_atual + 1);
            estado_atual++;
            // mostrar_regras({elem[i]});
        }

        // [shift] se o ponto está na posição de um terminal
        else if (elem[i].posicao_ponto < (int)elem[i].gerado.size() &&
                 this->terminais.find(elem[i].gerado[elem[i].posicao_ponto]) != this->terminais.end())
        {
            // cout << "terminal " << current_state << endl;
            this->automato[current_state][elem[i].gerado[elem[i].posicao_ponto]] = "s" + to_string(estado_atual + 1);
            estado_atual++;
            // mostrar_regras({elem[i]});
        }

        // [reduce] se o ponto está no final da regra
        else if (elem[i].posicao_ponto == (int)elem[i].gerado.size())
        {
            // reduce em cada terminal
            for (auto it = this->terminais.begin(); it != this->terminais.end(); it++)
            {
                // procura regra que reduz usando ordem regras
                for (int j = 0; j < (int)this->ordem_regras.size(); j++)
                {
                    // se a regra reduz
                    if (this->ordem_regras[j].first == elem[i].gerador &&
                        this->ordem_regras[j].second == Utils::join(elem[i].gerado, " "))
                    {
                        // cout << "reduce " << current_state << endl;
                        this->automato[current_state][*it] = "r" + to_string(j);
                        // mostrar_regras({elem[i]});
                    }
                }
            }
        }

        // [accept] se o elemento na posição do ponto é $
        else if (elem[i].gerado[elem[i].posicao_ponto] == "$")
        {
            // cout << "accept " << current_state << endl;
            this->automato[current_state]["$"] = "acc";
            // mostrar_regras({elem[i]});
        }
    }
}

void Automato::make_automato(ElemEstado elem_inicial)
{
    int current_state = 1;
    queue<ElemEstado> fila;

    fila.push(elem_inicial);

    vector<ElemEstado> closure = this->closure({elem_inicial}, 1);
    this->mem_regra[current_state] = elem_inicial.to_string();

    while (!fila.empty())
    {
        current_state = fila.front().estado;

        vector<ElemEstado> cs_element;

        // tira da fila enquando o estado for o mesmo
        while (!fila.empty() && fila.front().estado == current_state)
        {
            cs_element.push_back(fila.front());
            fila.pop();
        }

        // calcula o closure
        vector<ElemEstado> cs_closure = this->closure(cs_element, current_state);

        // mostrar closure
        cout << "closure " << current_state << endl;
        mostrar_regras(cs_closure);

        // calcula o goto para cada elemento do closure
        for (int i = 0; i < (int)cs_closure.size(); i++)
        {
            this->goto_(cs_closure, current_state);
        }

        // avanço o ponto de cada elemento do closure
        for (int i = 0; i < (int)cs_closure.size(); i++)
        {
            // se ao avançar o ponto, o ponto for maior que o tamanho do gerado
            // não adiciona na fila
            cs_closure[i].posicao_ponto += 1;

            if (cs_closure[i].posicao_ponto < (int)cs_closure[i].gerado.size())
            {
                // se o elemento na posição do ponto for $ não adiciona na fila
                if (cs_closure[i].gerado[cs_closure[i].posicao_ponto - 1] != "$")
                {
                    cs_closure[i].estado = i + current_state + 1;
                    // avança o ponto
                    // cs_closure[i].posicao_ponto++;
                    fila.push(cs_closure[i]);
                }
            }
        }

        // mostrar fila
        cout << "fila:" << endl;
        queue<ElemEstado> fila_aux = fila;
        while (!fila_aux.empty())
        {
            cout << fila_aux.front().to_string() << fila_aux.front().estado << " " << endl;
            fila_aux.pop();
        }
        cout << endl
             << endl;

        // break;
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
        cout << "string: " << caractere << endl;
        cout << "acao: " << acao << endl;
        cout << "estado atual: " << estado_atual << endl
             << endl;

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