#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.c"

int verifica_data(td_data *data) {
    if (data->mes < 1 || data->mes > 12) {
        return 0;
    }

    if (data->dia < 1) {
        return 0;
    }

    if (data->ano < 0) {
        return 0;
    }

    int dias_no_mes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // bissexto ou nao
    if ((data->ano % 4 == 0 && data->ano % 100 != 0) || (data->ano % 400 == 0)) {
        dias_no_mes[2] = 29; // fev aumenta 29
    }

    if (data->dia > dias_no_mes[data->mes]) {
        return 0;
    }

    return 1;
}

int verifica_horario(td_hora *hora) {
    if (hora->hora < 0 || hora->hora >= 24) {
        return 0;
    }
    
    if (hora->min < 0 || hora->min >= 60) {
        return 0;
    }
    
    return 1;
}

td_aluno* aloca_alunos(int *capacidade) {
    *capacidade = 10;
    return (td_aluno*) malloc((*capacidade) * sizeof(td_aluno));
}

td_aluno* realoca_alunos(td_aluno *alunos, int *capacidade) {
    *capacidade += 10;
    return (td_aluno*) realloc(alunos, (*capacidade) * sizeof(td_aluno));
}

td_compromisso* aloca_compromissos(int *capacidade) {
    *capacidade = 15;
    return (td_compromisso*) malloc((*capacidade) * sizeof(td_compromisso));
}

td_compromisso* realoca_compromissos(td_compromisso *compromissos, int *capacidade) {
    *capacidade += 5;
    return (td_compromisso*) realloc(compromissos, (*capacidade) * sizeof(td_compromisso));
}

void cadastra_aluno(td_aluno alunos[], int *qtd_alunos, int *capacidade) {
    if (*qtd_alunos >= *capacidade) {
        alunos = realoca_alunos(alunos, capacidade);
    }
    td_aluno *novo_aluno = &alunos[*qtd_alunos];
    printf("RA: ");
    scanf("%d", &novo_aluno->ra);
    getchar();
    printf("Nome: ");
    fgets(novo_aluno->nome, sizeof(novo_aluno->nome), stdin);
    novo_aluno->nome[strcspn(novo_aluno->nome, "\n")] = 0;
    printf("Email: ");
    fgets(novo_aluno->email, sizeof(novo_aluno->email), stdin);
    novo_aluno->email[strcspn(novo_aluno->email, "\n")] = 0;
    printf("Data de matrícula (dd mm aaaa): ");
    scanf("%d %d %d", &novo_aluno->matricula.dia, &novo_aluno->matricula.mes, &novo_aluno->matricula.ano);
    if (!verifica_data(&novo_aluno->matricula)) {
        printf("Data inválida!\n");
        return;
    }
    for (int i = 0; i < 4; i++) {
        printf("Código da disciplina %d (int): ", i + 1);
        scanf("%d", &novo_aluno->disciplinas[i].codigo_dis);
        getchar();
        printf("Nome da disciplina: ");
        fgets(novo_aluno->disciplinas[i].disciplina, sizeof(novo_aluno->disciplinas[i].disciplina), stdin);
        novo_aluno->disciplinas[i].disciplina[strcspn(novo_aluno->disciplinas[i].disciplina, "\n")] = 0;
        float soma_notas = 0;
        for (int j = 0; j < 4; j++) {
            printf("Nota %d: ", j + 1);
            scanf("%f", &novo_aluno->disciplinas[i].notas[j]);
            soma_notas += novo_aluno->disciplinas[i].notas[j];
        }
        novo_aluno->disciplinas[i].media = soma_notas / 4;
    }
    (*qtd_alunos)++;
}

