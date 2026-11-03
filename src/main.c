#include <locale.h>
#include <stdio.h>

#include "funcoes.h"
#include "modulo.h"

int main(void)
{
    Ativo carteira[MAX_ATIVOS];
    int quantidadeAtivos = 0;
    int opcao;

    setlocale(LC_ALL, "");

    carregarCarteira(carteira, &quantidadeAtivos);

    do
    {
        exibirMenu();
        opcao = lerOpcao();

        switch (opcao)
        {
        case 1:
            cadastrarAtivo(carteira, &quantidadeAtivos);
            pausar();
            break;

        case 2:
            listarAtivos(carteira, quantidadeAtivos);
            pausar();
            break;

        case 3:
            imprimirTitulo();

            if (quantidadeAtivos == 0)
            {
                printf("A carteira está vazia. Cadastre um ativo primeiro.\n\n");
                pausar();
                continue;
            }

            printf("Valor total da carteira: R$ %.2f\n\n", calcularValorTotal(carteira, quantidadeAtivos));
            pausar();
            break;

        case 4:
            imprimirTitulo();

            if (quantidadeAtivos == 0)
            {
                printf("A carteira está vazia. Cadastre um ativo primeiro.\n\n");
                pausar();
                continue;
            }

            printf("Rentabilidade geral da carteira: %.2f%%\n\n", calcularRentabilidadeGeral(carteira, quantidadeAtivos));
            pausar();
            break;

        case 5:
            ordenarCarteiraPorRentabilidade(carteira, quantidadeAtivos);
            pausar();
            break;

        case 6:
            simularInvestimentos(carteira, quantidadeAtivos);
            pausar();
            break;

        case 7:
            gerarRelatorioFinal(carteira, quantidadeAtivos);
            pausar();
            break;

        case 0:
            salvarCarteira(carteira, quantidadeAtivos);
            sair();
            break;

        default:
            printf("\nOpcao invalida. Digite uma opcao entre 0 e 7.\n\n");
            pausar();
        }
    } while (opcao != 0);

    return 0;
}
