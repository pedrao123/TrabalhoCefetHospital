#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MaxCaracteres 40
#define MAX_MEDICOS 20
#define MAX_PACIENTES 50
#define MAX_CONSULTAS 100
typedef struct
    {
        int id;
        char nome[MaxCaracteres] ;
        char especialidade[MaxCaracteres];
    } medico;
typedef struct
    {
        int id;
        char nome[MaxCaracteres];
        char identidade[MaxCaracteres];
        char endereco[MaxCaracteres];
        char telefone[MaxCaracteres];
        char sexo[MaxCaracteres];
    }paciente;
typedef struct
    {
        int numero;
        int idMedico;
        int idPaciente;
        char horario[MaxCaracteres];
        char duracao[MaxCaracteres];
        char data[MaxCaracteres];
    }consulta;

void incluirPaciente() {
    FILE *arq = fopen("pacientes.bin", "ab");
    paciente p;
    printf("Digite o ID do paciente: ");
    scanf("%d", &p.id);
    getchar();
    printf("Digite o nome do paciente: ");
    fgets(p.nome, MaxCaracteres, stdin);
    printf("Digite a identidade: ");
    fgets(p.identidade, MaxCaracteres, stdin);
    printf("Digite o endereço: ");
    fgets(p.endereco, MaxCaracteres, stdin);
    printf("Digite o telefone: ");
    fgets(p.telefone, MaxCaracteres, stdin);
    printf("Digite o sexo: ");
    fgets(p.sexo, MaxCaracteres, stdin);
    fwrite(&p, sizeof(paciente), 1, arq);
    fclose(arq);
}

void incluirMedico() {
    FILE *arq = fopen("medicos.bin", "ab");
    medico m;
    printf("Digite o ID do medico: ");
    scanf("%d", &m.id);
    getchar();
    printf("Digite o nome do medico: ");
    fgets(m.nome, MaxCaracteres, stdin);
    printf("Digite a especialidade: ");
    fgets(m.especialidade, MaxCaracteres, stdin);
    fwrite(&m, sizeof(medico), 1, arq);
    fclose(arq);
}

void pesquisarPaciente() {
    FILE *arq = fopen("pacientes.bin", "rb");
    if (!arq) return;
    paciente p;
    char busca[MaxCaracteres];
    int encontrado = 0;
    printf("Digite o ID ou Nome do paciente a pesquisar: ");
    fgets(busca, MaxCaracteres, stdin);
    busca[strcspn(busca, "\n")] = 0;
    while (fread(&p, sizeof(paciente), 1, arq)) {
        if (p.id == atoi(busca) || strcmp(p.nome, busca) == 0) {
            printf("ID: %d\nNome: %s\nIdentidade: %s\nEndereço: %s\nTelefone: %s\nSexo: %s\n", 
                p.id, p.nome, p.identidade, p.endereco, p.telefone, p.sexo);
            encontrado = 1;
            break;
        }
    }
    fclose(arq);
    if (!encontrado) printf("Paciente não encontrado.\n");
}

void pesquisarMedico() {
    FILE *arq = fopen("medicos.bin", "rb");
    if (!arq) return;
    medico m;
    char busca[MaxCaracteres];
    int encontrado = 0;
    printf("Digite o ID ou Nome do medico a pesquisar: ");
    fgets(busca, MaxCaracteres, stdin);
    busca[strcspn(busca, "\n")] = 0;
    while (fread(&m, sizeof(medico), 1, arq)) {
        if (m.id == atoi(busca) || strcmp(m.nome, busca) == 0) {
            printf("ID: %d\nNome: %s\nEspecialidade: %s\n", m.id, m.nome, m.especialidade);
            encontrado = 1;
            break;
        }
    }
    fclose(arq);
    if (!encontrado) printf("Médico não encontrado.\n");
}

