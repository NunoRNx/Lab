/**
 * @file main.c
 * @author Nuno Silva (28005@alunos.ipca.pt)
 * @author Joel Faria (28001@alunos.ipca.pt)
 * @author Diogo Graça (28004@alunos.ipca.pt)
 * @brief 
 * Este projeto tem como objetivo criar uma aplicação informática que apoie a gerir um comportamento de alimentação saudável.
 * Controlando e monitorizando a realização de uma deita alimentar saudável, é fundamental.
 * Esta aplicação premite a leitura de vários ficheiros de texto organizados com informação dos pacientes, o seus respetivos planos e diários nutricionais.
 * Tambem permite várias verificações como:
 * -Apresentação do número de pacientes que ultrapassaram determinada quantidade de calorias, num determinado período;
 * -Listagem dos pacientes, ordenada por ordem decrescente do número de paciente, que realizaram alguma refeição com quantidade de calorias fora do intervalo (de acordo com o plano nutricional) num determinado período;
 * -Listar o plano nutricional de um paciente para determinada refeição ao longo de um determinado período;
 * -Cálculo das médias da calorias consumidas por refeição por cada paciente ao longo de um determinado período;
 * -Gerar a tabela das refeições planeadas e realizadas para todos os pacientes, onde consta as seguintes informações: Número de Paciente, Nome, Tipo Refeição, Data de Início, Data de Fim, Calorias Mínimas, Calorias Máximas e Consumo realizado.
 *
 * @version 1.6
 * @date 2023-12-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "header.h"

/**
 * @brief Função para verificar qual comando foi inserido.
 *
 * @param argc quantidade de argumentos no comando.
 * @param argv  argumentos presentes no comando comando guardados num vetor unidimensional.
 * @param qt  quantidade de linhas lidas por ficheiro guardar num vetor unidimensional,
 * qt[0] corresponde às linhas no ficheiro de dados dos pacientes,
 * qt[1] corresponde às linhas no ficheiro do diário dos pacientes,
 * qt[2] corresponde às linhas no ficheiro do plano de todos os pacientes.
 * @param filename  argumentos presentes no comando comando guardados num vetor unidimensional.
 * @param cont contador do numero de argumentos no comando para ignorar, por exemplo: prog -tab -teste.txt, aqui cont=2 para que quero que comece a ser lido o conteúdo a partir de argv[2].
 */

