#ifndef FUNCOES_H
#define FUNCOES_H

#define TAM_NOME 80
#define TAM_CATEGORIA 40

void exibirMenu(void);
int lerOpcao(void);
void cadastrarAtivo(char nome[], char categoria[], double *quantidade,
                    double *precoCompra, double *precoAtual);
double calcularRentabilidade(double precoCompra, double precoAtual);
double calcularLucro(double precoCompra, double precoAtual, double quantidade);
void exibirResultados(const char nome[], const char categoria[],
                      double quantidade, double precoCompra, double precoAtual);
void classificarRisco(double rentabilidade);
void sair(void);

#endif
