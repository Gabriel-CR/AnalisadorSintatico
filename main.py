from gramatica import Gramatica
from firstFollow import FirstFollow

if __name__ == '__main__':
    a = Gramatica()
    a.readGramatica()

    print(a)



























    # ff = FirstFollow()
    # print(f"FIRST(S) = {ff.first('S')}")
    # print(f"FIRST(B) = {ff.first('B')}")
    # print(f"FIRST(P) = {ff.first('P')}")
    # print(f"FIRST(E) = {ff.first('E')}")

    # simbolos = a.naoTerminal
    # for i in a.terminal:
    #     simbolos.append(i)
    # for s in simbolos:
    #     print(f"FIRST({s}) -> {ff.first(s)}")
