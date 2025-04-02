def solve_shirt_distribution():
    t = int(input())  # Número de casos de teste
    
    results = []
    for _ in range(t):
        n, m = map(int, input().split())  # n: total de camisetas, m: número de voluntários
        
        # Calculando o número de camisetas por tamanho
        shirts_per_size = n // 6
        
        # Cada voluntário tem dois tamanhos que servem
        volunteer_preferences = []
        for i in range(m):
            sizes = input().split()
            volunteer_preferences.append(sizes)
        
        # Verificar se há solução usando Gale-Shapley adaptado
        if has_valid_distribution(volunteer_preferences, shirts_per_size):
            results.append("YES")
        else:
            results.append("NO")
    
    # Imprimir resultados
    for result in results:
        print(result)

def has_valid_distribution(volunteer_preferences, shirts_per_size):
    """
    Implementação adaptada do algoritmo de Gale-Shapley para o problema.
    """
    # Número de voluntários
    m = len(volunteer_preferences)
    
    # Inicialização das estruturas de dados
    shirt_sizes = ["XXL", "XL", "L", "M", "S", "XS"]
    available_shirts = {size: shirts_per_size for size in shirt_sizes}
    assigned_volunteers = set()
    
    # Lista de voluntários não atribuídos inicialmente (todos)
    unassigned_volunteers = list(range(m))
    
    # Enquanto houver voluntários sem camisetas
    while unassigned_volunteers:
        volunteer = unassigned_volunteers[0]
        
        # Verificar os dois tamanhos que servem para este voluntário
        size1, size2 = volunteer_preferences[volunteer]
        
        # Tentar atribuir o primeiro tamanho
        if available_shirts[size1] > 0:
            available_shirts[size1] -= 1
            assigned_volunteers.add(volunteer)
            unassigned_volunteers.pop(0)
        
        # Se não for possível, tentar o segundo tamanho
        elif available_shirts[size2] > 0:
            available_shirts[size2] -= 1
            assigned_volunteers.add(volunteer)
            unassigned_volunteers.pop(0)
        
        # Se ambos os tamanhos estiverem indisponíveis, tentar outro voluntário
        else:
            # Mover este voluntário para o final da fila
            unassigned_volunteers.pop(0)
            unassigned_volunteers.append(volunteer)
            
            # Se já tentamos todas as combinações possíveis e voltamos ao início
            if len(unassigned_volunteers) == 1 or volunteer == unassigned_volunteers[0]:
                return False
    
    # Se todos os voluntários foram atribuídos, temos uma solução
    return len(assigned_volunteers) == m

# Executar a solução
if __name__ == "__main__":
    solve_shirt_distribution()