#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MaxCaracteres 40
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
                printf("Opcao de Paciente selecionada.\n");
                int opcaoPaciente;
                do {
                    printf("1 - Incluir Paciente\n");
                    printf("2 - Listar Pacientes\n");
                    printf("3 - Voltar\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &opcaoPaciente);
                    getchar();
                    if (opcaoPaciente == 1) {
                        incluirPaciente();
                    } else if (opcaoPaciente == 2) {
                        listarPacientes();
                    }
                } while (opcaoPaciente != 3);
                break;
            case 3:
                printf("Opcao de Medico selecionada.\n");
                int opcaoMedico;
                do {
                    printf("1 - Incluir Médico\n");
                    printf("2 - Listar Médicos\n");
                    printf("3 - Voltar\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &opcaoMedico);
                    getchar();
                    if (opcaoMedico == 1) {
                        incluirMedico();
                    } else if (opcaoMedico == 2) {
                        listarMedicos();
                    }
                } while (opcaoMedico != 3);
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