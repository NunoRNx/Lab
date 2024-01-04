/**
 * @file pi.c
 * @author Nuno Silva (28005@alunos.ipca.pt)
 * @author Joel Faria (28001@alunos.ipca.pt)
 * @author Diogo Graça (28004@alunos.ipca.pt)
 * @brief 
 * Funções do projeto de Programação Imperativa + Verificações de datas e periodos de tempo.
 * @version 1.4
 * @date 2023-12-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "header.h"

/**
 * @brief Leitura e verificação de datas
 * Leitura de uma data introduzida pelo utilizador e verificação de validade da mesma.
 */
int data(int *dia, int *mes, int *ano){
    int x;
    do
    {
        x=0;
        printf("\nInsira a data no seguinte formato dd-mm-yyyy:\nData: ");
        scanf("%d-%d-%d", dia, mes, ano);
        if (*mes<1 || *mes > 12)
        {
            x++;
           printf("\n\nMes invalido.\n");
        }
        if (*dia<1 || *dia > 31)
        {
            x++;
           printf("\n\nDia invalido.\n");
        }
        switch (*mes)
        {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
            //meses com 31 dias
                break;
            case 2:
            //verificar 28/29
                if(*ano%4 == 0){
                    if (*dia>29)
                    {
                        printf("\nData nao e valida, o mes %d contem apenas 29 dias, tente novamente\n", *mes);
                        x++;
                    }
                }else{
                    if (*dia>28)
                    {
                        printf("\nData minima nao e valida, o mes %d contem apenas 28 dias dias no ano %d.\n", *mes, *ano);
                        x++;
                    }
                }
                break;
            case 4:
            case 6:
            case 9:
            case 11:
            //verificar 30 dias
                if (*dia>30)
                {
                    printf("\nData minima nao e valida, o mes %d contem apenas 30 dias.\n", *mes);
                    x++;
                }
                break;
            default:
                break;
        }
        if (x!=0)
        {
            printf("\nPor favor tente novamente.\n");
            
        }else{
            printf("\nData valida!\n");
        }
    } while (x!=0);
    return 0;
}

/**
 * @brief Leitura e verificação de períodos de tempo
 * Leitura de duas datas introduzidas pelo utilizador, data inicial/mínima e data final/máxima e verificação de validade das mesma.
 */
int verifperiodo(int *data0, int *data1){
    int i, x, dia[2], mes[2],ano[2];

    do
    {
        x=0;
        printf("\nInsira periodo no seguinte formato (De dd-mm-yyyy / Ate dd-mm-yyyy):\n");
        printf("De: ");
        scanf("%d-%d-%d", &dia[0], &mes[0], &ano[0]);
        printf("Ate: ");
        scanf("%d-%d-%d", &dia[1], &mes[1], &ano[1]);
        *data0=ano[0]*10000+mes[0]*100+dia[0];
        *data1=ano[1]*10000+mes[1]*100+dia[1];

        if (*data0>*data1)
        {
            x++;
            printf("\nData inicial maior que data final.\n");
        }
        
        if ((mes[0]<1 || mes[0] > 12) || (mes[1]<1 || mes[1] > 12))
        {
            x++;
           printf("\n\nMes invalido.\n");
        }
        if ((dia[0]<1 || dia[0] > 31) || (dia[1]<1 || dia[1] > 31))
        {
            x++;
           printf("\n\nDia invalido.\n");
        }
        
        for ( i = 0; i < 2; i++)
        {
            switch (mes[i])
            {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                //meses com 31 dias
                    break;
                case 2:
                //verificar 28/29
                    if(ano[i]%4 == 0){
                        if (dia[i]>29)
                        {
                            if (i==0)
                            {
                                printf("\nData minima nao e valida, o mes %d contem apenas 29 dias no ano %d.\n", mes[i], ano[i]);
                                x++;
                            }else{
                                printf("\nData maxima nao e valida, o mes %d contem apenas 29 dias no ano %d.\n", mes[i], ano[i]);
                                x++;
                            }
                        }
                    }else{
                        if (dia[i]>28)
                        {
                            if (i==0)
                            {
                                printf("\nData minima nao e valida, o mes %d contem apenas 28 dias no ano %d.\n", mes[i], ano[i]);
                                x++;
                            }else{
                                printf("\nData maxima nao e valida, o mes %d contem apenas 28 dias no ano %d.\n", mes[i], ano[i]);
                                x++;
                            }
                        }
                    }
                    break;
                case 4:
                case 6:
                case 9:
                case 11:
                //verificar 30 dias
                    if (dia[i]>30)
                        {
                            if (i==0)
                            {
                                printf("\nData minima nao e valida, o mes %d contem apenas 30 dias.\n", mes[i]);
                                x++;
                            }else{
                                printf("\nData maxima nao e valida, o mes %d contem apenas 30 dias.\n", mes[i]);
                                x++;
                            }
                        }
                    break;
                default:
                    break;
            }
        }
        if (x!=0)
        {
            printf("\nPor favor tente novamente.\n");
            
        }else{
            printf("\nPeriodo valido!\n");
        }
    } while (x!=0);
    return 0;
}

