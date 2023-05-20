import json


class Automato:
    def __init__(self, gramatica, naoTerminal):
        self.automato = {}
        self.gramatica = gramatica
        self.naoTerminal = naoTerminal

        self.state_count = 0

        self.regras = []

    def makeRegras(self):
        for i in self.gramatica:
            self.regras.append((i, self.gramatica.get(i)))

    def makeAutomato(self, inicial):
        new_regras = []
        new_regras.append((inicial[0], self.gramatica.get(inicial[0])))
        # Se comeca com um nao terminal, adiciona a regra
        for i in self.gramatica.get(inicial[0]):
            if i[0] in self.naoTerminal:
                new_regras.append((i[0], self.gramatica.get(i[0])))

        # Para cada regra, fazer automato
        temp = {}
        temp_cont = self.state_count
        for i in new_regras:
            # TODO: reducer
            # Se for terminal, faz um shift
            if i[1][0][0] not in self.naoTerminal:
                temp[i[1][0][0]] = f"s{temp_cont + 1}"
                temp_cont += 1
            # Se for nao terminal, faz um goto
            else:
                temp[i[1][0][0]] = f"g{temp_cont + 1}"
                temp_cont += 1
        self.automato[self.state_count] = temp
        print(json.dumps(self.automato, indent=4, ensure_ascii=False))

    def __makeAutomato(self):
        self.automato[1] = {
            "(": "s3",
            "A": "g2"
        }
        self.automato[2] = {
            "$": "a"
        }
        self.automato[3] = {
            "id": "s4",
            "B": "g5"
        }
        self.automato[4] = {
            "(": "r2",
            ")": "r2",
            "id": "r2",
            "$": "r2"
        }
        self.automato[5] = {
            ")": "s6"
        }
        self.automato[6] = {
            "(": "r1",
            ")": "r1",
            "id": "r1",
            "$": "r1"
        }

    def testWord(self, word):
        self.__makeAutomato()
        self.makeRegras()
        pilha = []
        current_state = 1

        for i in word.split():
            a = self.automato.get(current_state).get(i)
            print(f"current_state: {current_state}")
            if a[0] == 's':
                pilha.append(i)
                current_state = int(a[1:])
            elif a[0] == 'g':
                current_state = int(a[1:])
            elif a[0] == 'r':
                r = self.regras[int(a[1:]) - 1]
                pilha.append(i)
                for j in range(len(r[1])):
                    pilha.pop()
                pilha.append(r[0])
                current_state = 1
            elif a[0] == 'a':
                print("Aceito")
            else:
                print("Erro")
                break
        print(f"pilha: {pilha}")