int qt[3];
int main(int argc, char *argv[]) {
    struct Lnut nut[max];
    struct Lpac pac[max];
    struct Lplan pl[max];
    char filename[3][max];

    int i, cont,erro=0;
    FILE *file;

    printf("\n Para exibir todos os comandos digite: lab -c\n");
    printf(" Ajuda: 'lab -ajuda' ou 'lab -a'\n");
    if ((strcmp(argv[1], "-c") == 0)) {
        commands();
    }else{
        if ((argc==2) && ((strcmp(argv[1], "-a") == 0) || (strcmp(argv[1], "-ajuda") == 0))) {
        Ajuda();
        }else{
            if ((argc > 2) && (strcmp(argv[1], "-tab") == 0))
            {
                cont=2;
                for (i = 0; i < 3; i++)
                {
                    namefile(filename, argv, argc, cont);
                }

                for (i = 0; i < argc-2; i++)
                {
                    if (verificarFile(filename[i])==0)
                    {
                        file = fopen(filename[i], "w");
                        printf("\n Ficheiro %s criado.\n", filename[i]);
                        fclose(file);
                        if (i==0)
                        {
                            pacientetab(pac,filename[i]);
                        }
                        if (i==1)
                        {
                            nutricaotab(filename[i]);
                        }
                        if (i==2)
                        {
                            planotab(filename[i]);
                        }
                    }
                    else{
                        file = fopen(filename[i], "a");
                    }
                }
                if (argc==4)
                {
                    strcpy(filename[2],"plano_tab.txt");
                    file = fopen(filename[2], "w");
                    fclose(file);
                    printf("\nFicheiro %s\n", filename[2]);
                    planotab(filename[2]);
                }
                if (argc==3)
                {
                    strcpy(filename[1],"nutricao_tab.txt");
                    file = fopen(filename[1], "w");
                    fclose(file);
                    printf("\n Ficheiro %s\n", filename[1]);
                    nutricaotab(filename[1]);
                    strcpy(filename[2],"plano_tab.txt");
                    file = fopen(filename[2], "w");
                    fclose(file);
                    printf("\n Ficheiro %s\n", filename[2]);
                    planotab(filename[2]);
                }
                leituratab(pac, nut, pl, argv, argc, filename);
                menu(pac, nut, pl);
            }else{
                if ((argc == 5) && (strcmp(argv[1], "-bin") == 0))
                {
                    cont=2;
                    for (i = 0; i < 3; i++)
                    {
                        namefile(filename, argv, argc, cont);
                    }
                    for (i = 0; i < argc-2; i++)
                    {
                        file=fopen(filename[i], "r");
                        if(file==NULL){
                            printf("\n %s nao encontrado.\n", filename[i]);
                            erro++;
                        }else{
                            printf("\n %s encontrado\n", filename[i]);
                        }
                        fclose(file);
                    }
                    if (erro==0)
                    {
                        for ( int x = 0; x < 3; x++)
                        {
                            FILE *filebin;
                            char bin[max];
                            char copy[max];
                            strcpy(copy,filename[x]);
                            file=fopen(filename[x], "r");
                            strcat(filename[x], "_bin.txt");
                            filebin = fopen(filename[x], "w");
                            while (fscanf(file, " %8[^ \t\n]", bin) == 1) {
                                int valor = 0;
                                for (int i = 0; i < 8; i++) {
                                    if (bin[i] == '1') {
                                        valor += pow(2, 7 - i);
                                    }
                                }
                                fprintf(filebin, "%c", valor);
                            }
                            fclose(file);
                            fclose(filebin);
                            int resp=0;
                            do
                            {
                                printf("\n Os dados em binario do ficheiro %s estao dividos entre:\n1-Tab\n2-;\nResp: ", copy);
                                scanf("%d", &resp);
                            } while (resp != 1 && resp != 2);
                            if (resp==1)
                            {
                                leituratab(pac, nut, pl, argv, argc, filename);
                            }
                            if (resp==2)
                            {
                                leituraponto(pac, nut, pl, argv, argc, filename);
                            }
                        }
                        menu(pac, nut, pl);
                    }else{
                        printf("\n Nao foi possivel abrir todos os ficheiros indicados, verifique se os ficheiros em binario estao na mesma pasta que o executavel.\n");
                    }
                }else{
                    if ((strcmp(argv[1], "-bin") == 0))
                    {
                        printf("\n Nao estao presentes todos os argumentos para prosseguir.\n");
                    }else{
                        cont=1;
                        for (i = 0; i < 3; i++)
                        {
                            namefile(filename, argv, argc, cont);
                        }
                        for (i = 0; i < argc-1; i++)
                        {
                            if (verificarFile(filename[i])==0)
                            {
                                file = fopen(filename[i], "w");
                                printf("\n Ficheiro %s criado.\n", filename[i]);
                                fclose(file);
                                if (i==0)
                                {
                                    paciente(pac,filename[i]);
                                }
                                if (i==1)
                                {
                                    nutricao(filename[i]);
                                }
                                if (i==2)
                                {
                                    plano(filename[i]);
                                }
                            }
                            else{
                                file = fopen(filename[i], "a");
                            }
                        }  
                        if (argc==3)
                        {
                            strcpy(filename[2],"plano.txt");
                            file = fopen(filename[2], "w");
                            fclose(file);
                            printf("\nFicheiro %s\n", filename[2]);
                            plano(filename[2]);
                        }
                        if (argc==2)
                        {
                            strcpy(filename[1],"nutricao.txt");
                            file = fopen(filename[1], "w");
                            fclose(file);
                            printf("\nFicheiro %s\n", filename[1]);
                            nutricao(filename[1]);
                            strcpy(filename[2],"plano.txt");
                            file = fopen(filename[2], "w");
                            fclose(file);
                            printf("\nFicheiro %s\n", filename[2]);
                            plano(filename[2]);
                        }
                        leituraponto(pac, nut, pl, argv, argc, filename);
                        menu(pac, nut, pl);
                    }
                }
            }
        }
        
    }
    return 0;
}

