#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLI 500
#define MAX_VC  20
#define MAX_ESC 6
#define MAX_TXT 40
#define MAX_CONT 1000

typedef struct data {
  short int dia;
  short int mes;
  short int ano;
}data_tipo;

typedef struct veiculo {
  short int cod_vc;
  char      marca[10];
  char      modelo[10];
  char      matricula[8];
  short int cod_categoria;
  float     km;
  float     qt_comb;
  char      estado;
  short int local_ini;

}veiculo_tipo;

typedef struct contrato {
  short int cod_vc;
  short int cod_cl;
  float     preco_dia;
  float     preco_km;
  float     qt_km;
  data_tipo data_ini;
  data_tipo data_fim;
  short int escritorio_ini;
  short int escritorio_fim;
}contrato_tipo;

typedef struct cliente {
  short int cod_cl;
  char      nome[30];
  char      morada[40];
  short int tipo;
  char      carta_conducao[11];
}cliente_tipo;

char categoria[][10]={"capucine","integral","perfilada","furgao","citadina","utilitaria","familiar"};


short int lerInteiro(short int li,short int ls)
{
    short int num, certo=0;
    char valor[MAX_TXT];
    do
    {
        printf("\nDigite um valor entre %u e %u: ",li,ls);
        gets(valor);
        if (strlen(valor)==4)
        {
           num=atoi(valor);
           if (num>=li && num<=ls)
              certo=1;
           else
               printf("\nUnicamente digitos entre %u e %u !",li,ls);
        }
        else
            printf("\nComprimento invalido !");
    }while(certo==0); // enquanto o valor lido n�o estiver correcto
    return num;
}
// Esta fun��o l� inteiros de 1 e 2 d�gitos, enquanto que o lerInteiro que s� l� de 4 d�gitos
short int lerInteiroVec(short int li,short int ls)
{
    short int num, certo=0;
    char valor[MAX_TXT];
    do
    {
        printf("\nDigite um valor entre %u e %u: ",li,ls);
        gets(valor);
        if (strlen(valor)==1 ||strlen(valor)==2)
        {
           num=atoi(valor);
           if (num>=li && num<=ls)
              certo=1;
           else
               printf("\nUnicamente digitos entre %u e %u !",li,ls);
        }
        else
            printf("\nComprimento invalido !");
    }while(certo==0); // enquanto o valor lido n�o estiver correcto
    return num;
}
// Esta fun��o l� floats num determinado intervalo
float lerFloat(float li, float ls)
{
    float num=-10;
    do
    {
     printf("\nInsira um valor entre %.2f e %.2f: ",li,ls);
     scanf("%f", &num);
    }while(num<li || num>ls);
    return num;
}

void lerChars(char *s, short int tam, char *info)
{
     short int i=0;
     char ch;
     puts(info);
     ch=getchar();
     while(ch!='\n' && i<tam)
     {
        s[i]=ch;
        i++;
        ch=getchar();
     }
     s[i]='\0';
}
// Esta fun��o valida as datas. Quando o utilizador insere o ano e o m�s o programa verifica quantos dias ter� para cada situa��o
void validarData(data_tipo data[]){
    short int i, mes, ano, dia;
    char valor[MAX_TXT];
    printf("Indique o ano");
    ano = lerInteiro(1950,2050);
    printf("Indique o m�s");
    mes = lerInteiroVec(1,12);
            if((mes == 1) || (mes == 3) || (mes == 5) || (mes == 5) || (mes == 7) || (mes == 8) || (mes == 10) || (mes == 12)){
                printf("mes de 31 dias");
                dia = lerInteiroVec(1,31);
            }
            else
                {
                if(mes==2)
                {
                    if(((ano % 4) == 0) && ((ano % 100) != 0) || ((ano % 400) == 0)){
                        printf("mes de 29 dias");
                        dia = lerInteiroVec(1,29);
                    }
                    else{
                        printf("mes de 28 dias");
                        dia = lerInteiroVec(1,28);
                    }
                }
                 else{
                    printf("mes de 30 dias");
                    dia = lerInteiroVec(1,30);
                 }
                }
    data[0].dia = dia;
    data[0].mes = mes;
    data[0].ano = ano;
}

short int procurarCodigo(cliente_tipo cli[], short int qtd, short int cod)
{
    short int i, enc=-1;

    for(i=0;i<=qtd && enc==-1;i++)
       if (cli[i].cod_cl==cod)
            enc=i;

    return enc;
}
//Esta fun��o procura o c�digo do ve�culo. A fun��o foi baseada no procurarCodigo do codigo base
short int procurarCodigoVec(veiculo_tipo vec[], short int qtd, short int cod)
{
    short int i, enc=-1;

    for(i=0;i<=qtd && enc==-1 ; i++)
       if (vec[i].cod_vc==cod)
            enc=i;

    return enc;
}
//Esta fun��o pesquisa a data para a op��o 22, onde � pedida a data e o carro para encontrar a posi��o pedida
short int procurarData(contrato_tipo cont[], data_tipo data[],short int qtd )
{
    short int i, enc=-1;
    data_tipo dataux[0];
    validarData(data);
    for(i=0;i<=qtd; i++)
       if (cont[i].data_ini.dia==data[0].dia && cont[i].data_ini.mes==data[0].mes && cont[i].data_ini.ano == data[0].ano)
            enc=i;

    return enc;
}

