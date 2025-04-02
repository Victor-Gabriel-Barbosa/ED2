def verificar_compilacao(programa):
    # Dicionário para rastrear as variáveis que foram atribuídas
    variaveis_atribuidas = {}
    # Conjunto para rastrear as variáveis usadas como fonte
    variaveis_fonte = set()
    
    for linha in programa:
        # Pula linhas vazias
        if not linha.strip():
            continue
            
        tokens = linha.strip().split()
        
        # Verifica se a variável já foi atribuída anteriormente
        var_destino = tokens[0]
        if var_destino in variaveis_atribuidas:
            return "Compilation Error"  # Variável só pode ser atribuída uma vez
        variaveis_atribuidas[var_destino] = True
        
        if len(tokens) == 3:  # Instrução de atribuição: A := B
            if not tokens[2].isdigit():  # Se B não for um número, deve ser uma variável
                if tokens[2] not in variaveis_atribuidas:
                    return "Compilation Error"  # Uso de variável não inicializada
                variaveis_fonte.add(tokens[2])  # Adiciona à lista de variáveis fonte
                
        elif len(tokens) == 5:  # Instrução de soma: A := B + C
            # Verifica se B é uma variável e está inicializada
            if not tokens[2].isdigit():
                if tokens[2] not in variaveis_atribuidas:
                    return "Compilation Error"  # Uso de variável não inicializada
                variaveis_fonte.add(tokens[2])  # Adiciona à lista de variáveis fonte
                
            # Verifica se C é uma variável e está inicializada
            if not tokens[4].isdigit():
                if tokens[4] not in variaveis_atribuidas:
                    return "Compilation Error"  # Uso de variável não inicializada
                variaveis_fonte.add(tokens[4])  # Adiciona à lista de variáveis fonte
        
        # Verifica se o número de variáveis fonte excede 2
        if len(variaveis_fonte) > 2:
            return "Compilation Error"
            
    return "OK"

# Função principal
def principal():
    programa = []
    try:
        while True:
            linha = input()
            programa.append(linha)
    except EOFError:
        pass
    
    print(verificar_compilacao(programa))

if __name__ == "__main__":
    principal()