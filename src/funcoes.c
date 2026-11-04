#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <errno.h>
#include <math.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "funcoes.h"

void limparTela() {
	#ifdef _WIN32
	    system("cls");
	    SetConsoleOutputCP(1252);
	    SetConsoleCP(1252);
	#else
	    system("clear");
	#endif
}

void pausar() {
	#ifdef _WIN32
	    system("pause");
	#else
	    printf("\nPressione ENTER para continuar...");
	    getchar();
	#endif
}

void lerTexto(char mensagem[], char texto[], int tamanho) {
    int caractere;
    size_t comprimento;
    bool temConteudo;
    int i;

    while (true) {
        printf("%s", mensagem);

        if (fgets(texto, tamanho, stdin) == NULL) {
            texto[0] = '\0';
            return;
        }

        comprimento = strlen(texto);
        if (comprimento > 0 && texto[comprimento - 1] != '\n') {
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

        // o formato do arquivo usa ponto e virgula como separador
        if (strchr(texto, ';') != NULL) {
            printf("N\343o use ponto e v\355rgula (;) no texto.\n");
            continue;
        }

        temConteudo = false;
        for (i = 0; texto[i] != '\0'; i++) {
            if (!isspace((unsigned char) texto[i])) {
                temConteudo = true;
                break;
            }
        }

        if (temConteudo) {
            return;
        }

        printf("O campo n\343o pode ficar vazio.\n");
    }
}

double lerNumero(char mensagem[], bool aceitaZero) {
    char entrada[100];
    char extra;
    double valor;

    while (true) {
        lerTexto(mensagem, entrada, sizeof(entrada));

        if (sscanf(entrada, "%lf %c", &valor, &extra) == 1 &&
            isfinite(valor) &&
            (valor > 0.0 || (aceitaZero && valor == 0.0))) {
            return valor;
        }

        if (aceitaZero) {
            printf("Digite um n\372mero maior ou igual a zero, usando ponto para decimais.\n");
        } else {
            printf("Digite um n\372mero maior que zero, usando ponto para decimais.\n");
        }
    }
}

int lerInteiro(char mensagem[], int minimo, int maximo) {
    char entrada[100];
    char extra;
    int valor;

    while (true) {
        lerTexto(mensagem, entrada, sizeof(entrada));

        if (sscanf(entrada, "%d %c", &valor, &extra) == 1 && valor >= minimo && valor <= maximo) {
            return valor;
        }

        printf("Digite um n\372mero inteiro entre %d e %d.\n", minimo, maximo);
    }
}

void imprimirTitulo() {
    limparTela();
    
    printf("===============================================================\n");
    printf("================ CARTEIRA DE INVESTIMENTOS ====================\n");
    printf("===============================================================\n\n");
}

void exibirMenu() {
    imprimirTitulo();
    
    printf("[1] Cadastrar ativo\n");
    printf("[2] Listar ativos\n");
    printf("[3] Valor total da carteira\n");
    printf("[4] Rentabilidade geral\n");
    printf("[5] Ordenar carteira por rentabilidade\n");
    printf("[6] Simulador educativo\n");
    printf("[7] Relat\363rio final\n");
    printf("[0] Salvar e sair\n\n");
}

int lerOpcao() {
	char entrada[100];
    char extra;
    int valor;
    
	lerTexto("Op\347\343o: ", entrada, sizeof(entrada));
	
	if (sscanf(entrada, "%d %c", &valor, &extra) == 1 && valor >= 0 && valor <= 7) {
        return valor;
    }
    
    return -1;
}

void sair() {
    imprimirTitulo();
    
    printf("Dados salvos. Bons investimentos!\n");
}
