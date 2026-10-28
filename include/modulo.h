#ifndef MODULO_H
#define MODULO_H

#define TAM_NOME 100
#define TAM_CATEGORIA 50
#define MAX_ATIVOS 100
#define MAX_INTEIRO 2147483647
#define ARQUIVO_CARTEIRA "data/carteira.txt"

typedef struct {
    char nome[TAM_NOME];
    char categoria[TAM_CATEGORIA];
    int quantidade;
    double precoCompra;
    double precoAtual;
} Ativo;

void carregarCarteira(Ativo carteira[], int *quantidadeAtivos);
void salvarCarteira(Ativo carteira[], int quantidadeAtivos);
void cadastrarAtivo(Ativo carteira[], int *quantidadeAtivos);
void listarAtivos(Ativo carteira[], int quantidadeAtivos);
double calcularValorTotal(Ativo carteira[], int quantidadeAtivos);
double calcularRentabilidadeAtivo(Ativo ativo);
double calcularRentabilidadeGeral(Ativo carteira[], int quantidadeAtivos);
char *classificarRisco(double rentabilidade);

#endif
