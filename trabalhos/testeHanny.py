import time


def funcao_hash(nomecidade, tamtabela):
    return sum(nomecidade.encode("utf-8")) % tamtabela


def criar_tabela_hash(cidades, tamtabela, limite):
    tabela_hash = [[] for _ in range(tamtabela)]
    area_transbordo = []
    colisoes = 0
    
    for cidade in cidades:
        indice = funcao_hash(cidade, tamtabela)
        if len(tabela_hash[indice]) < limite:
            tabela_hash[indice].append(cidade)
        else:
            area_transbordo.append(cidade)
            colisoes += 1
    
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


with open("cidades.txt", "r", encoding="utf-8") as arquivo:
    cidades = [linha.strip() for linha in arquivo.readlines()]


tamanhos_tabela = [853, 1000, 1500, 2000, 2500]
limite_enlacamento = 3

print("\n### Análise de Tabela Hash de Cidades ###")
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