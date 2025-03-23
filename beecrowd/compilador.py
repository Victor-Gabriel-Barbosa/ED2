def pode_compilar(programa):
    vars_origem = set()  # Rastreamento de variáveis únicas usadas como fontes
    vars_atribuidas = set()  # Rastreamento de variáveis que receberam valores
    
    for linha in programa:
        tokens = linha.strip().split()
        var_destino = tokens[0]
        
        # Verifica se a variável está sendo atribuída mais de uma vez
        if var_destino in vars_atribuidas:
            return False
        
        vars_atribuidas.add(var_destino)
        
        if len(tokens) == 3:  # Declaração: A := B
            # Apenas uma atribuição de valor, nenhuma variável fonte usada
            continue
        else:  # Adição: A := B + C
            origem1 = tokens[2]
            origem2 = tokens[4]
            
            # Verifica se as origens são variáveis (não números) e adiciona ao nosso conjunto
            if not origem1.isdigit():
                # Verifica se a variável origem foi definida
                if origem1 not in vars_atribuidas:
                    return False
                vars_origem.add(origem1)
            
            if not origem2.isdigit():
                # Verifica se a variável origem foi definida
                if origem2 not in vars_atribuidas:
                    return False
                vars_origem.add(origem2)
            
            # Verifica se excedemos nosso limite de 2 variáveis de origem
            if len(vars_origem) > 2:
                return False
    
    return True

def principal():
    programa = []
    try:
        while True:
            linha = input()
            if not linha:
                break
            programa.append(linha)
    except EOFError:
        pass
    
    if pode_compilar(programa):
        print("OK")
    else:
        print("Compilation Error")

if __name__ == "__main__":
    principal()