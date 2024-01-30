#ifndef EMAIL_H
#define EMAIL_H

typedef struct Email {
    char* mensagem;
    int prioridade;
} Email;

typedef struct Usuario {
    char* nome;
    Email* caixa_entrada;
    int capacidade_caixa;
} Usuario;

typedef struct SistemaDeEmail {
    Usuario** usuarios;
    int num_usuarios;
} SistemaDeEmail;

SistemaDeEmail* criar_sistema();
void destruir_sistema(SistemaDeEmail* sistema);
void cadastrar_usuario(SistemaDeEmail* sistema, const char* nome);
void remover_usuario(SistemaDeEmail* sistema, const char* nome);
void entregar_email(SistemaDeEmail* sistema, const char* destinatario, const char* mensagem, int prioridade);
void consultar_email(SistemaDeEmail* sistema, const char* destinatario);
void exibir_menu();
#endif