void alterarPaciente() {
    FILE *arq = fopen("pacientes.bin", "rb+"), *temp;
    if (!arq) return;
    paciente p;
    int idBusca, encontrado = 0;
    char nomeBusca[MaxCaracteres];
    printf("Digite o ID ou Nome do paciente a alterar: ");
    fgets(nomeBusca, MaxCaracteres, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;
    while (fread(&p, sizeof(paciente), 1, arq)) {
        if (p.id == atoi(nomeBusca) || strcmp(p.nome, nomeBusca) == 0) {
            printf("Novo nome: ");
            fgets(p.nome, MaxCaracteres, stdin);
            printf("Nova identidade: ");
            fgets(p.identidade, MaxCaracteres, stdin);
            printf("Novo endereço: ");
            fgets(p.endereco, MaxCaracteres, stdin);
            printf("Novo telefone: ");
            fgets(p.telefone, MaxCaracteres, stdin);
            printf("Novo sexo: ");
            fgets(p.sexo, MaxCaracteres, stdin);
            fseek(arq, -sizeof(paciente), SEEK_CUR);
            fwrite(&p, sizeof(paciente), 1, arq);
            encontrado = 1;
            break;
        }
    }
    fclose(arq);
    if (!encontrado) printf("Paciente nao encontrado.\n");
}

void alterarMedico() {
    FILE *arq = fopen("medicos.bin", "rb+"), *temp;
    if (!arq) return;
    medico m;
    int idBusca, encontrado = 0;
    char nomeBusca[MaxCaracteres];
    printf("Digite o ID ou Nome do médico a alterar: ");
    fgets(nomeBusca, MaxCaracteres, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;
    while (fread(&m, sizeof(medico), 1, arq)) {
        if (m.id == atoi(nomeBusca) || strcmp(m.nome, nomeBusca) == 0) {
            printf("Novo nome: ");
            fgets(m.nome, MaxCaracteres, stdin);
            printf("Nova especialidade: ");
            fgets(m.especialidade, MaxCaracteres, stdin);
            fseek(arq, -sizeof(medico), SEEK_CUR);
            fwrite(&m, sizeof(medico), 1, arq);
            encontrado = 1;
            break;
        }
    }
    fclose(arq);
    if (!encontrado) printf("Médico não encontrado.\n");
}

void listarPacientes() {
    FILE *arq = fopen("pacientes.bin", "rb");
    paciente p;
    while (fread(&p, sizeof(paciente), 1, arq)) {
        printf("ID: %d, Nome: %s, Identidade: %s, Endereco: %s, Telefone: %s, Sexo: %s\n", p.id, p.nome, p.identidade, p.endereco, p.telefone, p.sexo);
    }
    fclose(arq);
}
void listarMedicos() {
    FILE *arq = fopen("medicos.bin", "rb");
    medico m;
    while (fread(&m, sizeof(medico), 1, arq)) {
        printf("ID: %d, Nome: %s, Especialidade: %s\n", m.id, m.nome, m.especialidade);
    }
    fclose(arq);
}

void excluirPaciente() {
    FILE *arq = fopen("pacientes.bin", "rb");
    FILE *temp = fopen("temp.bin", "wb");
    if (!arq || !temp) return;
    paciente p;
    int id;
    printf("Digite o ID do paciente a excluir: ");
    scanf("%d", &id);
    getchar();
    while (fread(&p, sizeof(paciente), 1, arq)) {
        if (p.id != id) {
            fwrite(&p, sizeof(paciente), 1, temp);
        }
    }
    fclose(arq);
    fclose(temp);
    remove("pacientes.bin");
    rename("temp.bin", "pacientes.bin");
}

void excluirMedico() {
    FILE *arq = fopen("medicos.bin", "rb");
    FILE *temp = fopen("temp.bin", "wb");
    if (!arq || !temp) return;
    medico m;
    int id;
    printf("Digite o ID do médico a excluir: ");
    scanf("%d", &id);
    getchar();
    while (fread(&m, sizeof(medico), 1, arq)) {
        if (m.id != id) {
            fwrite(&m, sizeof(medico), 1, temp);
        }
    }
    fclose(arq);
    fclose(temp);
    remove("medicos.bin");
    rename("temp.bin", "medicos.bin");
}


int main()
{
    FILE *arqmed = fopen("medicos.bin","r");
    if(arqmed==NULL){
        FILE *arqmed = fopen("medicos.bin","w");
        fclose(arqmed);
    }
    else{
        fclose(arqmed);
    }

    FILE *arqpac = fopen("pacientes.bin","r");
    if(arqmed==NULL){
        FILE *arqpac = fopen("pacientes.bin","w");
        fclose(arqpac);
    }
    else{
        fclose(arqpac);
    }

    FILE *arqcons = fopen("consultas.bin","r");
    if(arqcons==NULL){
        FILE *arqcons = fopen("cansultas.bin","w");
        fclose(arqcons);
    }
    else{
        fclose(arqcons);
    }
    
    int opcao;
    do{
        printf("\nMenu Principal:\n");
        printf("1 - Consulta\n");
        printf("2 - Paciente\n");
        printf("3 - Medico\n");
        printf("4 - Relatorios\n");
        printf("5 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Opcao de Consulta selecionada.\n");

                break;
            case 2:
                printf("Opcao de PACIENTE selecionada.\n");
                int opcaoPaciente;
                do {
                    printf("1 - Incluir\n");
                    printf("2 - Listar\n");
                    printf("3 - Alterar\n");
                    printf("4 - Pesquisar\n");
                    printf("5 - Excluir\n");
                    printf("6 - Voltar\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &opcaoPaciente);
                    getchar();
                    if (opcaoPaciente == 1) {
                        incluirPaciente();
                    } else if (opcaoPaciente == 2) {
                        listarPacientes();
                    } else if (opcaoPaciente == 3) {
                        alterarPaciente();
                    } else if(opcaoPaciente == 4) {
                        pesquisarPaciente();
                    } else if(opcaoPaciente == 5) {
                        excluirPaciente();
                    }
                } while (opcaoPaciente != 6);
                break;
            case 3:
            printf("Opcao de MEDICO selecionada.\n");
            int opcaoMedico;
            do {
                printf("1 - Incluir\n");
                printf("2 - Listar\n");
                printf("3 - Alterar\n");
                printf("4 - Pesquisar\n");
                printf("5 - Excluir\n");
                printf("6 - Voltar\n");
                printf("Escolha uma opção: ");
                scanf("%d", &opcaoMedico);
                getchar();
                if (opcaoMedico == 1) {
                    incluirMedico();
                } else if (opcaoMedico == 2) {
                    listarMedico();
                } else if (opcaoMedico == 3) {
                    alterarMedico();
                } else if(opcaoMedico == 4) {
                    pesquisarMedico();
                } else if(opcaoMedico == 5) {
                    excluirMedico();
                }
            } while (opcaoMedico != 6);
            break;
            case 4:
                printf("Opcao de Relatorios selecionada.\n");

                break;
            case 5:
                printf("Saindo...\n");

                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 5);
    return 0;
}