// L� dados de um cliente e guarda no vetor
void inserirCli(cliente_tipo cli[], short int *qtd)
{
     short int n, i, encontrou=-1;
     char valor[MAX_TXT];

     if (*qtd==MAX_CLI)
        printf("\nDe momento nao admitimos mais clientes!!\n");
     else
     {
         printf("\n--- Dados do cliente ---");
         n=lerInteiro(1000,9999);
         encontrou=procurarCodigo(cli,*qtd,n);
         printf("\n\t\t encontrou %hd e *qtd %hd ",encontrou, *qtd);
         while(encontrou>=0) // Significa que � repetido e n�o pode acontecer!!!
         {
             n=lerInteiro(1000,9999);
             encontrou=procurarCodigo(cli,*qtd,n);
         }
         printf("\n\t\t Fora: ");
         cli[*qtd].cod_cl=n;
         lerChars(valor,30,"\nNome (max 30 caracteres):");
         printf("\n\t %s ", valor);
         strcpy(cli[*qtd].nome,valor);
         lerChars(valor,40,"\nMorada (max 40 caracteres):");
         printf("\n\t %s ", valor);
         strcpy(cli[*qtd].morada,valor);
         lerChars(valor,5,"\nCarta de conducao (max 5 caracteres):");
         printf("\n\t %s \n", valor);
         strcpy(cli[*qtd].carta_conducao,valor);
         cli[*qtd].tipo=0;
         getchar();
     }
     (*qtd)++;  // Incrementa a quantidade de clientes existentes no vector
}
//Esta fun��o insere um ve�culo, validando sempre o codigo e a categoria inserida, pois ser� importante para o contrato
void inserirVec(veiculo_tipo vec[], short int *qtd, short int local[][MAX_ESC])
{
     short int n, i, encontrou=-1;
     char valor[MAX_TXT], valor2;

     if (*qtd==MAX_VC)
        printf("\nDe momento nao admitimos mais carros!!\n");
     else
     {
         printf("\n--- Dados do carro ---");
         n=lerInteiroVec(10,99);
         encontrou=procurarCodigoVec(vec,*qtd,n);
         printf("\n\t\t encontrou %hd e *qtd %hd ",encontrou, *qtd);
         while(encontrou>=0) // Significa que � repetido e n�o pode acontecer!!!
         {
             n=lerInteiroVec(10,99);
             encontrou=procurarCodigoVec(vec,*qtd,n);
         }
         printf("\n\t\t Fora: ");
         vec[*qtd].cod_vc=n;
         lerChars(valor,10,"\nMarca (max 10 caracteres):");
         printf("\n\t %s ", valor);
         strcpy(vec[*qtd].marca,valor);
         lerChars(valor,10,"\nModelo (max 10 caracteres):");
         printf("\n\t %s ", valor);
         strcpy(vec[*qtd].modelo,valor);
         lerChars(valor,8,"\nMatricula (max 8 caracteres):");
         printf("\n\t %s ", valor);
         strcpy(vec[*qtd].matricula,valor);
         printf("\nC�digo Categoria:\n");
         vec[*qtd].cod_categoria=lerInteiroVec(0,6);
         vec[*qtd].estado='d';
         //Atrav�s da categoria � definido se se trata de uma caravana ou autocaravana, o que ir� ditar diferen�as em todas as fun��es do contrato.
         if(vec[*qtd].cod_categoria<4){
            printf("\nKms:\n");
            vec[*qtd].km=lerFloat(0,9999);
            printf("\nQuantidade de Combust�vel\n");
            vec[*qtd].qt_comb=lerFloat(0,9999);
         }
        printf("\nEscritorio onde se encontra o veiculo");
        printf("\n0 Braga 1 Coimbra 2 Guarda 3 Faro 4 Lisboa 5 Porto");
        n=lerInteiroVec(0,5);
        (local[*qtd][n])++;
        vec[*qtd].local_ini=n;
        (*qtd)++;  // Incrementa a quantidade de ve�culos existentes no vector
     }

}
// Esta fun��o serve para alugar um ve�culo. Serve-se das fun��es procurarCodigo e procurarCodigoVec, por�m, neste caso, o que interessa � que ele exista, logo faz-se while(encontrou<0)
void inserirContrato(contrato_tipo cont[], cliente_tipo cli[], veiculo_tipo vec[], short int local[][MAX_ESC], data_tipo data[], short int qtdcli, short int qtdvec, short int *qtd){
         if(*qtd==MAX_CONT)
            printf("De momento n�o aceitamos mais contratos...");
         else{
            short int n, encontrou=-1, aux=0, i;
            char valor[MAX_TXT], valor2;
            if(qtdvec==0 || qtdcli==0)
                printf("N�o existem clientes/veiculos para efectuar o contrato\n");
            else
            {
                printf("\nInsira o n�mero de cliente\n");
                n=lerInteiro(1000,9999);
                encontrou=procurarCodigo(cli,qtdcli,n);
                printf("\n\t\t encontrou %hd e *qtd %hd ",encontrou, *qtd);
                while(encontrou<0)
                {
                    n=lerInteiro(1000,9999);
                    encontrou=procurarCodigo(cli,qtdcli,n);
                    printf("\n\t\t encontrou %hd e *qtd %hd ",encontrou, *qtd);

                }
                if(cli[encontrou].tipo==1)
                    printf("\nO cliente � de risco pelo que n�o lhe � poss�vel efectuar contratos\n");
                else{
                    printf("\n\t\t Fora: ");
                    cont[*qtd].cod_cl=n;
                    printf("\nInsira o n�mero do ve�culo\n");
                    n=lerInteiroVec(10,99);
                    encontrou=procurarCodigoVec(vec,qtdvec,n);
                    printf("\n\t\t encontrou %hd e *qtd %hd ",encontrou, *qtd);
                    while(encontrou<0)
                    {
                        n=lerInteiroVec(10,99);
                        encontrou=procurarCodigoVec(vec,qtdvec,n);
                        printf("\n\t\t encontrou %hd e *qtd %hd ",encontrou, *qtd);
                    }
                    if (vec[encontrou].estado=='a')
                        printf("\nN�o � poss�vel alugar este ve�culo pois o mesmo n�o se encontra dispon�vel\n");
                    else{
                        vec[encontrou].estado='a';
                        printf("\n\t\t Fora: ");
                        cont[*qtd].cod_vc=n;
                        valor2='?';
                        if(vec[encontrou].cod_categoria>3){
                            printf("\nIndique o pre�o por dia\n");
                            cont[*qtd].preco_dia=lerFloat(0.01,9999);
                        }
                        else{
                            printf("\nIndique o pre�o por km\n");
                            cont[*qtd].preco_km=lerFloat(0.01,9999);
                        }
                        validarData(data);
                        cont[*qtd].data_ini= data[0];
                        for(i=0;i<*qtd;i++)
                            while((cont[*qtd].cod_vc==cont[i].cod_vc && cont[*qtd].data_ini.dia>=cont[i].data_ini.dia && cont[*qtd].data_ini.dia<cont[*qtd].data_fim.dia && cont[*qtd].data_ini.mes==cont[i].data_ini.mes && cont[*qtd].data_ini.mes== cont[i].data_fim.mes && cont[*qtd].data_ini.ano == cont[i].data_ini.ano && cont[*qtd].data_ini.ano==cont[i].data_fim.ano) || (cont[*qtd].cod_vc==cont[i].cod_vc && cont[*qtd].data_ini.mes>=cont[i].data_ini.mes && cont[*qtd].data_ini.mes<cont[i].data_fim.mes && cont[*qtd].data_ini.ano== cont[i].data_ini.ano && cont[*qtd].data_ini.ano==cont[i].data_fim.ano) || (cont[*qtd].cod_vc==cont[i].cod_vc && cont[*qtd].data_ini.ano>=cont[i].data_ini.ano && cont[*qtd].data_ini.ano<cont[i].data_fim.ano) ){
   //Nota: Este while faz o seguinte: No caso de existir um contrato de 1/1/2000 a 1/1/2001, como este ja foi finalizado, o veiculo passaria a 'd' e seria possivel outra vez alug�-lo. Por�m, este while n�o permite que hajam alugueres entre as datas de outro aluguer do mesmo veiculo, logo, por exemplo, a data 22/2/2000 ser� impossivel para o mesmo vec.
                                printf("\nO ve�culo em quest�o esteve alugado na data em que inseriu, pelo que seria imposs�vel alug�-lo pois este estava indispon�vel\n");
                                validarData(data);
                                cont[*qtd].data_ini= data[0];
                            }
//A partir desta linha, � verificado o numero de vezes que o contrato existe para validar o escritorio inicial e final, e tamb�m para alterar a matriz(ultimo ciclo for)
                        for(i=0; i<*qtd; i++)
                            if(cont[*qtd].cod_vc==cont[i].cod_vc)
                                aux++;

                        if (aux==0)
                            cont[*qtd].escritorio_ini=vec[encontrou].local_ini;
                        else if(aux>0){
                            for(i=0;i<*qtd;i++)
                                if(cont[*qtd].cod_vc==cont[i].cod_vc)
                                    aux=i;
                            cont[*qtd].escritorio_ini=cont[aux].escritorio_fim;
                        }
                        (*qtd)++;
                        for(i=0;i<=MAX_ESC;i++){
                            if(local[encontrou][i]==1)
                                (local[encontrou][i])--;
                        }
                    }
                }
            }
        }
}

