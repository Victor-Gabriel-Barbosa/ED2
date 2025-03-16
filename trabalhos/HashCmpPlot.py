import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

# Configura o estilo dos gráficos
plt.style.use('ggplot')
plt.rcParams.update({'font.size': 12})

def carregar_dados():
    # Caminho para os arquivos CSV
    hash_cpp_enlacamento = "c:/Users/usuario/Desktop/Programas/ED_2/trabalhos/resultados_hash2.csv"
    hash_cpp_divisao = "c:/Users/usuario/Desktop/Programas/ED_2/trabalhos/resultados_hash1.csv"
    hash_python_enlacamento = "c:/Users/usuario/Desktop/Programas/ED_2/HashHanny/resultados_hash2.csv"
    hash_python_divisao = "c:/Users/usuario/Desktop/Programas/ED_2/HashHanny/resultados_hash1.csv"
    
    # Verifica se os arquivos existem
    arquivos = [hash_cpp_enlacamento, hash_cpp_divisao, hash_python_enlacamento, hash_python_divisao]
    for arquivo in arquivos:
        if not os.path.exists(arquivo):
            print(f"ERRO: Arquivo {arquivo} não encontrado!")
            return None, None, None, None
    
    # Carrega dados
    df_cpp_enlacamento = pd.read_csv(hash_cpp_enlacamento)
    df_cpp_divisao = pd.read_csv(hash_cpp_divisao)
    df_python_enlacamento = pd.read_csv(hash_python_enlacamento)
    df_python_divisao = pd.read_csv(hash_python_divisao)
    
    print("Dados carregados com sucesso!")
    return df_cpp_enlacamento, df_cpp_divisao, df_python_enlacamento, df_python_divisao

def criar_pasta_saida():
    pasta_saida = "c:/Users/usuario/Desktop/Programas/ED_2/trabalhos/graficos_cpp_vs_python"
    if not os.path.exists(pasta_saida):
        os.makedirs(pasta_saida)
    return pasta_saida

def comparar_colisoes(df_cpp_enlacamento, df_cpp_divisao, df_python_enlacamento, df_python_divisao, pasta_saida):
    plt.figure(figsize=(12, 8))
    
    x = df_cpp_enlacamento['Tamanho']
    plt.plot(x, df_cpp_enlacamento['Colisoes'], 'o-', linewidth=2, markersize=8, label='C++ (Enlaçamento)')
    plt.plot(x, df_cpp_divisao['Colisoes'], 'o--', linewidth=2, markersize=8, label='C++ (Divisão)')
    plt.plot(x, df_python_enlacamento['Colisoes'], 's-', linewidth=2, markersize=8, label='Python (Enlaçamento)')
    plt.plot(x, df_python_divisao['Colisoes'], '^-', linewidth=2, markersize=8, label='Python (Divisão)')
    
    plt.title('Comparação de Colisões por Tamanho da Tabela')
    plt.xlabel('Tamanho da Tabela')
    plt.ylabel('Número de Colisões')
    plt.grid(True)
    plt.legend()
    
    # Exibe valores nos pontos
    for i, (x_val, y_cpp_en, y_cpp_div, y_py_en, y_py_div) in enumerate(zip(
            x, df_cpp_enlacamento['Colisoes'], df_cpp_divisao['Colisoes'], 
            df_python_enlacamento['Colisoes'], df_python_divisao['Colisoes'])):
        plt.annotate(f'{y_cpp_en}', (x_val, y_cpp_en), textcoords="offset points", xytext=(0,10), ha='center')
        plt.annotate(f'{y_cpp_div}', (x_val, y_cpp_div), textcoords="offset points", xytext=(0,10), ha='center')
        plt.annotate(f'{y_py_en}', (x_val, y_py_en), textcoords="offset points", xytext=(0,10), ha='center')
        plt.annotate(f'{y_py_div}', (x_val, y_py_div), textcoords="offset points", xytext=(0,10), ha='center')
    
    plt.tight_layout()
    plt.savefig(f"{pasta_saida}/comparacao_colisoes.png", dpi=300)
    print(f"Gráfico de colisões salvo em {pasta_saida}/comparacao_colisoes.png")

