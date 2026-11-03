#include <stdio.h>
#include <string.h>

#include "modulo.h"
#include "funcoes.h"

void carregarCarteira(Ativo carteira[], int *quantidadeAtivos) {
    FILE *arquivo;
    Ativo ativo;
    int resultado;

    *quantidadeAtivos = 0;
    arquivo = fopen(ARQUIVO_CARTEIRA, "r");

    if (arquivo == NULL) {
        // na primeira execu��o, o arquivo pode ainda n�o existir
        printf("Aviso: n�o foi poss�vel abrir %s para leitura.\n", ARQUIVO_CARTEIRA);
        printf("A carteira ser� iniciada vazia e o arquivo ser� criado ao salvar.\n\n");
        return;
    }

    while (*quantidadeAtivos < MAX_ATIVOS) {
        resultado = fscanf(arquivo, " %99[^;];%49[^;];%d;%lf;%lf", ativo.nome, ativo.categoria, &ativo.quantidade, &ativo.precoCompra, &ativo.precoAtual);

        if (resultado != 5) {
            printf("Aviso: registro inv�lido encontrado em %s.\n\n", ARQUIVO_CARTEIRA);
            break;
        }

        if (ativo.quantidade < 0 || ativo.precoCompra <= 0 || ativo.precoAtual < 0) {
            printf("Aviso: ativo inv�lido ignorado no arquivo.\n\n");
            continue;
        }

        carteira[*quantidadeAtivos] = ativo;
        (*quantidadeAtivos)++;
    }

    if (*quantidadeAtivos == MAX_ATIVOS) {
        printf("Aviso: limite de %d ativos atingido durante a leitura.\n\n", MAX_ATIVOS);
    }

    fclose(arquivo);
}

void salvarCarteira(Ativo carteira[], int quantidadeAtivos) {
    FILE *arquivo;
    int i;

    arquivo = fopen(ARQUIVO_CARTEIRA, "w");
    if (arquivo == NULL) {
        printf("\nErro: n�o foi poss�vel abrir realizar a grava��o dos dados.\n\n");
        return;
    }

    for (i = 0; i < quantidadeAtivos; i++) {
        fprintf(arquivo, "%s;%s;%d;%.2f;%.2f\n", carteira[i].nome, carteira[i].categoria, carteira[i].quantidade, carteira[i].precoCompra, carteira[i].precoAtual);
    }

    fclose(arquivo);
    printf("Carteira salva em %s.\n\n", ARQUIVO_CARTEIRA);
}

void cadastrarAtivo(Ativo carteira[], int *quantidadeAtivos) {
    Ativo novoAtivo;
    
    limparTela();

    if (*quantidadeAtivos >= MAX_ATIVOS) {
        printf("A carteira atingiu o limite de %d ativos.\n", MAX_ATIVOS);
        pausar();
        return;
    }

    printf("\n========== Cadastro de ativo ==========\n\n");
    lerTexto("Nome: ", novoAtivo.nome, TAM_NOME);
    lerTexto("Categoria: ", novoAtivo.categoria, TAM_CATEGORIA);
    novoAtivo.quantidade = lerInteiro("Quantidade: ", 1, MAX_INTEIRO);
    novoAtivo.precoCompra = lerNumero("Pre�o de compra por unidade: ", false);
    novoAtivo.precoAtual = lerNumero("Pre�o atual por unidade: ", true);

    carteira[*quantidadeAtivos] = novoAtivo;
    (*quantidadeAtivos)++;

    salvarCarteira(carteira, *quantidadeAtivos);
    printf("Ativo cadastrado com sucesso!\n\n");
}

double calcularRentabilidadeAtivo(Ativo ativo) {
    return (ativo.precoAtual - ativo.precoCompra) / ativo.precoCompra * 100.0;
}

double calcularValorTotal(Ativo carteira[], int quantidadeAtivos) {
    double total = 0;
    int i;

    for (i = 0; i < quantidadeAtivos; i++) {
        total += carteira[i].quantidade * carteira[i].precoAtual;
    }

    return total;
}