/**
 * @brief Menu
 * Menu com opções de filtro de dados armazenados nas estruturas
 * @param resp resposta do utilizador perante o menu
 */
int menu(struct Lpac pac[],struct Lnut nut[],struct Lplan plan[]) {
    int resp=0;
    do
    {
        printf("\n\n");
        printf("1-Numero de pacientes que ultrapassaram determinada quantidade de calorias, num determinado periodo\n");
        printf("2-Listagem de Pacientes que realizaram alguma refeicao com quantidade de calorias fora do intervalo\n");
        printf("3-Plano nutricional de um paciente para determinada refeicao\n");
        printf("4-Medias da calorias consumidas por refeicao por cada paciente\n");
        printf("5-Tabela dos os pacientes\n");
        printf("0-Sair\n\n");
        printf("Resp:\t");
        scanf("%d", &resp);
        switch (resp)
        {
        case 1:
            periodo(pac,nut,plan);
            break;
        case 2:
            ListarPaciente(pac,nut,plan);
            break;
        case 3:
            refeicao(pac,plan);
            break;
        case 4:
            medRefeicao(pac,nut);
            break;

        case 5:
            tabela(pac,nut,plan);
            break;
        case 0:
            break;
        default:
            printf("Por favor insira um dos valores indicados\n");
            break;
        }
    } while (resp!=0);
    return 0;
}

/**
 * @brief Quantidade de pacientes que ultrapassaram o plano
 * É um filtro que verifica se algum paciente ultrapassou a quantidade de calorias consumidas que está no seu plano e mostra ao utilizador a quantidade de pacientes que não respeitaram o mesmo.
 * @param data0 data inicial
 * @param data1 data final
 * @param num numero de pacientes que ultrapassaram as calorias do plano
 */
int periodo(struct Lpac pac[],struct Lnut nut[],struct Lplan pl[]){
    int i, x, y, v,num=0, data0, data1;
    
    verifperiodo(&data0, &data1);     
    for (i = 0; i < qt[0]; i++)
    {
        v=0;
        for (x = 0; x < qt[1]; x++)
        {
            if (strcmp(pac[i].code, nut[x].code) == 0) {
                if (data0<=nut[x].data.full && nut[x].data.full<=data1) {
                    for (y = 0; y < qt[2]; y++)
                    {
                        if (nut[x].data.full==pl[y].data.full && (strcmp(nut[x].refeicao,pl[y].refeicao)==0))
                        {
                            if (nut[x].cal > pl[y].calmax) {
                                v++;
                            }
                        }
                    }
                }
            }
        }
        if (v>0)
        {
            num++;
        }
    }
    if (num==0)
    {
        printf("\nTodos os pacientes cumpriram com o plano no periodo determinando.\n");
    }else{
        printf("\n%d pacientes nao cumpriram com o plano no periodo determinado\n", num);
    }
    return 0;
}

/**
 * @brief Verificação de cumprimento do plano
 * É um filtro que verifica se algum paciente não respeitou o seu plano e mostra ao utilizador os pacientes que não respeitaram o mesmo por ordem decrescente.
 * @param data0 data inicial
 * @param data1 data final
 * @param codec guarda em char o codigo do utilizador que não respeitou o seu plano
 * @param codei guarda em char o codigo do utilizador que não respeitou o seu plano e serve para organizar por ordem decrescente
 * @param v verificação se algum paciente não cumpriu com o plano dentro do periodo determinado pelo utilizador,
 * inicializado como 0 se no fim continua como 0 mostra uma mensagem ao utilizador a expressar que nenhum paciente desrespeitou o plano no periodo indicado
 */
