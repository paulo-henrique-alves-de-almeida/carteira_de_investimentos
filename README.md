<div align="center">

![Linguagem](https://img.shields.io/badge/linguagem-C99-00599C?logo=c&logoColor=white)
![Compilador](https://img.shields.io/badge/compilador-GCC%20%7C%20MinGW-A42E2B?logo=gnu&logoColor=white)
![IDE](https://img.shields.io/badge/IDE-Dev--C%2B%2B-4B8BBE)
![Plataforma](https://img.shields.io/badge/plataforma-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey)
![Versão](https://img.shields.io/badge/vers%C3%A3o-3.1-success)
![Licença](https://img.shields.io/badge/licen%C3%A7a-MIT-green)

**Aplicação de console para cadastrar, acompanhar e analisar uma carteira de investimentos, com persistência em arquivo texto e um simulador educativo de renda fixa.**

[Descrição](#1-descrição-do-projeto) •
[Público-alvo](#2-público-alvo) •
[Funcionalidades](#3-funcionalidades-do-sistema) •
[Tecnologias](#4-tecnologias-utilizadas) •
[Requisitos](#5-requisitos-mínimos-para-execução) •
[Execução](#6-instruções-para-execução) •
[Desenvolvedores](#7-desenvolvedores)

</div>

---

## 1. Descrição do projeto

A **Carteira de Investimentos** é um sistema de console desenvolvido em **linguagem C** que permite registrar ativos financeiros — ações, títulos de renda fixa, fundos etc. — e acompanhar o desempenho da carteira: valor de mercado, rentabilidade individual, rentabilidade geral ponderada e classificação de risco de cada ativo.

Os dados ficam salvos em um arquivo texto (`data/carteira.txt`), de modo que a carteira é preservada entre uma execução e outra. O sistema também traz um **simulador educativo** que compara quanto o valor da carteira renderia em 12 meses na Poupança, no Tesouro Selic e em um CDB.

Do ponto de vista acadêmico, o projeto aplica conceitos fundamentais de programação estruturada:

- `struct` e **vetor de structs** para modelar os ativos;
- **modularização** em arquivos `.c` / `.h` com responsabilidades separadas;
- **passagem por referência** com ponteiros;
- **leitura e gravação de arquivos** texto (`fopen`, `fscanf`, `fprintf`);
- **validação de entrada** do usuário;
- **ordenação** com algoritmo *Quicksort* implementado manualmente.

### Impacto social — ODS 8.10

O simulador apresenta alternativas de investimento em linguagem simples, ajudando a compreender **rentabilidade, risco e liquidez**. A proposta se alinha à meta **8.10 dos Objetivos de Desenvolvimento Sustentável da ONU**, que incentiva a ampliação do acesso a serviços financeiros para todas as pessoas.

---

## 2. Público-alvo

- **Investidores iniciantes** que desejam organizar seus ativos em um só lugar e entender, de forma simples, se estão tendo lucro ou prejuízo.
- **Pessoas com pouco acesso a ferramentas financeiras**, que precisam de uma solução leve, gratuita e que funcione offline em computadores modestos.
- **Estudantes e educadores de educação financeira**, que podem usar o simulador para comparar Poupança, Tesouro Selic e CDB em sala de aula.
- **Estudantes de programação**, como exemplo prático de structs, modularização, arquivos e algoritmos de ordenação em C.

---

## 3. Funcionalidades do sistema

| Opção | Funcionalidade | Descrição |
|:-----:|----------------|-----------|
| `1` | **Cadastrar ativo** | Registra nome, categoria, quantidade, preço de compra e preço atual. Salva automaticamente. |
| `2` | **Listar ativos** | Exibe cada posição com valor atual, rentabilidade e classificação de risco, além dos totais da carteira. |
| `3` | **Valor total da carteira** | Soma o valor de mercado de todas as posições. |
| `4` | **Rentabilidade geral** | Calcula a rentabilidade consolidada, ponderada pelo capital investido. |
| `5` | **Ordenar por rentabilidade** ¹ | Ordena a carteira (Quicksort, decrescente) e salva a nova ordem. |
| `6` | **Simulador educativo** ¹ | Projeta o valor da carteira em 12 meses na Poupança, Tesouro Selic e CDB. |
| `7` | **Relatório final** ¹ | Ranking por rentabilidade, valor total, rentabilidade geral e lucro/prejuízo. |
| `0` | **Salvar e sair** | Grava a carteira em disco e encerra o programa. |

### Classificação de risco

| Rentabilidade do ativo | Classificação |
|------------------------|:-------------:|
| abaixo de −10% | **Alto** |
| de −10% até 0% (exclusive) | **Atenção** |
| exatamente 0% | **Neutro** |
| acima de 0% | **Positivo** |

### Regras de cálculo

| Métrica | Fórmula |
|---------|---------|
| Valor atual da posição | `quantidade × precoAtual` |
| Rentabilidade do ativo | `(precoAtual − precoCompra) ÷ precoCompra × 100` |
| Valor total da carteira | `Σ (quantidade × precoAtual)` |
| Rentabilidade geral | `(valorAtualTotal − custoTotal) ÷ custoTotal × 100` |
| Lucro / prejuízo | `valorAtualTotal − custoTotal` |
| Simulação (juros compostos) | `valorInicial × (1 + taxaMensal)^12` |

Taxas mensais usadas no simulador: Poupança **0,50%**, Tesouro Selic **0,80%** e CDB **0,90%**.

> [!WARNING]
> As taxas do simulador são **fixas e ilustrativas**. Não refletem as taxas vigentes de mercado e **não constituem recomendação de investimento**.

### Validações de entrada

- Campos de texto não podem ficar vazios nem exceder o tamanho máximo (nome: 99, categoria: 49 caracteres).
- O caractere `;` é proibido nos textos, pois é o separador do arquivo de dados.
- Quantidade: inteiro entre `1` e `2.147.483.647`.
- Preço de compra: número **maior que zero**. Preço atual: número **maior ou igual a zero**.
- Entradas inválidas (ex.: `10abc`) são rejeitadas e solicitadas novamente.
- Limite de **100 ativos** por carteira.

---

## 4. Tecnologias utilizadas

| Tecnologia | Uso no projeto |
|------------|----------------|
| **Linguagem C (padrão C99)** | Linguagem de desenvolvimento de todo o sistema |
| **Biblioteca padrão do C** | `stdio.h`, `stdlib.h`, `string.h`, `ctype.h`, `stdbool.h`, `math.h`, `errno.h`, `locale.h` |
| **GCC / MinGW** | Compilação do código-fonte |
| **Dev-C++ 5.11** | IDE utilizada no desenvolvimento (`carteira_de_investimentos.dev`, `Makefile.win`) |
| **Arquivo texto (`.txt`)** | Persistência dos dados da carteira, com campos separados por `;` |
| **Git e GitHub** | Versionamento e hospedagem do código |

### Estrutura do projeto

```text
carteira_de_investimentos/
├── include/
│   ├── funcoes.h                 # Protótipos de entrada, validação e interface
│   └── modulo.h                  # Struct Ativo, constantes e protótipos da carteira
├── src/
│   ├── main.c                    # Ponto de entrada: menu e fluxo principal
│   ├── funcoes.c                 # Leitura validada, menu, limpeza de tela, pausa
│   └── modulo.c                  # Regras de negócio, cálculos, ordenação e persistência
├── data/
│   └── carteira.txt              # Base de dados (texto, separado por ";")
├── carteira_de_investimentos.dev # Projeto do Dev-C++
├── Makefile.win                  # Makefile gerado pelo Dev-C++
└── LICENSE
```

### Modelo de dados

```c
typedef struct {
    char   nome[100];
    char   categoria[50];
    int    quantidade;
    double precoCompra;
    double precoAtual;
} Ativo;
```

---

## 5. Requisitos mínimos para execução

| Item | Requisito mínimo |
|------|------------------|
| **Sistema operacional** | Windows 7 ou superior, Linux ou macOS |
| **Processador** | Qualquer processador x86 ou x64 (ou ARM, no macOS/Linux) |
| **Memória RAM** | 512 MB (o programa usa menos de 1 MB) |
| **Espaço em disco** | 5 MB livres para o código, o executável e os dados |
| **Compilador** | GCC 4.9 ou superior, com suporte a C99 (no Windows: MinGW ou o compilador do Dev-C++) |
| **Terminal** | Prompt de Comando, PowerShell ou terminal Linux/macOS |
| **Permissões** | Leitura e escrita na pasta `data/` do projeto |
| **Internet** | Não é necessária |

---

## 6. Instruções para execução

### Passo 1 — Obter o código

```bash
git clone https://github.com/paulo-henrique-alves-de-almeida/carteira_de_investimentos.git
cd carteira_de_investimentos
```

Ou baixe pelo botão **Code → Download ZIP** no GitHub e extraia a pasta.

### Passo 2 — Compilar

**Opção A: Dev-C++ (Windows)**

1. Abra o arquivo `carteira_de_investimentos.dev`.
2. Clique em **Executar → Compilar & Executar** (ou pressione `F11`).

**Opção B: terminal no Windows (MinGW)**

```bash
gcc -Wall -Wextra -std=c99 -Iinclude src/main.c src/funcoes.c src/modulo.c -o programa.exe
```

**Opção C: terminal no Linux / macOS**

```bash
gcc -Wall -Wextra -std=c99 -Iinclude src/main.c src/funcoes.c src/modulo.c -o programa -lm
```

### Passo 3 — Executar

```bash
programa.exe      # Windows
./programa        # Linux / macOS
```

> [!IMPORTANT]
> **Execute a partir da pasta raiz do projeto.** O programa usa o caminho relativo `data/carteira.txt`, e a pasta `data/` precisa existir. Se o arquivo não existir, a carteira começa vazia e ele é criado no primeiro salvamento.

### Passo 4 — Usar o sistema

Escolha uma opção do menu digitando o número correspondente e pressionando `Enter`:

```text
===============================================================
================ CARTEIRA DE INVESTIMENTOS ====================
===============================================================

[1] Cadastrar ativo
[2] Listar ativos
[3] Valor total da carteira
[4] Rentabilidade geral
[0] Salvar e sair

Opção: 1

========== Cadastro de ativo ==========

Nome: PETR4
Categoria: Ação
Quantidade: 100
Preço de compra por unidade: 28.00
Preço atual por unidade: 31.50
Carteira salva em data/carteira.txt.
Ativo cadastrado com sucesso!
```

> [!NOTE]
> O programa segue a configuração regional do sistema (`setlocale`). Em computadores configurados em português, os valores decimais podem ser gravados com **vírgula** no arquivo (`28,00`). Se a digitação com ponto for recusada, use vírgula.

### Formato do arquivo de dados

Cada linha de `data/carteira.txt` representa um ativo:

```text
nome;categoria;quantidade;precoCompra;precoAtual
PETR4;Ação;100;28,00;31,50
```

---

## 7. Desenvolvedores

Projeto desenvolvido em grupo por 6 alunos:

| Nº | Desenvolvedor |
|:--:|---------------|
| 1 | Paulo Henrique Alves de Almeida |
| 2 | Murilo Roselini |
| 3 | Raphael Souza Araujo Barbosa |
| 4 | Matheus Avanzo dos Santos |
| 5 | Petterson Augusto Papa de Souza |
| 6 | Pedro Henrique Mello Rodrigues |

---

## Licença

Distribuído sob a licença **MIT**. Consulte o arquivo [`LICENSE`](LICENSE) para mais detalhes.
