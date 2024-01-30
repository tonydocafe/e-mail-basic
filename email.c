#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "email.h"

SistemaDeEmail* criar_sistema() {
    SistemaDeEmail* sistema = (SistemaDeEmail*)malloc(sizeof(SistemaDeEmail));
    sistema->usuarios = NULL;
    sistema->num_usuarios = 0;
    return sistema;
}

void destruir_sistema(SistemaDeEmail* sistema) {
    if (sistema) {
        for (int i = 0; i < sistema->num_usuarios; i++) {
            free(sistema->usuarios[i]->nome);
            free(sistema->usuarios[i]->caixa_entrada);
            free(sistema->usuarios[i]);
        }
        free(sistema->usuarios);
        free(sistema);
    }
}

void cadastrar_usuario(SistemaDeEmail* sistema, const char* nome) {
    if (!sistema) return;

    for (int i = 0; i < sistema->num_usuarios; i++) {
        if (strcmp(sistema->usuarios[i]->nome, nome) == 0) {
            printf("Erro: O usuário %s já existe.\n", nome);
            return;
        }
    }

    sistema->num_usuarios++;
    sistema->usuarios = (Usuario**)realloc(sistema->usuarios, sistema->num_usuarios * sizeof(Usuario*));

    Usuario* novo_usuario = (Usuario*)malloc(sizeof(Usuario));
    novo_usuario->nome = strdup(nome);
    novo_usuario->caixa_entrada = NULL;
    novo_usuario->capacidade_caixa = 0;

    sistema->usuarios[sistema->num_usuarios - 1] = novo_usuario;

    printf("Usuário %s cadastrado com sucesso.\n", nome);
}

void remover_usuario(SistemaDeEmail* sistema, const char* nome) {
    if (!sistema) return;

    int indice_usuario = -1;
    for (int i = 0; i < sistema->num_usuarios; i++) {
        if (strcmp(sistema->usuarios[i]->nome, nome) == 0) {
            indice_usuario = i;
            break;
        }
    }

    if (indice_usuario != -1) {
        free(sistema->usuarios[indice_usuario]->nome);
        free(sistema->usuarios[indice_usuario]->caixa_entrada);
        free(sistema->usuarios[indice_usuario]);

        for (int i = indice_usuario; i < sistema->num_usuarios - 1; i++) {
            sistema->usuarios[i] = sistema->usuarios[i + 1];
        }

        sistema->num_usuarios--;
        sistema->usuarios = (Usuario**)realloc(sistema->usuarios, sistema->num_usuarios * sizeof(Usuario*));

        printf("Usuário %s removido com sucesso.\n", nome);
    } else {
        printf("Erro: O usuário %s não existe.\n", nome);
    }
}

void entregar_email(SistemaDeEmail* sistema, const char* destinatario, const char* mensagem, int prioridade) {
    if (!sistema) return;

    int indice_usuario = -1;
    for (int i = 0; i < sistema->num_usuarios; i++) {
        if (strcmp(sistema->usuarios[i]->nome, destinatario) == 0) {
            indice_usuario = i;
            break;
        }
    }

    if (indice_usuario != -1) {
        Usuario* usuario = sistema->usuarios[indice_usuario];

        usuario->capacidade_caixa++;
        usuario->caixa_entrada = (Email*)realloc(usuario->caixa_entrada, usuario->capacidade_caixa * sizeof(Email));

        Email novo_email;
        novo_email.mensagem = strdup(mensagem);
        novo_email.prioridade = prioridade;

        usuario->caixa_entrada[usuario->capacidade_caixa - 1] = novo_email;

        // Ordenar caixa de entrada por prioridade e tempo de recebimento
        for (int i = usuario->capacidade_caixa - 1; i > 0; i--) {
            if (usuario->caixa_entrada[i].prioridade > usuario->caixa_entrada[i - 1].prioridade ||
                (usuario->caixa_entrada[i].prioridade == usuario->caixa_entrada[i - 1].prioridade &&
                 strlen(usuario->caixa_entrada[i].mensagem) > strlen(usuario->caixa_entrada[i - 1].mensagem))) {
                Email temp = usuario->caixa_entrada[i];
                usuario->caixa_entrada[i] = usuario->caixa_entrada[i - 1];
                usuario->caixa_entrada[i - 1] = temp;
            } else {
                break;
            }
        }

        printf("Email entregue com sucesso para %s.\n", destinatario);
    } else {
        printf("Erro: O usuário %s não existe. Email não entregue.\n", destinatario);
    }
}

void consultar_email(SistemaDeEmail* sistema, const char* destinatario) {
    if (!sistema) return;

    int indice_usuario = -1;
    for (int i = 0; i < sistema->num_usuarios; i++) {
        if (strcmp(sistema->usuarios[i]->nome, destinatario) == 0) {
            indice_usuario = i;
            break;
        }
    }

    if (indice_usuario != -1) {
        Usuario* usuario = sistema->usuarios[indice_usuario];

        if (usuario->capacidade_caixa > 0) {
            printf("Próxima mensagem para %s: %s\n", destinatario, usuario->caixa_entrada[0].mensagem);

            // Remover mensagem da caixa de entrada
            free(usuario->caixa_entrada[0].mensagem);
            for (int i = 0; i < usuario->capacidade_caixa - 1; i++) {
                usuario->caixa_entrada[i] = usuario->caixa_entrada[i + 1];
            }
            usuario->capacidade_caixa--;
            usuario->caixa_entrada = (Email*)realloc(usuario->caixa_entrada, usuario->capacidade_caixa * sizeof(Email));
        } else {
            printf("A caixa de entrada de %s está vazia.\n", destinatario);
        }
    } else {
        printf("Erro: O usuário %s não existe.\n", destinatario);
    }
}

void exibir_menu() {
    printf("\nMenu:\n");
    printf("1. Cadastrar Usuário\n");
    printf("2. Entregar E-mail\n");
    printf("3. Consultar E-mails\n");
    printf("4. Remover Usuário\n");
    printf("5. Sair\n");
    printf("Escolha uma opção: ");
}