//Esta fun��o devolve o ve�culo. � verificado se este j� foi terminado para nao haver altera��o de valores.
void acabarContrato(contrato_tipo cont[], short int pos, data_tipo data[], veiculo_tipo vec[], cliente_tipo cli[], short int qtdcli, short int qtdvec, short int qtdcont, short int local[][MAX_ESC]){
         if(cont[pos].data_fim.dia!=0)
            printf("\n O contrato j� foi finalizado!!!\n");
         else{
            char valor2='?';
            short int i, aux, encontrou;
            float custo;
            printf("\nO ve�culo foi devolvido em bom estado? Sim(s) N�o(n)\n");
            valor2='?';
            while(valor2!='s' && valor2!='S' && valor2!='n' && valor2!='N'){
                scanf("%c",&valor2);
            }
            if(valor2=='n' || valor2=='N'){
                aux=procurarCodigo(cli,qtdcli,cont[pos].cod_cl);
                cli[aux].tipo=1;
            }
            encontrou=procurarCodigoVec(vec,qtdvec,cont[pos].cod_vc);
            vec[encontrou].estado='d';
            if(vec[encontrou].cod_categoria<4){
                printf("\n Indique a quantidade de kms\n");
                cont[pos].qt_km=lerFloat(0.01,5000);
                vec[encontrou].km=cont[pos].qt_km+ vec[encontrou].km;
                custo =cont[pos].qt_km * cont[pos].preco_km;
                printf("\nO custo � %.2f\n",custo);
            }
            validarData(data);
            cont[pos].data_fim= data[0];
            for(i=0;i<qtdcont;i++)
//Nota: Este while faz o seguinte: No caso de existir um contrato de 1/1/2000 a 1/1/2001, como este ja foi finalizado, o veiculo passaria a 'd' e seria possivel outra vez alug�-lo. Por�m, este while n�o permite que hajam alugueres entre as datas de outro aluguer do mesmo veiculo, logo, por exemplo, a data 22/2/2000 ser� impossivel para o mesmo vec.
                while((cont[pos].cod_vc==cont[i].cod_vc && cont[pos].data_fim.dia>cont[i].data_ini.dia && cont[pos].data_fim.dia<cont[pos].data_fim.dia && cont[pos].data_fim.mes==cont[i].data_ini.mes && cont[pos].data_ini.mes== cont[i].data_fim.mes && cont[pos].data_fim.ano == cont[i].data_ini.ano && cont[pos].data_fim.ano==cont[i].data_fim.ano) || (cont[pos].cod_vc==cont[i].cod_vc && cont[pos].data_fim.mes>=cont[i].data_ini.mes && cont[pos].data_fim.mes<cont[i].data_fim.mes && cont[pos].data_fim.ano== cont[i].data_ini.ano && cont[pos].data_fim.ano==cont[i].data_fim.ano) || (cont[pos].cod_vc==cont[i].cod_vc && cont[pos].data_fim.ano>=cont[i].data_ini.ano && cont[pos].data_fim.ano<cont[i].data_fim.ano) ){
                    printf("\nO ve�culo em quest�o esteve alugado na data em que inseriu, pelo que seria imposs�vel alug�-lo pois este estava indispon�vel\n");
                    validarData(data);
                    cont[pos].data_ini= data[0];
                    }
//Este while verifica se a data final � menor que a inicial. Enquanto for, ir� sempre pedir datas novas, estando a data final e a inicial validadas consoante o mes e o ano.
            while((cont[pos].data_ini.dia>cont[pos].data_fim.dia && cont[pos].data_ini.mes==cont[pos].data_fim.mes && cont[pos].data_ini.ano==cont[pos].data_fim.ano)||(cont[pos].data_ini.mes>cont[pos].data_fim.mes && cont[pos].data_ini.ano==cont[pos].data_fim.ano) || cont[pos].data_ini.ano>cont[pos].data_fim.ano){
                printf("\n A data � inv�lida! Insira outra vez...\n");
                validarData(data);
                cont[pos].data_fim= data[0];
            }
            // Volta a escrever a nova posi��o da caravana na matriz, que ao ter sido alugada passou a estar num local desconhecido
            printf("\nEscritorio onde se encontra o veiculo:");
            printf("\n0 Braga 1 Coimbra 2 Guarda 3 Faro 4 Lisboa 5 Porto");
            aux=lerInteiroVec(0,5);
            //O escritorio final ser� igual a localiza��o depois deste contrato
            cont[pos].escritorio_fim=aux;
            (local[encontrou][aux])++;
         }
}
// Esta fun��o difere da fun��o inserirContrato pois esta baseia-se em qualquer posi��o da fun��o, modificando-a, logo nao altera o valor da quantidade.
void editarContrato(contrato_tipo cont[], veiculo_tipo vec[], short int pos, data_tipo data[], short int qtdvec, short int qtd){
            if (cont[pos].data_fim.ano !=0)
                printf("\n N�o � poss�vel editar o contrato pois este j� se encontra finalizado\n");
            else{
                short int i, encontrou;
                char valor2;
                encontrou=procurarCodigoVec(vec,qtdvec,cont[pos].cod_vc);
                if(vec[encontrou].cod_categoria>3){
                    printf("\nIndique o pre�o por dia\n");
                    cont[pos].preco_dia=lerFloat(0.01,9999);
                }
                else{
                    printf("\nIndique o pre�o por km\n");
                    cont[pos].preco_km=lerFloat(0.01,9999);
                }
                validarData(data);
                cont[pos].data_ini= data[0];
                for(i=0;i<qtd;i++)
                while((cont[pos].cod_vc==cont[i].cod_vc && cont[pos].data_ini.dia>=cont[i].data_ini.dia && cont[pos].data_ini.dia<cont[pos].data_fim.dia && cont[pos].data_ini.mes==cont[i].data_ini.mes && cont[pos].data_ini.mes== cont[i].data_fim.mes && cont[pos].data_ini.ano == cont[i].data_ini.ano && cont[pos].data_ini.ano==cont[i].data_fim.ano) || (cont[pos].cod_vc==cont[i].cod_vc && cont[pos].data_ini.mes>=cont[i].data_ini.mes && cont[pos].data_ini.mes<cont[i].data_fim.mes && cont[pos].data_ini.ano== cont[i].data_ini.ano && cont[pos].data_ini.ano==cont[i].data_fim.ano) || (cont[pos].cod_vc==cont[i].cod_vc && cont[pos].data_ini.ano>=cont[i].data_ini.ano && cont[pos].data_ini.ano<cont[i].data_fim.ano) ){
                    printf("\nO ve�culo em quest�o esteve alugado na data em que inseriu, pelo que seria imposs�vel alug�-lo pois este estava indispon�vel\n");
                    validarData(data);
                    cont[pos].data_ini= data[0];
                }
            }
}

