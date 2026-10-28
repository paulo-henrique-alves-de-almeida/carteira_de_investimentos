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
    novoAtivo.precoCompra = lerNumero("Preço de compra por unidade: ", false);
    novoAtivo.precoAtual = lerNumero("Preço atual por unidade: ", true);

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
        printf("Classificação de risco: %s\n\n", classificarRisco(rentabilidade));
    }

	printf("======================================\n");
    printf("| Valor total da carteira: R$ %.2f \n", calcularValorTotal(carteira, quantidadeAtivos));
    printf("| \n");
    printf("| Rentabilidade geral: %.2f%% \n", calcularRentabilidadeGeral(carteira, quantidadeAtivos));
    printf("======================================\n\n");
}