def comparar_tempo_execucao(df_cpp_enlacamento, df_cpp_divisao, df_python_enlacamento, df_python_divisao, pasta_saida):
    plt.figure(figsize=(12, 8))
    
    x = df_cpp_enlacamento['Tamanho']
    plt.plot(x, df_cpp_enlacamento['TempoExecucao'], 'o-', linewidth=2, markersize=8, label='C++ (Enlaçamento)')
    plt.plot(x, df_cpp_divisao['TempoExecucao'], 'o--', linewidth=2, markersize=8, label='C++ (Divisão)')
    plt.plot(x, df_python_enlacamento['TempoExecucao'], 's-', linewidth=2, markersize=8, label='Python (Enlaçamento)')
    plt.plot(x, df_python_divisao['TempoExecucao'], '^-', linewidth=2, markersize=8, label='Python (Divisão)')
    
    plt.title('Comparação de Tempo de Execução por Tamanho da Tabela')
    plt.xlabel('Tamanho da Tabela')
    plt.ylabel('Tempo de Execução (ms)')
    plt.grid(True)
    plt.legend()
    
    # Exibe valores nos pontos
    for i, (x_val, y_cpp_en, y_cpp_div, y_py_en, y_py_div) in enumerate(zip(
            x, df_cpp_enlacamento['TempoExecucao'], df_cpp_divisao['TempoExecucao'], 
            df_python_enlacamento['TempoExecucao'], df_python_divisao['TempoExecucao'])):
        plt.annotate(f'{y_cpp_en:.2f}', (x_val, y_cpp_en), textcoords="offset points", xytext=(0,10), ha='center')
        plt.annotate(f'{y_cpp_div:.2f}', (x_val, y_cpp_div), textcoords="offset points", xytext=(0,10), ha='center')
        plt.annotate(f'{y_py_en:.2f}', (x_val, y_py_en), textcoords="offset points", xytext=(0,10), ha='center')
        plt.annotate(f'{y_py_div:.2f}', (x_val, y_py_div), textcoords="offset points", xytext=(0,10), ha='center')
    
    plt.tight_layout()
    plt.savefig(f"{pasta_saida}/comparacao_tempo_execucao.png", dpi=300)
    print(f"Gráfico de tempo de execução salvo em {pasta_saida}/comparacao_tempo_execucao.png")

def comparar_fator_carga(df_cpp_enlacamento, df_cpp_divisao, df_python_enlacamento, df_python_divisao, pasta_saida):
    plt.figure(figsize=(12, 8))
    
    x = df_cpp_enlacamento['Tamanho']
    plt.plot(x, df_cpp_enlacamento['FatorCarga'], 'o-', linewidth=2, markersize=8, label='C++ (Enlaçamento)')
    plt.plot(x, df_cpp_divisao['FatorCarga'], 'o--', linewidth=2, markersize=8, label='C++ (Divisão)')
    plt.plot(x, df_python_enlacamento['FatorCarga'], 's-', linewidth=2, markersize=8, label='Python (Enlaçamento)')
    plt.plot(x, df_python_divisao['FatorCarga'], '^-', linewidth=2, markersize=8, label='Python (Divisão)')
    
    plt.title('Comparação de Fator de Carga por Tamanho da Tabela')
    plt.xlabel('Tamanho da Tabela')
    plt.ylabel('Fator de Carga')
    plt.grid(True)
    plt.legend()
    
    # Exibe valores nos pontos
    for i, (x_val, y_cpp_en, y_cpp_div, y_py_en, y_py_div) in enumerate(zip(
            x, df_cpp_enlacamento['FatorCarga'], df_cpp_divisao['FatorCarga'],
            df_python_enlacamento['FatorCarga'], df_python_divisao['FatorCarga'])):
        plt.annotate(f'{y_cpp_en:.2f}', (x_val, y_cpp_en), textcoords="offset points", xytext=(0,10), ha='center')
        plt.annotate(f'{y_cpp_div:.2f}', (x_val, y_cpp_div), textcoords="offset points", xytext=(0,10), ha='center')
        plt.annotate(f'{y_py_en:.2f}', (x_val, y_py_en), textcoords="offset points", xytext=(0,10), ha='center')
        plt.annotate(f'{y_py_div:.2f}', (x_val, y_py_div), textcoords="offset points", xytext=(0,10), ha='center')
    
    plt.tight_layout()
    plt.savefig(f"{pasta_saida}/comparacao_fator_carga.png", dpi=300)
    print(f"Gráfico de fator de carga salvo em {pasta_saida}/comparacao_fator_carga.png")

