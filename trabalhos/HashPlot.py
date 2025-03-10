import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

# Configurações para melhorar a apresentação dos gráficos
plt.style.use('ggplot')
plt.rcParams['figure.figsize'] = (12, 7)
plt.rcParams['font.size'] = 12

# Caminho para o arquivo CSV e pasta de saída
csv_path = 'C:/Users/usuario/Desktop/Programas/ED_2/trabalhos/resultados_hash2.csv'
output_dir = 'C:/Users/usuario/Desktop/Programas/ED_2/trabalhos/graficos2'

if not os.path.exists(output_dir):
    os.makedirs(output_dir)

# Função para salvar figuras
def salvar_figura(fig, nome):
    caminho_completo = os.path.join(output_dir, nome)
    fig.savefig(caminho_completo, bbox_inches='tight', dpi=300)
    print(f"Gráfico salvo em: {caminho_completo}")

# Carregando os dados do CSV
try:
    df = pd.read_csv(csv_path)
    print("Dados carregados com sucesso:")
    print(df.head())
except Exception as e:
    print(f"Erro ao carregar o arquivo CSV: {e}")
    exit(1)

# ======== Gráfico 1: Colisões por Tamanho da Tabela ========
fig1, ax1 = plt.subplots()
ax1.plot(df['Tamanho'], df['Colisoes'], marker='o', linewidth=2, markersize=8)
ax1.set_xlabel('Tamanho da Tabela')
ax1.set_ylabel('Número de Colisões')
ax1.set_title('Colisões vs Tamanho da Tabela Hash')
ax1.grid(True)

# Adiciona valores acima dos pontos
for x, y in zip(df['Tamanho'], df['Colisoes']):
    ax1.annotate(str(y), xy=(x, y), xytext=(0, 5), textcoords='offset points', ha='center')

salvar_figura(fig1, 'colisoes_por_tamanho.png')

# ======== Gráfico 2: Fator de Carga e Colisões ========
fig2, ax2 = plt.subplots()
ax2.plot(df['Tamanho'], df['FatorCarga'], marker='s', color='green', linewidth=2, 
         markersize=8, label='Fator de Carga')
ax2.set_xlabel('Tamanho da Tabela')
ax2.set_ylabel('Fator de Carga')
ax2.set_title('Fator de Carga e Porcentagem de Colisões por Tamanho da Tabela')

# Cria um segundo eixo y para as colisões
ax2_2 = ax2.twinx()
# Calcula a porcentagem de colisões em relação ao número de elementos
df['PorcentagemColisoes'] = df['Colisoes'] * 100 / df['Elementos']
ax2_2.plot(df['Tamanho'], df['PorcentagemColisoes'], marker='^', color='red', 
           linewidth=2, markersize=8, label='% Colisões')
ax2_2.set_ylabel('% de Colisões')

# Combina as legendas dos dois eixos
linhas1, labels1 = ax2.get_legend_handles_labels()
linhas2, labels2 = ax2_2.get_legend_handles_labels()
ax2.legend(linhas1 + linhas2, labels1 + labels2, loc='best')

salvar_figura(fig2, 'fator_carga_colisoes.png')

# ======== Gráfico 3: Distribuição de Itens por Endereço ========
# Extrai colunas de distribuição
colunas_dist = [col for col in df.columns if col.startswith('Qtd_')]
dados_dist = df.loc[:, colunas_dist].T

# Renomeia as colunas para serem os tamanhos das tabelas
dados_dist.columns = df['Tamanho']

# Preparação de figura e subplots
fig3, ax3 = plt.subplots()

# Cria barras para cada tamanho de tabela
bar_width = 0.15
posicoes = np.arange(len(dados_dist.index))
num_tabelas = len(df['Tamanho'])
cores = plt.cm.viridis(np.linspace(0, 1, num_tabelas))

for i, tamanho in enumerate(df['Tamanho']):
    offset = bar_width * (i - num_tabelas/2 + 0.5)
    ax3.bar(posicoes + offset, dados_dist[tamanho], 
            width=bar_width, label=f'Tabela {tamanho}', 
            color=cores[i], alpha=0.7)

# Ajustes do gráfico
ax3.set_xticks(posicoes)
ax3.set_xticklabels([col.replace('Qtd_', '') for col in colunas_dist])
ax3.set_xlabel('Número de Itens por Endereço')
ax3.set_ylabel('Quantidade de Endereços')
ax3.set_title('Distribuição de Itens por Endereço para Diferentes Tamanhos de Tabela')
ax3.legend(title='Tamanho da Tabela')

salvar_figura(fig3, 'distribuicao_itens.png')

# ======== Gráfico 4: Tempo de Execução por Tamanho da Tabela ========
fig4, ax4 = plt.subplots()
ax4.plot(df['Tamanho'], df['TempoExecucao'], marker='D', color='purple', 
         linewidth=2, markersize=8)
ax4.set_xlabel('Tamanho da Tabela')
ax4.set_ylabel('Tempo de Execução (ms)')
ax4.set_title('Tempo de Execução vs Tamanho da Tabela Hash')

# Adiciona valores acima dos pontos
for x, y in zip(df['Tamanho'], df['TempoExecucao']):
    ax4.annotate(f"{y:.2f}", xy=(x, y), xytext=(0, 5), 
                 textcoords='offset points', ha='center')

salvar_figura(fig4, 'tempo_execucao.png')

# ======== Gráfico 5: Eficiência de Espaço ========
fig5, ax5 = plt.subplots()
ax5.bar(df['Tamanho'].astype(str), df['PorcentagemEnderecos'], color='teal', alpha=0.7)
ax5.set_xlabel('Tamanho da Tabela')
ax5.set_ylabel('% de Endereços Utilizados')
ax5.set_title('Porcentagem de Endereços Utilizados por Tamanho da Tabela')

# Adiciona valores acima das barras
for i, v in enumerate(df['PorcentagemEnderecos']):
    ax5.text(i, v + 1, f"{v:.1f}%", ha='center')

ax5.set_ylim(0, max(df['PorcentagemEnderecos']) * 1.2)

salvar_figura(fig5, 'eficiencia_espaco.png')

print("\nTodos os gráficos foram gerados com sucesso!")
print(f"Local: {output_dir}")

# Exibe os gráficos
plt.show()
