import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

# Configurações para melhorar a apresentação dos gráficos
plt.style.use('ggplot')
plt.rcParams['figure.figsize'] = (12, 7)
plt.rcParams['font.size'] = 12

# Obtém o diretório atual do script
diretorio_atual = os.path.dirname(os.path.abspath(__file__))

# Caminho para os arquivos CSV e pasta de saída
csv_path_div = os.path.join(diretorio_atual, 'resultados_hash1.csv')
csv_path_el = os.path.join(diretorio_atual, 'resultados_hash2.csv')
output_dir = os.path.join(diretorio_atual, 'graficos_comparativos')

if not os.path.exists(output_dir):
    os.makedirs(output_dir)

# Função para salvar figuras
def salvar_figura(fig, nome):
    caminho_completo = os.path.join(output_dir, nome)
    fig.savefig(caminho_completo, bbox_inches='tight', dpi=300)
    print(f"Gráfico salvo em: {caminho_completo}")

# Carregando os dados dos CSVs
try:
    df_div = pd.read_csv(csv_path_div)
    df_el = pd.read_csv(csv_path_el)
    print("Dados do método da divisão:")
    print(df_div.head())
    print("\nDados do método de enlaçamento limite:")
    print(df_el.head())
except Exception as e:
    print(f"Erro ao carregar os arquivos CSV: {e}")
    exit(1)

# ======== Gráfico 1: Comparação de Colisões por Tamanho da Tabela ========
fig1, ax1 = plt.subplots()
ax1.plot(df_div['Tamanho'], df_div['Colisoes'], marker='o', linewidth=2, markersize=8,
         label='Método da Divisão', color='blue')
ax1.plot(df_el['Tamanho'], df_el['Colisoes'], marker='s', linewidth=2, markersize=8,
         label='Método do Enlaçamento', color='red')
ax1.set_xlabel('Tamanho da Tabela')
ax1.set_ylabel('Número de Colisões')
ax1.set_title('Comparação de Colisões entre Métodos de Tabela Hash')
ax1.legend()
ax1.grid(True)

# Adiciona valores acima dos pontos
for x, y in zip(df_div['Tamanho'], df_div['Colisoes']):
    ax1.annotate(str(y), xy=(x, y), xytext=(0, 5), textcoords='offset points', ha='center')

for x, y in zip(df_el['Tamanho'], df_el['Colisoes']):
    ax1.annotate(str(y), xy=(x, y), xytext=(0, -15), textcoords='offset points', ha='center')

salvar_figura(fig1, 'comparacao_colisoes.png')

# ======== Gráfico 2: Comparação de Fator de Carga e Colisões ========
fig2, ax2 = plt.subplots()
ax2.plot(df_div['Tamanho'], df_div['FatorCarga'], marker='s', color='darkblue', 
         linewidth=2, markersize=8, label='Fator Carga (Divisão)')
ax2.plot(df_el['Tamanho'], df_el['FatorCarga'], marker='d', color='darkgreen', 
         linewidth=2, markersize=8, label='Fator Carga (Enlaçamento)')
ax2.set_xlabel('Tamanho da Tabela')
ax2.set_ylabel('Fator de Carga')
ax2.set_title('Comparação do Fator de Carga e Porcentagem de Colisões')

# Cria um segundo eixo y para as colisões
ax2_2 = ax2.twinx()
# Calcula a porcentagem de colisões em relação ao número de elementos
df_div['PorcentagemColisoes'] = df_div['Colisoes'] * 100 / df_div['Elementos']
df_el['PorcentagemColisoes'] = df_el['Colisoes'] * 100 / df_el['Elementos']
ax2_2.plot(df_div['Tamanho'], df_div['PorcentagemColisoes'], marker='^', color='orange', 
           linewidth=2, markersize=8, label='% Colisões (Divisão)')
ax2_2.plot(df_el['Tamanho'], df_el['PorcentagemColisoes'], marker='*', color='red', 
           linewidth=2, markersize=8, label='% Colisões (Enlaçamento)')
ax2_2.set_ylabel('% de Colisões')

# Combina as legendas dos dois eixos
linhas1, labels1 = ax2.get_legend_handles_labels()
linhas2, labels2 = ax2_2.get_legend_handles_labels()
ax2.legend(linhas1 + linhas2, labels1 + labels2, loc='best')

salvar_figura(fig2, 'comparacao_fator_carga.png')

# ======== Gráfico 3: Comparação da Distribuição de Itens por Endereço ========
# Método 1: Divisão
fig3a, ax3a = plt.subplots()
# Extrai colunas de distribuição
colunas_dist = [col for col in df_div.columns if col.startswith('Qtd_')]
dados_dist_div = df_div.loc[:, colunas_dist].T

# Renomeia as colunas para serem os tamanhos das tabelas
dados_dist_div.columns = df_div['Tamanho']

# Prepara o gráfico
bar_width = 0.15
posicoes = np.arange(len(dados_dist_div.index))
num_tabelas = len(df_div['Tamanho'])
cores = plt.cm.viridis(np.linspace(0, 1, num_tabelas))

for i, tamanho in enumerate(df_div['Tamanho']):
    offset = bar_width * (i - num_tabelas/2 + 0.5)
    ax3a.bar(posicoes + offset, dados_dist_div[tamanho], 
            width=bar_width, label=f'Tabela {tamanho}', 
            color=cores[i], alpha=0.7)

# Ajustes do gráfico
ax3a.set_xticks(posicoes)
ax3a.set_xticklabels([col.replace('Qtd_', '') for col in colunas_dist])
ax3a.set_xlabel('Número de Itens por Endereço')
ax3a.set_ylabel('Quantidade de Endereços')
ax3a.set_title('Distribuição de Itens por Endereço - Método da Divisão')
ax3a.legend(title='Tamanho da Tabela')

