#include "../headers/gramatica.h"

Gramatica::Gramatica(string caminho)
{
    this->caminho = caminho;
}

void Gramatica::read_gramatica_file()
{
    cout << "Lendo arquivo de gramatica..." << endl;
    fstream file;
    file.open(this->caminho, ios::in);

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            vector<string> temp = Utils::split(line, " -> ");

            string nao_terminal = temp[0];
            string gerador = temp[1];

            this->gramatica[nao_terminal].push_back(gerador);
        }
        file.close();
        cout << "Gramatica lida com sucesso!" << endl;
    }
    else
    {
        cout << "Erro ao abrir arquivo de gramatica." << endl;
    }
}

void Gramatica::make_terminais()
{
    cout << "Criando conjunto de terminais..." << endl;
    for (auto i : this->gramatica)
    {
        this->nao_terminais.insert(i.first);
    }
}

void Gramatica::make_nao_terminais()
{
    cout << "Criando conjunto de nao terminais..." << endl;
    for (auto i : this->gramatica)
    {
        for (auto j : i.second)
        {
            vector<string> split_gramatica = Utils::split(j, " ");
            for (auto k : split_gramatica)
            {
                if (this->nao_terminais.find(k) == this->nao_terminais.end())
                {
                    this->terminais.insert(k);
                }
            }
        }
    }
}

map<string, vector<string>> Gramatica::get_gramatica()
{
    return this->gramatica;
}

set<string> Gramatica::get_terminais()
{
    return this->terminais;
}

set<string> Gramatica::get_nao_terminais()
{
    return this->nao_terminais;
}

void Gramatica::print_gramatica()
{
    cout << "\nImprimindo gramatica..." << endl;
    for (auto it = this->gramatica.begin(); it != this->gramatica.end(); it++)
    {
        cout << it->first << " -> ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            cout << *it2 << " | ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "Imprimindo terminais..." << endl;
    for (auto it = this->terminais.begin(); it != this->terminais.end(); it++)
    {
        cout << *it << endl;
    }
    cout << endl;
    cout << "Imprimindo nao terminais..." << endl;
    for (auto it = this->nao_terminais.begin(); it != this->nao_terminais.end(); it++)
    {
        cout << *it << endl;
    }
}
