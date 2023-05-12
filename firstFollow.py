from gramatica import Gramatica

class FirstFollow:
    def __init__(self):
        self.gramatica = Gramatica().getGramatica()
        self.terminal = Gramatica().terminal
        self.naoTerminal = Gramatica().naoTerminal


    def first(self, simbolo):
        """
        :param simbolo:
        :return: first do simbolo passado
        Usa a gramática obtida da classe Gramatica
        """
        resultado = set()

        if simbolo in self.terminal:
            resultado.add(simbolo)
        else:
            for producao in self.gramatica[simbolo]:
                if producao != '':
                    b = producao.split()
                    if b[0] in self.terminal:
                        resultado.add(b[0])
                    else:
                        resultado |= self.first(b[0])

        return resultado

    def follow(self):
        # TODO
        pass
