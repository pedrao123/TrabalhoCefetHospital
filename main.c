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
}medico;
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
    scanf(" %[^\n]",&m.especialidade);
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
            printf("ID: %d\nNome: %s\nIdentidade: %s\nEndereco: %s\nTelefone: %s\nSexo: %s\n", 
                p.id, p.nome, p.identidade, p.endereco, p.telefone, p.sexo);
            encontrado = 1;
            break;
        }
    }
    fclose(arq);
    if (!encontrado) printf("Paciente nao encontrado.\n");
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
    if (!encontrado) printf("Medico não encontrado.\n");
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
    printf("Digite o ID ou Nome do medico a alterar: ");
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
    if (!encontrado) printf("Medico não encontrado.\n");
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
    FILE *arq2 = fopen("consultas.bin", "rb");
    FILE *temp = fopen("temp.bin", "wb");
    FILE *temp2 = fopen("temp2.bin", "wb");
    if (!arq || !temp) return;
    paciente p;
    consulta c;
    int id;
    printf("Digite o ID do paciente a excluir: ");
    scanf("%d", &id);
    getchar();
    while (fread(&p, sizeof(paciente), 1, arq)) {
        if (p.id != id) {
            fwrite(&p, sizeof(paciente), 1, temp);
        }
        else{
            printf("O paciente :\nID: %d\nNome: %s\nIdentidade: %s\nEndereco: %s\nTelefone: %s\nSexo: %s\nfoi excluido com sucesso\n", 
                p.id, p.nome, p.identidade, p.endereco, p.telefone, p.sexo);
        }
    }
    while (fread(&c, sizeof(consulta), 1, arq)){
        if(id != c.idPaciente){
            fwrite(&c, sizeof(consulta), 1, temp2);
        }
    }
    fclose(arq2);
    fclose(temp2);
    fclose(arq);
    fclose(temp);
    remove("pacientes.bin");
    remove("consultas.bin");
    rename("temp.bin", "pacientes.bin");
    rename("temp2.bin", "consultas.bin");
}

void excluirMedico() {
    FILE *arq = fopen("medicos.bin", "rb");
    FILE *arq2 = fopen("consultas.bin", "rb");
    FILE *temp = fopen("temp.bin", "wb");
    FILE *temp2 = fopen("temp2.bin", "wb");
    if (!arq || !temp) return;
    medico m;
    consulta c;
    int id;
    printf("Digite o ID do medico a excluir: ");
    scanf("%d", &id);
    getchar();
    while (fread(&m, sizeof(medico), 1, arq)) {
        if (m.id != id) {
            fwrite(&m, sizeof(medico), 1, temp);
        }
        else{
            printf("O medico:\nID: %d, Nome: %s, Especialidade: %s\nFoi excluido com sucesso\n", m.id, m.nome, m.especialidade);
        }
    }
    while (fread(&c,sizeof(consulta),1,temp2))
    {
        if(id!=c.idMedico){
            fwrite(&c,sizeof(consulta),1,temp2);
        }
    }
    fclose(arq2);
    fclose(temp2);
    fclose(arq);
    fclose(temp);
    remove("consultas.bin");
    remove("medicos.bin");
    rename("temp2.bin","consultas.bin");
    rename("temp.bin", "medicos.bin");
}

//TUDO SOBRE CONSULTAS:

void incluirConsulta() {
    FILE *arq = fopen("consultas.bin", "ab");
    if (!arq) return;
    consulta c;
    printf("Digite o numero da consulta: ");
    scanf("%d", &c.numero);
    printf("Digite o ID do medico: ");
    scanf("%d", &c.idMedico);
    printf("Digite o ID do paciente: ");
    scanf("%d", &c.idPaciente);
    printf("Digite o horario da consulta: ");
    scanf(" %[^\n]", c.horario);
    printf("Digite a duracao da consulta: ");
    scanf(" %[^\n]", c.duracao);
    printf("Digite a data da consulta: ");
    scanf(" %[^\n]", c.data);
    fwrite(&c, sizeof(consulta), 1, arq);
    fclose(arq);
    printf("Consulta cadastrada com sucesso!\n");
}

void alterarConsulta() {
    FILE *arq = fopen("consultas.bin", "rb+");
    if (!arq) return;
    consulta c;
    int numero;
    printf("Digite o numero da consulta a alterar: ");
    scanf("%d", &numero);
    while (fread(&c, sizeof(consulta), 1, arq)) {
        if (c.numero == numero) {
            printf("Consulta encontrada! Digite os novos dados:\n");
            printf("Digite o ID do medico: ");
            scanf("%d", &c.idMedico);
            printf("Digite o ID do paciente: ");
            scanf("%d", &c.idPaciente);
            printf("Digite o horario da consulta: ");
            scanf(" %[^\n]", c.horario);
            printf("Digite a duracao da consulta: ");
            scanf(" %[^\n]", c.duracao);
            printf("Digite a data da consulta: ");
            scanf(" %[^\n]", c.data);
            fseek(arq, -sizeof(consulta), SEEK_CUR);
            fwrite(&c, sizeof(consulta), 1, arq);
            fclose(arq);
            printf("Consulta alterada com sucesso!\n");
            return;
        }
    }
    fclose(arq);
    printf("Consulta nao encontrada!\n");
}

