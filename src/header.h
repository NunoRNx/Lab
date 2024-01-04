/**
 * @file header.h
 * @author Nuno Silva (28005@alunos.ipca.pt)
 * @author Joel Faria (28001@alunos.ipca.pt)
 * @author Diogo Graça (28004@alunos.ipca.pt)
 * @brief 
 * Main com função de mostrar comandos e função de ajuda
 * @version 1.0
 * @date 2023-12-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/**
 * @brief Bibliotecas.
 * @param max definido como 100 para utilizar como limite de vetores, quantidade de caracters, etc...
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define max 100

/**
 * @brief Estrutura de datas
 *
 * Estas estruturas foi criada com intenção de ser utilizada em outras estruturas que precisem de datas.
 * Desta forma em fez de criar mais 4 variaveis em 3 diferentes estruturas temos 1 estrutura separada com todas as 4.
 */
struct Data {
    int dia;
    int mes;
    int ano;
    int full;
};
/**
 * @brief Estruturas de armazenamento de dados
 *
 * Estas estruturas são para armazenar os dados de cada ficheiro:
 * Lpac para guardar os dados dos pacientes;
 * Lnut para guardar os dados do diario de nutricao dos pacientes;
 * Lpac para guardar os dados do plano de todos os pacientes.
 */
struct Lpac {
    char code[max];
    char nome[max];
    char tele[max];
};
struct Lnut {
    char code[max];
    struct Data data;
    char refeicao[max];
    char alimento[max];
    int cal;
};
struct Lplan {
    char code[max];
    struct Data data;
    char refeicao[max];
    int calmin;
    int calmax;
};
/**
 * @brief Estrutura Tabela
 *
 * Esta estrutura serve para armazenar os dados de cada refeição por paciente desda primeira refeição até à ultima.
 */
struct Tabela {
    struct Data dataini;
    struct Data datafim;
    char refeicao[max];
    int calmax;
    int calmin;
    int calconsum;
};

extern int qt[3];

/**
 * @brief Declaração de funções
 * Declaração de todas as funções presentes em todo o projeto.
 */
void commands();
void Ajuda();
int namefile(char filename[][max], char* argv[], int argc, int cont);
int verificarFile(char* filename);
int paciente(struct Lpac pac[], char* filename);
int pacientetab(struct Lpac pac[], char* filename);
int nutricao(char* filename);
int nutricaotab(char* filename);
int plano(char* filename);
int planotab(char* filename);
int leituraponto(struct Lpac pac[],struct Lnut nut[],struct Lplan pl[], char *argv[], int argc, char filename[][max]);
int leituratab(struct Lpac pac[],struct Lnut nut[],struct Lplan pl[], char *argv[], int argc, char filename[][max]);
int menu(struct Lpac pac[], struct Lnut nut[], struct Lplan pl[]);
int periodo(struct Lpac pac[],struct Lnut nut[],struct Lplan pl[]);
int ListarPaciente(struct Lpac pac[],struct Lnut nut[],struct Lplan pl[]);
int refeicao(struct Lpac pac[],struct Lplan pl[]);
int medRefeicao(struct Lpac pac[],struct Lnut nut[]);
int tabela(struct Lpac pac[],struct Lnut nut[],struct Lplan pl[]);
int data(int *dia, int *mes, int *ano);
int verifperiodo(int *data0, int *data1);