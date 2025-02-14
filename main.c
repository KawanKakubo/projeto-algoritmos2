/* Utilizando structs a seguir:
----------------------------

1 - uma struct para armazenar data:
typedef struct {
    int dia;
    int mes;
    int ano;
} td_data;

2 - uma struct para armazenar horário:
typedef struct {
    int hora;
    int min;
} td_hora;

3 - uma struct para armazenar dados de disciplina:
typedef struct{
    int codigo_dis;
    char disciplina[100];
    float notas[4];
    float media;
} td_disciplina;

4 - uma struct para armazenar dados de aluno:
typedef struct {
    int ra;
    char nome[100];
    td_data matrícula;
    td_disciplina disciplinas[4];
    char email[100];
} td_aluno;

5 - uma struct para armazenar dados de compromisso:
typedef struct {
    td_aluno aluno;
    td_hora horario;
    td_data data;
    char descricao[300];
} td_compromisso;

 

Escrever funções para:
----------------------

 

1 - cadastrar aluno, sendo:
  a - um aluno deve cursar ao menos 4 disciplinas

  b - para cada disciplina deve haver 4 notas, com o respectivo cálculo da sua média

//recebe um vetor do tipo td_aluno e sua dimensão
void cadastra aluno(td_aluno [], int);

 

2 - validar data - não deve ser permitido o cadastro de uma data que não seja válida

//recebe um ponteiro para a struct td_data, que irá apontar para a data de matrícula na struct td_aluno
int verifica_data(td_data *);

 

3 - validar hora - não deve ser permitido o cadastro de um horário que não seja válido

//recebe um ponteiro para a struct td_hora, que irá apontar para o horário do compromisso
int verifica_horario(td_hora *);

 

4 - cadastrar um compromisso
  a - um aluno não pode ter mais do que dois compromissos cadastrados na mesma data
  b - caso um aluno possua dois compromissos na mesma data, os horários não podem estar sobrepostos/coincidentes

//recebe um vetor do tipo td_compromisso e sua dimensão
void cadastra compromisso(td_compromisso, int)

 

5 - imprimir os dados de aluno:

//recebe um vetor do tipo aluno e sua dimensão
void imprime_vetor_de_alunos(td_aluno [], int);

 

6 – alocar dinamicamente o vetor de alunos

 

7 – realocar dinamicamente o vetor de alunos

 

8 – alocar dinamicamente o vetor de compromissos

 

9 – realocar dinamicamente o vetor de compromissos


Opcionalmente podem ser escritas funções para:
----------------------------------------------

- ler horário

//recebe um ponteiro para a struct td_hora, que irá apontar para o horário do compromisso
void le_horario(td_hora *);

 

- ler data

//recebe um ponteiro para a struct data, que irá apontar para a data de matrícula na struct td_aluno
void le_data(data *);

 

O programa deve, obrigatoriamente, possuir:
-------------------------------------------

 

Um menu de opções da seguinte forma:

1 - cadastrar disciplina
2 - cadastrar aluno
3 - cadastrar compromisso
4 - imprimir compromissos
    a - de um aluno                    - ordenado por data e hora
    b - de todos os alunos             - ordenado por de ra, data e hora
    c - de uma data                    - ordenado por hora e ra
    d - de todas as datas              - ordenado por data, hora e ra
5 - imprimir dados de um aluno
6 - imprimir dados de todos os alunos  - ordenado por ra
7 - sair

 

Observações:

------------

 

- o vetor de alunos deve ser alocado dinamicamente, com a dimensão inicial 10, através de uma função;

- deve haver uma função para realocar o vetor de alunos, aumentando sempre a dimensão em 10, toda vez que o vetor for preenchido completamente;

- o vetor de compromissos deve ser alocado dinamicamente, com a dimensão inicial 15, através de função;

- deve haver uma função para realocar o vetor de compromissos, aumentando sempre a dimensão em 5, toda vez que o vetor for preenchido completamente;

- utilizar a função qsort (disponível em stdlib.h), para reallizar ordenação de vetores.
*/

