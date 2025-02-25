def calculate_min_frequencies(N, lengths):
    """
    Calculate minimum frequencies that could generate given Huffman code lengths.
    """
    # Ordena os comprimentos em ordem decrescente
    lengths.sort(reverse=True)
    
    # Inicializa as frequências
    freqs = [1] * N
    
    # Para cada posição i
    for i in range(N-1):
        # Soma todas as frequências até i+1
        sum_freq = sum(freqs[:i+1])
        
        # Se a próxima frequência é menor que a soma até agora
        # precisamos ajustar para manter a propriedade de Huffman
        if freqs[i+1] < sum_freq:
            freqs[i+1] = sum_freq
    
    return sum(freqs)

def process_input():
    """Process multiple test cases until EOF."""
    try:
        while True:
            # Lê N (número de caracteres diferentes)
            N = int(input())
            
            # Lê os comprimentos dos códigos
            lengths = list(map(int, input().split()))
            
            # Calcula e imprime o resultado
            result = calculate_min_frequencies(N, lengths)
            print(result)
            
    except EOFError:
        return

# Executa a solução
if __name__ == "__main__":
    process_input()