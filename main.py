from teste import Teste

from gramatica import Gramatica
from firstFollow import FirstFollow
from automato import Automato

if __name__ == '__main__':
    a = Gramatica("g.txt")
    a.readGramaticaFile()

    aut = Automato(a.gramatica, a.naoTerminal)
    # inicial = list(a.gramatica.keys())[0]
    # aut.makeAutomato((inicial, a.gramatica.get(inicial)))
    aut.testWord("( id ) $")

    # t = Teste(a.gramatica, a.terminal, a.naoTerminal)
    # t.testFirst()
    # t.testFollow()
    # t.testNullable()