// Esta fun��o difere da fun��o inserirCli pois esta baseia-se em qualquer posi��o da fun��o, modificando-a, logo nao altera o valor da quantidade.
void editarCli(cliente_tipo cli[], contrato_tipo cont[], short int pos){
    int i, aux=0;
    for(i=0; i<MAX_CONT;i++){
        if(cont[i].cod_cl==cli[pos].cod_cl && cont[i].data_fim.dia==0){
            printf("\n O cliente encontra-se em contrato pelo que n�o � poss�vel modific�-lo\n");
            aux++;
        }
    }
    if(aux==0) {
         short int n;
         printf("\n--- Dados do cliente ---");
         char valor[MAX_TXT];
         lerChars(valor,30,"\nNome (max 30 caracteres):");
         printf("\n\t %s ", valor);
         strcpy(cli[pos].nome,valor);
         lerChars(valor,40,"\nMorada (max 40 caracteres):");
         printf("\n\t %s ", valor);
         strcpy(cli[pos].morada,valor);
         lerChars(valor,5,"\nCarta de conducao (max 5 caracteres):");
         printf("\n\t %s \n", valor);
         strcpy(cli[pos].carta_conducao,valor);
    }
}

// Esta fun��o difere da fun��o inserirVec pois esta baseia-se em qualquer posi��o da fun��o, modificando-a, logo nao altera o valor da quantidade.
void editarVec(veiculo_tipo vec[], contrato_tipo cont[], short int pos, short int local[][MAX_ESC]){
         int i, aux=0;
         for(i=0; i<MAX_CONT;i++){
            if(cont[i].cod_vc==vec[pos].cod_vc && cont[i].data_fim.dia==0){
                printf("\n O ve�culo encontra-se em contrato pelo que n�o � poss�vel modific�-lo\n");
                aux++;
            }
         }
            if(aux==0) {
                short int n, encontrou=-1, i;
                char valor[MAX_TXT], valor2='f';
                printf("\n--- Dados do carro ---");
                lerChars(valor,10,"\nMarca (max 10 caracteres):");
                printf("\n\t %s ", valor);
                strcpy(vec[pos].marca,valor);
                lerChars(valor,10,"\nModelo (max 10 caracteres):");
                printf("\n\t %s ", valor);
                strcpy(vec[pos].modelo,valor);
                lerChars(valor,8,"\nMatricula (max 8 caracteres):");
                printf("\n\t %s ", valor);
                strcpy(vec[pos].matricula,valor);
                printf("\nC�digo Categoria:\n");
                vec[pos].cod_categoria=lerInteiroVec(0,6);
//Atrav�s da categoria � definido se se trata de uma caravana ou autocaravana, o que ir� ditar diferen�as em todas as fun��es do contrato.
                if(vec[pos].cod_categoria<4){
                    printf("\nKms:\n");
                    vec[pos].km=lerFloat(0,9999);
                    printf("\nQuantidade de Combust�vel\n");
                    vec[pos].qt_comb=lerFloat(0,9999);
                }
                else if(vec[pos].cod_categoria>=4){
                    vec[pos].km=0;
                    vec[pos].qt_comb=0;
                }
                for(i=0;i<=MAX_ESC;i++){
                    if(local[pos][i]==1)
                        (local[pos][i])--;
                }
                printf("\nEscritorio onde se encontra o veiculo");
                printf("\n0 Braga 1 Coimbra 2 Guarda 3 Faro 4 Lisboa 5 Porto");
                n=lerInteiroVec(0,5);
                (local[pos][n])++;
                vec[pos].local_ini=n;
            }
}

