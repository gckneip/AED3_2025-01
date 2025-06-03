## 🧪 Executando o Código

Após fazer o download do repositório do GitHub:

1. Extraia o conteúdo do `.zip` (ou clone o repositório).
2. Acesse a pasta com os arquivos no terminal.
3. Execute o seguinte passo a passo:

```bash
$ make clean
$ make
$ ./TSP_algorithms tsp/{nome_do_arquivo.txt} 0
```

## 🔢 Parâmetro do Algoritmo

O número no final do comando indica qual algoritmo será utilizado para resolver o problema:
```bash
0 → Força Bruta

1 → Held-Karp

2 → Christofides