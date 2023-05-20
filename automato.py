import json


class Automato:
    def __init__(self, gramatica, naoTerminal):
        self.automato = {}
        self.gramatica = gramatica
        self.naoTerminal = naoTerminal

        self.state_count = 0

    def makeAutomato(self, inicial):
        regras = []
        regras.append(self.gramatica.get(inicial))
        # Se comeca com um nao terminal, adiciona a regra
        for i in self.gramatica.get(inicial):
            if i[0] in self.naoTerminal:
                regras.append(self.gramatica.get(i[0]))

        # Para cada regra, fazer automato
        temp = {}
        temp_cont = self.state_count
        for i in regras:
            if i[0][0] not in self.naoTerminal:    # Se for terminal, faz um shift
                temp[i[0][0]] = f"s{temp_cont + 1}"
                temp_cont += 1
            else:   # Se for nao terminal, faz um goto
                temp[i[0][0]] = f"g{temp_cont + 1}"
                temp_cont += 1
            # self.makeAutomato(i[:1])
        self.automato[self.state_count] = temp
        print(json.dumps(self.automato, indent=4, ensure_ascii=False))

    def testWord(self):
        # TODO
        pass