double calcularRentabilidadeGeral(Ativo carteira[], int quantidadeAtivos) {
    double custoTotal = 0;
    double valorAtualTotal = 0;
    int i;

    for (i = 0; i < quantidadeAtivos; i++) {
        custoTotal += carteira[i].quantidade * carteira[i].precoCompra;
        valorAtualTotal += carteira[i].quantidade * carteira[i].precoAtual;
    }

    if (custoTotal == 0) {
        return 0;
    }

    return (valorAtualTotal - custoTotal) / custoTotal * 100.0;
}

static void trocarAtivos(Ativo *primeiro, Ativo *segundo) {
    Ativo temporario = *primeiro;
    *primeiro = *segundo;
    *segundo = temporario;
}

static void quicksortPorRentabilidade(Ativo carteira[], int inicio, int fim) {
    int esquerda = inicio;
    int direita = fim;
    double pivo;

    if (inicio >= fim) {
        return;
    }

    pivo = calcularRentabilidadeAtivo(carteira[(inicio + fim) / 2]);

    while (esquerda <= direita) {
        while (calcularRentabilidadeAtivo(carteira[esquerda]) > pivo) {
            esquerda++;
        }

        while (calcularRentabilidadeAtivo(carteira[direita]) < pivo) {
            direita--;
        }

        if (esquerda <= direita) {
            trocarAtivos(&carteira[esquerda], &carteira[direita]);
            esquerda++;
            direita--;
        }
    }

    if (inicio < direita) {
        quicksortPorRentabilidade(carteira, inicio, direita);
    }

    if (esquerda < fim) {
        quicksortPorRentabilidade(carteira, esquerda, fim);
    }
}

void ordenarCarteiraPorRentabilidade(Ativo carteira[], int quantidadeAtivos) {
    limparTela();
    printf("========== Carteira ordenada por rentabilidade ==========\n\n");

    if (quantidadeAtivos == 0) {
        printf("Nenhum ativo cadastrado.\n\n");
        return;
    }

    quicksortPorRentabilidade(carteira, 0, quantidadeAtivos - 1);
    listarAtivos(carteira, quantidadeAtivos);
    salvarCarteira(carteira, quantidadeAtivos);
}

static double simularValor(double valorInicial, double taxaMensal) {
    double valor = valorInicial;
    int mes;

    for (mes = 0; mes < MESES_SIMULACAO; mes++) {
        valor *= (1.0 + taxaMensal);
    }

    return valor;
}

void simularInvestimentos(Ativo carteira[], int quantidadeAtivos) {
    double valorInicial;
    double valorPoupanca;
    double valorTesouro;
    double valorCdb;

    limparTela();
    printf("================ SIMULADOR EDUCATIVO ================\n\n");

    if (quantidadeAtivos == 0) {
        printf("Nenhum ativo cadastrado. Cadastre um ativo primeiro.\n\n");
        return;
    }

    valorInicial = calcularValorTotal(carteira, quantidadeAtivos);
    valorPoupanca = simularValor(valorInicial, TAXA_POUPANCA);
    valorTesouro = simularValor(valorInicial, TAXA_TESOURO_SELIC);
    valorCdb = simularValor(valorInicial, TAXA_CDB);

    printf("E se os R$ %.2f da sua carteira ficassem\n", valorInicial);
    printf("investidos por %d meses em cada opcao?\n\n", MESES_SIMULACAO);
    printf("POUPANCA       (%.2f%%/mes): R$ %.2f (+R$ %.2f)\n",
           TAXA_POUPANCA * 100.0, valorPoupanca, valorPoupanca - valorInicial);
    printf("TESOURO SELIC  (%.2f%%/mes): R$ %.2f (+R$ %.2f)\n",
           TAXA_TESOURO_SELIC * 100.0, valorTesouro, valorTesouro - valorInicial);
    printf("CDB            (%.2f%%/mes): R$ %.2f (+R$ %.2f)\n\n",
           TAXA_CDB * 100.0, valorCdb, valorCdb - valorInicial);

    printf("O que isso significa?\n");
    printf("- Poupanca: e conhecida e costuma render menos.\n");
    printf("- Tesouro Selic: e um titulo publico de baixo risco e permite\n");
    printf("  investir valores acessiveis. Confira as regras vigentes.\n");
    printf("- CDB: pode render mais, tem cobertura do FGC dentro dos limites\n");
    printf("  aplicaveis, mas alguns produtos exigem esperar ate o vencimento.\n");
    printf("As taxas acima sao ilustrativas e nao sao recomendacao de investimento.\n\n");
}

