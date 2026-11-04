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
        // na primeira execução, o arquivo pode ainda não existir
        printf("Aviso: não foi possível abrir %s para leitura.\n", ARQUIVO_CARTEIRA);
        printf("A carteira será iniciada vazia e o arquivo será criado ao salvar.\n\n");
        return;
    }

    while (*quantidadeAtivos < MAX_ATIVOS) {
        resultado = fscanf(arquivo, " %99[^;];%49[^;];%d;%lf;%lf", ativo.nome, ativo.categoria, &ativo.quantidade, &ativo.precoCompra, &ativo.precoAtual);

        if (resultado != 5) {
            printf("Aviso: registro inválido encontrado em %s.\n\n", ARQUIVO_CARTEIRA);
            break;
        }

        if (ativo.quantidade < 0 || ativo.precoCompra <= 0 || ativo.precoAtual < 0) {
            printf("Aviso: ativo inválido ignorado no arquivo.\n\n");
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
        printf("\nErro: não foi possível abrir realizar a gravação dos dados.\n\n");
        return;
    }

    for (i = 0; i < quantidadeAtivos; i++) {
        fprintf(arquivo, "%s;%s;%d;%.2f;%.2f\n", carteira[i].nome, carteira[i].categoria, carteira[i].quantidade, carteira[i].precoCompra, carteira[i].precoAtual);
    }

    fclose(arquivo);
}

void cadastrarAtivo(Ativo carteira[], int *quantidadeAtivos) {
    Ativo novoAtivo;
    
    limparTela();

    if (*quantidadeAtivos >= MAX_ATIVOS) {
        printf("A carteira atingiu o limite de %d ativos.\n", MAX_ATIVOS);
        pausar();
        return;
    }

    printf("\n========== CADASTRO DE ATIVO ==========\n\n");
    lerTexto("Nome: ", novoAtivo.nome, TAM_NOME);
    lerTexto("Categoria: ", novoAtivo.categoria, TAM_CATEGORIA);
    novoAtivo.quantidade = lerInteiro("Quantidade: ", 1, MAX_INTEIRO);
    novoAtivo.precoCompra = lerNumero("Preço de compra por unidade: ", false);
    novoAtivo.precoAtual = lerNumero("Preço atual por unidade: ", true);

    carteira[*quantidadeAtivos] = novoAtivo;
    (*quantidadeAtivos)++;

    salvarCarteira(carteira, *quantidadeAtivos);
    printf("\nAtivo cadastrado com sucesso!\n\n");
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

void bubbleSortPorRentabilidade(Ativo carteira[], int quantidadeAtivos) {
    int i, j;
    Ativo troca;

    for (i = 0; i < quantidadeAtivos - 1; i++) {
        for (j = 0; j < quantidadeAtivos - 1 - i; j++) {

            if (calcularRentabilidadeAtivo(carteira[j]) <
                calcularRentabilidadeAtivo(carteira[j + 1])) {

                troca = carteira[j];
                carteira[j] = carteira[j + 1];
                carteira[j + 1] = troca;
            }
        }
    }
}

void ordenarCarteiraPorRentabilidade(Ativo carteira[], int quantidadeAtivos) {
    limparTela();
    printf("========== CARTEIRA ORDENADA POR RENTABILIDADE ==========\n\n");

    if (quantidadeAtivos == 0) {
        printf("Nenhum ativo cadastrado.\n\n");
        return;
    }

    bubbleSortPorRentabilidade(carteira, quantidadeAtivos);
    listarAtivos(carteira, quantidadeAtivos);
    salvarCarteira(carteira, quantidadeAtivos);
    
    printf("Carteira ordenada por rentabilidade com sucesso!\n\n");
}

double simularValor(double valorInicial, double taxaMensal) {
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
    printf("investidos por %d meses em cada opção?\n\n", MESES_SIMULACAO);
    printf("POUPANÇA       (%.2f%%/mês): R$ %.2f (+R$ %.2f)\n", TAXA_POUPANCA * 100.0, valorPoupanca, valorPoupanca - valorInicial);
    printf("TESOURO SELIC  (%.2f%%/mês): R$ %.2f (+R$ %.2f)\n", TAXA_TESOURO_SELIC * 100.0, valorTesouro, valorTesouro - valorInicial);
    printf("CDB            (%.2f%%/mês): R$ %.2f (+R$ %.2f)\n\n", TAXA_CDB * 100.0, valorCdb, valorCdb - valorInicial);

    printf("O que isso significa?\n");
    printf("- Poupança: é conhecida e costuma render menos.\n");
    printf("- Tesouro Selic: é um título público de baixo risco e permite\n");
    printf("  investir valores acessíveis. Confira as regras vigentes.\n");
    printf("- CDB: pode render mais, tem cobertura do FGC dentro dos limites\n");
    printf("  aplicáveis, mas alguns produtos exigem esperar até o vencimento.\n");
    printf("As taxas acima são ilustrativas e não são recomendação de investimento.\n\n");
}

void gerarRelatorioFinal(Ativo carteira[], int quantidadeAtivos) {
    double custoTotal = 0.0;
    double valorAtualTotal;
    double lucroPrejuizo;
    int i;

    limparTela();
    printf("================ RELATÓRIO FINAL ================\n\n");

    if (quantidadeAtivos == 0) {
        printf("Nenhum ativo cadastrado.\n\n");
        return;
    }

    bubbleSortPorRentabilidade(carteira, quantidadeAtivos);

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
    printf("Assim, contribui para a inclusão financeira relacionada ao ODS 8.10 da ONU,\n");
    printf("que incentiva o acesso a serviços financeiros para todas as pessoas.\n\n");

    salvarCarteira(carteira, quantidadeAtivos);
}

char *classificarRisco(double rentabilidade) {
    if (rentabilidade < -10.0) {
        return "Alto";
    }

    if (rentabilidade < 0.0) {
        return "Atenção";
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
    printf("\n========== LISTA DE ATIVOS ==========\n\n");

    if (quantidadeAtivos == 0) {
        printf("Nenhum ativo cadastrado.\n\n");
        return;
    }

    for (i = 0; i < quantidadeAtivos; i++) {
        valorAtual = carteira[i].quantidade * carteira[i].precoAtual;
        rentabilidade = calcularRentabilidadeAtivo(carteira[i]);

        printf("%d. %s - %s - %d unidades - R$ %.2f\n", i + 1, carteira[i].nome, carteira[i].categoria, carteira[i].quantidade, carteira[i].precoAtual);
        printf("Valor atual: R$ %.2f\nRentabilidade: %.2f%%\n", valorAtual, rentabilidade);
        printf("Classificação de risco: %s\n\n", classificarRisco(rentabilidade));
    }

	printf("==================================================\n");
	printf("| Valor total da carteira: R$ %-13.2f      |\n", calcularValorTotal(carteira, quantidadeAtivos));
	printf("|                                                |\n");
	printf("| Rentabilidade geral:        %-7.2f%%           |\n", calcularRentabilidadeGeral(carteira, quantidadeAtivos));
	printf("==================================================\n\n");
}