int ListarPaciente(struct Lpac pac[],struct Lnut nut[],struct Lplan pl[]){
    int i=0, x, y, v=0, z=0, data0, data1, copyi;
    char copyc[max];
    char codec[max][max];
    int codei[max];

    verifperiodo(&data0, &data1);
    for (i = 0; i < qt[0]; i++)
    {
        v=0;
        for (x = 0; x < qt[1]; x++)
        {
            if (strcmp(pac[i].code, nut[x].code) == 0) {
                if (data0<=nut[x].data.full && nut[x].data.full<=data1) {
                    for (y = 0; y < qt[2]; y++)
                    {
                        if (strcmp(pac[i].code, pl[y].code)==0)
                        {
                            if (nut[x].data.full==pl[y].data.full)
                            {
                                if (strcmp(nut[x].refeicao, pl[y].refeicao) == 0)
                                {
                                    if (pl[y].calmin>nut[x].cal || nut[x].cal>pl[y].calmax)
                                    {                                  
                                        strcpy(codec[z],pac[i].code);
                                        codei[z] = atoi(codec[z]);
                                        z++;
                                        v++;
                                    }
                                } 
                            } 
                        }
                        if (v>0)
                        {
                            y=qt[2];
                        }
                    }
                }
            }
            if (v>0)
            {
                x=qt[1];
            }
        }
    }
    for (i = 0; i < x; i++)
    {
        if (i==0)
        {
        }else{
            x=i;
            while (codei[x]<codei[x-1] && x-1>=0)
            {
                copyi=codei[x-1];
                strcpy(copyc, codec[x-1]);
                codei[x-1]=codei[x];
                strcpy(codec[x-1], codec[x]);
                codei[x]=copyi;
                strcpy(codec[x], copyc);
                x--;
            }
        }
    }
    if (v==0)
    {
        printf("Nenhum pacientes realizou alguma refeicao com quantidade de calorias fora do intervalo no periodo determinado\n");
    }else{    
        printf("Pacientes que realizaram alguma refeicao com quantidade de calorias fora do intervalo no periodo determinado:\n");
        for (x = 0; v > x; v--)
        {
            printf("\nPaciente:%s\n",codec[v]);
        }
    }
    return 0;
}

/**
 * @brief Pesquisa de refeição no plano
 * É um filtro que verifica se os pacientes têm no plano a refeição indicada pelo utilizador.
 * @param data0 data inicial
 * @param data1 data final
 * @param refeicao guarda em char a refeição que o utilizador prentede pesquisar
 * @param v verificação se os pacientes têm no plano a refeição indicada pelo utilizador dentro do periodo de tempo determinado,
 * inicializado como 0 antes de passar para o próximo paciente mostra uma mensagem ao utilizador a expressar que a refeição não se encontra no plano no periodo indicado
 */
int refeicao(struct Lpac pac[],struct Lplan pl[]){
    int i,x,v,data0,data1;
    char refeicao[max];
    verifperiodo(&data0, &data1);
    printf("\nRefeicao?\nResp: ");
    scanf(" %[^\n]%*c", refeicao);
    for (i = 0; i < qt[0]; i++)
    {
        v=0;
        printf("\nPaciente: %s\n", pac[i].code);
        for (x = 0; x < qt[2]; x++)
        {
            if (strcmp(pac[i].code, pl[x].code) == 0)
            {
                if (data0<=pl[x].data.full && pl[x].data.full<=data1)
                {
                    if (strcmp(refeicao, pl[x].refeicao) == 0)
                    {
                        printf("Dia: %d-%d-%d\n", pl[x].data.dia, pl[x].data.mes, pl[x].data.ano);
                        printf("Calorias:\n");
                        printf("Minimas: %d\n",pl[x].calmin);
                        printf("Maximas: %d\n",pl[x].calmax);
                        v++;
                    }
                }
            }
        }
        if (v==0)
        {
            printf("O paciente %s nao tem nenhum plano para a refeicao %s no periodo que indicou.\n", pac[i].code, refeicao);
        }
    }
    return 0;
}

/**
 * @brief Cálculo das médias da calorias consumidas
 * É um filtro que cálcula as médias da calorias consumidas por refeição por cada paciente ao longo de um determinado período de tempo indicado pelo utilizador.
 * @param data0 data inicial
 * @param data1 data final
 * @param media guarda o valor da médias da calorias consumidas 
 * @param caltotal guarda as calorias totais consumidas por refeição por cada paciente
 */
int medRefeicao(struct Lpac pac[],struct Lnut nut[]){
    int i=0, x, cont, data0, data1;
    float media, caltotal;

    verifperiodo(&data0, &data1);
    printf("teste 1");
    printf("teste qt %d", qt[0]);
    for (i = 0; i < qt[0]; i++)
    {
        printf("teste 1");
        caltotal=0;
        cont=0;
        for (x = 0; x < qt[1]; x++)
        {
            if (strcmp(pac[i].code, nut[x].code) == 0) {
                if (data0<=nut[x].data.full && nut[x].data.full<=data1)
                {
                    caltotal+=nut[x].cal;
                    cont++;
                }
            }
        }
        printf("teste 1");
        media=caltotal/cont;
        printf("\nPaciente: %s\n", pac[i].code);
        printf("Media de calorias por refeicao: %.1f\n", media);
    }
    return 0;
}

