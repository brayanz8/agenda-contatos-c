#include <stdio.h>    
#include <string.h>   
#include <stdlib.h> 

#define MAXIMO  100
#define ARQUIVO "agenda.dat"


typedef struct {
    char nome[50];
    char telefone[20];
    char email[50];
} Contato;


Contato agenda[MAXIMO];
int total = 0;


void pausar(void);
void salvar(void);
void carregar(void);
void incluir(void);
void listar(void);
void consultar(void);
void excluir(void);
void buscarParcial(void);


void pausar(void) {
    printf("\n  Pressione Enter para continuar...");
    fflush(stdin);
    getchar();
}

void salvar(void) {
    FILE *f;
    f = fopen(ARQUIVO, "wb");
    if (f == NULL) {
        printf("\n  Erro ao salvar!\n");
        return;
    }
    fwrite(&total, sizeof(int),     1,     f);
    fwrite(agenda, sizeof(Contato), total, f);
    fclose(f);
}

void carregar(void) {
    FILE *f;
    f = fopen(ARQUIVO, "rb");
    if (f == NULL) return;
    fread(&total, sizeof(int),     1,     f);
    fread(agenda, sizeof(Contato), total, f);
    fclose(f);
}


void incluir(void) {
    int pos;

    system("cls");

    if (total >= MAXIMO) {
        printf("\n  Agenda cheia!\n");
        pausar();
        return;
    }

    pos = total;

    printf("\n  --- INCLUIR CONTATO ---\n\n");

    printf("  Nome: ");
    fflush(stdin);
    fgets(agenda[pos].nome, 50, stdin);
    agenda[pos].nome[strlen(agenda[pos].nome) - 1] = '\0';

    printf("  Telefone: ");
    fflush(stdin);
    fgets(agenda[pos].telefone, 20, stdin);
    agenda[pos].telefone[strlen(agenda[pos].telefone) - 1] = '\0';

    printf("  Email (opcional): ");
    fflush(stdin);
    fgets(agenda[pos].email, 50, stdin);
    agenda[pos].email[strlen(agenda[pos].email) - 1] = '\0';

    total++;
    salvar();

    printf("\n  Contato incluido com sucesso!\n");
    pausar();
}


void listar(void) {
    int i;

    system("cls");

    if (total == 0) {
        printf("\n  Nenhum contato cadastrado!\n");
        pausar();
        return;
    }

    printf("\n  --- LISTA (%d contato(s)) ---\n\n", total);

    for (i = 0; i < total; i++) {
        printf("  [%d] Nome: %s\n", i + 1, agenda[i].nome);
        printf("      Tel:  %s\n", agenda[i].telefone);
        if (strlen(agenda[i].email) > 0) {
            printf("      Email: %s\n", agenda[i].email);
        }
        printf("  ----------------------------\n");
    }

    pausar();
}


void consultar(void) {
    char nomeBusca[50];
    int i;
    int achou = 0;

    system("cls");

    if (total == 0) {
        printf("\n  Nenhum contato cadastrado!\n");
        pausar();
        return;
    }

    printf("\n  --- CONSULTAR CONTATO ---\n\n");

    printf("  Nome: ");
    fflush(stdin);
    fgets(nomeBusca, 50, stdin);
    nomeBusca[strlen(nomeBusca) - 1] = '\0';

    printf("\n");

    for (i = 0; i < total; i++) {
        if (strcmp(agenda[i].nome, nomeBusca) == 0) {
            achou = 1;
            printf("  Nome: %s\n", agenda[i].nome);
            printf("  Tel:  %s\n", agenda[i].telefone);
            if (strlen(agenda[i].email) > 0) {
                printf("  Email: %s\n", agenda[i].email);
            }
            printf("  ----------------------------\n");
        }
    }

    if (achou == 0) {
        printf("  Contato nao encontrado!\n");
    }

    pausar();
}

void excluir(void) {
    char nomeBusca[50];
    char confirma;
    int i;
    int j;
    int achou = 0;

    system("cls");

    if (total == 0) {
        printf("\n  Nenhum contato cadastrado!\n");
        pausar();
        return;
    }

    printf("\n  --- EXCLUIR CONTATO ---\n\n");

    printf("  Nome: ");
    fflush(stdin);
    fgets(nomeBusca, 50, stdin);
    nomeBusca[strlen(nomeBusca) - 1] = '\0';

    for (i = 0; i < total; i++) {
        if (strcmp(agenda[i].nome, nomeBusca) == 0) {
            achou = 1;
            printf("\n  Encontrado: %s | Tel: %s\n", agenda[i].nome, agenda[i].telefone);
            printf("  Confirmar exclusao? (s/n): ");
            fflush(stdin);
            scanf("%c", &confirma);

            if (confirma == 's' || confirma == 'S') {
                for (j = i; j < total - 1; j++) {
                    agenda[j] = agenda[j + 1];
                }
                total--;
                i--;
                salvar();
                printf("\n  Excluido com sucesso!\n");
            } else {
                printf("\n  Exclusao cancelada.\n");
            }
        }
    }

    if (achou == 0) {
        printf("\n  Contato nao encontrado!\n");
    }

    pausar();
}

void buscarParcial(void) {
    char parte[50];
    int i;
    int achou = 0;

    system("cls");

    if (total == 0) {
        printf("\n  Nenhum contato cadastrado!\n");
        pausar();
        return;
    }

    printf("\n  --- BUSCA PARCIAL ---\n\n");

    printf("  Parte do nome: ");
    fflush(stdin);
    fgets(parte, 50, stdin);
    parte[strlen(parte) - 1] = '\0';

    printf("\n");

    for (i = 0; i < total; i++) {
        if (strstr(agenda[i].nome, parte) != NULL) {
            achou++;
            printf("  [%d] %s | Tel: %s\n", achou, agenda[i].nome, agenda[i].telefone);
        }
    }

    if (achou == 0) {
        printf("  Nenhum resultado encontrado!\n");
    } else {
        printf("\n  %d resultado(s) encontrado(s).\n", achou);
    }

    pausar();
}

int main(void) {
    int opcao = 0;

    carregar();

    do {
        system("cls");
        printf("  ================================\n");
        printf("     AGENDA DE CONTATOS\n");
        printf("  ================================\n");
        printf("\n  Contatos cadastrados: %d\n\n", total);
        printf("  1 - Incluir contato\n");
        printf("  2 - Listar contatos\n");
        printf("  3 - Consultar pelo nome\n");
        printf("  4 - Excluir contato\n");
        printf("  5 - Busca parcial  [BONUS]\n");
        printf("  6 - Sair\n");
        printf("\n  Opcao: ");

        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 1: incluir();       break;
            case 2: listar();        break;
            case 3: consultar();     break;
            case 4: excluir();       break;
            case 5: buscarParcial(); break;
            case 6:
                printf("\n  Ate logo!\n\n");
                break;
            default:
                printf("\n  Opcao invalida!\n");
                pausar();
                break;
        }

    } while (opcao != 6);

    return 0;
}