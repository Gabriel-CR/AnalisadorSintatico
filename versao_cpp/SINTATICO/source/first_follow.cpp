#include "../headers/first_follow.h"

FirstFollow::FirstFollow()
{
}

bool FirstFollow::nullable(string str)
{
    if (str == "eps")
    {
        return true;
    }
    if (this->terminais.find(str) != this->terminais.end() && str != "eps")
    {
        return false;
    }

    // flag usada para saber se todas as producoes sao nulas
    bool nullable = true;
    vector<string> producao = this->gramatica[str];

    for (int i = 0; i < (int)producao.size(); i++)
    {
        vector<string> split_producao = Utils::split(producao[i], " ");

        // testar todas as strigs da producao
        // se todas forem nulas, flag = true
        // se alguma nao for nula, flag = false
        for (int j = 0; j < (int)split_producao.size(); j++)
        {
            // não chamar a recursão para um símbolo igual
            // evita loop infinito
            if (split_producao[j] == str)
                return false;

            if (this->nullable(split_producao[j]) == false)
            {
                nullable = false;
                break;
            }
        }

        if (nullable == true)
        {
            return true;
        }
    }

    return false;
}

set<string> FirstFollow::first(string str)
{
    set<string> firsts;

    // caso str seja um terminal, retorna ele mesmo
    // não inclui o eps
    if (this->terminais.find(str) != this->terminais.end())
    {
        if (str != "eps")
        {
            firsts.insert(str);
        }
    }
    else
    {
        vector<string> producao = this->gramatica[str];

        for (int i = 0; i < (int)producao.size(); i++)
        {
            vector<string> split_producao = Utils::split(producao[i], " ");

            // se o primeiro elemento da producao for um terminal, adiciona ele no firsts
            if (this->terminais.find(split_producao[0]) != this->terminais.end())
            {
                if (split_producao[0] != "eps")
                {
                    firsts.insert(split_producao[0]);
                }
            }
            else
            {
                // evitar loop infinito
                if (split_producao[0] == str)
                    return firsts;

                // se o primeiro elemento da producao for um nao terminal, adiciona o first dele no firsts
                set<string> firsts_producao = this->first(split_producao[0]);
                firsts.insert(firsts_producao.begin(), firsts_producao.end());

                // se o primeiro elemento da producao for nulo, adiciona o first do proximo elemento no firsts
                // faz isso até encontrar um elemento que não seja nulo
                while (this->nullable(split_producao[0]) == true)
                {
                    if (split_producao.size() == 1)
                    {
                        break;
                    }
                    else
                    {
                        split_producao.erase(split_producao.begin());
                        // evitar loop infinito
                        if (split_producao[0] == str)
                            return firsts;
                        set<string> firsts_producao = this->first(split_producao[0]);
                        firsts.insert(firsts_producao.begin(), firsts_producao.end());
                    }
                }
            }
        }
    }

    return firsts;
}

set<string> FirstFollow::follow(string str)
{
    set<string> follows;

    // para cada regra da gramatica
    for (auto it = this->gramatica.begin(); it != this->gramatica.end(); it++)
    {
        // para cada producao da regra
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            // para cada elemento da producao
            vector<string> split_gramatica = Utils::split(*it2, " ");
            for (int i = 0; i < split_gramatica.size(); i++)
            {
                // se encontrei str na producao
                if (split_gramatica[i] == str)
                {
                    // se tem um elemento depois de str
                    if (i < split_gramatica.size() - 1)
                    {
                        // se o proximo elemento é um terminal, adiciona ele no follow
                        if (this->terminais.find(split_gramatica[i + 1]) != this->terminais.end())
                        {
                            follows.insert(split_gramatica[i + 1]);
                        }
                        // se o proximo elemento é um nao terminal, adiciona o first dele no follow
                        else
                        {
                            set<string> firsts_producao = this->first(split_gramatica[i + 1]);
                            follows.insert(firsts_producao.begin(), firsts_producao.end());

                            // se o proximo elemento é nulo, adiciona o follow da regra no follow
                            // faz isso até encontrar um elemento que não seja nulo
                            // ou não exista mais elementos
                            while (this->nullable(split_gramatica[i + 1]) == true)
                            {
                                if (i + 1 == split_gramatica.size() - 1)
                                {
                                    break;
                                }
                                else
                                {
                                    set<string> firsts_producao = this->first(split_gramatica[i + 2]);
                                    follows.insert(firsts_producao.begin(), firsts_producao.end());
                                    i++;
                                }
                            }
                        }
                    }
                    // se não tem um elemento depois de str
                    else
                    {
                        // se str é diferente da regra, adiciona o follow da regra no follow
                        if (it->first != str)
                        {
                            set<string> follows_producao = this->follow(it->first);
                            follows.insert(follows_producao.begin(), follows_producao.end());
                        }
                    }
                }
            }
        }
    }

    return follows;
}

void FirstFollow::set_gramatica(map<string, vector<string>> gramatica)
{
    this->gramatica = gramatica;
}

void FirstFollow::set_terminais(set<string> terminais)
{
    this->terminais = terminais;
}

void FirstFollow::set_nao_terminais(set<string> nao_terminais)
{
    this->nao_terminais = nao_terminais;
}