// Apaga a posi��o desejada pelo utilizador, decrementando a quantidade 1 vez
void apagarCli(cliente_tipo cli[], contrato_tipo cont[], short int pos, short int *qtd){
    int i, aux=0;
    for(i=0; i<MAX_CONT;i++){
        if(cont[i].cod_cl==cli[pos].cod_cl && cont[i].data_fim.dia==0){
            printf("\n O cliente encontra-se em contrato pelo que n�o � poss�vel elimin�-lo\n");
            aux++;
        }
    }
    if(aux==0) {
        int i;
        for(i=pos; i <= *qtd; i++){
            cli[i] = cli[i+1];
        }
        (*qtd)--; // como retiramos um elemento do vetor o seu tamanho diminui
    }
}

// Apaga a posi��o desejada pelo utilizador, decrementando a quantidade 1 vez
void apagarVec(veiculo_tipo vec[], contrato_tipo cont[], short int pos, short int *qtd, short int local[][MAX_ESC]){
    int i, aux=0;
    for(i=0; i<MAX_CONT;i++){
        if(cont[i].cod_vc==vec[pos].cod_vc && cont[i].data_fim.dia==0){
            printf("\n O ve�culo encontra-se em contrato pelo que n�o � poss�vel elimin�-lo\n");
            aux++;
        }
    }
    if(aux==0) {
        for(i=pos; i <= *qtd; i++){
            vec[i] = vec[i+1];
        }
        (*qtd)--; // como retiramos um elemento do vetor o seu tamanho diminui

        for(i=0;i<=MAX_ESC;i++){
            if(local[pos][i]==1)
                (local[pos][i])--;
        }
    }
}

