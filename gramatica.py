class Gramatica:
    def __init__(self):
        self.gramatica = {}
        # self.makeGramatica()
        # self.naoTerminal = ["S", "B", "P", "E"]
        # self.terminal = ["$", "id", "(", "]", "", ")", ","]
        self.naoTerminal = set()
        self.terminal = set()

    def readGramatica(self):
        qtdRegras = int(input())
        while qtdRegras > 0:
            line = str(input())
            if self.gramatica.get(line[0]) == None:
                self.gramatica[line[0]] = [line[5:]]
            else:
                self.gramatica[line[0]].append(line[5:])
            qtdRegras -= 1

    def makeNaoTerminal(self):
        pass

    def makeTerminal(self):
        pass

    def getGramatica(self):
        return self.gramatica

    def isTerminal(self, symbol):
        return symbol in self.terminal

    def isNaoTerminal(self, symbol):
        return symbol in self.naoTerminal

    def __str__(self):
        res = str()
        for i in self.gramatica:
            res += f"{i} -> {self.gramatica[i]}\n"
        return res
