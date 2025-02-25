# Lista
lista = [1, 2, 3]
lista.append(4)
lista.remove(2)

# Fila 
from queue import Queue
fila = Queue()
fila.put(1)
fila.put(2)
primeiro = fila.get()

# Pilha
from collections import deque
pilha = deque()
pilha.append(1)
pilha.append(2)
topo = pilha.pop()

# Árvore
class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

print("Teste")
print("Parado")