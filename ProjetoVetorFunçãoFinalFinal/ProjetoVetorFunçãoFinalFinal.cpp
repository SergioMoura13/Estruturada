#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USUARIOS 1000
#define TAM_NOME 100
#define TAM_EMAIL 100

char nomes[MAX_USUARIOS][TAM_NOME]; 
int idades[MAX_USUARIOS];
char email[MAX_USUARIOS] [TAM_EMAIL];
char sexo[MAX_USUARIOS];
char endereco[MAX_USUARIOS] [TAM_EMAIL];
double altura[MAX_USUARIOS];
int vacina[MAX_USUARIOS];

int numUsuarios = 0;


void menu(){
	 	
        printf("1 - Adicionar Usuario\n");
        printf("2 - Editar Usuarios\n");
        printf("3 - Excluir Usuarios\n");
        printf("4 - Exibir Usuarios\n");
        printf("5 - Fechar Programa\n");
        printf("6 - Realizar Backup\n");
        printf("7 - Fazer busca por email\n");

}

bool validarSexo(const char *sexos){
	if(strcmp(sexo, "Feminino") == 0 || strcmp(sexo, "Masculino") == 0 || strcmp(sexo, "Indiferente") == 0){
		return true;
	}
	return false;
}

bool validarVacina(int valor){
	if(valor == 0 || valor == 1){
		return true;
	}
	return false;
}


void incluirUsuario() {
    if (numUsuarios >= MAX_USUARIOS) {
        printf("Numero maximo de usuarios permitidos...\n");
        return;
    }

    printf("Digite o nome:\n ");
    getchar();
  	fgets(nomes[numUsuarios], TAM_NOME, stdin);
    nomes[numUsuarios][strcspn(nomes[numUsuarios], "\n")] = '\0';

    printf("Digite a idade:\n ");
    scanf("%d", &idades[numUsuarios]);
    
    printf("Digite o email:\n ");
    getchar();
    fgets(email[numUsuarios], TAM_EMAIL, stdin);
    email[numUsuarios][strcspn(email[numUsuarios], "\n")] = '\0';
    
    
    do{
    printf("Digite o sexo:\n ");
    printf("Masculino - Feminino - Indiferente\n");
    printf("->");
    scanf("%s", &sexo);
	} while (!validarSexo(sexo));
	
    

    
    printf("Digite o endereco:\n");
    getchar();
    fgets(endereco[numUsuarios], TAM_EMAIL, stdin);
    endereco[numUsuarios][strcspn(endereco[numUsuarios], "\n")] = '\0';
    
    printf("Digite a altura:\n");
    scanf("%f", &altura[numUsuarios]);
    
    int vacinas;
    
    do{
   	printf("Tomou a vacina: \n");
    printf("1 - Sim / 2 - Nao\n");
    printf("->");
    scanf("%d", &vacinas);
	} while(!validarVacina(vacinas));
    vacina[numUsuarios] = vacinas;

    numUsuarios++;

    printf("Usuario Adicionado.\n");
}

void editarUsuario() {
    int id;

    printf("Digite o id do usuario: ", numUsuarios - 1);
    scanf("%d", &id);

    if (id < 0 || id >= numUsuarios) {
        printf("id errado...\n");
        return;
    }

    printf("Digite o novo nome: ");
    fgets(nomes[numUsuarios], TAM_NOME, stdin);
    nomes[numUsuarios][strcspn(nomes[numUsuarios], "\n")] = '\0';

    printf("Digite a nova idade: ");
    scanf("%d", &idades[id]);

    printf("Usuario editado com sucesso.\n");
}

void excluirUsuario() {
    int id;

    printf("Digite o id: ", numUsuarios - 1);
    scanf("%d", &id);

    if (id < 0 || id >= numUsuarios) {
        printf("id errado...\n");
        return;
    }

    for (int i = id; i < numUsuarios - 1; i++) {
        strcpy(nomes[i], nomes[i + 1]);
        idades[i] = idades[i + 1];
    }

    numUsuarios--;

    printf("Usuario excluido...\n");
}

void usuarioEmail(){
	char email1[TAM_EMAIL];
	int enc = 0;
	
	printf("Digite o email: ");
	scanf("%s", email1);
	
	for(int i = 0; i < numUsuarios; i++){
		if(strcmp(email1, email[i]) == 0){
			printf("Nome: %s\n", nomes[i]);
			printf("Email: %s\n", email[i]);
			printf("idade: %s\n", idades[i]);
			enc = 1;
			break;
		}
	}
	
	if(!enc){
		printf("Email nao encontrado...\n");
	}
}

void exibirUsuarios() {
    printf("Lista de usuarios:\n");

    for (int i = 0; i < numUsuarios; i++) {
        printf("Usuario %d:\n", i);
        printf("Nome: %s\n", nomes[i]);
        printf("Idade: %d\n", idades[i]);
        printf("Email: %s\n", email[i]);
        printf("-----------------------\n");
    }
}

void realizarBackup(){
	FILE *arquivo;
	arquivo = fopen("backup.txt", "w");
	
	if(arquivo == NULL){
		printf("Nao foi possivel criar o backup...\n");
		return;
	}
	
	for(int i = 0; i <numUsuarios; i++){
		fprintf(arquivo, "Usuario %d:\n", i);
		fprintf(arquivo, "Nome: %s\n", nomes[i]);
		fprintf(arquivo, "Email: %s\n", email[i]);
		fprintf(arquivo, "Sexo: %s\n", sexo[i]);
		fprintf(arquivo, "Idade: %d\n", idades[i]);
		fprintf(arquivo, "Vacina: %s\n", vacina[i] ? "Sim" : "Nao");
	}
	
	fclose(arquivo);
	
	printf("Backup feito...\n");
}


int main() {
    int escolha;

    do {
       
       menu();
        printf("opcao -> ");
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
                printf("Opção inválida.\n");
                break;
        }
    } while (escolha != 5);

    return 0;
}
