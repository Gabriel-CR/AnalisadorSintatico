from gramatica import Gramatica
from firstFollow import FirstFollow

if __name__ == '__main__':
    a = Gramatica()
    a.readGramaticaFile()
    a.makeNaoTerminal()
    a.makeTerminal()

    ff = FirstFollow()

    print(a.naoTerminal)
    print(a.terminal)
