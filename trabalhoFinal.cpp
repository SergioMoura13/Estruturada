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

Usuario *usuarios[MAX_USUARIOS];
int numUsuarios = 0;

void menu() {
    printf("1 - Adicionar Usuario\n");
    printf("2 - Editar Usuarios\n");
    printf("3 - Excluir Usuarios\n");
    printf("4 - Exibir Usuarios\n");
    printf("5 - Fechar Programa\n");
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

Usuario* criarUsuario() {
    Usuario* novoUsuario = (Usuario*)malloc(sizeof(Usuario));
    if (novoUsuario == NULL) {
        printf("Erro ao alocar memoria para o usuario.\n");
        return NULL;
    }
    return novoUsuario;
}

void liberarUsuario(Usuario *usuario) {
    free(usuario);
}

void incluirUsuario() {
    if (numUsuarios >= MAX_USUARIOS) {
        printf("Numero maximo de usuarios permitidos...\n");
        return;
    }

    Usuario *novoUsuario = criarUsuario();
    if (novoUsuario == NULL) {
        return;
    }

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

    usuarios[numUsuarios] = novoUsuario;
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

    Usuario *usuarioAtualizado = usuarios[id];

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

    Usuario *usuarioExcluido = usuarios[id];
    liberarUsuario(usuarioExcluido);

    for (int i = id; i < numUsuarios - 1; i++) {
        usuarios[i] = usuarios[i + 1];
    }

    numUsuarios--;

    printf("Usuario excluido.\n");
}

void exibirUsuarios() {
    printf("Lista de usuarios:\n");

    for (int i = 0; i < numUsuarios; i++) {
        Usuario *usuario = usuarios[i];
        printf("Usuario %d:\n", i);
        printf("Nome: %s\n", usuario->nome);
        printf("Idade: %d\n", usuario->idade);
        printf("Email: %s\n", usuario->email);
        printf("-----------------------\n");
    }
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
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (escolha != 5);

    for (int i = 0; i < numUsuarios; i++) {
        liberarUsuario(usuarios[i]);
    }

    return 0;
}