#include "lib.h"

int main() {
    int capacidade_alunos, capacidade_compromissos;
    int qtd_alunos = 0, qtd_compromissos = 0;
    td_aluno *alunos = aloca_alunos(&capacidade_alunos);
    td_compromisso *compromissos = aloca_compromissos(&capacidade_compromissos);
    
    int opcao, opcao_imprimir_compromissos;
    do {
        printf("\n");
        menu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                cadastra_aluno(alunos, &qtd_alunos, &capacidade_alunos);
                break;
            case 2:
                // cadastra compromisso
                if (qtd_alunos == 0) {
                    printf("Nenhum aluno cadastrado.\n");
                    break;
                } else {
                    cadastra_compromisso(compromissos, &qtd_compromissos, &capacidade_compromissos, alunos, qtd_alunos);
                    break;
                }
            case 3:
                //  imprimir compromissos
                printf("1 - de um aluno\n"); //ordenado por data e hora
                printf("2 - de todos os alunos\n");
                printf("3 - de uma data\n");
                printf("4 - de todas as datas\n");
                printf("Escolha uma opção: ");
                scanf("%d", &opcao_imprimir_compromissos);
                switch (opcao_imprimir_compromissos) {
                    case 1:
                        // imprime compromissos de um aluno ordenados por data e hora
                        int ra_aluno;
                        printf("Digite o RA do aluno: ");
                        scanf("%d", &ra_aluno);
                        if (!existe_aluno(alunos, qtd_alunos, ra_aluno)) {
                            printf("Aluno não encontrado!\n");
                        } else {
                            imprime_compromissos_aluno(compromissos, qtd_compromissos, ra_aluno);
                        }
                        break;
                    case 2:
                        // imprime todos os compromissos ordenados por ra, data e hora
                        if (qtd_compromissos == 0) {
                            printf("Nenhum compromisso cadastrado.\n");
                        } else {
                            imprime_todos_compromissos(compromissos, qtd_compromissos);
                        }
                        break;
                    case 3:
                        // imprime compromissos de uma data ordenados por hora e ra
                        td_data data;
                        printf("Digite a data (dd mm aaaa): ");
                        scanf("%d %d %d", &data.dia, &data.mes, &data.ano);
                        if (!verifica_data(&data)) {
                            printf("Data inválida!\n");
                            break;
                        }
                        imprime_compromissos_data(compromissos, qtd_compromissos, data);
                        break;
                    case 4:
                        // imprime todos os compromissos ordenados por data, hora e ra
                        if (qtd_compromissos == 0) {
                            printf("Nenhum compromisso cadastrado.\n");
                        } else {
                            imprime_todas_datas(compromissos, qtd_compromissos);
                        }
                        break;
                    default:
                        printf("Opção inválida!\n");
                        break;
                }
                break;
            case 4:
                // Imprimir dados de um aluno
                int ra;
                printf("Digite o RA do aluno: ");
                scanf("%d", &ra);

                int encontrado = 0;

                for (int i = 0; i < qtd_alunos; i++) {
                    if (alunos[i].ra == ra) {
                        printf("------------------------------------\n");
                        imprime_vetor_de_1_aluno(alunos[i]);
                        encontrado = 1;
                        break;
                    }
                }

                if (!encontrado) {
                    printf("Aluno não encontrado!\n");
                }
                break;

            case 5:
                // imprimir dados de todos os alunos
                printf("\n------------------------------------\n");
                if (qtd_alunos == 0) {
                    printf("Nenhum aluno cadastrado.\n");
                    break;
                } else {
                    imprime_vetor_de_alunos(alunos, qtd_alunos);
                    break;
                }
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 6);
    
    free(alunos);
    free(compromissos);
    return 0;
}

