from teste import Teste

from gramatica import Gramatica
from firstFollow import FirstFollow
from automato import Automato

if __name__ == '__main__':
    a = Gramatica(str(input()))
    a.readGramaticaFile()

    t = Teste(a.gramatica, a.terminal, a.naoTerminal)
    t.testFirst()
    # t.testFollow()
    # t.testNullable()
