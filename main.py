from gramatica import Gramatica
from firstFollow import FirstFollow

if __name__ == '__main__':
    a = Gramatica()
    a.readGramaticaFile()

    ff = FirstFollow(a.gramatica, a.terminal, a.naoTerminal)
    print(ff.first('eps'))

    # print(a.gramatica.get("S"))


    # print(a)