void cadastra_compromisso(td_compromisso *compromissos, int *qtd_compromissos, int *capacidade_compromissos, td_aluno *alunos, int qtd_alunos) {
    if (*qtd_compromissos >= *capacidade_compromissos) {
        compromissos = realoca_compromissos(compromissos, capacidade_compromissos);
    }
    
    td_compromisso *novo_compromisso = &compromissos[*qtd_compromissos];
    
    printf("RA do aluno: ");
    int ra;
    scanf("%d", &ra);
    
    int aluno_encontrado = 0;
    for (int i = 0; i < qtd_alunos; i++) {
        if (alunos[i].ra == ra) {
            novo_compromisso->aluno = alunos[i];
            aluno_encontrado = 1;
            break;
        }
    }
    
    if (!aluno_encontrado) {
        printf("Aluno não encontrado!\n");
        return;
    }
    
    printf("Data do compromisso (dd mm aaaa): ");
    scanf("%d %d %d", &novo_compromisso->data.dia, &novo_compromisso->data.mes, &novo_compromisso->data.ano);
    
    if (!verifica_data(&novo_compromisso->data)) {
        printf("Data inválida!\n");
        return;
    }
    
    printf("Horário do compromisso (hh mm): ");
    scanf("%d %d", &novo_compromisso->horario.hora, &novo_compromisso->horario.min);
    
    if (!verifica_horario(&novo_compromisso->horario)) {
        printf("Horário inválido!\n");
        return;
    }
    
    printf("Descrição do compromisso: ");
    getchar(); // Limpa buffer
    fgets(novo_compromisso->descricao, 300, stdin);
    novo_compromisso->descricao[strcspn(novo_compromisso->descricao, "\n")] = 0;
    
    (*qtd_compromissos)++;
}

int compara_data_hora(const void *a, const void *b) {
    td_compromisso *comp1 = (td_compromisso *)a;
    td_compromisso *comp2 = (td_compromisso *)b;
    
    if (comp1->data.ano != comp2->data.ano)
        return comp1->data.ano - comp2->data.ano;
    if (comp1->data.mes != comp2->data.mes)
        return comp1->data.mes - comp2->data.mes;
    if (comp1->data.dia != comp2->data.dia)
        return comp1->data.dia - comp2->data.dia;
    if (comp1->horario.hora != comp2->horario.hora)
        return comp1->horario.hora - comp2->horario.hora;
    return comp1->horario.min - comp2->horario.min;
}

int compara_ra_data_hora(const void *a, const void *b) {
    td_compromisso *comp1 = (td_compromisso *)a;
    td_compromisso *comp2 = (td_compromisso *)b;
    
    if (comp1->aluno.ra != comp2->aluno.ra)
        return comp1->aluno.ra - comp2->aluno.ra;
    return compara_data_hora(a, b);
}

int compara_hora_ra(const void *a, const void *b) {
    td_compromisso *comp1 = (td_compromisso *)a;
    td_compromisso *comp2 = (td_compromisso *)b;
    
    if (comp1->horario.hora != comp2->horario.hora)
        return comp1->horario.hora - comp2->horario.hora;
    if (comp1->horario.min != comp2->horario.min)
        return comp1->horario.min - comp2->horario.min;
    return comp1->aluno.ra - comp2->aluno.ra;
}

void imprime_compromissos_aluno(td_compromisso *compromissos, int qtd_compromissos, int ra) {
    if (qtd_compromissos == 0) {
        printf("Nenhum compromisso cadastrado.\n");
        return;
    }

    // Ordenar por data e hora
    qsort(compromissos, qtd_compromissos, sizeof(td_compromisso), compara_data_hora);
    
    int encontrou = 0;
    printf("\nCompromissos do aluno RA %d:\n", ra);
    for (int i = 0; i < qtd_compromissos; i++) {
        if (compromissos[i].aluno.ra == ra) {
            printf("%02d/%02d/%04d - %02d:%02d - %s\n",
                   compromissos[i].data.dia, compromissos[i].data.mes, compromissos[i].data.ano,
                   compromissos[i].horario.hora, compromissos[i].horario.min,
                   compromissos[i].descricao);
            encontrou = 1;
        }
    }
    
    if (!encontrou) {
        printf("Nenhum compromisso encontrado para este aluno.\n");
    }
}

void imprime_todos_compromissos(td_compromisso *compromissos, int qtd_compromissos) {
    if (qtd_compromissos == 0) {
        printf("Nenhum compromisso cadastrado.\n");
        return;
    }

    // Ordenar por RA, data e hora
    qsort(compromissos, qtd_compromissos, sizeof(td_compromisso), compara_ra_data_hora);
    
    printf("\nTodos os compromissos (ordenados por RA, data e hora):\n");
    for (int i = 0; i < qtd_compromissos; i++) {
        printf("RA: %d - %02d/%02d/%04d - %02d:%02d - %s\n",
               compromissos[i].aluno.ra,
               compromissos[i].data.dia, compromissos[i].data.mes, compromissos[i].data.ano,
               compromissos[i].horario.hora, compromissos[i].horario.min,
               compromissos[i].descricao);
    }
}

