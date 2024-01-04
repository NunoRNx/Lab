/**
 * @file lab.c
 * @author Nuno Silva (28005@alunos.ipca.pt)
 * @author Joel Faria (28001@alunos.ipca.pt)
 * @author Diogo Graça (28004@alunos.ipca.pt)
 * @brief 
 * Funções do projeto
 * @version 1.4
 * @date 2023-12-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "header.h"

/**
 * @brief Função para removeção do Hífen
 *
 * Função para removeção do Hífen dos argumentos que incluem o nome do ficheiro.
 *
 * @param qt  quantidade de linhas lidas por ficheiro guardar num vetor unidimensional,
 * qt[0] corresponde às linhas no ficheiro de dados dos pacientes,
 * qt[1] corresponde às linhas no ficheiro do diário nutricional de todos os pacientes,
 * qt[2] corresponde às linhas no ficheiro do plano nutricional de todos os pacientes.
 */
int namefile(char filename[][max], char* argv[], int argc, int cont){
    int i=0;
    while((cont < argc) && (i < 3)){
    strcpy(filename[i], argv[cont] + 1);
    i++;
    cont++;
    }
    return 0;
}

/**
 * @brief Função verificar se ficheiro existe
 * @return devolve em 0 se o ficheiro foi aberto com sucesso, 1 se não for possivel abrir.
 */
int verificarFile(char* filename){
    FILE *file;
    file=fopen(filename, "r");
    if(file==NULL){
        printf("%s nao existe, a criar...", filename);
        return 0;
    }else{
        printf("\n%s ja existe\n", filename);
        return 1;
    }
    fclose(file);
}

/**
 * @brief Função para ler dados
 * Ler todos os dados e armazenar nas estruturas
 * leituraponto: leitura com dados dividos entre ponto e virgula ";"
 * leituratab: leitura com dados dividos entre espaços "Tab" "  "
 */
int leituraponto(struct Lpac pac[],struct Lnut nut[],struct Lplan pl[], char *argv[], int argc, char filename[][max]){
    int i=0;
    
    /* for (i = 0; i < 3; i++)
    {
       printf("\nMEga teste bin: %s\n", filename[i]);
    } */
    
    FILE *filep=fopen(filename[0], "r");
    FILE *filen=fopen(filename[1], "r"); 
    FILE *filepl=fopen(filename[2], "r");
    //i=0;
    while (fscanf(filep, "%[^;];%[^;];%[^\n]\n", pac[i].code, pac[i].nome, pac[i].tele) == 3) {
        i++;
    }
    qt[0]=i;
    i=0;
    while (fscanf(filen, "%[^;];%d-%d-%d;%[^;];%[^;];%d%*[^\n]\n", nut[i].code, &nut[i].data.dia, &nut[i].data.mes, &nut[i].data.ano, nut[i].refeicao, nut[i].alimento, &nut[i].cal) == 7) {
        nut[i].data.full=nut[i].data.ano*10000+nut[i].data.mes*100+nut[i].data.dia;
        i++;
    }
    qt[1]=i;
    i=0;
    while (fscanf(filepl, "%[^;];%d-%d-%d;%[^;];%d%*[^,], %d%*[^\n]\n", pl[i].code, &pl[i].data.dia, &pl[i].data.mes, &pl[i].data.ano, pl[i].refeicao, &pl[i].calmin, &pl[i].calmax) == 7) {
        pl[i].data.full=pl[i].data.ano*10000+pl[i].data.mes*100+pl[i].data.dia;
        i++;
    }
    qt[2]=i;
    
    fclose(filep);
    fclose(filen);
    fclose(filepl);
    return 0;
}
int leituratab(struct Lpac pac[],struct Lnut nut[],struct Lplan pl[], char *argv[], int argc, char filename[][max]){
    int i=0;
    
    FILE *filep=fopen(filename[0], "r");
    FILE *filen=fopen(filename[1], "r"); 
    FILE *filepl=fopen(filename[2], "r");

    while (fscanf(filep, "%[^;]\t%[^;]\t%[^\n]\n", pac[i].code, pac[i].nome, pac[i].tele) == 3) {
        i++;
    }
    qt[0]=i;
    i=0;
    while (fscanf(filen, "%[^;]\t%d-%d-%d\t%[^;]\t%[^;]\t%d%*[^\n]\n", nut[i].code, &nut[i].data.dia, &nut[i].data.mes, &nut[i].data.ano, nut[i].refeicao, nut[i].alimento, &nut[i].cal) == 7) {
        nut[i].data.full=nut[i].data.ano*10000+nut[i].data.mes*100+nut[i].data.dia;
        i++;
    }
    qt[1]=i;
    i=0;
    while (fscanf(filepl, "%[^;]\t%d-%d-%d\t%[^;]\t%d%*[^,], %d%*[^\n]\n", pl[i].code, &pl[i].data.dia, &pl[i].data.mes, &pl[i].data.ano, pl[i].refeicao, &pl[i].calmin, &pl[i].calmax) == 7) {
        pl[i].data.full=pl[i].data.ano*10000+pl[i].data.mes*100+pl[i].data.dia;
        i++;
    }
    qt[2]=i;
    
    fclose(filep);
    fclose(filen);
    fclose(filepl);
    return 0;
}

