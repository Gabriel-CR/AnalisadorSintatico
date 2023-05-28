#include "../headers/controller.h"

Controller::Controller(string caminho)
{
    this->caminho = caminho;
}

void Controller::menu()
{
    cout << "[ERRO] erro nos argumentos passados ou falta deles" << endl;

    cout << "Para compilar o código, use:" << endl;
    cout << "g++ -o run ./source/*.cpp  *.cpp" << endl;

    cout << "Para executar o código, use:" << endl;
    cout << "./run [argumento] [palavra] [ver automato]" << endl;
    cout << "\t[argumento] pode ser ff ou aut" << endl;
    cout << "\t[palavra] deve estar entre aspas e cada token deve ser separado por espaco" << endl;
    cout << "\t[ver automato] deve ser sa para visualizar o automato gerado" << endl;
    cout << "\t[OBS] [palavra] e [ver automato] deve ser usada somente com argumento aut" << endl;

    cout << "Exemplo de uso:" << endl;
    cout << "./run ff" << endl;
    cout << "./run aut \"print ( id )\" sa" << endl;
}

void Controller::read_gramatica_file()
{
    // cout << "Lendo arquivo de gramatica..." << endl;
    map<string, vector<string>> gramatica;
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

            gramatica[nao_terminal].push_back(gerador);
            // guardar a ordem das regras
            this->ordem_regras.push_back(make_pair(nao_terminal, gerador));
        }
        file.close();
        // cout << "Gramatica lida com sucesso!" << endl;
        this->make_gramatica(gramatica);
    }
    else
    {
        cout << "Erro ao abrir arquivo de gramatica." << endl;
    }
}

void Controller::make_gramatica(map<string, vector<string>> gramatica)
{
    this->gramatica.set_gramatica(gramatica);
    this->gramatica.make_terminais();
    this->gramatica.make_nao_terminais();
    this->first_follow.set_gramatica(gramatica);
    this->first_follow.set_terminais(this->gramatica.get_terminais());
    this->first_follow.set_nao_terminais(this->gramatica.get_nao_terminais());
}

void Controller::make_nullable()
{
    for (string nao_terminal : gramatica.get_nao_terminais())
    {
        cout << nao_terminal << " = " << (first_follow.nullable(nao_terminal) ? "True" : "False") << endl;
    }
    cout << endl;
}

void Controller::make_firsts()
{
    for (string nao_terminal : gramatica.get_nao_terminais())
    {
        set<string> firsts = first_follow.first(nao_terminal);
        cout << "First(" << nao_terminal << ") = { ";
        for (string first : firsts)
        {
            cout << first << " ";
        }
        cout << "}" << endl;
    }
    cout << endl;
}

void Controller::make_follows()
{
    for (string nao_terminal : gramatica.get_nao_terminais())
    {
        set<string> follows = first_follow.follow(nao_terminal);
        cout << "Follow(" << nao_terminal << ") = { ";
        for (string follow : follows)
        {
            cout << follow << " ";
        }
        cout << "}" << endl;
    }
}

void Controller::make_automato(string palavra, bool print_automato)
{
    this->automato.set_ordem_regras(this->ordem_regras);
    this->automato.set_gramatica(this->gramatica.get_gramatica());
    this->automato.set_terminais(this->gramatica.get_terminais());
    this->automato.set_nao_terminais(this->gramatica.get_nao_terminais());

    vector<ElemEstado> elem_inicial;
    this->automato.make_automato(ElemEstado(this->ordem_regras[0].first, this->ordem_regras[0].second, 0, 1));

    if (print_automato)
    {
        this->automato.print_automato();
    }
    this->automato.test_word(palavra + " $");
}