salvar_figura(fig3a, 'distribuicao_itens_divisao.png')

# Método 2: Enlaçamento
fig3b, ax3b = plt.subplots()
# Extrai colunas de distribuição
dados_dist_el = df_el.loc[:, colunas_dist].T

# Renomeia as colunas para serem os tamanhos das tabelas
dados_dist_el.columns = df_el['Tamanho']

# Prepara o gráfico
cores = plt.cm.plasma(np.linspace(0, 1, num_tabelas))

for i, tamanho in enumerate(df_el['Tamanho']):
    offset = bar_width * (i - num_tabelas/2 + 0.5)
    ax3b.bar(posicoes + offset, dados_dist_el[tamanho], 
            width=bar_width, label=f'Tabela {tamanho}', 
            color=cores[i], alpha=0.7)

# Ajustes do gráfico
ax3b.set_xticks(posicoes)
ax3b.set_xticklabels([col.replace('Qtd_', '') for col in colunas_dist])
ax3b.set_xlabel('Número de Itens por Endereço')
ax3b.set_ylabel('Quantidade de Endereços')
ax3b.set_title('Distribuição de Itens por Endereço - Método de Enlaçamento')
ax3b.legend(title='Tamanho da Tabela')

salvar_figura(fig3b, 'distribuicao_itens_enlacamento.png')

# ======== Gráfico 4: Comparação do Tempo de Execução ========
fig4, ax4 = plt.subplots()
ax4.plot(df_div['Tamanho'], df_div['TempoExecucao'], marker='D', color='purple', 
         linewidth=2, markersize=8, label='Método da Divisão')
ax4.plot(df_el['Tamanho'], df_el['TempoExecucao'], marker='o', color='green', 
         linewidth=2, markersize=8, label='Método do Enlaçamento')
ax4.set_xlabel('Tamanho da Tabela')
ax4.set_ylabel('Tempo de Execução (ms)')
ax4.set_title('Comparação do Tempo de Execução entre Métodos')
ax4.legend()

# Adiciona valores acima dos pontos
for x, y in zip(df_div['Tamanho'], df_div['TempoExecucao']):
    ax4.annotate(f"{y:.2f}", xy=(x, y), xytext=(0, 5), 
                 textcoords='offset points', ha='center')

for x, y in zip(df_el['Tamanho'], df_el['TempoExecucao']):
    ax4.annotate(f"{y:.2f}", xy=(x, y), xytext=(0, -15), 
                 textcoords='offset points', ha='center')

salvar_figura(fig4, 'comparacao_tempo_execucao.png')

# ======== Gráfico 5: Comparação da Eficiência de Espaço ========
fig5, ax5 = plt.subplots()
largura = 0.35
posicoes = np.arange(len(df_div['Tamanho']))

# Barras lado a lado para os dois métodos
ax5.bar(posicoes - largura/2, df_div['PorcentagemEnderecos'], largura, color='blue', alpha=0.7, label='Divisão')
ax5.bar(posicoes + largura/2, df_el['PorcentagemEnderecos'], largura, color='red', alpha=0.7, label='Enlaçamento')

ax5.set_xlabel('Tamanho da Tabela')
ax5.set_ylabel('% de Endereços Utilizados')
ax5.set_title('Comparação da Porcentagem de Endereços Utilizados')
ax5.set_xticks(posicoes)
ax5.set_xticklabels(df_div['Tamanho'])
ax5.legend()

# Adiciona valores acima das barras
for i, v in enumerate(df_div['PorcentagemEnderecos']):
    ax5.text(i - largura/2, v + 1, f"{v:.1f}%", ha='center')

for i, v in enumerate(df_el['PorcentagemEnderecos']):
    ax5.text(i + largura/2, v + 1, f"{v:.1f}%", ha='center')

ax5.set_ylim(0, max(max(df_div['PorcentagemEnderecos']), max(df_el['PorcentagemEnderecos'])) * 1.2)

salvar_figura(fig5, 'comparacao_eficiencia_espaco.png')

# ======== Gráfico 6: Comparação Direta da Taxa de Colisões ========
fig6, ax6 = plt.subplots()

# Calcula a taxa de colisão (colisões/elementos)
df_div['TaxaColisao'] = df_div['Colisoes'] / df_div['Elementos']
df_el['TaxaColisao'] = df_el['Colisoes'] / df_el['Elementos']

largura = 0.35
posicoes = np.arange(len(df_div['Tamanho']))

ax6.bar(posicoes - largura/2, df_div['TaxaColisao'], largura, color='blue', alpha=0.7, label='Divisão')
ax6.bar(posicoes + largura/2, df_el['TaxaColisao'], largura, color='red', alpha=0.7, label='Enlaçamento')

ax6.set_xlabel('Tamanho da Tabela')
ax6.set_ylabel('Taxa de Colisões (colisões/elementos)')
ax6.set_title('Comparação da Taxa de Colisões entre os Métodos')
ax6.set_xticks(posicoes)
ax6.set_xticklabels(df_div['Tamanho'])
ax6.legend()

# Adiciona valores acima das barras
for i, v in enumerate(df_div['TaxaColisao']):
    ax6.text(i - largura/2, v + 0.01, f"{v:.3f}", ha='center')

for i, v in enumerate(df_el['TaxaColisao']):
    ax6.text(i + largura/2, v + 0.01, f"{v:.3f}", ha='center')

salvar_figura(fig6, 'comparacao_taxa_colisoes.png')

print("\nTodos os gráficos comparativos foram gerados com sucesso!")
print(f"Local: {output_dir}")

# Exibe os gráficos
plt.show()