/**
 * @brief Inserir dados no ficheiro dos pacientes
 * Inserir manualmente os dados no ficheiro de dados dos pacientes
 * paciente: escrita com dados dividos entre ponto e virgula ";"
 * pacientetab: escrita com dados dividos entre espaços "Tab" "  "
 */
int paciente(struct Lpac pac[], char* filename){
    FILE *file;
    char nump[max], numt[max], nome[max];
    int i, x=0;
    file = fopen(filename, "a");
    do{
        printf("\nNumero de paciente?\n");
        scanf(" %[^\n]%*c", nump);
        for (i = 0; i < qt[0]; i++)
        {
            if (strcmp(pac[i].code,nump)==0)
            {
                printf("Codigo ja foi utilizado, tente um codigo diferente.\n");
            }else{
                x++;
            }
        }
        if (qt[0]==0)
        {
            x++;
        } 
    }while(x==0);
    
    fprintf(file, "%s;", nump);
    printf("\nNome do paciente?\n");
    scanf(" %[^\n]%*c", nome);
    fprintf(file, "%s;", nome);
    printf("\nNumero de telemovel?\n");
    scanf(" %[^\n]%*c", numt);
    fprintf(file, "%s\n", numt);
    fclose(file);
    printf("\nRegisto do paciente criado.\n");
    return 0;
}
int pacientetab(struct Lpac pac[], char* filename){
    FILE *file;
    char nump[max], numt[max], nome[max];
    int i, x=0;
    printf("Teste: %s\n",filename);
    file = fopen(filename, "a");
    do{
        printf("\nNumero de paciente?\n");
        scanf(" %[^\n]%*c", nump);
        for (i = 0; i < qt[0]; i++)
        {
            if (strcmp(pac[i].code,nump)==0)
            {
                printf("Codigo ja foi utilizado, tente um codigo diferente.\n");
            }else{
                x++;
            }
        }
        if (qt[0]==0)
        {
            x++;
        } 
    }while(x==0);
    
    fprintf(file, "%s\t", nump);
    printf("\nNome do paciente?\n");
    scanf(" %[^\n]%*c", nome);
    fprintf(file, "%s\t", nome);
    printf("\nNumero de telemovel?\n");
    scanf(" %[^\n]%*c", numt);
    fprintf(file, "%s\n", numt);
    fclose(file);
    printf("\nRegisto do paciente criado.\n");
    return 0;
}

/**
 * @brief Inserir dados no ficheiro do diário nutricional de todos os pacientes
 * Inserir manualmente os dados no ficheiro do diário nutricional de todos os pacientes
 * nutricao: escrita com dados dividos entre ponto e virgula ";"
 * nutricaotab: escrita com dados dividos entre espaços "Tab" "  "
 */
