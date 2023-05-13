class Gramatica:
    def __init__(self):
        self.gramatica = {}
        self.naoTerminal = set()
        self.terminal = set()

    def readGramatica(self):
        """
        Ler a gramática via terminal
        Armazena a grámatica no atributo gramática da classe
        Chama a função mekeTNT() para obter os Terminais e NaoTerminais
        """
        qtdRegras = int(input('Digite a quantidade de regras da gramática: '))
        print("A gramática deve seguir o formato: A -> a B c")
        print("Digite a sua gramática: ")
        while qtdRegras > 0:
            line = str(input())
            if self.gramatica.get(line[0]) is None:
                self.gramatica[line[0]] = [line[5:]]
            else:
                self.gramatica[line[0]].append(line[5:])
            qtdRegras -= 1

        self.makeTNT()

    def readGramaticaFile(self):
        """
        Ler a gramática de um arquivo .txt
        O arquivo tem que ter a sua última linha em branco
        Armazena a grámatica no atributo gramática da classe
        Chama as funções makeNaoTerminal() e makeTerminal()
        para obter os Terminais e NaoTerminais
        """
        # caminho = str(input('Digite caminho do arquivo da gramática: '))
        caminho = "./gramatica.txt"
        file = open(caminho, 'r')
        for line in file:
            if self.gramatica.get(line[0]) is None:
                self.gramatica[line[0]] = [line[5:len(line) - 1]]
            else:
                self.gramatica[line[0]].append(line[5:len(line) - 1])

        self.makeNaoTerminal()
        self.makeTerminal()

    def makeNaoTerminal(self):
        """
        Obtem os não terminais da gramática
        Usa as keys de gramatica como nao terminal
        """
        for regra in self.gramatica:
            self.naoTerminal.add(regra)

    def makeTerminal(self):
        """
        Obtem os terminais da gramática
        Usa os não terminais como referencia
            -> aquilo que não é não terminal, é terminal
        """
        for regra in self.gramatica.values():
            for r in regra:
                for i in r.split():
                    if i not in self.naoTerminal:
                        self.terminal.add(i)

    def getGramatica(self):
        return self.gramatica

    def isTerminal(self, symbol):
        return symbol in self.terminal

    def isNaoTerminal(self, symbol):
        return symbol in self.naoTerminal

    def __str__(self):
        """
        :return: Gramática com o formato P -> a b c
        """
        res = str()
        for i in self.gramatica:
            res += f"{i} -> {self.gramatica[i]}\n"
        return res
