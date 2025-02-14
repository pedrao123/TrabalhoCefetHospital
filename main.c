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
    
    return 0;
}
