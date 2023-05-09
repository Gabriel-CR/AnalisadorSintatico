class Gramatica:
    def __init__(self):
        self.gramatica = {}
        self.makeGramatica()
        self.naoTerminal = ["S", "B", "P", "E"]
        self.terminal = ["$", "id", "(", "]", "", ")", ","]

    def makeGramatica(self):
        self.gramatica["S"] = ["B $"]
        self.gramatica["B"] = ["id P", "id ( E ]"]
        self.gramatica["P"] = ["", "( E )"]
        self.gramatica["E"] = ["B , E"]

    def getGramatica(self):
        return self.gramatica

    def isTerminal(self, symbol):
        return symbol in self.terminal

    def isNaoTerminal(self, symbol):
        return symbol in self.naoTerminal