// Apaga a posi��o desejada pelo utilizador, decrementando a quantidade 1 vez
void apagarContrato(contrato_tipo contrato[], short int pos, short int *qtd){
    if(contrato[pos].data_fim.dia==0)
        printf("\nO contrato n�o pode ser eliminado pois ainda n�o foi finalizado\n");
    else{
        int i;
        for(i=pos; i <= *qtd; i++){
            contrato[i] = contrato[i+1];
        }
        (*qtd)--; // como retiramos um elemento do vetor o seu tamanho diminui
    }
}
// Recebe um cliente por par�metro e mostra os seus dados
void mostrarCli(cliente_tipo cli)
{
    short int i,cat;
    printf("\n--- Dados do cliente ---\n");
    printf("\n Codigo: %hd",cli.cod_cl);
    printf("\n Nome: %s",cli.nome);
    printf("\n Morada: %s",cli.morada);
    printf("\n Tipo: %d",cli.tipo);
    printf("\n Carta de condu��o: %s\n",cli.carta_conducao);
}

// Recebe um ve�culo por par�metro e mostra os seus dados
void mostrarVec(veiculo_tipo vec)
{
    short int i,cat;
    printf("\n--- Dados do ve�culo ---\n");
    printf("\n C�digo: %hd", vec.cod_vc);
    printf("\n Marca: %s",vec.marca);
    printf("\n Modelo: %s",vec.modelo);
    printf("\n Matricula: %s",vec.matricula);
    printf("\n C�digo Categoria: %hd",vec.cod_categoria);
    printf("\n Kms: %.2f", vec.km);
    printf("\n Quantidade Combustivel: %.2f", vec.qt_comb);
    printf("\n Estado: %c\n", vec.estado);
}

// Recebe um contrato por par�metro e mostra os seus dados
void mostrarContrato(contrato_tipo contrato)
{
    short int i,cat;
    printf("\n--- Dados do contrato ---\n");
    printf("\n Codigo cliente: %hd",contrato.cod_cl);
    printf("\n Codigo veiculo: %hd",contrato.cod_vc);
    printf("\n Pre�o dia: %.2f",contrato.preco_dia);
    printf("\n Pre�o km: %.2f",contrato.preco_km);
    printf("\n Quantidade kms: %.2f", contrato.qt_km);
    printf("\n Data inicio: dia %hd mes %hd ano %hd", contrato.data_ini.dia, contrato.data_ini.mes, contrato.data_ini.ano);
    printf("\n Data fim: dia %hd mes %hd ano %hd ", contrato.data_fim.dia, contrato.data_fim.mes, contrato.data_fim.ano);
    printf("\n Escritorio inicio %hd", contrato.escritorio_ini);
    printf("\n Escritorio fim %hd", contrato.escritorio_fim);
    printf("\n Legenda: \n 0 Braga 1 Coimbra 2 Guarda 3 Faro 4 Lisboa 5 Porto");
    printf("\n Nota:Se a data fim estiver a 0, o valor do escrit�rio fim n�o � Braga, mas sim nulo\n");
//Esta nota explica que se a data fim estiver a 0 o valor do escrit�rio fim � desprez�vel, pelo que aparecer� tudo a 0 na matriz em vez de aparecer 1 em Braga
}

// Procura um cliente e mostra todos os seus dados
short int mostrarDadosCli(cliente_tipo cli[], short int qtd)
{
     short int i, n, encontrou=-1;

     if (qtd==0)
        printf("\nNao existem clientes registados!!\n");
     else
     {
         n=lerInteiro(1000,9999);
         encontrou=procurarCodigo(cli,qtd,n);
         if (encontrou>=0)
             mostrarCli(cli[encontrou]);
         else
            printf("\nNao existe nenhum cliente com codigo = %hd\n",n);
    }
     getchar();
     return encontrou;
}
// Procura um ve�culo e mostra todos os seus dados
short int mostrarDadosVec(veiculo_tipo vec[], short int qtd)
{
     short int i, n, encontrou=-1;

     if (qtd==0)
        printf("\nNao existem ve�culos registados!!\n");
     else
     {
         n=lerInteiroVec(10,99);
         encontrou=procurarCodigoVec(vec,qtd,n);
         if (encontrou>=0)
             mostrarVec(vec[encontrou]);
         else
            printf("\nNao existe nenhum ve�culo com codigo = %hd\n",n);
    }
     getchar();
     return encontrou;
}
// Procura um contrato e mostra todos os seus dados
short int mostrarDadosContrato(contrato_tipo contrato[], data_tipo data[], short int qtd)
{
     short int i, n,encontrou=-1, aux=-1, codvec=-1;

     if (qtd==0)
        printf("\nNao existem contratos registados!!\n");
     else
     {
         printf("Indique a data de inicio do respectivo contrato\n");
         encontrou=procurarData(contrato,data, qtd);
         printf("Indique o c�digo do ve�culo\n");
         scanf("%hd", &codvec);
         for(i=0; i<=qtd; i++){
            if (contrato[i].data_ini.dia==data[0].dia && contrato[i].data_ini.mes==data[0].mes && contrato[i].data_ini.ano == data[0].ano && contrato[i].cod_vc==codvec){
                    mostrarContrato(contrato[encontrou]);
                    aux = i;
            }
         }
     }
     getchar();
     return aux;
}
// Mostrar todos os dados de todos os clientes
void mostrarDadosClis(cliente_tipo cli[], short int qtd)
{
     short int n, i;
     if (qtd==0){
           printf("\nNao existem clientes registados!!\n");
           getchar();
     }
     else
        for(i=0;i<qtd;i++)
        {
           mostrarCli(cli[i]);
           getchar();
        }
}
// Mostrar todos os dados de todos os ve�culos
void mostrarDadosVecs(veiculo_tipo vec[], short int qtd)
{
     short int n, i;
     if (qtd==0){
           printf("\nNao existem ve�culos registados!!\n");
           getchar();
     }
     else
        for(i=0;i<qtd;i++)
        {
           mostrarVec(vec[i]);
           getchar();
        }
}
// Mostrar todos os dados de todos os contratos e, se o utilizador desejar, ordena-o por datas. Por�m, o programa s� faz esta pergunta se existir mais que um contrato.
void mostrarDadosContratos(contrato_tipo cont[], short int qtd)
{
     short int n, i, j;
     char valor;
     contrato_tipo contaux[0];
     if (qtd==0){
           printf("\nNao existem contratos registados!!\n");
           getchar();
     }
     else{
        for(i=0;i<qtd;i++)
        {
           mostrarContrato(cont[i]);
        }
            if(qtd>1){
                printf("\nDeseja ordenar por datas? Sim(s) N�o(n)\n");
                scanf("%c", &valor);
                while(valor!='n' && valor!='N' && valor!='s' && valor!='S'){
                    scanf("%c", &valor);
                }
                if(valor=='s'|| valor=='S'){
                    for(j = 1; j < qtd; j++)
                    {
                        for (i = 0; i < qtd -1 ; i++)
                        {
                            if((cont[i].data_ini.dia>cont[i+1].data_ini.dia && cont[i].data_ini.mes==cont[i+1].data_ini.mes && cont[i].data_ini.ano==cont[i+1].data_ini.ano)||(cont[i].data_ini.mes>cont[i+1].data_ini.mes && cont[i].data_ini.ano==cont[i+1].data_ini.ano) || (cont[i].data_ini.ano>cont[i+1].data_ini.ano)){
                                contaux[0] = cont[i];
                                cont[i] = cont[i+1];
                                cont[i+1] = contaux[0];
                            }
                        }
                    }
                    for(i=0;i<qtd;i++)
                    {
                    mostrarContrato(cont[i]);
                    }
                }
            }
        }
    getchar();
}


