#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdbool.h>

void lerTexto(char mensagem[], char texto[], int tamanho);
double lerNumero(char mensagem[], bool aceitaZero);
int lerInteiro(char mensagem[], int minimo, int maximo);
void limparTela(void);
void pausar(void);
void imprimirTitulo(void);
void exibirMenu(void);
int lerOpcao(void);
void sair(void);

#endif
