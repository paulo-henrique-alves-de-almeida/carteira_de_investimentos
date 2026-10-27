#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

/* Auxiliar interna: le uma linha inteira e rejeita textos longos ou vazios. */
static void lerTexto(const char mensagem[], char texto[], int tamanho)
{
    int caractere;
    int i;
    int temConteudo;

    while (1) {
        printf("%s", mensagem);
        if (fgets(texto, tamanho, stdin) == NULL) {
            printf("\nEntrada encerrada.\n");
            exit(EXIT_SUCCESS);
        }

        if (strchr(texto, '\n') == NULL) {
            caractere = getchar();
            if (caractere != '\n' && caractere != EOF) {
                while (caractere != '\n' && caractere != EOF) {
                    caractere = getchar();
                }
                printf("Entrada muito longa. Limite: %d caracteres.\n", tamanho - 1);
                continue;
            }
        }

        texto[strcspn(texto, "\r\n")] = '\0';
        temConteudo = 0;
        for (i = 0; texto[i] != '\0'; i++) {
            if (!isspace((unsigned char) texto[i])) {
                temConteudo = 1;
            }
        }
        if (temConteudo) {
            return;
        }
        printf("O campo nao pode ficar vazio.\n");
    }
}

/* O caractere extra permite rejeitar entradas como 25abc ou 25,50. */
static double lerNumero(const char mensagem[], int aceitaZero)
{
    char entrada[100];
    char extra;
    double valor;

    while (1) {
        lerTexto(mensagem, entrada, sizeof(entrada));
        if (sscanf(entrada, "%lf %c", &valor, &extra) == 1 && isfinite(valor)) {
            if (valor > 0.0 || (aceitaZero && valor == 0.0)) {
                return valor;
            }
        }
        printf("Digite um numero %s, usando ponto para decimais.\n",
               aceitaZero ? "maior ou igual a zero" : "maior que zero");
    }
}

void exibirMenu(void)
{
    printf("\n=== Carteira de Investimentos ===\n");
    printf("1. Cadastrar ativo\n");
    printf("2. Ver rentabilidade e lucro/prejuizo\n");
    printf("3. Classificar risco\n");
    printf("4. Sair\n");
}

int lerOpcao(void)
{
    char entrada[100];
    char opcao;
    char extra;

    lerTexto("Opcao: ", entrada, sizeof(entrada));
    if (sscanf(entrada, " %c %c", &opcao, &extra) == 1 &&
        opcao >= '1' && opcao <= '4') {
        return opcao - '0';
    }
    return 0;
}

void cadastrarAtivo(char nome[], char categoria[], double *quantidade,
                    double *precoCompra, double *precoAtual)
{
    printf("\nCadastro de um unico ativo (substitui o anterior).\n");
    lerTexto("Nome: ", nome, TAM_NOME);
    lerTexto("Categoria: ", categoria, TAM_CATEGORIA);
    /* Ponteiros permitem atualizar as variaveis declaradas na main. */
    *quantidade = lerNumero("Quantidade: ", 0);
    *precoCompra = lerNumero("Preco de compra: ", 0);
    *precoAtual = lerNumero("Preco atual: ", 1);
    printf("Ativo cadastrado com sucesso.\n");
}

double calcularRentabilidade(double precoCompra, double precoAtual)
{
    /* O cadastro garante precoCompra > 0, evitando divisao por zero. */
    return (precoAtual - precoCompra) / precoCompra * 100.0;
}

double calcularLucro(double precoCompra, double precoAtual, double quantidade)
{
    return (precoAtual - precoCompra) * quantidade;
}

void exibirResultados(const char nome[], const char categoria[],
                      double quantidade, double precoCompra, double precoAtual)
{
    double rentabilidade = calcularRentabilidade(precoCompra, precoAtual);
    double lucro = calcularLucro(precoCompra, precoAtual, quantidade);

    printf("\nAtivo: %s | Categoria: %s\n", nome, categoria);
    printf("Quantidade: %.2f\n", quantidade);
    printf("Rentabilidade: %.2f%%\n", rentabilidade);
    if (lucro > 0.0) {
        printf("Lucro: R$ %.2f\n", lucro);
    } else if (lucro < 0.0) {
        printf("Prejuizo: R$ %.2f\n", -lucro);
    } else {
        printf("Sem lucro ou prejuizo: R$ 0.00\n");
    }
}

void classificarRisco(double rentabilidade)
{
    /* Regra didatica baseada somente na variacao do preco. */
    if (rentabilidade < -10.0) {
        printf("Risco: Alto - rentabilidade abaixo de -10%%.\n");
    } else if (rentabilidade < 0.0) {
        printf("Risco: Atencao - rentabilidade negativa entre -10%% e 0%% (exclusive).\n");
    } else if (rentabilidade == 0.0) {
        printf("Risco: Rentabilidade neutra.\n");
    } else {
        printf("Risco: Rentabilidade positiva.\n");
    }
}

void sair(void)
{
    printf("Programa encerrado. Ate logo!\n");
}
