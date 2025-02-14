#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    typedef struct
    {
        int id;
        char *nome ;
        char *especialidade;
    } medico;
    typedef struct
    {
        int id;
        char *nome;
        char *identidade;
        char *endereco;
        char *telefone;
        char *sexo
    }paciente;
    typedef struct
    {
        int numero;
        int idMedico;
        int idPaciente;
        char *horario;
        char *duracao;
        char *data;
    }consulta;
    
    return 0;
}
