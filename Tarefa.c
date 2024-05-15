#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void adicionar_tarefa() {
    char data[11]; // Considerando o formato DD/MM/AAAA
    char descricao[100]; // Ajuste o tamanho conforme necessário

    printf("Digite a data da tarefa (DD/MM/AAAA): ");
    scanf("%s", data);
    getchar(); // Limpa o buffer do teclado

    printf("Digite a descrição da tarefa: ");
    fgets(descricao, sizeof(descricao), stdin);

    FILE *arquivo = fopen("tarefas.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    fprintf(arquivo, "%s: %s\n", data, descricao);
    fclose(arquivo);

    printf("Tarefa adicionada com sucesso!\n");
}

void mostrar_tarefas_por_data(char *data) {
    FILE *arquivo = fopen("tarefas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    char linha[150]; // Ajuste o tamanho conforme necessário
    int encontrou = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strstr(linha, data) != NULL) {
            printf("%s", linha);
            encontrou = 1;
        }
    }

    fclose(arquivo);

    if (!encontrou) {
        printf("Nenhuma tarefa agendada para a data %s\n", data);
    }
}

void apagar_tarefa_por_data(char *data) {
    FILE *arquivo_leitura = fopen("tarefas.txt", "r");
    if (arquivo_leitura == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    FILE *arquivo_temp = fopen("temp.txt", "w");
    if (arquivo_temp == NULL) {
        printf("Erro ao abrir o arquivo temporário.\n");
        exit(1);
    }

    char linha[150]; // Ajuste o tamanho conforme necessário
    int encontrou = 0;

    while (fgets(linha, sizeof(linha), arquivo_leitura)) {
        if (strstr(linha, data) == NULL) {
            fprintf(arquivo_temp, "%s", linha);
        } else {
            encontrou = 1;
        }
    }

    fclose(arquivo_leitura);
    fclose(arquivo_temp);

    if (!encontrou) {
        printf("Nenhuma tarefa encontrada para a data %s\n", data);
    } else {
        remove("tarefas.txt");
        rename("temp.txt", "tarefas.txt");
        printf("Tarefas para a data %s foram apagadas com sucesso!\n", data);
    }
}

int main() {
    while (1) {
        printf("\n=== Sistema de Arquivamento de Tarefas ===\n");
        printf("1. Adicionar Tarefa\n");
        printf("2. Verificar Tarefas por Data\n");
        printf("3. Apagar Tarefa por Data\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");

        int escolha;
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer do teclado

        switch (escolha) {
            case 1:
                adicionar_tarefa();
                break;
            case 2: {
                char data[11];
                printf("Digite a data para verificar as tarefas (DD/MM/AAAA): ");
                scanf("%s", data);
                getchar(); // Limpa o buffer do teclado
                mostrar_tarefas_por_data(data);
                break;
            }
            case 3: {
                char data[11];
                printf("Digite a data para apagar as tarefas (DD/MM/AAAA): ");
                scanf("%s", data);
                getchar(); // Limpa o buffer do teclado
                apagar_tarefa_por_data(data);
                break;
            }
            case 4:
                printf("Saindo do programa...\n");
                return 0;
            default:
                printf("Opção inválida. Por favor, escolha novamente.\n");
        }
    }

    return 0;
}

