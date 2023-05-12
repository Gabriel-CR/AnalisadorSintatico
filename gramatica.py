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
        Chama a função mekeTNT() para obter os Terminais e NaoTerminais
        """
        # caminho = str(input('Digite caminho do arquivo da gramática: '))
        caminho = str(input(''))
        file = open(caminho, 'r')
        for line in file:
            if self.gramatica.get(line[0]) is None:
                self.gramatica[line[0]] = [line[5:len(line) - 1]]
            else:
                self.gramatica[line[0]].append(line[5:len(line) - 1])
            # print(line[:len(line) - 1])
        self.makeTNT()


    def makeTNT(self):
        """
        Produz os terminais e não terminais com base na gramática dada
        TODO: fazer os terminais
        """
        for prod in self.gramatica:
            # print(prod, self.gramatica[prod])
            self.naoTerminal.add(prod)
            for i in self.gramatica[prod]:
                if i.islower():
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
