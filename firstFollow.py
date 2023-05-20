class FirstFollow:
    def __init__(self, gramatica, terminal, naoTerminal):
        self.gramatica = gramatica
        self.terminal = terminal
        self.naoTerminal = naoTerminal

    def first(self, simbolo):
        """
        :param: simbolo
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
                for i in producao.split():
                    if i in self.terminal:
                        if i != "eps":
                            resultado.add(i)
                        else:
                            return self.first(i)
                    else:
                        if self.nullable(i):
                            pass
                        else:
                            resultado = resultado.union(self.first(i))
                            break

        return resultado

    def follow(self, simbolo):
        # TODO
        pass

    def nullable(self, simbolo):
        """
        Calcula se o simbolo é nullable
        :param simbolo: simbolo do alfabeto a ser calculado
        :return: True se o simbolo é nullable, False caso contrário
        """
        if simbolo == "eps":
            return True
        if simbolo in self.terminal:
            return False
        for producao in self.gramatica.get(simbolo):
            flag = True
            for i in producao.split():
                if i != simbolo:
                    if not self.nullable(i):
                        flag = False
                        break
            if flag:
                return True
        return False
