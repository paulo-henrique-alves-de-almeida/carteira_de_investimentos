#include <locale.h>
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "funcoes.h"
#include "modulo.h"

int main(void)
{
    Ativo carteira[MAX_ATIVOS];
    int quantidadeAtivos = 0;
    int opcao;

    setlocale(LC_ALL, "");

#ifdef _WIN32
    // Acentos em escapes numericos para evitar conversao ao salvar no Dev-C++.
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
#endif

    carregarCarteira(carteira, &quantidadeAtivos);

    do {
        exibirMenu();
        opcao = lerOpcao();

        switch (opcao) {
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

            if (quantidadeAtivos == 0) {
                printf("A carteira est\341 vazia. Cadastre um ativo primeiro.\n\n");
                pausar();
                continue;
            }

            printf("Valor total da carteira: R$ %.2f\n\n", calcularValorTotal(carteira, quantidadeAtivos));
            pausar();
            break;

        case 4:
            imprimirTitulo();

            if (quantidadeAtivos == 0) {
                printf("A carteira est\341 vazia. Cadastre um ativo primeiro.\n\n");
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
            printf("\nOp\347\343o inv\341lida. Digite uma op\347\343o entre 0 e 7.\n\n");
            pausar();
        }
    } while (opcao != 0);

    return 0;
}
