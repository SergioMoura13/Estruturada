#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USUARIOS 1000
#define TAM_NOME 100
#define TAM_EMAIL 100

typedef struct {
    char nome[TAM_NOME];
    int idade;
    char email[TAM_EMAIL];
    char sexo[TAM_EMAIL];
    char endereco[TAM_EMAIL];
    double altura;
    int vacina;
} Usuario;

Usuario usuarios[MAX_USUARIOS];
int numUsuarios = 0;

void menu() {
    printf("1 - Adicionar Usuario\n");
    printf("2 - Editar Usuarios\n");
    printf("3 - Excluir Usuarios\n");
    printf("4 - Exibir Usuarios\n");
    printf("5 - Fechar Programa\n");
    printf("6 - Realizar Backup\n");
    printf("7 - Fazer busca por email\n");
}

bool validarSexo(const char *sexo) {
    if (strcmp(sexo, "Feminino") == 0 || strcmp(sexo, "Masculino") == 0 || strcmp(sexo, "Indiferente") == 0) {
        return true;
    }
    return false;
}

bool validarVacina(int valor) {
    if (valor == 0 || valor == 1) {
        return true;
    }
    return false;
}

void incluirUsuario() {
    if (numUsuarios >= MAX_USUARIOS) {
        printf("Numero maximo de usuarios permitidos...\n");
        return;
    }

    Usuario *novoUsuario = &usuarios[numUsuarios];

    printf("Digite o nome: ");
    getchar();
    fgets(novoUsuario->nome, TAM_NOME, stdin);
    novoUsuario->nome[strcspn(novoUsuario->nome, "\n")] = '\0';

    printf("Digite a idade: ");
    scanf("%d", &novoUsuario->idade);

    printf("Digite o email: ");
    getchar();
    fgets(novoUsuario->email, TAM_EMAIL, stdin);
    novoUsuario->email[strcspn(novoUsuario->email, "\n")] = '\0';

    do {
        printf("Digite o sexo: ");
        printf("Masculino - Feminino - Indiferente\n");
        printf("-> ");
        scanf("%s", novoUsuario->sexo);
    } while (!validarSexo(novoUsuario->sexo));

    printf("Digite o endereco: ");
    getchar();
    fgets(novoUsuario->endereco, TAM_EMAIL, stdin);
    novoUsuario->endereco[strcspn(novoUsuario->endereco, "\n")] = '\0';

    printf("Digite a altura: ");
    scanf("%lf", &novoUsuario->altura);

    do {
        printf("Tomou a vacina: ");
        printf("1 - Sim / 0 - Nao\n");
        printf("-> ");
        scanf("%d", &novoUsuario->vacina);
    } while (!validarVacina(novoUsuario->vacina));

    numUsuarios++;

    printf("Usuario adicionado.\n");
}

void editarUsuario() {
    int id;

    printf("Digite o id do usuario: ");
    scanf("%d", &id);

    if (id < 0 || id >= numUsuarios) {
        printf("ID errado...\n");
        return;
    }

    Usuario *usuarioAtualizado = &usuarios[id];

    printf("Digite o novo nome: ");
    getchar();
    fgets(usuarioAtualizado->nome, TAM_NOME, stdin);
    usuarioAtualizado->nome[strcspn(usuarioAtualizado->nome, "\n")] = '\0';

    printf("Digite a nova idade: ");
    scanf("%d", &usuarioAtualizado->idade);

    printf("Usuario editado com sucesso.\n");
}

void excluirUsuario() {
    int id;

    printf("Digite o id do usuario: ");
    scanf("%d", &id);

    if (id < 0 || id >= numUsuarios) {
        printf("ID errado...\n");
        return;
    }

    for (int i = id; i < numUsuarios - 1; i++) {
        usuarios[i] = usuarios[i + 1];
    }

    numUsuarios--;

    printf("Usuario excluido.\n");
}

void usuarioEmail() {
    char email[TAM_EMAIL];
    int encontrado = 0;

    printf("Digite o email: ");
    scanf("%s", email);

    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(email, usuarios[i].email) == 0) {
            printf("Nome: %s\n", usuarios[i].nome);
            printf("Email: %s\n", usuarios[i].email);
            printf("Idade: %d\n", usuarios[i].idade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Email nao encontrado.\n");
    }
}

void exibirUsuarios() {
    printf("Lista de usuarios:\n");

    for (int i = 0; i < numUsuarios; i++) {
        printf("Usuario %d:\n", i);
        printf("Nome: %s\n", usuarios[i].nome);
        printf("Idade: %d\n", usuarios[i].idade);
        printf("Email: %s\n", usuarios[i].email);
        printf("-----------------------\n");
    }
}

void realizarBackup() {
    FILE *arquivo;
    arquivo = fopen("backup.txt", "w");

    if (arquivo == NULL) {
        printf("Nao foi possivel criar o backup.\n");
        return;
    }

    for (int i = 0; i < numUsuarios; i++) {
        fprintf(arquivo, "Usuario %d:\n", i);
        fprintf(arquivo, "Nome: %s\n", usuarios[i].nome);
        fprintf(arquivo, "Email: %s\n", usuarios[i].email);
        fprintf(arquivo, "Sexo: %s\n", usuarios[i].sexo);
        fprintf(arquivo, "Idade: %d\n", usuarios[i].idade);
        fprintf(arquivo, "Vacina: %s\n", usuarios[i].vacina ? "Sim" : "Nao");
    }

    fclose(arquivo);

    printf("Backup feito.\n");
}

int main() {
    int escolha;

    do {
        menu();
        printf("Opcao -> ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                incluirUsuario();
                break;
            case 2:
                editarUsuario();
                break;
            case 3:
                excluirUsuario();
                break;
            case 4:
                exibirUsuarios();
                break;
            case 5:
                printf("Encerrando o programa.\n");
                break;
            case 6:
                realizarBackup();
                break;
            case 7:
                usuarioEmail();
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (escolha != 5);

    return 0;
}

