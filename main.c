#include <stdio.h>
#include "funcoes.h"

int main(void)
{
    /* Estes vetores guardam textos, nao uma lista de ativos. */
    char nome[TAM_NOME] = "";
    char categoria[TAM_CATEGORIA] = "";
    double quantidade = 0.0;
    double precoCompra = 0.0;
    double precoAtual = 0.0;
    int cadastrado = 0;
    int opcao = 0;

    while (opcao != 4) {
        exibirMenu();
        opcao = lerOpcao();

        switch (opcao) {
            case 1:
                cadastrarAtivo(nome, categoria, &quantidade,
                               &precoCompra, &precoAtual);
                cadastrado = 1;
                break;
            case 2:
                if (cadastrado) {
                    exibirResultados(nome, categoria, quantidade,
                                     precoCompra, precoAtual);
                } else {
                    printf("Cadastre um ativo primeiro.\n");
                }
                break;
            case 3:
                if (cadastrado) {
                    classificarRisco(calcularRentabilidade(precoCompra, precoAtual));
                } else {
                    printf("Cadastre um ativo primeiro.\n");
                }
                break;
            case 4:
                sair();
                break;
            default:
                printf("Opcao invalida. Digite um numero de 1 a 4.\n");
        }
    }

    return 0;
}
