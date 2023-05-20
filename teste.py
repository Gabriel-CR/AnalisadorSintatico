from firstFollow import FirstFollow


class Teste:
    def __init__(self, gramatica, terminal, naoTerminal):
        self.gramatica = gramatica
        self.terminal = terminal
        self.naoTerminal = naoTerminal

    def testNullable(self):
        ff = FirstFollow(self.gramatica, self.terminal, self.naoTerminal)
        for i in sorted(self.naoTerminal):
            print(f"NULLABLE({i}) = {ff.nullable(i)}")

    def testFirst(self):
        ff = FirstFollow(self.gramatica, self.terminal, self.naoTerminal)
        a = ff.first("S")
        for i in sorted(self.naoTerminal):
            print(f"FIRST({i}) = {a[i]}")