def comparar_distribuicao(df_cpp_enlacamento, df_cpp_divisao, df_python_enlacamento, df_python_divisao, pasta_saida):
    # Seleciona a tabela de tamanho 2000 para comparação de distribuição
    df_cpp_en_2000 = df_cpp_enlacamento[df_cpp_enlacamento['Tamanho'] == 2000].iloc[0]
    df_cpp_div_2000 = df_cpp_divisao[df_cpp_divisao['Tamanho'] == 2000].iloc[0]
    df_py_en_2000 = df_python_enlacamento[df_python_enlacamento['Tamanho'] == 2000].iloc[0]
    df_py_div_2000 = df_python_divisao[df_python_divisao['Tamanho'] == 2000].iloc[0]
    
    # Obtém contagens por quantidade de elementos
    categories = [str(i) for i in range(10)] + ['10+']
    qtds_cpp_en = [df_cpp_en_2000[f'Qtd_{i}'] for i in range(10)] + [df_cpp_en_2000['Qtd_10']]
    qtds_cpp_div = [df_cpp_div_2000[f'Qtd_{i}'] for i in range(10)] + [df_cpp_div_2000['Qtd_10']]
    qtds_py_en = [df_py_en_2000[f'Qtd_{i}'] for i in range(10)] + [df_py_en_2000['Qtd_10']]
    qtds_py_div = [df_py_div_2000[f'Qtd_{i}'] for i in range(10)] + [df_py_div_2000['Qtd_10']]
    
    # Configura largura das barras e posições
    bar_width = 0.2
    r1 = np.arange(len(categories))
    r2 = [x + bar_width for x in r1]
    r3 = [x + bar_width for x in r2]
    r4 = [x + bar_width for x in r3]
    
    # Cria gráfico de barras
    plt.figure(figsize=(16, 10))
    plt.bar(r1, qtds_cpp_en, width=bar_width, label='C++ (Enlaçamento)', color='skyblue', edgecolor='black')
    plt.bar(r2, qtds_cpp_div, width=bar_width, label='C++ (Divisão)', color='royalblue', edgecolor='black')
    plt.bar(r3, qtds_py_en, width=bar_width, label='Python (Enlaçamento)', color='lightgreen', edgecolor='black')
    plt.bar(r4, qtds_py_div, width=bar_width, label='Python (Divisão)', color='salmon', edgecolor='black')
    
    # Adiciona rótulos e legendas
    plt.xlabel('Quantidade de Elementos por Posição')
    plt.ylabel('Número de Posições na Tabela')
    plt.title('Distribuição de Elementos na Tabela Hash (Tamanho 2000)')
    plt.xticks([r + bar_width * 1.5 for r in range(len(categories))], categories)
    plt.legend()
    
    # Salva gráfico
    plt.tight_layout()
    plt.savefig(f"{pasta_saida}/comparacao_distribuicao.png", dpi=300)
    print(f"Gráfico de distribuição salvo em {pasta_saida}/comparacao_distribuicao.png")
    
    # Gráfico de barras empilhadas para distribuição percentual
    plt.figure(figsize=(16, 10))
    
    # Calcula percentuais
    total_cpp_en = sum(qtds_cpp_en)
    total_cpp_div = sum(qtds_cpp_div)
    total_py_en = sum(qtds_py_en)
    total_py_div = sum(qtds_py_div)
    
    perc_cpp_en = [100 * q / total_cpp_en for q in qtds_cpp_en]
    perc_cpp_div = [100 * q / total_cpp_div for q in qtds_cpp_div]
    perc_py_en = [100 * q / total_py_en for q in qtds_py_en]
    perc_py_div = [100 * q / total_py_div for q in qtds_py_div]
    
    # Configura gráfico de barras
    width = 0.2
    x = np.arange(len(categories))
    
    fig, ax = plt.subplots(figsize=(16, 10))
    rects1 = ax.bar(x - width*1.5, perc_cpp_en, width, label='C++ (Enlaçamento)')
    rects2 = ax.bar(x - width/2, perc_cpp_div, width, label='C++ (Divisão)')
    rects3 = ax.bar(x + width/2, perc_py_en, width, label='Python (Enlaçamento)')
    rects4 = ax.bar(x + width*1.5, perc_py_div, width, label='Python (Divisão)')
    
    # Adiciona valores nas barras
    def autolabel(rects):
        for rect in rects:
            height = rect.get_height()
            ax.annotate(f'{height:.1f}%',
                        xy=(rect.get_x() + rect.get_width() / 2, height),
                        xytext=(0, 3),  # 3 points vertical offset
                        textcoords="offset points",
                        ha='center', va='bottom')
    
    autolabel(rects1)
    autolabel(rects2)
    autolabel(rects3)
    autolabel(rects4)
    
    ax.set_ylabel('Porcentagem (%)')
    ax.set_xlabel('Quantidade de Elementos por Posição')
    ax.set_title('Distribuição Percentual por Posição na Tabela Hash (Tamanho 2000)')
    ax.set_xticks(x)
    ax.set_xticklabels(categories)
    ax.legend()
    
    fig.tight_layout()
    plt.savefig(f"{pasta_saida}/comparacao_distribuicao_percentual.png", dpi=300)
    print(f"Gráfico de distribuição percentual salvo em {pasta_saida}/comparacao_distribuicao_percentual.png")

