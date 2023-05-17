from gramatica import Gramatica
from firstFollow import FirstFollow
from automato import Automato

if __name__ == '__main__':
    a = Gramatica("./utils/t.txt")
    a.readGramaticaFile()

    ff = FirstFollow(a.gramatica, a.terminal, a.naoTerminal)
    for i in a.gramatica.keys():
        print(f"NULLABLE({i}) = {ff.nullable(i)}")
    for i in a.gramatica.values():
        for j in i:
            for k in j.split():
                if k not in a.naoTerminal:
                    print(f"NULLABLE({k}) = {ff.nullable(k)}")
