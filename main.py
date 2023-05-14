from gramatica import Gramatica
from firstFollow import FirstFollow
from automato import Automato

if __name__ == '__main__':
    a = Gramatica()
    a.readGramaticaFile()

    # aut = Automato(a.gramatica, a.naoTerminal)
    # aut.makeAutomato(list(a.gramatica.items())[0])

    ff = FirstFollow(a.gramatica, a.terminal, a.naoTerminal)
    for i in a.gramatica.keys():
        print(f"FIRST({i}) = {ff.first(i)}")

    for i in a.gramatica.values():
        for j in i:
            for k in j.split():
                if k not in a.naoTerminal:
                    print(f"FIRST({k}) = {ff.first(k)}")

    """
    TODO
    for i in a.gramatica:
        print(f"FIRST({i}) = {ff.follow(i)}")
    """

    # print(a)