def gerar_grafico_desempenho(df_cpp_enlacamento, df_cpp_divisao, df_python_enlacamento, df_python_divisao, pasta_saida):
    """Gera um gráfico de radar comparando os quatro métodos em várias métricas"""
    
    # Seleciona dados para o tamanho 2000
    df_cpp_en_2000 = df_cpp_enlacamento[df_cpp_enlacamento['Tamanho'] == 2000].iloc[0]
    df_cpp_div_2000 = df_cpp_divisao[df_cpp_divisao['Tamanho'] == 2000].iloc[0]
    df_py_en_2000 = df_python_enlacamento[df_python_enlacamento['Tamanho'] == 2000].iloc[0]
    df_py_div_2000 = df_python_divisao[df_python_divisao['Tamanho'] == 2000].iloc[0]
    
    # Normaliza os dados para o radar plot
    # Quanto menor as colisões, melhor (inverter)
    col_max = max(df_cpp_en_2000['Colisoes'], df_cpp_div_2000['Colisoes'], 
                 df_py_en_2000['Colisoes'], df_py_div_2000['Colisoes'])
    col_cpp_en_norm = 1 - (df_cpp_en_2000['Colisoes'] / col_max)
    col_cpp_div_norm = 1 - (df_cpp_div_2000['Colisoes'] / col_max)
    col_py_en_norm = 1 - (df_py_en_2000['Colisoes'] / col_max)
    col_py_div_norm = 1 - (df_py_div_2000['Colisoes'] / col_max)
    
    # Quanto menor o tempo, melhor (inverter)
    time_max = max(df_cpp_en_2000['TempoExecucao'], df_cpp_div_2000['TempoExecucao'],
                  df_py_en_2000['TempoExecucao'], df_py_div_2000['TempoExecucao'])
    time_cpp_en_norm = 1 - (df_cpp_en_2000['TempoExecucao'] / time_max)
    time_cpp_div_norm = 1 - (df_cpp_div_2000['TempoExecucao'] / time_max)
    time_py_en_norm = 1 - (df_py_en_2000['TempoExecucao'] / time_max)
    time_py_div_norm = 1 - (df_py_div_2000['TempoExecucao'] / time_max)
    
    # Quanto maior a porcentagem de endereços utilizados, melhor
    end_cpp_en_norm = df_cpp_en_2000['PorcentagemEnderecos'] / 100
    end_cpp_div_norm = df_cpp_div_2000['PorcentagemEnderecos'] / 100
    end_py_en_norm = df_py_en_2000['PorcentagemEnderecos'] / 100
    end_py_div_norm = df_py_div_2000['PorcentagemEnderecos'] / 100
    
    # Quanto melhor distribuído, menor a quantidade em Qtd_0 (posições vazias)
    dist_cpp_en_norm = 1 - (df_cpp_en_2000['Qtd_0'] / 2000)
    dist_cpp_div_norm = 1 - (df_cpp_div_2000['Qtd_0'] / 2000)
    dist_py_en_norm = 1 - (df_py_en_2000['Qtd_0'] / 2000)
    dist_py_div_norm = 1 - (df_py_div_2000['Qtd_0'] / 2000)
    
    # Dados para o gráfico radar
    categories = ['Menos Colisões', 'Velocidade', 'Uso de Endereços', 'Distribuição']
    
    values_cpp_en = [col_cpp_en_norm, time_cpp_en_norm, end_cpp_en_norm, dist_cpp_en_norm]
    values_cpp_div = [col_cpp_div_norm, time_cpp_div_norm, end_cpp_div_norm, dist_cpp_div_norm]
    values_py_en = [col_py_en_norm, time_py_en_norm, end_py_en_norm, dist_py_en_norm]
    values_py_div = [col_py_div_norm, time_py_div_norm, end_py_div_norm, dist_py_div_norm]
    
    # Número de variáveis
    N = len(categories)
    
    # Ângulos para cada eixo (divididos igualmente)
    angles = [n / float(N) * 2 * np.pi for n in range(N)]
    angles += angles[:1]  # Fechar o gráfico
    
    # Valores para cada método (fechar o gráfico)
    values_cpp_en += values_cpp_en[:1]
    values_cpp_div += values_cpp_div[:1]
    values_py_en += values_py_en[:1]
    values_py_div += values_py_div[:1]
    
    # Inicializa o gráfico
    fig, ax = plt.subplots(figsize=(12, 10), subplot_kw=dict(polar=True))
    
    # Plotar cada método
    ax.plot(angles, values_cpp_en, 'o-', linewidth=2, label='C++ (Enlaçamento)')
    ax.fill(angles, values_cpp_en, alpha=0.1)
    
    ax.plot(angles, values_cpp_div, 'o--', linewidth=2, label='C++ (Divisão)')
    ax.fill(angles, values_cpp_div, alpha=0.1)
    
    ax.plot(angles, values_py_en, 's-', linewidth=2, label='Python (Enlaçamento)')
    ax.fill(angles, values_py_en, alpha=0.1)
    
    ax.plot(angles, values_py_div, '^-', linewidth=2, label='Python (Divisão)')
    ax.fill(angles, values_py_div, alpha=0.1)
    
    # Adiciona rótulos
    ax.set_thetagrids(np.degrees(angles[:-1]), categories)
    
    # Adiciona título e legenda
    ax.set_title('Comparação de Desempenho entre Métodos de Hash (Tabela 2000)')
    ax.legend(loc='upper right', bbox_to_anchor=(0.1, 0.1))
    
    # Ajusta limites do eixo y
    ax.set_ylim(0, 1)
    
    # Salvar gráfico
    plt.tight_layout()
    plt.savefig(f"{pasta_saida}/comparacao_radar.png", dpi=300)
    print(f"Gráfico radar salvo em {pasta_saida}/comparacao_radar.png")

