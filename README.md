# Carteira de Investimentos em C

Projeto de checkpoint: cadastro de múltiplos ativos com `struct`, vetor de structs e persistência em arquivo texto.

## Estrutura

- `src/main.c`: menu e fluxo principal.
- `src/funcoes.c`: entrada, validação e apresentação.
- `src/modulo.c`: cadastro, listagem, cálculos e persistência.
- `include/funcoes.h`: protótipos das funções auxiliares.
- `include/modulo.h`: definição de `Ativo`, constantes e protótipos da carteira.
- `data/carteira.txt`: arquivo de exemplo com dois ativos.

## Compilação com GCC

Execute o comando a partir da pasta `meu-projeto-c`:

```bash
gcc -Wall -Wextra -Iinclude src/main.c src/funcoes.c src/modulo.c -o programa
```

No Linux/macOS, execute:

```bash
./programa
```

No Windows, execute `programa.exe` ou `programa`, conforme o terminal utilizado.

## Observação sobre o arquivo de dados

O programa usa o caminho relativo `data/carteira.txt`. Execute o programa com a pasta do projeto como diretório de trabalho para que o arquivo seja encontrado. Se o arquivo não existir ou não puder ser aberto para leitura, a carteira começa vazia; ao cadastrar ou sair, o programa tenta salvar os dados nesse caminho. A pasta `data` deve existir.

## Cálculos

- Valor atual de cada posição: `quantidade * precoAtual`.
- Rentabilidade de cada ativo: `(precoAtual - precoCompra) / precoCompra * 100`.
- Rentabilidade geral: `(valorAtualTotal - custoTotal) / custoTotal * 100`, ponderada pelo valor investido em cada ativo.

O cadastro permite até 100 ativos. Quantidade deve ser um inteiro não negativo; preço de compra deve ser maior que zero e preço atual pode ser zero.
