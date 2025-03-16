import time
import csv
import os


def funcao_hash(nomecidade, tamtabela):
    GRUPO_TAMANHO = 3  
    grupos = []
  
    for i in range(0, len(nomecidade), GRUPO_TAMANHO):
        valor = 0
        fim = min(i + GRUPO_TAMANHO, len(nomecidade))
        
     
        for j in range(i, fim):
            valor = valor * 10 + (ord(nomecidade[j]) % 10)
        
        grupos.append(valor)
    
   
    for i in range(1, len(grupos) - 1):
        original = grupos[i]
        invertido = 0
        while original > 0:
            invertido = invertido * 10 + original % 10
            original //= 10
        grupos[i] = invertido
    
   
    return sum(grupos) % tamtabela


def criar_tabela_hash(cidades, tamtabela, limite):
    tabela_hash = [[] for _ in range(tamtabela)]
    area_transbordo = []
    colisoes = 0
    
    for cidade in cidades:
        indice = funcao_hash(cidade, tamtabela)
        if len(tabela_hash[indice]) >= limite: 
            colisoes += 1
            area_transbordo.append(cidade)
        else:
            if tabela_hash[indice]:  
                colisoes += 1
            tabela_hash[indice].append(cidade)
    
    return tabela_hash, area_transbordo, colisoes


def calcular_estatisticas(tabela_hash, area_transbordo):
    tamanhos_buckets = [len(bucket) for bucket in tabela_hash]
    estatisticas = {i: 0 for i in range(11)}
    
    for tamanho in tamanhos_buckets:
        if tamanho >= 10:
            estatisticas[10] += 1
        else:
            estatisticas[tamanho] += 1
    
    estatisticas['transbordo'] = len(area_transbordo)
    return estatisticas

# Obtém o diretório atual do script
diretorio_atual = os.path.dirname(os.path.abspath(__file__))
# Define o caminho do arquivo CSV no mesmo diretório do código
csv_path = os.path.join(diretorio_atual, 'resultados_hash2.csv')

with open(os.path.join(diretorio_atual, 'cidades.txt'), "r", encoding="utf-8") as arquivo:
    cidades = [linha.strip() for linha in arquivo.readlines()]

# Lista para armazenar os resultados
resultados = []

tamanhos_tabela = [853, 1000, 1500, 2000, 2500]
limite_enlacamento = 3

print("\n### Análise de Tabela Hash de Cidades (Enlaçamento Limite) ###")
print(f"Total de cidades carregadas: {len(cidades)}\n")
print("| Tabela | Colisões | F.Carga | Tempo (µs) |")
print("|--------|----------|---------|-------------|")

for tamanho_tabela in tamanhos_tabela:
    inicio = time.time()
    tabela_hash, area_transbordo, colisoes = criar_tabela_hash(cidades, tamanho_tabela, limite_enlacamento)
    estatisticas = calcular_estatisticas(tabela_hash, area_transbordo)
    tempo_execucao = (time.time() - inicio) * 1e6  
    
   
    enderecos_utilizados = sum(1 for bucket in tabela_hash if bucket) 
    fator_carga = len(cidades) / tamanho_tabela
    
    print(f"| {tamanho_tabela} | {colisoes} | {fator_carga:.4f} | {int(tempo_execucao)} µs |")
    
    print(f"\n### Estatísticas da Tabela ({tamanho_tabela}) ###")
    print(f"- Tamanho da tabela: {tamanho_tabela}")
    print(f"- Total de elementos: {len(cidades)}")
    print(f"- Fator de carga: {fator_carga:.4f}")
    print(f"- Total de colisões: {colisoes}")
    print(f"- Endereços utilizados: {enderecos_utilizados} ({(enderecos_utilizados/tamanho_tabela) * 100:.4f}%)\n")
    
    print("### Distribuição de Cidades por Posição ###")
    print("| Quant. | Endereços | % | Acumulado % |")
    print("|--------|-----------|--------|-------------|")
    
    distribuicao = {i: estatisticas.get(i, 0) for i in range(11)}
    acumulado = 0
    for i in range(11):
        perc = (distribuicao[i] / tamanho_tabela) * 100
        acumulado += perc
        print(f"| {i if i < 10 else '10+'} | {distribuicao[i]} | {perc:.2f}% | {acumulado:.2f}% |")
    
    print(f"| Área de Transbordo | {estatisticas['transbordo']} | - | - |\n")
    
    # Armazena os resultados para o CSV
    resultado = {
        'Tamanho': tamanho_tabela,
        'Elementos': len(cidades),
        'Colisoes': colisoes,
        'FatorCarga': fator_carga,
        'EnderecoUtilizados': enderecos_utilizados,
        'PorcentagemEnderecos': (enderecos_utilizados/tamanho_tabela) * 100,
        'TempoExecucao': tempo_execucao / 1000,  # Converter para milissegundos
        'AreaTransbordo': estatisticas['transbordo']
    }
    
    # Adiciona dados de distribuição
    for i in range(11):
        resultado[f'Qtd_{i}'] = distribuicao[i]
    
    resultados.append(resultado)

# Salva resultados em CSV
with open(csv_path, 'w', newline='') as csvfile:
    # Define os campos
    fieldnames = ['Tamanho', 'Elementos', 'Colisoes', 'FatorCarga', 'EnderecoUtilizados', 
                 'PorcentagemEnderecos', 'TempoExecucao', 'AreaTransbordo']
    
    # Adiciona campos para distribuição
    for i in range(11):
        fieldnames.append(f'Qtd_{i}')
    
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
    
    writer.writeheader()
    for resultado in resultados:
        writer.writerow(resultado)

print(f"\nResultados salvos em {csv_path}")