/**
 * @brief Gerar tabela
 * É um filtro que gera uma tabela das refeições planeadas e realizadas para todos os pacientes, onde consta a seguinte informação: Número de Paciente, Nome, Tipo Refeição, Data deInício,Data de Fim, Calorias Mínimo, Calorias Máximo e Consumo realizado.
 * @param data0 data inicial
 * @param data1 data final
 * @param tabela guarda todas as diferentes refeições que existem no diário dos pacientes
 * @param y quantidade de diferentes refeições que existem no diário dos pacientes
 * @param caltotal guarda as calorias totais consumidas por refeição por cada paciente
 */
int tabela(struct Lpac pac[],struct Lnut nut[],struct Lplan pl[]){
    int i, a, w=0, x, y, z,qtt=0;
    struct Tabela t[max];
    char tabela[max][max];

    for (i = 0; i < qt[1]; i++)
    {
        t[i].calconsum=0;
        t[i].calmin=0;
        t[i].calmax=0;
    }
    
    for (i = 0; i < qt[1]; i++)
    {
        y=0;
        if (i==0)
        {
            strcpy(tabela[i], nut[i].refeicao);
            qtt++;
        }else{
            for (x = 0; x < qtt; x++)
            {
                if (strcmp(tabela[x],nut[i].refeicao)==0)
                {
                    y++;
                }
            }
            if (y==0)
            {
                strcpy(tabela[qtt], nut[i].refeicao);
                qtt++;
            }
        }
    }

    for (i = 0; i < qt[0]; i++)
    {
        for (x = 0; x < qtt; x++){
            z=0;
            for (y = 0; y < qt[1]; y++)
            {
                if(strcmp(pac[i].code,nut[y].code)==0){
                    if (strcmp(tabela[x], nut[y].refeicao)==0)
                    {
                        for (a = 0; a < qt[2]; a++)
                        {
                            if (nut[y].data.full==pl[a].data.full && (strcmp(tabela[x],pl[a].refeicao)==0) && (strcmp(pl[a].code,pac[i].code)==0))
                            {
                                if (z==0)
                                {
                                    t[w].dataini.dia=nut[y].data.dia;
                                    t[w].dataini.mes=nut[y].data.mes;
                                    t[w].dataini.ano=nut[y].data.ano;
                                    t[w].dataini.full=nut[y].data.full;
                                    t[w].datafim.dia=nut[y].data.dia;
                                    t[w].datafim.mes=nut[y].data.mes;
                                    t[w].datafim.ano=nut[y].data.ano;
                                    t[w].datafim.full=nut[y].data.full;
                                    t[w].calconsum+=nut[y].cal;
                                    t[w].calmax+=pl[a].calmax;
                                    t[w].calmin+=pl[a].calmin;
                                }else{
                                    if (t[w].dataini.full>nut[y].data.full)
                                    {
                                        t[w].dataini.dia=nut[y].data.dia;
                                        t[w].dataini.mes=nut[y].data.mes;
                                        t[w].dataini.ano=nut[y].data.ano;
                                        t[w].dataini.full=nut[y].data.full;
                                    }
                                    if (t[w].datafim.full<nut[y].data.full)
                                    {
                                        t[w].datafim.dia=nut[y].data.dia;
                                        t[w].datafim.mes=nut[y].data.mes;
                                        t[w].datafim.ano=nut[y].data.ano;
                                        t[w].datafim.full=nut[y].data.full;
                                    }
                                    t[w].calconsum+=nut[y].cal;
                                    t[w].calmax+=pl[a].calmax;
                                    t[w].calmin+=pl[a].calmin;
                                }
                                z++;
                            }
                        }
                    }
                }
            }
            if (z==0)
            {
                //paciente nao fez refeicao tabela[x]
            }else{
                printf("|NP: %s |Nome: %s ", pac[i].code, pac[i].nome);
                printf("|Refeicao: %s ",tabela[x]);
                printf("|Inicio: %d-%d-%d |Fim: %d-%d-%d ", t[w].dataini.dia, t[w].dataini.mes, t[w].dataini.ano, t[w].datafim.dia, t[w].datafim.mes, t[w].datafim.ano);
                printf("|Minimo: %d |Maximo: %d |Consumo: %d|\n\n", t[w].calmin, t[w].calmax, t[w].calconsum);
                w++;
            } 
        }
    }
    if (w==0)
    {
        printf("\nNenhuma refeicao registada no periodo indicado.\n");
    }
    return 0;
}