void limpar_matriz(veiculo_tipo vec[], short int local[][MAX_ESC]){

     short int l,c;
     for(l=0;l<MAX_VC;l++){
        vec[l].cod_vc=0;
        for(c=0;c<MAX_ESC;c++)
            local[l][c]=0;
     }
}

void mostrar_matriz(veiculo_tipo vec[], short int local[][MAX_ESC], short int qtd){

     short int l,c;
     printf("               ------------------ ESCRITORIOS -------------------");
     printf("\nVEICULOS       Braga   Coimbra   Guarda   Faro    Lisboa    Porto");
     for(l=0;l<6;l++)  //for(l=0;l<qtd;l++)
     {
        printf("\n%-9u",vec[l].cod_vc);
        for(c=0;c<MAX_ESC;c++)
            printf("%9u",local[l][c]);
     }
     getchar();
}

// Esta fun��o carrega dados para existirem clientes e ve�culos no instante em que se abre o programa
void criarDados(cliente_tipo cli [], veiculo_tipo vec[],short int *qtdcli, short int *qtdvec, short int local[][MAX_ESC])
{
    int n;
     cli[0].cod_cl=1000;
     strcpy(cli[0].nome,"Client 1");
     strcpy(cli[0].morada,"Example Address 1");
     strcpy(cli[0].carta_conducao,"P-12345678");
     cli[0].tipo=0;
     (*qtdcli)++;

     cli[1].cod_cl=1001;
     strcpy(cli[1].nome,"Client 2");
     strcpy(cli[1].morada,"Example Address 2");
     strcpy(cli[1].carta_conducao,"P-98765432");
     cli[1].tipo=1;
     (*qtdcli)++;

     vec[0].cod_vc=10;
     strcpy(vec[0].marca,"Fiat");
     strcpy(vec[0].modelo,"Ducato");
     strcpy(vec[0].matricula,"LA-35-61");
     vec[0].estado='d';
     vec[0].km=12.000;
     vec[0].qt_comb=1000.00;
     vec[0].cod_categoria=0;
     n=2;
     (local[0][n])++;
     vec[0].local_ini=n;

     (*qtdvec)++;

}
// Menu de op��es
int formulario()
{
     int op;
     do
     {
        system("title GEST�O DO ALUGUER DE UMA FROTA DE (AUTO)CARAVANAS");
#ifdef WINDOWS
        system("cls");
#else
        system("clear");
#endif
        printf("----------------------- MENU ----------------------\n\n");
        printf("----------------- AREA DO CLIENTE -----------------\n");
        printf("1 - Inserir Cliente\n");
        printf("2 - Mostrar/Modificar/Apagar um cliente\n");
        printf("3 - Mostrar dados de todos os clientes\n\n");
        printf("----------------- AREA DO VEICULO -----------------\n");
        printf("11- Inserir Veiculo\n");
        printf("12- Mostrar/Modificar/Apagar um veiculo\n");
        printf("13- Mostrar dados de todos os veiculos\n");
        printf("14- Mostrar localizacao de todos os veiculos\n\n");
        printf("----------------- AREA DO CONTRATO ----------------\n");
        printf("21- Alugar veiculo\n");
        printf("22- Devolver veiculo || Mostrar/Modificar/Apagar um contrato\n");
        printf("23- Mostrar dados de todos os contratos\n\n");
        printf("0 - Sair\n");
        printf("Digite opcao:");
        scanf("%d",&op);
        }while(op!=0   &&
               op!=1  && op!=2  && op!=3  &&
               op!=11 && op!=12 && op!=13 && op!=14 &&
               op!=21 && op!=22 && op!=23);
       return op;
}
// Fun��o principal
int main()
{
    short int qtd_cli=0, qtd_vc=0, qtd_cont=0, qtd_data, pos_cli=-1, pos_vc=-1, pos_cont=-1;
    cliente_tipo vec_cli[MAX_CLI];
    short int ch, local[MAX_VC][MAX_ESC];
    veiculo_tipo veiculos_vec[MAX_VC];
    contrato_tipo contrato_vec[MAX_CONT];
    data_tipo data_vec[MAX_CLI];
    char op;
    limpar_matriz(veiculos_vec,local);
    criarDados(vec_cli,veiculos_vec, &qtd_cli, &qtd_vc, local);
    do
    {
       ch=formulario();
       switch (ch)
       {
       case 1:{
#ifdef WINDOWS
        system("cls");
#else
        system("clear");
#endif
        inserirCli(vec_cli,&qtd_cli);
        system("pause");
        break; }
       case 2:{
#ifdef WINDOWS
        system("cls");
#else
        system("clear");
#endif
                pos_cli=mostrarDadosCli(vec_cli,qtd_cli);
                if(pos_cli>=0){
                  printf("\n'M'=Modificar 'A'=Apagar\n");
                  op=getchar();
                if(op=='M' || op=='m')
                  {
                   editarCli(vec_cli, contrato_vec, pos_cli);


                   // colocar aqui o c�digo para chamar o m�dulo modificar cliente
                  }
               else if(op=='A' || op=='a')
                  {
                   apagarCli(vec_cli, contrato_vec, pos_cli, &qtd_cli);
                      // colocar aqui o c�digo para chamar o m�dulo apagar cliente
                  }
                }
                system("pause");
                break; }
       case 3:{
#ifdef WINDOWS
        system("cls");
#else
        system("clear");
#endif
            mostrarDadosClis(vec_cli,qtd_cli);
            system("pause");
            break; }

       case 11:{
#ifdef WINDOWS
        system("cls");
#else
        system("clear");
#endif
                 inserirVec(veiculos_vec,&qtd_vc, local);
                 // colocar aqui o c�digo para chamar o m�dulo inserir veiculo
                 system("pause");
                 break; }
       case 12:{
#ifdef WINDOWS
        system("cls");
#else
        system("clear");
#endif// seguindo o sugerido na op��o 2
                pos_vc=mostrarDadosVec(veiculos_vec,qtd_vc);
                if(pos_vc>=0){
                  printf("\n'M'=Modificar 'A'=Apagar\n");
                  op=getchar();
                if(op=='M' || op=='m')
                  {
                   editarVec(veiculos_vec, contrato_vec, pos_vc, local);

                  }
                    // colocar aqui o c�digo para chamar o m�dulo modificar veiculo
               else if(op=='A' || op=='a')
                  {
                   apagarVec(veiculos_vec,contrato_vec, pos_vc, &qtd_vc, local);
                  }
                }  // colocar aqui o c�digo para chamar o m�dulo apagar veiculo
                system("pause");
                break; }
       case 13:{
#ifdef WINDOWS
        system("cls");
#else
        system("clear");
#endif
                mostrarDadosVecs(veiculos_vec, qtd_vc);
                // Colocar aqui c�digo para chamar m�dulo mostrar veiculos
                system("pause");
                break; }

       case 14:{
#ifdef WINDOWS
        system("cls");
#else
        system("clear");
#endif
                mostrar_matriz(veiculos_vec,local,qtd_vc);
                system("pause");
                break; }
       case 21:{
#ifdef WINDOWS
        system("cls");
#else
        system("clear");
#endif
                inserirContrato(contrato_vec, vec_cli, veiculos_vec, local, data_vec, qtd_cli, qtd_vc, &qtd_cont);
                // Colocar aqui o c�digo para chamar o m�dulo alugar veiculo
                system("pause");
                break; }
       case 22:{
#ifdef WINDOWS
        system("cls");
#else
        system("clear");
#endif
                // Colocar aqui o c�digo para chamar o m�dulo modificar contrato e/ou apagar contrato
                pos_cont=mostrarDadosContrato(contrato_vec, data_vec,  qtd_cont);
                if(pos_cont>=0){
                  printf("\n 'T'=Terminar contrato 'M'=Modificar 'A'=Apagar\n");
                  op=getchar();
                if(op=='T' || op=='t')
                  {
                   acabarContrato(contrato_vec, pos_cont, data_vec, veiculos_vec, vec_cli, qtd_cli, qtd_vc, qtd_cont, local);
                   //Colocar aqui o c�digo para devolver ve�culo
                  }
                if(op=='M' || op=='m')
                  {
                   editarContrato(contrato_vec, veiculos_vec, pos_cont, data_vec, qtd_cont, qtd_cont);

                   // colocar aqui o c�digo para chamar o m�dulo modificar contrato
                  }
               else if(op=='A' || op=='a')
                  {
                    apagarContrato(contrato_vec, pos_cont, &qtd_cont );
                  }
                }
                system("pause");
                break; }
       case 23:{
#ifdef WINDOWS
        system("cls");
#else
        system("clear");
#endif
                mostrarDadosContratos(contrato_vec, qtd_cont);
                // Colocar aqui o c�digo para chamar o m�dulo mostrar contratos
                system("pause");
                break; }

       }
    }while(ch!=0);
system("PAUSE");
return 0;
}
