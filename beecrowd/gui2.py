def gale_shapley_tshirt(n, m, preferences):
    # Inicializa a capacidade de cada tamanho
    size_capacity = n // 6
    available = {
        'XXL': size_capacity,
        'XL': size_capacity,
        'L': size_capacity,
        'M': size_capacity,
        'S': size_capacity,
        'XS': size_capacity
    }
    
    # Cada voluntário tenta suas preferências em ordem
    for volunteer_prefs in preferences:
        allocated = False
        for size in volunteer_prefs:
            if available[size] > 0:
                available[size] -= 1
                allocated = True
                break
        if not allocated:
            return "NO"
    return "YES"

# Leitura da entrada e processamento
import sys

input = sys.stdin.read().split()
idx = 0
t = int(input[idx])
idx +=1
for _ in range(t):
    n = int(input[idx])
    m = int(input[idx+1])
    idx +=2
    prefs = []
    for _ in range(m):
        s1 = input[idx]
        s2 = input[idx+1]
        prefs.append((s1, s2))
        idx +=2
    print(gale_shapley_tshirt(n, m, prefs))