void pesquisarConsulta() {
    FILE *arq = fopen("consultas.bin", "rb");
    if (!arq) return;
    consulta c;
    int busca;
    printf("Digite o numero da consulta: ");
    scanf("%d", &busca);
    while (fread(&c, sizeof(consulta), 1, arq)) {
        if ((c.numero == busca)) {
            printf("Consulta encontrada:\nNumero: %d\nMedico ID: %d\nPaciente ID: %d\nHorario: %s\nDuracao: %s\nData: %s\n", c.numero, c.idMedico, c.idPaciente, c.horario, c.duracao, c.data);
        }
    }
    fclose(arq);
}

void excluirConsulta(){
    FILE *arq = fopen("consultas.bin","rb");
    FILE *temp = fopen("temp.bin","wb");
    consulta c;
    printf("Digite o numero da consulta que deseja excluir:\n");
    int n;
    scanf("%d",&n);
    while (fread(&c,sizeof(consulta),1,arq)==1)
    {
        if(c.numero!=n){
            fwrite(&c,sizeof(consulta),1,temp);
        }
        else{
            printf("Consulta as %s dia %s excluida com sucesso!\n",c.data,c.horario);
        }
    }
    fclose(arq);
    fclose(temp);
    remove("consultas.bin");
    rename("temp.bin","pacientes.bin");
}
void relatorioPaciente(){
    int id;
    FILE *arq = fopen("consultas.bin","rb");
    printf("digite o id do paciente:\n");
    scanf("%d",&id);
    consulta c;
    while (fread(&c,sizeof(consulta),1,arq)==1)
    {
        if (id==c.idPaciente)
        {
            printf ("Numero: %d\nMedico ID: %d\nPaciente ID: %d\nHorario: %s\nDuracao: %s\nData: %s\n\n", c.numero, c.idMedico, c.idPaciente, c.horario, c.duracao, c.data);
        }
    }
    fclose(arq);
}

void relatorioMedico(){
    int id;
    FILE *arq = fopen("consultas.bin","rb");
    printf("digite o id do medico:\n");
    scanf("%d",&id);
    consulta c;
    while (fread(&c,sizeof(consulta),1,arq)==1){
        if (id==c.idMedico)
        {
            printf ("Numero: %d\nMedico ID: %d\nPaciente ID: %d\nHorario: %s\nDuracao: %s\nData: %s\n\n", c.numero, c.idMedico, c.idPaciente, c.horario, c.duracao, c.data);
        }
    }
    fclose(arq);
}

void relatorioEspecialidades(){
    char especialidade[MaxCaracteres];
    FILE *arq = fopen("medicos.bin","rb");
    printf("digite a especialidade:\n");
    scanf(" %[^\n]",especialidade);
    medico m;
    while (fread(&m,sizeof(medico),1,arq)==1)
    {
        if(strcmp(especialidade,m.especialidade)==0){
            printf("ID: %d, Nome: %s\n", m.id, m.nome);
        }
    }
    fclose(arq);
}

void menu(){
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
                printf("Opcao de CONSULTA selecionada.\n");
                int opcaoConsulta;
                do {
                    printf("1 - Incluir\n");
                    printf("2 - Alterar\n");
                    printf("3 - Pesquisar\n");
                    printf("4 - Excluir\n");
                    printf("5 - Voltar\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opcaoConsulta);
                    getchar();
                    if (opcaoConsulta == 1) {
                        incluirConsulta();
                    } else if (opcaoConsulta == 2) {
                        alterarConsulta();
                    } else if(opcaoConsulta == 3) {
                        pesquisarConsulta();
                    } else if(opcaoConsulta == 4) {
                        excluirConsulta();
                    }
                } while (opcaoConsulta != 5);
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
                    printf("Escolha uma opcao: ");
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
                printf("Escolha uma opcao: ");
                scanf("%d", &opcaoMedico);
                getchar();
                if (opcaoMedico == 1) {
                    incluirMedico();
                } else if (opcaoMedico == 2) {
                    listarMedicos();
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
                int opcaoRelatorios;
                do{
                    printf("1 - Lista de consultas agendadas para o paciente\n");
                    printf("2 - Lista de consultas agendadas para o medico\n");
                    printf("3 - Lista de medicos por especialidade\n");
                    printf("4 - Voltar\n");
                    scanf("%d",&opcaoRelatorios);
                    if (opcaoRelatorios == 1){
                        relatorioPaciente();
                    } else if (opcaoRelatorios == 2){
                        relatorioMedico();
                    } else if (opcaoRelatorios == 3){
                        relatorioEspecialidades();
                    }
                } while (opcaoRelatorios != 4);
                break;
            case 5:
                printf("Saindo...\n");

                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 5);
}

void inciarArquivos(){
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
        FILE *arqcons = fopen("consultas.bin","w");
        fclose(arqcons);
    }
    else{
        fclose(arqcons);
    }
}

int main()
{
    inciarArquivos();
    menu();
    return 0;
}