def main():
    print("=== Comparação de Métodos Hash (C++ vs Python) ===")
    
    # Carrega dados dos arquivos CSV
    df_cpp_enlacamento, df_cpp_divisao, df_python_enlacamento, df_python_divisao = carregar_dados()
    if df_cpp_enlacamento is None:
        return
    
    # Cria pasta para salvar gráficos
    pasta_saida = criar_pasta_saida()
    
    # Gera gráficos comparativos
    comparar_colisoes(df_cpp_enlacamento, df_cpp_divisao, df_python_enlacamento, df_python_divisao, pasta_saida)
    comparar_tempo_execucao(df_cpp_enlacamento, df_cpp_divisao, df_python_enlacamento, df_python_divisao, pasta_saida)
    comparar_fator_carga(df_cpp_enlacamento, df_cpp_divisao, df_python_enlacamento, df_python_divisao, pasta_saida)
    comparar_distribuicao(df_cpp_enlacamento, df_cpp_divisao, df_python_enlacamento, df_python_divisao, pasta_saida)
    gerar_grafico_desempenho(df_cpp_enlacamento, df_cpp_divisao, df_python_enlacamento, df_python_divisao, pasta_saida)
    
    print("\nAnálise concluída! Todos os gráficos foram salvos na pasta de saída.")
    print(f"Caminho: {pasta_saida}")

if __name__ == "__main__":
    main()