int nutricao(char* filename){
    FILE *file;
    char nump[max], ref[max], ali[max];
    int mes, dia, ano, cal;
    file = fopen(filename, "a");
    
    printf("\nNumero de paciente?\n");
    scanf(" %[^\n]%*c", nump);
    fprintf(file, "%s;", nump);
    data(&dia, &mes, &ano);
    fprintf(file, "%d-%d-%d;", dia, mes, ano);
    printf("\nTipo de refeicao:\n");
    scanf(" %[^\n]%*c", ref);
    fprintf(file, "%s;", ref);
    printf("\nAlimento:\n");
    scanf(" %[^\n]%*c", ali);
    fprintf(file, "%s;", ali);
    printf("\nCalorias:\n");
    scanf(" %d", &cal);
    fprintf(file, "%d cal\n", cal);
    fclose(file);
    return 0;
}
int nutricaotab(char* filename){
    FILE *file;
    char nump[max], ref[max], ali[max];
    int mes, dia, ano, cal;
    file = fopen(filename, "a");
    
    printf("\nNumero de paciente?\n");
    scanf(" %[^\n]%*c", nump);
    fprintf(file, "%s\t", nump);
    data(&dia, &mes, &ano);
    fprintf(file, "%d-%d-%d\t", dia, mes, ano);
    printf("\nTipo de refeicao:\n");
    scanf(" %[^\n]%*c", ref);
    fprintf(file, "%s\t", ref);
    printf("\nAlimento:\n");
    scanf(" %[^\n]%*c", ali);
    fprintf(file, "%s\t", ali);
    printf("\nCalorias:\n");
    scanf(" %d", &cal);
    fprintf(file, "%d cal\n", cal);
    fclose(file);
    return 0;
}

/**
 * @brief Inserir dados no ficheiro do plano nutricional de todos os pacientes
 * Inserir manualmente os dados no ficheiro do plano nutricional de todos os pacientes
 * plano: escrita com dados dividos entre ponto e virgula ";"
 * planotab: escrita com dados dividos entre espaços "Tab" "  "
 */
int plano(char* filename){
    FILE *file;
    char nump[max], ref[max];
    int mes, dia, ano, minc, maxc;
    file = fopen(filename, "a");
    
    printf("\nNumero de paciente?\n");
    scanf(" %[^\n]%*c", nump);
    fprintf(file, "%s;", nump);
    data(&dia, &mes, &ano);
    fprintf(file, "%d-%d-%d;", dia, mes, ano);
    printf("\nTipo de refeicao:\n");
    scanf(" %[^\n]%*c", ref);
    fprintf(file, "%s;", ref);
    printf("\nCalorias:\n");
    do
    {
        printf("\nMinimo:\t");
        scanf(" %d", &minc);
        printf("\nMaximo:\t");
        scanf(" %d", &maxc);
        if (minc>maxc)
        {
            printf("\nIntervalo de calorias nao valido, cosumo minimo de calorias maior que consumo maximo.\n");
        }
    } while (minc<=maxc);
    fprintf(file, "%d cal, %d cal\n", minc, maxc);
    fclose(file);
    return 0;
}
int planotab(char* filename){
    FILE *file;
    char nump[max], ref[max];
    int mes, dia, ano, minc, maxc;
    file = fopen(filename, "a");
    
    printf("\nNumero de paciente?\n");
    scanf(" %[^\n]%*c", nump);
    fprintf(file, "%s\t", nump);
    data(&dia, &mes, &ano);
    fprintf(file, "%d-%d-%d\t", dia, mes, ano);
    printf("\nTipo de refeicao:\n");
    scanf(" %[^\n]%*c", ref);
    fprintf(file, "%s\t", ref);
    printf("\nCalorias:\n");
    do
    {
        printf("\nMinimo:\t");
        scanf(" %d", &minc);
        printf("\nMaximo:\t");
        scanf(" %d", &maxc);
        if (minc>maxc)
        {
            printf("\nIntervalo de calorias nao valido, cosumo minimo de calorias maior que consumo maximo.\n");
        }
    } while (minc<=maxc);
    fprintf(file, "%d cal, %d cal\n", minc, maxc);
    fclose(file);
    return 0;
}