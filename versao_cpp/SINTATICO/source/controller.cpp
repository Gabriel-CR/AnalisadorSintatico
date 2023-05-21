#include "../headers/controller.h"

Controller::Controller(string caminho) : gramatica(caminho)
{
    gramatica.read_gramatica_file();
    gramatica.make_terminais();
    gramatica.make_nao_terminais();
    // gramatica.print_gramatica();

    this->first_follow.set_gramatica(gramatica.get_gramatica());
    this->first_follow.set_terminais(gramatica.get_terminais());
    this->first_follow.set_nao_terminais(gramatica.get_nao_terminais());
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

/*
void Controller::make_automato() {
    this->automato.set_gramatica(gramatica.get_gramatica());
    this->automato.set_terminais(gramatica.get_terminais());
    this->automato.set_nao_terminais(gramatica.get_nao_terminais());
    this->automato.make_automato();
    this->automato.print_automato();
}
*/