import time
import csv
import os

def funcao_hash(nomeCidade, tamanhoTabela):
    hash_value = 0
    for c in nomeCidade:
        hash_value = (hash_value + ord(c)) & 0xFFFFFFFF  
    return hash_value % tamanhoTabela

    
def criar_tabela_hash(cidades, tamtabela):
    tabela_hash = [[] for _ in range(tamtabela)]
    colisoes = 0
    
    for cidade in cidades:
        indice = funcao_hash(cidade, tamtabela)
        if tabela_hash[indice]: 
            colisoes += 1
        tabela_hash[indice].append(cidade)
    
    return tabela_hash, colisoes


def calcular_estatisticas(tabela_hash):
    tamanhos_buckets = [len(bucket) for bucket in tabela_hash]
    estatisticas = {i: 0 for i in range(11)}
    
    for tamanho in tamanhos_buckets:
        if tamanho >= 10:
            estatisticas[10] += 1
        else:
            estatisticas[tamanho] += 1
    
    return estatisticas

# Obtém o diretório atual do script
diretorio_atual = os.path.dirname(os.path.abspath(__file__))
# Define o caminho do arquivo CSV no mesmo diretório do código
csv_path = os.path.join(diretorio_atual, 'resultados_hash1.csv')

with open(os.path.join(diretorio_atual, 'cidades.txt'), "r", encoding="utf-8") as arquivo:
    cidades = [linha.strip() for linha in arquivo.readlines()]

# Lista para armazenar os resultados
resultados = []

tamanhos_tabela = [853, 1000, 1500, 2000, 2500]

print("\n### Análise de Tabela Hash (Método da Divisão) ###")
print(f"Total de cidades carregadas: {len(cidades)}\n")
print("| Tabela | Colisões | F.Carga | Tempo (µs) |")
print("|--------|----------|---------|-------------|")

for tamanho_tabela in tamanhos_tabela:
    inicio = time.time()
    tabela_hash, colisoes = criar_tabela_hash(cidades, tamanho_tabela)
    estatisticas = calcular_estatisticas(tabela_hash)
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
    
    # Armazena os resultados para o CSV
    resultado = {
        'Tamanho': tamanho_tabela,
        'Elementos': len(cidades),
        'Colisoes': colisoes,
        'FatorCarga': fator_carga,
        'EnderecoUtilizados': enderecos_utilizados,
        'PorcentagemEnderecos': (enderecos_utilizados/tamanho_tabela) * 100,
        'TempoExecucao': tempo_execucao / 1000  # Converte para milissegundos
    }
    
    # Adiciona dados de distribuição
    for i in range(11):
        resultado[f'Qtd_{i}'] = distribuicao[i]
    
    resultados.append(resultado)

# Salva resultados em CSV
with open(csv_path, 'w', newline='') as csvfile:
    # Define os campos
    fieldnames = ['Tamanho', 'Elementos', 'Colisoes', 'FatorCarga', 'EnderecoUtilizados', 
                 'PorcentagemEnderecos', 'TempoExecucao']
    
    # Adiciona campos para distribuição
    for i in range(11):
        fieldnames.append(f'Qtd_{i}')
    
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
    
    writer.writeheader()
    for resultado in resultados:
        writer.writerow(resultado)

print(f"\nResultados salvos em {csv_path}")
