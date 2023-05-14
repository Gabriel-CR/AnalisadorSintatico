class FirstFollow:
    def __init__(self, gramatica, terminal, naoTerminal):
        self.gramatica = gramatica
        self.terminal = terminal
        self.naoTerminal = naoTerminal

    def first(self, simbolo):
        """
        :param simbolo:
        :return: first do simbolo passado
        Usa a gramática obtida da classe Gramatica
        """
        resultado = set()

        if simbolo in self.terminal:
            if simbolo == "eps":
                return {}
            else:
                resultado.add(simbolo)
        else:
            for producao in self.gramatica.get(simbolo):
                if producao != '':
                    b = producao.split()
                    if b[0] in self.terminal:
                        resultado.add(b[0])
                    elif b[0] != simbolo:
                        resultado |= self.first(b[0])

        return resultado

    def follow(self, simbolo):
        # TODO
        pass
