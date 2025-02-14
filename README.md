# Gerenciamento de Alunos e Compromissos

Este projeto, desenvolvido em linguagem C, é uma aplicação voltada para o gerenciamento de informações de alunos, disciplinas e compromissos acadêmicos. Utiliza estruturas (`structs`) para organizar os dados de forma eficiente, além de implementar alocação dinâmica de memória para armazenar e manipular os registros de forma escalável.

## 📌 Funcionalidades

### 📋 Cadastro
- **Alunos**: Cada aluno deve estar matriculado em pelo menos quatro disciplinas, sendo necessário o registro de quatro notas por disciplina e o cálculo da média.
- **Compromissos**: Cada aluno pode registrar compromissos, respeitando a limitação de dois eventos por data e evitando sobreposição de horários.

### ✅ Validação de Dados
- **Data**: Confirma a validade da data antes do armazenamento.
- **Horário**: Verifica se o horário informado é válido.

### 📄 Impressão de Registros
- Exibição de dados de um único aluno ou de todos os alunos cadastrados.
- Listagem de compromissos com ordenação por data, horário e RA.

### 🔄 Alocação Dinâmica de Memória
- **Alunos**: O vetor inicial suporta 10 registros e aumenta em blocos de 10 conforme necessário.
- **Compromissos**: Começa com 15 registros e aumenta em blocos de 5 conforme o preenchimento.

## 🏗 Estruturas de Dados

O projeto emprega diferentes estruturas para representar as entidades do sistema:

```c
// Representação de uma data
typedef struct {
    int dia;
    int mes;
    int ano;
} td_data;

// Representação de um horário
typedef struct {
    int hora;
    int min;
} td_hora;

// Representação de uma disciplina
typedef struct {
    int codigo_dis;
    char disciplina[100];
    float notas[4];
    float media;
} td_disciplina;

// Representação de um aluno
typedef struct {
    int ra;
    char nome[100];
    td_data matricula;
    td_disciplina disciplinas[4];
    char email[100];
} td_aluno;

// Representação de um compromisso
typedef struct {
    td_aluno aluno;
    td_hora horario;
    td_data data;
    char descricao[300];
} td_compromisso;
```

## 🖥 Estrutura do Menu

1. Cadastrar disciplina
2. Cadastrar aluno
3. Cadastrar compromisso
4. Imprimir compromissos:
   - a) De um aluno (ordenado por data e hora).
   - b) De todos os alunos (ordenado por RA, data e hora).
   - c) De uma data específica (ordenado por hora e RA).
   - d) De todas as datas (ordenado por data, hora e RA).
5. Exibir dados de um aluno
6. Exibir dados de todos os alunos (ordenado por RA)
7. Sair

## ⚙️ Implementação Técnica

### 🔧 Alocação e Gerenciamento de Memória
- Vetores de alunos e compromissos são gerenciados dinamicamente para otimizar o uso de memória e garantir escalabilidade.
- Funções específicas garantem a realocação eficiente conforme a necessidade.

### 📌 Ordenação
- A função `qsort` da biblioteca `stdlib.h` é utilizada para ordenar compromissos e alunos conforme critérios pré-definidos.

### 🛡 Validação de Entradas
- O programa valida datas e horários antes de permitir qualquer inserção no sistema.

## 🚀 Como Compilar e Executar

Para compilar o projeto utilizando `gcc`:

```bash
gcc -o gerenciamento_alunos main.c
```

Para executar o programa:

```bash
./gerenciamento_alunos
```

## 🖥 Requisitos do Ambiente

- Compilador C compatível com o padrão ANSI C (exemplo: GCC).
- Sistema operacional compatível com a biblioteca padrão da linguagem C.

---

Com esta aplicação, é possível organizar de forma eficiente informações acadêmicas, garantindo controle e acessibilidade a dados essenciais para a gestão de alunos e seus compromissos.