void gerarRelatorioFinal(Ativo carteira[], int quantidadeAtivos) {
    double custoTotal = 0.0;
    double valorAtualTotal;
    double lucroPrejuizo;
    int i;

    limparTela();
    printf("================ RELATORIO FINAL ================\n\n");

    if (quantidadeAtivos == 0) {
        printf("Nenhum ativo cadastrado.\n\n");
        return;
    }

    quicksortPorRentabilidade(carteira, 0, quantidadeAtivos - 1);

    printf("ATIVOS ORDENADOS POR RENTABILIDADE\n\n");
    for (i = 0; i < quantidadeAtivos; i++) {
        printf("%d. %s (%s) - Rentabilidade: %.2f%% - Valor atual: R$ %.2f\n",
               i + 1,
               carteira[i].nome,
               carteira[i].categoria,
               calcularRentabilidadeAtivo(carteira[i]),
               carteira[i].quantidade * carteira[i].precoAtual);
        custoTotal += carteira[i].quantidade * carteira[i].precoCompra;
    }

    valorAtualTotal = calcularValorTotal(carteira, quantidadeAtivos);
    lucroPrejuizo = valorAtualTotal - custoTotal;

    printf("\nValor total da carteira: R$ %.2f\n", valorAtualTotal);
    printf("Rentabilidade geral: %.2f%%\n", calcularRentabilidadeGeral(carteira, quantidadeAtivos));
    printf("Lucro/prejuizo total: R$ %.2f\n", lucroPrejuizo);

    printf("\nImpacto social\n");
    printf("O simulador apresenta alternativas de investimento em linguagem simples,\n");
    printf("ajudando mais pessoas a compreender rentabilidade, risco e liquidez.\n");
    printf("Assim, contribui para a inclusao financeira relacionada ao ODS 8.10 da ONU,\n");
    printf("que incentiva o acesso a servicos financeiros para todas as pessoas.\n\n");

    salvarCarteira(carteira, quantidadeAtivos);
}

char *classificarRisco(double rentabilidade) {
    if (rentabilidade < -10.0) {
        return "Alto";
    }

    if (rentabilidade < 0.0) {
        return "Atencao";
    }

    if (rentabilidade == 0.0) {
        return "Neutro";
    }

    return "Positivo";
}

void listarAtivos(Ativo carteira[], int quantidadeAtivos) {
    int i;
    double valorAtual;
    double rentabilidade;

	limparTela();
    printf("\n========== Lista de ativos ==========\n\n");

    if (quantidadeAtivos == 0) {
        printf("Nenhum ativo cadastrado.\n\n");
        return;
    }

    for (i = 0; i < quantidadeAtivos; i++) {
        valorAtual = carteira[i].quantidade * carteira[i].precoAtual;
        rentabilidade = calcularRentabilidadeAtivo(carteira[i]);

        printf("%d. %s - %s - %d unidades - Preco atual: R$ %.2f\n", i + 1, carteira[i].nome, carteira[i].categoria, carteira[i].quantidade, carteira[i].precoAtual);
        printf("Valor atual: R$ %.2f\nRentabilidade: %.2f%%\n", valorAtual, rentabilidade);
        printf("Classifica��o de risco: %s\n\n", classificarRisco(rentabilidade));
    }

	printf("======================================\n");
    printf("| Valor total da carteira: R$ %.2f \n", calcularValorTotal(carteira, quantidadeAtivos));
    printf("| \n");
    printf("| Rentabilidade geral: %.2f%% \n", calcularRentabilidadeGeral(carteira, quantidadeAtivos));
    printf("======================================\n\n");
}
