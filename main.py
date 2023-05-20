from teste import Teste

from gramatica import Gramatica
from firstFollow import FirstFollow
from automato import Automato

if __name__ == '__main__':
    a = Gramatica("g.txt")
    a.readGramaticaFile()

    aut = Automato(a.gramatica, a.naoTerminal)
    aut.makeAutomato(list(a.gramatica.keys())[0])

    # t = Teste(a.gramatica, a.terminal, a.naoTerminal)
    # t.testFirst()
    # t.testFollow()
    # t.testNullable()
