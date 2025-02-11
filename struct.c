//1 - uma struct para armazenar data:
typedef struct {
    int dia;
    int mes;
    int ano;
} td_data;

//2 - uma struct para armazenar horário:
typedef struct {
    int hora;
    int min;
} td_hora;

//3 - uma struct para armazenar dados de disciplina:
typedef struct{
    int codigo_dis;
    char disciplina[100];
    float notas[4];
    float media;
} td_disciplina;

//4 - uma struct para armazenar dados de aluno:
typedef struct {
    int ra;
    char nome[100];
    td_data matricula;
    td_disciplina disciplinas[4];
    char email[100];
} td_aluno;

//5 - uma struct para armazenar dados de compromisso:
typedef struct {
    td_aluno aluno;
    td_hora horario;
    td_data data;
    char descricao[300];
} td_compromisso;