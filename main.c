#include "email.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    SistemaDeEmail* sistema = criar_sistema();

    int opcao;
    char usuario[50];
    char mensagem[50];
    int prioridade;

    while (1) {
        exibir_menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o nome do usuário: ");
                scanf("%s", usuario);
                cadastrar_usuario(sistema, usuario);
                break;
            case 2:
                printf("Digite o nome do destinatário: ");
                scanf("%s", usuario);
                printf("Digite a mensagem: ");
                scanf("%s", mensagem);
                printf("Digite a prioridade: ");
                scanf("%d", &prioridade);
                entregar_email(sistema, usuario, mensagem, prioridade);
                break;
            case 3:
                printf("Digite o nome do usuário: ");
                scanf("%s", usuario);
                consultar_email(sistema, usuario);
                break;
            case 4:
                printf("Digite o nome do usuário: ");
                scanf("%s", usuario);
                remover_usuario(sistema, usuario);
                break;
            case 5:
                destruir_sistema(sistema);
                printf("Programa encerrado.\n");
                return 0;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}
