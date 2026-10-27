# Carteira de Investimentos — CP1

Projeto em C para o primeiro checkpoint, com foco em funções e modularização.
O programa simula uma carteira com um único ativo e apresenta sua rentabilidade,
lucro ou prejuízo e uma classificação didática de risco. O tema é inclusão
financeira, relacionado à ODS 8.10 apresentada no enunciado.

## Arquivos

- `main.c`: variáveis do ativo, menu controlado por `while` e seleção com `switch`.
- `funcoes.c`: implementação das funções e validação das entradas.
- `funcoes.h`: protótipos e tamanhos dos campos de texto.
- `README.md`: instruções e casos de teste.

## Compilação e execução

É necessário ter o GCC instalado e disponível no terminal. Abra o terminal na
pasta `meu-projeto-c` e compile os dois arquivos `.c` juntos:

```sh
gcc main.c funcoes.c -o programa
```

Para conferir também avisos do compilador:

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic main.c funcoes.c -o programa
```

No Windows, execute no PowerShell:

```powershell
.\programa.exe
```

No Linux ou macOS:

```sh
./programa
```

## Como usar

1. Escolha **1** e informe nome, categoria, quantidade, preço de compra e preço atual.
2. Escolha **2** para consultar rentabilidade e lucro/prejuízo.
3. Escolha **3** para consultar a classificação de risco.
4. Escolha **4** para encerrar.

Use ponto nos valores decimais (ex.: `25.50`). Nome e categoria aceitam espaços,
com limites de 79 e 39 bytes, respectivamente. Quantidade aceita frações e deve
ser maior que zero. O preço de compra deve ser maior que zero; o preço atual
pode ser zero. Entradas vazias, texto em campos numéricos, números não finitos
e opções inválidas são rejeitados. Consultas exigem cadastro prévio.

Um novo cadastro substitui o ativo anterior. Os dados existem apenas enquanto
o programa está em execução. Não há `struct`, vetor de ativos nem leitura ou
gravação de arquivos. Os vetores de caracteres armazenam somente textos.

## Funções e cálculos

As funções `calcularRentabilidade` e `calcularLucro` retornam valores `double`:

```text
rentabilidade = (precoAtual - precoCompra) / precoCompra * 100
lucro         = (precoAtual - precoCompra) * quantidade
```

As funções `cadastrarAtivo`, `exibirResultados`, `classificarRisco` e `sair`
são `void` e atendem às quatro opções. O cadastro recebe ponteiros para atualizar
as variáveis da `main`. As funções auxiliares `lerTexto` e `lerNumero` são
`static`, pois são usadas somente dentro de `funcoes.c`.

A classificação usa uma cadeia de `if/else`:

| Rentabilidade | Mensagem |
| --- | --- |
| Menor que -10% | Alto |
| De -10%, inclusive, até 0%, exclusive | Atenção |
| Igual a 0% | Rentabilidade neutra |
| Maior que 0% | Rentabilidade positiva |

Esta regra é uma simplificação para o exercício: descreve a variação de preço,
não uma avaliação completa do risco de um investimento. Os cálculos não incluem
taxas, impostos ou dividendos. Valores monetários aparecem com duas casas
decimais; o prejuízo é exibido como magnitude positiva com o rótulo “Prejuizo”.

## Exemplo

Cadastre `PETR4`, categoria `Acao`, quantidade `100`, preço de compra `25.00`
e preço atual `28.00`. A opção 2 apresenta:

```text
Ativo: PETR4 | Categoria: Acao
Quantidade: 100.00
Rentabilidade: 12.00%
Lucro: R$ 300.00
```

A opção 3 apresenta `Risco: Rentabilidade positiva.`.

## Casos de teste

Validação realizada com GCC 16.2.0 no Windows: compilação em C11 com
`-Wall -Wextra -Wpedantic -Werror`, sem erros nem avisos. Foram aprovados
15 cenários de execução, incluindo os casos abaixo, as validações de entrada,
o limite dos campos de texto, a troca de ativo e o fim da entrada durante cadastro.

Após cada cadastro, use as opções 2 e 3 para verificar:

| Quantidade | Compra | Atual | Rentabilidade | Resultado | Classificação |
| ---: | ---: | ---: | ---: | --- | --- |
| 100 | 25.00 | 28.00 | 12.00% | Lucro R$ 300.00 | Positiva |
| 100 | 25.00 | 20.00 | -20.00% | Prejuízo R$ 500.00 | Alto |
| 10 | 100.00 | 90.00 | -10.00% | Prejuízo R$ 100.00 | Atenção |
| 10 | 100.00 | 95.00 | -5.00% | Prejuízo R$ 50.00 | Atenção |
| 10 | 100.00 | 100.00 | 0.00% | Sem lucro ou prejuízo | Neutra |
| 10 | 100.00 | 0.00 | -100.00% | Prejuízo R$ 1000.00 | Alto |
| 0.5 | 10.00 | 12.00 | 20.00% | Lucro R$ 1.00 | Positiva |

Verifique também consultas antes do cadastro, substituição do ativo, opções
inválidas, campos vazios, textos longos, letras em valores numéricos, preço de
compra zero, valores negativos, números com vírgula e encerramento pela opção 4.

## Entrega

O ZIP contém a pasta `meu-projeto-c` com os quatro arquivos acima. Extraia a
pasta, compile e confira a execução. Envie o ZIP pelo grupo do Blackboard,
conforme o enunciado (Aula 10, 21/10).
