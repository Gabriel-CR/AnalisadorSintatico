class Automato:
    def __init__(self, gramatica, naoTerminal):
        self.automato = {}
        self.gramatica = gramatica
        self.naoTerminal = naoTerminal

    def makeAutomato(self, initial):
        # TODO
        regras = []
        if initial[1][0][0] in self.naoTerminal:
            print(initial[1][0][0])
            regras.append((initial[1][0][0], self.gramatica[initial[1][0][0]]))
            print(regras)

    def testWord(self):
        # TODO
        pass