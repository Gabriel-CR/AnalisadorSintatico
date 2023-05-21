#include "../headers/automato.h"

Automato::Automato()
{
}

void Automato::make_automato()
{
    for (auto it = this->gramatica.begin(); it != this->gramatica.end(); it++)
    {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            vector<string> split_gramatica = Utils::split(*it2, " ");
            for (int i = 0; i < split_gramatica.size(); i++)
            {
                if (this->nao_terminais.find(split_gramatica[i]) != this->nao_terminais.end())
                {
                    if (i == split_gramatica.size() - 1)
                    {
                        this->automato[it->first]["e"] = split_gramatica[i];
                    }
                    else
                    {
                        this->automato[it->first][split_gramatica[i + 1]] = split_gramatica[i];
                    }
                }
            }
        }
    }
}

void Automato::set_gramatica(map<string, vector<string>> gramatica)
{
    this->gramatica = gramatica;
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
        cout << it->first << " -> ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            cout << it2->first << " ";
        }
        cout << endl;
    }
}