void imprime_compromissos_data(td_compromisso *compromissos, int qtd_compromissos, td_data data) {
    if (qtd_compromissos == 0) {
        printf("Nenhum compromisso cadastrado.\n");
        return;
    }

    td_compromisso *temp = malloc(qtd_compromissos * sizeof(td_compromisso));
    int qtd_temp = 0;
    
    for (int i = 0; i < qtd_compromissos; i++) {
        if (compromissos[i].data.dia == data.dia &&
            compromissos[i].data.mes == data.mes &&
            compromissos[i].data.ano == data.ano) {
            temp[qtd_temp++] = compromissos[i];
        }
    }

    if (qtd_temp == 0) {
        printf("\nNenhum compromisso encontrado na data %02d/%02d/%04d.\n",
               data.dia, data.mes, data.ano);
        free(temp);
        return;
    }

    // Ordenar por hora e RA
    qsort(temp, qtd_temp, sizeof(td_compromisso), compara_hora_ra);
    
    printf("\nCompromissos do dia %02d/%02d/%04d (ordenados por hora e RA):\n",
           data.dia, data.mes, data.ano);
    for (int i = 0; i < qtd_temp; i++) {
        printf("%02d:%02d - RA: %d - %s\n",
               temp[i].horario.hora, temp[i].horario.min,
               temp[i].aluno.ra,
               temp[i].descricao);
    }
    
    free(temp);
}

void imprime_todas_datas(td_compromisso *compromissos, int qtd_compromissos) {
    if (qtd_compromissos == 0) {
        printf("Nenhum compromisso cadastrado.\n");
        return;
    }

    // Ordenar por data, hora e RA
    qsort(compromissos, qtd_compromissos, sizeof(td_compromisso), compara_data_hora);
    
    printf("\nTodos os compromissos (ordenados por data, hora e RA):\n");
    for (int i = 0; i < qtd_compromissos; i++) {
        printf("%02d/%02d/%04d - %02d:%02d - RA: %d - %s\n",
               compromissos[i].data.dia, compromissos[i].data.mes, compromissos[i].data.ano,
               compromissos[i].horario.hora, compromissos[i].horario.min,
               compromissos[i].aluno.ra,
               compromissos[i].descricao);
    }
}

void imprime_vetor_de_1_aluno(td_aluno aluno) {
    printf("RA: %d\nNome: %s\nEmail: %s\nMatrícula: %02d/%02d/%04d\n", 
           aluno.ra, aluno.nome, aluno.email, 
           aluno.matricula.dia, aluno.matricula.mes, aluno.matricula.ano);
    printf("Disciplinas:\n");
    for (int j = 0; j < 4; j++) {
        printf("  Código: %d - %s - Média: %.2f\n", aluno.disciplinas[j].codigo_dis, aluno.disciplinas[j].disciplina, aluno.disciplinas[j].media);
    }
    printf("------------------------------------\n");
}

void imprime_vetor_de_alunos(td_aluno alunos[], int qtd_alunos) {
    for (int i = 0; i < qtd_alunos; i++) {
        printf("RA: %d\nNome: %s\nEmail: %s\nMatrícula: %02d/%02d/%04d\n", 
               alunos[i].ra, alunos[i].nome, alunos[i].email, 
               alunos[i].matricula.dia, alunos[i].matricula.mes, alunos[i].matricula.ano);
        printf("Disciplinas:\n");
        for (int j = 0; j < 4; j++) {
            printf("  Código: %d - %s - Média: %.2f\n", alunos[i].disciplinas[j].codigo_dis, alunos[i].disciplinas[j].disciplina, alunos[i].disciplinas[j].media);
        }
        printf("------------------------------------\n");
    }
}

void menu() {
    printf("1 - Cadastrar aluno\n");
    printf("2 - Cadastrar compromisso\n");
    printf("3 - Imprimir compromissos\n");
    printf("4 - Imprimir dados de um aluno\n");
    printf("5 - Imprimir dados de todos os alunos\n");
    printf("6 - Sair\n");
}

int existe_aluno(td_aluno alunos[], int qtd_alunos, int ra_aluno) {
    for (int i = 0; i < qtd_alunos; i++) {
        if (alunos[i].ra == ra_aluno) {
            return 1;
        }
    }
    return 0;
}