/**
 * @brief Comandos
 * Lista dos comandos ao qual a aplicação responde e como eles funcionam.
 */
void commands() {
    printf("\n");
    printf("\nLeitura de dados:\n");
    printf("Dados separados por Tab:\n");
    printf("Comando: 'lab -tab -ficheiro_dos_paciente.extensao -ficheiro_do_diario_nutricional.extensao -ficheiro_do_plano_nutricional.extensao'\n");
    printf("Dados separados por ponto e virgula (;):\n");
    printf("Comando: 'lab -ficheiro_dos_paciente.extensao -ficheiro_do_diario_nutricional.extensao -ficheiro_do_plano_nutricional.extensao'\n");
    printf("Caso um dos nomes de ficheiros inseridos nao exista ira ser iniciada a criacao e insercao manual dos dados no ficheiro do mesmo nome\n");
}

/**
 * @brief Ajuda
 * Texto de ajuda que explica como usar e para que serve o programa.
 */
void Ajuda() {
    printf("\n");
    printf("Bem vindo ao programa.\n");
    printf("Este programa tem como objetivo ajudar a filtrar dados sobre pacientes de um gabite de nutricao.\n");
    printf("Permite:\n -O carregamento de dados em estruturas, calculo de calorias consumidas, \n");
    printf(" -Apresentação do número de pacientes que ultrapassaram determinada quantidade de calorias, num determinado período;\n");
    printf(" -Listagem dos pacientes, ordenada por ordem decrescente do número de paciente, que realizaram alguma refeição com quantidade de calorias fora do intervalo (de acordo com o plano nutricional) num determinado período;\n");
    printf(" -Listar o plano nutricional de um paciente para determinada refeição ao longo de um determinado período;\n");
    printf(" -Cálculo das médias da calorias consumidas por refeição por cada paciente ao longo de um determinado período;\n");
    printf(" -Cálculo das médias da calorias consumidas por refeição por cada paciente ao longo de um determinado período;\n");
    printf(" -Gerar a tabela das refeições planeadas e realizadas para todos os pacientes, onde consta as seguintes informações: Número de Paciente, Nome, Tipo Refeição, Data de Início, Data de Fim, Calorias Mínimas, Calorias Máximas e Consumo realizado.\n");
    printf("Para que perceba como utilizar o programa temos um comando para ver todos os comandos possiveis.\n");
    printf("Vamos entao comecar por explicar.\n");
    printf("O carregamento do conteudo nas estruturas de dados deve ser feito atraves de 3 ficheiros diferentes, um dedicado aos dados dos pacientes, um dedicado ao diario de nutricao de todos os pacientes e um com o plano nutricional de todos os pacientes.\n"); 
    printf("Se o utilizador pretender carregar o conteudo a partir de ficheiros de texto deve escrever a extensao do ficheiro no nome quando inserir o comando, exemplo: -fichiero_exemplo.txt\n");
    printf("Tambem pode inserir ficheiros sem extensao e ficheiros com extensoes de excel como .csv, .xlsx, etc...\n");
    printf("Os argumentos necessitam de estar por esta ordem, primeiro os dados dos pacientes, em segundo o diario de nutricao de todos os pacientes e por ultimo o plano nutricional de todos os pacientes.\n");
    printf("Caso sejam inseridos argumentos a mais, apenas os primeiros 3 argumentos iram ser utilizados\n");
    printf("Caso sejam inseridos argumentos a menos, ira ser inicializada a insercao manual de dados, ira ser criado um fichiero e o nome do ficheiro criado era ser mostrado ao utilizador\n");
    printf("Se o nome do ficheiro nao existir ao nao for possivel abrir o mesmo processo de insercao manual ira comecar.\n");
    printf("Se quiser colocar novamente os argumentos corretos, devera sairdo programa e inicia-lo novamente com a passagem dos argumentos corretos.\n");
    printf("\n");
}