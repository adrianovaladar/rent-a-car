#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLI 500
#define MAX_VC 20
#define MAX_ESC 6
#define MAX_TXT 40
#define MAX_CONT 1000

typedef struct date {
    short int day;
    short int month;
    short int year;
} date;

typedef struct vehicle {
    short int code;
    char brand[10];
    char model[10];
    char registrationPlate[8];
    short int codeCategory;
    float km;
    float quantityFuel;
    char state;
    short int startPlace;
} vehicle;

typedef struct contract {
    short int codeVehicle;
    short int codeClient;
    float priceDay;
    float priceKm;
    float quantityKm;
    date startDate;
    date endDate;
    short int startOffice;
    short int endOffice;
} contract;

typedef struct client {
    short int code;
    char name[30];
    char address[40];
    short int type;
    char driverLicense[11];
} client;

char category[][10] = {"capucine", "integral", "perfilada", "furgao", "citadina", "utilitaria", "familiar"};

int countNumberOfDigits(int number) {
    int count = 0;
    while (number != 0) {
        number = number / 10;
        count++;
    }
    return count;
}

short int readInteger(int li, int ls, int startLength, int endLength) {
    int value;
    int check;
    do {
        printf("\nInsert a number between %d and %d: ", li, ls);
        check = scanf("%d", &value);
        if (check != 1) {
            while ((check = fgetc(stdin)) != '\n' && check != EOF)
                ;// flush stdin
        }
        if (countNumberOfDigits(value) == 4) {
            if (value >= li && value <= ls)
                break;
            else
                printf("\nOnly values between %d and %d are accepted", li, ls);
        } else
            printf("\nInvalid length");
    } while (1);
    return value;
}

// Esta fun��o l� floats num determinado intervalo
float lerFloat(float li, float ls) {
    float num = -10;
    do {
        printf("\nInsira um valor entre %.2f e %.2f: ", li, ls);
        scanf("%f", &num);
    } while (num < li || num > ls);
    return num;
}

void lerChars(char *s, short int tam, char *info) {
    short int i = 0;
    char ch;
    puts(info);
    ch = getchar();
    while (ch != '\n' && i < tam) {
        s[i] = ch;
        i++;
        ch = getchar();
    }
    s[i] = '\0';
}
// Esta fun��o valida as datas. Quando o utilizador insere o year e o m�s o programa verifica quantos dias ter� para cada situa��o
void validarData(date data[]) {
    short int i, mes, ano, dia;
    char valor[MAX_TXT];
    printf("Indique o year");
    ano = readInteger(1950, 2050, 4, 4);
    printf("Indique o m�s");
    mes = readInteger(1, 12, 1, 2);
    if ((mes == 1) || (mes == 3) || (mes == 5) || (mes == 5) || (mes == 7) || (mes == 8) || (mes == 10) || (mes == 12)) {
        printf("month de 31 dias");
        dia = readInteger(1, 31, 1, 2);
    } else {
        if (mes == 2) {
            if (((ano % 4) == 0) && ((ano % 100) != 0) || ((ano % 400) == 0)) {
                printf("month de 29 dias");
                dia = readInteger(1, 29, 1, 2);
            } else {
                printf("month de 28 dias");
                dia = readInteger(1, 28, 1, 2);
            }
        } else {
            printf("month de 30 dias");
            dia = readInteger(1, 30, 1, 2);
        }
    }
    data[0].day = dia;
    data[0].month = mes;
    data[0].year = ano;
}

short int procurarCodigo(client cli[], short int qtd, short int cod) {
    short int i, enc = -1;

    for (i = 0; i <= qtd && enc == -1; i++)
        if (cli[i].code == cod)
            enc = i;

    return enc;
}
//Esta fun��o procura o c�digo do ve�culo. A fun��o foi baseada no procurarCodigo do codigo base
short int procurarCodigoVec(vehicle vec[], short int qtd, short int cod) {
    short int i, enc = -1;

    for (i = 0; i <= qtd && enc == -1; i++)
        if (vec[i].code == cod)
            enc = i;

    return enc;
}
//Esta fun��o pesquisa a date para a op��o 22, onde � pedida a date e o carro para encontrar a posi��o pedida
short int procurarData(contract cont[], date data[], short int qtd) {
    short int i, enc = -1;
    date dataux[0];
    validarData(data);
    for (i = 0; i <= qtd; i++)
        if (cont[i].startDate.day == data[0].day && cont[i].startDate.month == data[0].month && cont[i].startDate.year == data[0].year)
            enc = i;

    return enc;
}

// L� dados de um client e guarda no vetor
void inserirCli(client cli[], short int *qtd) {
    short int n, i, encontrou = -1;
    char valor[MAX_TXT];

    if (*qtd == MAX_CLI)
        printf("\nDe momento nao admitimos mais clientes!!\n");
    else {
        printf("\n--- Dados do client ---");
        n = readInteger(1000, 9999, 4, 4);
        encontrou = procurarCodigo(cli, *qtd, n);
        printf("\n\t\t encontrou %hd e *qtd %hd ", encontrou, *qtd);
        while (encontrou >= 0)// Significa que � repetido e n�o pode acontecer!!!
        {
            n = readInteger(1000, 9999, 4, 4);
            encontrou = procurarCodigo(cli, *qtd, n);
        }
        printf("\n\t\t Fora: ");
        cli[*qtd].code = n;
        lerChars(valor, 30, "\nNome (max 30 caracteres):");
        printf("\n\t %s ", valor);
        strcpy(cli[*qtd].name, valor);
        lerChars(valor, 40, "\nMorada (max 40 caracteres):");
        printf("\n\t %s ", valor);
        strcpy(cli[*qtd].address, valor);
        lerChars(valor, 5, "\nCarta de conducao (max 5 caracteres):");
        printf("\n\t %s \n", valor);
        strcpy(cli[*qtd].driverLicense, valor);
        cli[*qtd].type = 0;
        getchar();
    }
    (*qtd)++;// Incrementa a quantidade de clientes existentes no vector
}
//Esta fun��o insere um ve�culo, validando sempre o codigo e a category inserida, pois ser� importante para o contract
void inserirVec(vehicle vec[], short int *qtd, short int local[][MAX_ESC]) {
    short int n, i, encontrou = -1;
    char valor[MAX_TXT], valor2;

    if (*qtd == MAX_VC)
        printf("\nDe momento nao admitimos mais carros!!\n");
    else {
        printf("\n--- Dados do carro ---");
        n = readInteger(10, 99, 1, 2);
        encontrou = procurarCodigoVec(vec, *qtd, n);
        printf("\n\t\t encontrou %hd e *qtd %hd ", encontrou, *qtd);
        while (encontrou >= 0)// Significa que � repetido e n�o pode acontecer!!!
        {
            n = readInteger(10, 99, 2, 2);
            encontrou = procurarCodigoVec(vec, *qtd, n);
        }
        printf("\n\t\t Fora: ");
        vec[*qtd].code = n;
        lerChars(valor, 10, "\nMarca (max 10 caracteres):");
        printf("\n\t %s ", valor);
        strcpy(vec[*qtd].brand, valor);
        lerChars(valor, 10, "\nModelo (max 10 caracteres):");
        printf("\n\t %s ", valor);
        strcpy(vec[*qtd].model, valor);
        lerChars(valor, 8, "\nMatricula (max 8 caracteres):");
        printf("\n\t %s ", valor);
        strcpy(vec[*qtd].registrationPlate, valor);
        printf("\nC�digo Categoria:\n");
        vec[*qtd].codeCategory = readInteger(0, 6, 1, 1);
        vec[*qtd].state = 'd';
        //Atrav�s da category � definido se se trata de uma caravana ou autocaravana, o que ir� ditar diferen�as em todas as fun��es do contract.
        if (vec[*qtd].codeCategory < 4) {
            printf("\nKms:\n");
            vec[*qtd].km = lerFloat(0, 9999);
            printf("\nQuantidade de Combust�vel\n");
            vec[*qtd].quantityFuel = lerFloat(0, 9999);
        }
        printf("\nEscritorio onde se encontra o vehicle");
        printf("\n0 Braga 1 Coimbra 2 Guarda 3 Faro 4 Lisboa 5 Porto");
        n = readInteger(0, 5, 1, 1);
        (local[*qtd][n])++;
        vec[*qtd].startPlace = n;
        (*qtd)++;// Incrementa a quantidade de ve�culos existentes no vector
    }
}
// Esta fun��o serve para alugar um ve�culo. Serve-se das fun��es procurarCodigo e procurarCodigoVec, por�m, neste caso, o que interessa � que ele exista, logo faz-se while(encontrou<0)
void inserirContrato(contract cont[], client cli[], vehicle vec[], short int local[][MAX_ESC], date data[], short int qtdcli, short int qtdvec, short int *qtd) {
    if (*qtd == MAX_CONT)
        printf("De momento n�o aceitamos mais contratos...");
    else {
        short int n, encontrou = -1, aux = 0, i;
        char valor[MAX_TXT], valor2;
        if (qtdvec == 0 || qtdcli == 0)
            printf("N�o existem clientes/veiculos para efectuar o contract\n");
        else {
            printf("\nInsira o n�mero de client\n");
            n = readInteger(1000, 9999, 4, 4);
            encontrou = procurarCodigo(cli, qtdcli, n);
            printf("\n\t\t encontrou %hd e *qtd %hd ", encontrou, *qtd);
            while (encontrou < 0) {
                n = readInteger(1000, 9999, 4, 4);
                encontrou = procurarCodigo(cli, qtdcli, n);
                printf("\n\t\t encontrou %hd e *qtd %hd ", encontrou, *qtd);
            }
            if (cli[encontrou].type == 1)
                printf("\nO client � de risco pelo que n�o lhe � poss�vel efectuar contratos\n");
            else {
                printf("\n\t\t Fora: ");
                cont[*qtd].codeClient = n;
                printf("\nInsira o n�mero do ve�culo\n");
                n = readInteger(10, 99, 2, 2);
                encontrou = procurarCodigoVec(vec, qtdvec, n);
                printf("\n\t\t encontrou %hd e *qtd %hd ", encontrou, *qtd);
                while (encontrou < 0) {
                    n = readInteger(10, 99, 2, 2);
                    encontrou = procurarCodigoVec(vec, qtdvec, n);
                    printf("\n\t\t encontrou %hd e *qtd %hd ", encontrou, *qtd);
                }
                if (vec[encontrou].state == 'a')
                    printf("\nN�o � poss�vel alugar este ve�culo pois o mesmo n�o se encontra dispon�vel\n");
                else {
                    vec[encontrou].state = 'a';
                    printf("\n\t\t Fora: ");
                    cont[*qtd].codeVehicle = n;
                    valor2 = '?';
                    if (vec[encontrou].codeCategory > 3) {
                        printf("\nIndique o pre�o por day\n");
                        cont[*qtd].priceDay = lerFloat(0.01, 9999);
                    } else {
                        printf("\nIndique o pre�o por km\n");
                        cont[*qtd].priceKm = lerFloat(0.01, 9999);
                    }
                    validarData(data);
                    cont[*qtd].startDate = data[0];
                    for (i = 0; i < *qtd; i++)
                        while ((cont[*qtd].codeVehicle == cont[i].codeVehicle && cont[*qtd].startDate.day >= cont[i].startDate.day && cont[*qtd].startDate.day < cont[*qtd].endDate.day && cont[*qtd].startDate.month == cont[i].startDate.month && cont[*qtd].startDate.month == cont[i].endDate.month && cont[*qtd].startDate.year == cont[i].startDate.year && cont[*qtd].startDate.year == cont[i].endDate.year) || (cont[*qtd].codeVehicle == cont[i].codeVehicle && cont[*qtd].startDate.month >= cont[i].startDate.month && cont[*qtd].startDate.month < cont[i].endDate.month && cont[*qtd].startDate.year == cont[i].startDate.year && cont[*qtd].startDate.year == cont[i].endDate.year) || (cont[*qtd].codeVehicle == cont[i].codeVehicle && cont[*qtd].startDate.year >= cont[i].startDate.year && cont[*qtd].startDate.year < cont[i].endDate.year)) {
                            //Nota: Este while faz o seguinte: No caso de existir um contract de 1/1/2000 a 1/1/2001, como este ja foi finalizado, o vehicle passaria a 'd' e seria possivel outra vez alug�-lo. Por�m, este while n�o permite que hajam alugueres entre as datas de outro aluguer do mesmo vehicle, logo, por exemplo, a date 22/2/2000 ser� impossivel para o mesmo vec.
                            printf("\nO ve�culo em quest�o esteve alugado na date em que inseriu, pelo que seria imposs�vel alug�-lo pois este estava indispon�vel\n");
                            validarData(data);
                            cont[*qtd].startDate = data[0];
                        }
                    //A partir desta linha, � verificado o numero de vezes que o contract existe para validar o escritorio inicial e final, e tamb�m para alterar a matriz(ultimo ciclo for)
                    for (i = 0; i < *qtd; i++)
                        if (cont[*qtd].codeVehicle == cont[i].codeVehicle)
                            aux++;

                    if (aux == 0)
                        cont[*qtd].startOffice = vec[encontrou].startPlace;
                    else if (aux > 0) {
                        for (i = 0; i < *qtd; i++)
                            if (cont[*qtd].codeVehicle == cont[i].codeVehicle)
                                aux = i;
                        cont[*qtd].startOffice = cont[aux].endOffice;
                    }
                    (*qtd)++;
                    for (i = 0; i <= MAX_ESC; i++) {
                        if (local[encontrou][i] == 1)
                            (local[encontrou][i])--;
                    }
                }
            }
        }
    }
}

//Esta fun��o devolve o ve�culo. � verificado se este j� foi terminado para nao haver altera��o de valores.
void acabarContrato(contract cont[], short int pos, date data[], vehicle vec[], client cli[], short int qtdcli, short int qtdvec, short int qtdcont, short int local[][MAX_ESC]) {
    if (cont[pos].endDate.day != 0)
        printf("\n O contract j� foi finalizado!!!\n");
    else {
        char valor2 = '?';
        short int i, aux, encontrou;
        float custo;
        printf("\nO ve�culo foi devolvido em bom state? Sim(s) N�o(n)\n");
        valor2 = '?';
        while (valor2 != 's' && valor2 != 'S' && valor2 != 'n' && valor2 != 'N') {
            scanf("%c", &valor2);
        }
        if (valor2 == 'n' || valor2 == 'N') {
            aux = procurarCodigo(cli, qtdcli, cont[pos].codeClient);
            cli[aux].type = 1;
        }
        encontrou = procurarCodigoVec(vec, qtdvec, cont[pos].codeVehicle);
        vec[encontrou].state = 'd';
        if (vec[encontrou].codeCategory < 4) {
            printf("\n Indique a quantidade de kms\n");
            cont[pos].quantityKm = lerFloat(0.01, 5000);
            vec[encontrou].km = cont[pos].quantityKm + vec[encontrou].km;
            custo = cont[pos].quantityKm * cont[pos].priceKm;
            printf("\nO custo � %.2f\n", custo);
        }
        validarData(data);
        cont[pos].endDate = data[0];
        for (i = 0; i < qtdcont; i++)
            //Nota: Este while faz o seguinte: No caso de existir um contract de 1/1/2000 a 1/1/2001, como este ja foi finalizado, o vehicle passaria a 'd' e seria possivel outra vez alug�-lo. Por�m, este while n�o permite que hajam alugueres entre as datas de outro aluguer do mesmo vehicle, logo, por exemplo, a date 22/2/2000 ser� impossivel para o mesmo vec.
            while ((cont[pos].codeVehicle == cont[i].codeVehicle && cont[pos].endDate.day > cont[i].startDate.day && cont[pos].endDate.day < cont[pos].endDate.day && cont[pos].endDate.month == cont[i].startDate.month && cont[pos].startDate.month == cont[i].endDate.month && cont[pos].endDate.year == cont[i].startDate.year && cont[pos].endDate.year == cont[i].endDate.year) || (cont[pos].codeVehicle == cont[i].codeVehicle && cont[pos].endDate.month >= cont[i].startDate.month && cont[pos].endDate.month < cont[i].endDate.month && cont[pos].endDate.year == cont[i].startDate.year && cont[pos].endDate.year == cont[i].endDate.year) || (cont[pos].codeVehicle == cont[i].codeVehicle && cont[pos].endDate.year >= cont[i].startDate.year && cont[pos].endDate.year < cont[i].endDate.year)) {
                printf("\nO ve�culo em quest�o esteve alugado na date em que inseriu, pelo que seria imposs�vel alug�-lo pois este estava indispon�vel\n");
                validarData(data);
                cont[pos].startDate = data[0];
            }
        //Este while verifica se a date final � menor que a inicial. Enquanto for, ir� sempre pedir datas novas, estando a date final e a inicial validadas consoante o month e o year.
        while ((cont[pos].startDate.day > cont[pos].endDate.day && cont[pos].startDate.month == cont[pos].endDate.month && cont[pos].startDate.year == cont[pos].endDate.year) || (cont[pos].startDate.month > cont[pos].endDate.month && cont[pos].startDate.year == cont[pos].endDate.year) || cont[pos].startDate.year > cont[pos].endDate.year) {
            printf("\n A date � inv�lida! Insira outra vez...\n");
            validarData(data);
            cont[pos].endDate = data[0];
        }
        // Volta a escrever a nova posi��o da caravana na matriz, que ao ter sido alugada passou a estar num local desconhecido
        printf("\nEscritorio onde se encontra o vehicle:");
        printf("\n0 Braga 1 Coimbra 2 Guarda 3 Faro 4 Lisboa 5 Porto");
        aux = readInteger(0, 5, 1, 1);
        //O escritorio final ser� igual a localiza��o depois deste contract
        cont[pos].endOffice = aux;
        (local[encontrou][aux])++;
    }
}
// Esta fun��o difere da fun��o inserirContrato pois esta baseia-se em qualquer posi��o da fun��o, modificando-a, logo nao altera o valor da quantidade.
void editarContrato(contract cont[], vehicle vec[], short int pos, date data[], short int qtdvec, short int qtd) {
    if (cont[pos].endDate.year != 0)
        printf("\n N�o � poss�vel editar o contract pois este j� se encontra finalizado\n");
    else {
        short int i, encontrou;
        char valor2;
        encontrou = procurarCodigoVec(vec, qtdvec, cont[pos].codeVehicle);
        if (vec[encontrou].codeCategory > 3) {
            printf("\nIndique o pre�o por day\n");
            cont[pos].priceDay = lerFloat(0.01, 9999);
        } else {
            printf("\nIndique o pre�o por km\n");
            cont[pos].priceKm = lerFloat(0.01, 9999);
        }
        validarData(data);
        cont[pos].startDate = data[0];
        for (i = 0; i < qtd; i++)
            while ((cont[pos].codeVehicle == cont[i].codeVehicle && cont[pos].startDate.day >= cont[i].startDate.day && cont[pos].startDate.day < cont[pos].endDate.day && cont[pos].startDate.month == cont[i].startDate.month && cont[pos].startDate.month == cont[i].endDate.month && cont[pos].startDate.year == cont[i].startDate.year && cont[pos].startDate.year == cont[i].endDate.year) || (cont[pos].codeVehicle == cont[i].codeVehicle && cont[pos].startDate.month >= cont[i].startDate.month && cont[pos].startDate.month < cont[i].endDate.month && cont[pos].startDate.year == cont[i].startDate.year && cont[pos].startDate.year == cont[i].endDate.year) || (cont[pos].codeVehicle == cont[i].codeVehicle && cont[pos].startDate.year >= cont[i].startDate.year && cont[pos].startDate.year < cont[i].endDate.year)) {
                printf("\nO ve�culo em quest�o esteve alugado na date em que inseriu, pelo que seria imposs�vel alug�-lo pois este estava indispon�vel\n");
                validarData(data);
                cont[pos].startDate = data[0];
            }
    }
}

// Esta fun��o difere da fun��o inserirCli pois esta baseia-se em qualquer posi��o da fun��o, modificando-a, logo nao altera o valor da quantidade.
void editarCli(client cli[], contract cont[], short int pos) {
    int i, aux = 0;
    for (i = 0; i < MAX_CONT; i++) {
        if (cont[i].codeClient == cli[pos].code && cont[i].endDate.day == 0) {
            printf("\n O client encontra-se em contract pelo que n�o � poss�vel modific�-lo\n");
            aux++;
        }
    }
    if (aux == 0) {
        short int n;
        printf("\n--- Dados do client ---");
        char valor[MAX_TXT];
        lerChars(valor, 30, "\nNome (max 30 caracteres):");
        printf("\n\t %s ", valor);
        strcpy(cli[pos].name, valor);
        lerChars(valor, 40, "\nMorada (max 40 caracteres):");
        printf("\n\t %s ", valor);
        strcpy(cli[pos].address, valor);
        lerChars(valor, 5, "\nCarta de conducao (max 5 caracteres):");
        printf("\n\t %s \n", valor);
        strcpy(cli[pos].driverLicense, valor);
    }
}

// Esta fun��o difere da fun��o inserirVec pois esta baseia-se em qualquer posi��o da fun��o, modificando-a, logo nao altera o valor da quantidade.
void editarVec(vehicle vec[], contract cont[], short int pos, short int local[][MAX_ESC]) {
    int i, aux = 0;
    for (i = 0; i < MAX_CONT; i++) {
        if (cont[i].codeVehicle == vec[pos].code && cont[i].endDate.day == 0) {
            printf("\n O ve�culo encontra-se em contract pelo que n�o � poss�vel modific�-lo\n");
            aux++;
        }
    }
    if (aux == 0) {
        short int n, encontrou = -1, i;
        char valor[MAX_TXT], valor2 = 'f';
        printf("\n--- Dados do carro ---");
        lerChars(valor, 10, "\nMarca (max 10 caracteres):");
        printf("\n\t %s ", valor);
        strcpy(vec[pos].brand, valor);
        lerChars(valor, 10, "\nModelo (max 10 caracteres):");
        printf("\n\t %s ", valor);
        strcpy(vec[pos].model, valor);
        lerChars(valor, 8, "\nMatricula (max 8 caracteres):");
        printf("\n\t %s ", valor);
        strcpy(vec[pos].registrationPlate, valor);
        printf("\nC�digo Categoria:\n");
        vec[pos].codeCategory = readInteger(0, 6, 1, 1);
        //Atrav�s da category � definido se se trata de uma caravana ou autocaravana, o que ir� ditar diferen�as em todas as fun��es do contract.
        if (vec[pos].codeCategory < 4) {
            printf("\nKms:\n");
            vec[pos].km = lerFloat(0, 9999);
            printf("\nQuantidade de Combust�vel\n");
            vec[pos].quantityFuel = lerFloat(0, 9999);
        } else if (vec[pos].codeCategory >= 4) {
            vec[pos].km = 0;
            vec[pos].quantityFuel = 0;
        }
        for (i = 0; i <= MAX_ESC; i++) {
            if (local[pos][i] == 1)
                (local[pos][i])--;
        }
        printf("\nEscritorio onde se encontra o vehicle");
        printf("\n0 Braga 1 Coimbra 2 Guarda 3 Faro 4 Lisboa 5 Porto");
        n = readInteger(0, 5, 1, 1);
        (local[pos][n])++;
        vec[pos].startPlace = n;
    }
}

// Apaga a posi��o desejada pelo utilizador, decrementando a quantidade 1 vez
void apagarCli(client cli[], contract cont[], short int pos, short int *qtd) {
    int i, aux = 0;
    for (i = 0; i < MAX_CONT; i++) {
        if (cont[i].codeClient == cli[pos].code && cont[i].endDate.day == 0) {
            printf("\n O client encontra-se em contract pelo que n�o � poss�vel elimin�-lo\n");
            aux++;
        }
    }
    if (aux == 0) {
        int i;
        for (i = pos; i <= *qtd; i++) {
            cli[i] = cli[i + 1];
        }
        (*qtd)--;// como retiramos um elemento do vetor o seu tamanho diminui
    }
}

// Apaga a posi��o desejada pelo utilizador, decrementando a quantidade 1 vez
void apagarVec(vehicle vec[], contract cont[], short int pos, short int *qtd, short int local[][MAX_ESC]) {
    int i, aux = 0;
    for (i = 0; i < MAX_CONT; i++) {
        if (cont[i].codeVehicle == vec[pos].code && cont[i].endDate.day == 0) {
            printf("\n O ve�culo encontra-se em contract pelo que n�o � poss�vel elimin�-lo\n");
            aux++;
        }
    }
    if (aux == 0) {
        for (i = pos; i <= *qtd; i++) {
            vec[i] = vec[i + 1];
        }
        (*qtd)--;// como retiramos um elemento do vetor o seu tamanho diminui

        for (i = 0; i <= MAX_ESC; i++) {
            if (local[pos][i] == 1)
                (local[pos][i])--;
        }
    }
}

// Apaga a posi��o desejada pelo utilizador, decrementando a quantidade 1 vez
void apagarContrato(contract contrato[], short int pos, short int *qtd) {
    if (contrato[pos].endDate.day == 0)
        printf("\nO contract n�o pode ser eliminado pois ainda n�o foi finalizado\n");
    else {
        int i;
        for (i = pos; i <= *qtd; i++) {
            contrato[i] = contrato[i + 1];
        }
        (*qtd)--;// como retiramos um elemento do vetor o seu tamanho diminui
    }
}
// Recebe um client por par�metro e mostra os seus dados
void mostrarCli(client cli) {
    short int i, cat;
    printf("\n--- Dados do client ---\n");
    printf("\n Codigo: %hd", cli.code);
    printf("\n Nome: %s", cli.name);
    printf("\n Morada: %s", cli.address);
    printf("\n Tipo: %d", cli.type);
    printf("\n Carta de condu��o: %s\n", cli.driverLicense);
}

// Recebe um ve�culo por par�metro e mostra os seus dados
void mostrarVec(vehicle vec) {
    short int i, cat;
    printf("\n--- Dados do ve�culo ---\n");
    printf("\n C�digo: %hd", vec.code);
    printf("\n Marca: %s", vec.brand);
    printf("\n Modelo: %s", vec.model);
    printf("\n Matricula: %s", vec.registrationPlate);
    printf("\n C�digo Categoria: %hd", vec.codeCategory);
    printf("\n Kms: %.2f", vec.km);
    printf("\n Quantidade Combustivel: %.2f", vec.quantityFuel);
    printf("\n Estado: %c\n", vec.state);
}

// Recebe um contract por par�metro e mostra os seus dados
void mostrarContrato(contract contrato) {
    short int i, cat;
    printf("\n--- Dados do contract ---\n");
    printf("\n Codigo client: %hd", contrato.codeClient);
    printf("\n Codigo vehicle: %hd", contrato.codeVehicle);
    printf("\n Pre�o day: %.2f", contrato.priceDay);
    printf("\n Pre�o km: %.2f", contrato.priceKm);
    printf("\n Quantidade kms: %.2f", contrato.quantityKm);
    printf("\n Data inicio: day %hd month %hd year %hd", contrato.startDate.day, contrato.startDate.month, contrato.startDate.year);
    printf("\n Data fim: day %hd month %hd year %hd ", contrato.endDate.day, contrato.endDate.month, contrato.endDate.year);
    printf("\n Escritorio inicio %hd", contrato.startOffice);
    printf("\n Escritorio fim %hd", contrato.endOffice);
    printf("\n Legenda: \n 0 Braga 1 Coimbra 2 Guarda 3 Faro 4 Lisboa 5 Porto");
    printf("\n Nota:Se a date fim estiver a 0, o valor do escrit�rio fim n�o � Braga, mas sim nulo\n");
    //Esta nota explica que se a date fim estiver a 0 o valor do escrit�rio fim � desprez�vel, pelo que aparecer� tudo a 0 na matriz em vez de aparecer 1 em Braga
}

// Procura um client e mostra todos os seus dados
short int mostrarDadosCli(client cli[], short int qtd) {
    short int i, n, encontrou = -1;

    if (qtd == 0)
        printf("\nNao existem clientes registados!!\n");
    else {
        n = readInteger(1000, 9999, 4, 4);
        encontrou = procurarCodigo(cli, qtd, n);
        if (encontrou >= 0)
            mostrarCli(cli[encontrou]);
        else
            printf("\nNao existe nenhum client com codigo = %hd\n", n);
    }
    getchar();
    return encontrou;
}
// Procura um ve�culo e mostra todos os seus dados
short int mostrarDadosVec(vehicle vec[], short int qtd) {
    short int i, n, encontrou = -1;

    if (qtd == 0)
        printf("\nNao existem ve�culos registados!!\n");
    else {
        n = readInteger(10, 99, 2, 2);
        encontrou = procurarCodigoVec(vec, qtd, n);
        if (encontrou >= 0)
            mostrarVec(vec[encontrou]);
        else
            printf("\nNao existe nenhum ve�culo com codigo = %hd\n", n);
    }
    getchar();
    return encontrou;
}
// Procura um contract e mostra todos os seus dados
short int mostrarDadosContrato(contract contrato[], date data[], short int qtd) {
    short int i, n, encontrou = -1, aux = -1, codvec = -1;

    if (qtd == 0)
        printf("\nNao existem contratos registados!!\n");
    else {
        printf("Indique a date de inicio do respectivo contract\n");
        encontrou = procurarData(contrato, data, qtd);
        printf("Indique o c�digo do ve�culo\n");
        scanf("%hd", &codvec);
        for (i = 0; i <= qtd; i++) {
            if (contrato[i].startDate.day == data[0].day && contrato[i].startDate.month == data[0].month && contrato[i].startDate.year == data[0].year && contrato[i].codeVehicle == codvec) {
                mostrarContrato(contrato[encontrou]);
                aux = i;
            }
        }
    }
    getchar();
    return aux;
}
// Mostrar todos os dados de todos os clientes
void mostrarDadosClis(client cli[], short int qtd) {
    short int n, i;
    if (qtd == 0) {
        printf("\nNao existem clientes registados!!\n");
        getchar();
    } else
        for (i = 0; i < qtd; i++) {
            mostrarCli(cli[i]);
            getchar();
        }
}
// Mostrar todos os dados de todos os ve�culos
void mostrarDadosVecs(vehicle vec[], short int qtd) {
    short int n, i;
    if (qtd == 0) {
        printf("\nNao existem ve�culos registados!!\n");
        getchar();
    } else
        for (i = 0; i < qtd; i++) {
            mostrarVec(vec[i]);
            getchar();
        }
}
// Mostrar todos os dados de todos os contratos e, se o utilizador desejar, ordena-o por datas. Por�m, o programa s� faz esta pergunta se existir mais que um contract.
void mostrarDadosContratos(contract cont[], short int qtd) {
    short int n, i, j;
    char valor;
    contract contaux[0];
    if (qtd == 0) {
        printf("\nNao existem contratos registados!!\n");
        getchar();
    } else {
        for (i = 0; i < qtd; i++) {
            mostrarContrato(cont[i]);
        }
        if (qtd > 1) {
            printf("\nDeseja ordenar por datas? Sim(s) N�o(n)\n");
            scanf("%c", &valor);
            while (valor != 'n' && valor != 'N' && valor != 's' && valor != 'S') {
                scanf("%c", &valor);
            }
            if (valor == 's' || valor == 'S') {
                for (j = 1; j < qtd; j++) {
                    for (i = 0; i < qtd - 1; i++) {
                        if ((cont[i].startDate.day > cont[i + 1].startDate.day && cont[i].startDate.month == cont[i + 1].startDate.month && cont[i].startDate.year == cont[i + 1].startDate.year) || (cont[i].startDate.month > cont[i + 1].startDate.month && cont[i].startDate.year == cont[i + 1].startDate.year) || (cont[i].startDate.year > cont[i + 1].startDate.year)) {
                            contaux[0] = cont[i];
                            cont[i] = cont[i + 1];
                            cont[i + 1] = contaux[0];
                        }
                    }
                }
                for (i = 0; i < qtd; i++) {
                    mostrarContrato(cont[i]);
                }
            }
        }
    }
    getchar();
}


void limpar_matriz(vehicle vec[], short int local[][MAX_ESC]) {

    short int l, c;
    for (l = 0; l < MAX_VC; l++) {
        vec[l].code = 0;
        for (c = 0; c < MAX_ESC; c++)
            local[l][c] = 0;
    }
}

void mostrar_matriz(vehicle vec[], short int local[][MAX_ESC], short int qtd) {

    short int l, c;
    printf("               ------------------ ESCRITORIOS -------------------");
    printf("\nVEICULOS       Braga   Coimbra   Guarda   Faro    Lisboa    Porto");
    for (l = 0; l < 6; l++)//for(l=0;l<qtd;l++)
    {
        printf("\n%-9u", vec[l].code);
        for (c = 0; c < MAX_ESC; c++)
            printf("%9u", local[l][c]);
    }
    getchar();
}

// Esta fun��o carrega dados para existirem clientes e ve�culos no instante em que se abre o programa
void criarDados(client cli[], vehicle vec[], short int *qtdcli, short int *qtdvec, short int local[][MAX_ESC]) {
    int n;
    cli[0].code = 1000;
    strcpy(cli[0].name, "Client 1");
    strcpy(cli[0].address, "Example Address 1");
    strcpy(cli[0].driverLicense, "P-12345678");
    cli[0].type = 0;
    (*qtdcli)++;

    cli[1].code = 1001;
    strcpy(cli[1].name, "Client 2");
    strcpy(cli[1].address, "Example Address 2");
    strcpy(cli[1].driverLicense, "P-98765432");
    cli[1].type = 1;
    (*qtdcli)++;

    vec[0].code = 10;
    strcpy(vec[0].brand, "Fiat");
    strcpy(vec[0].model, "Ducato");
    strcpy(vec[0].registrationPlate, "LA-35-61");
    vec[0].state = 'd';
    vec[0].km = 12.000;
    vec[0].quantityFuel = 1000.00;
    vec[0].codeCategory = 0;
    n = 2;
    (local[0][n])++;
    vec[0].startPlace = n;

    (*qtdvec)++;
}
// Menu de op��es
int formulario() {
    int op;
    do {
        system("title GEST�O DO ALUGUER DE UMA FROTA DE (AUTO)CARAVANAS");
#ifdef WINDOWS
        system("cls");
#else
        system("clear");
#endif
        printf("----------------------- MENU ----------------------\n\n");
        printf("----------------- AREA DO CLIENTE -----------------\n");
        printf("1 - Inserir Cliente\n");
        printf("2 - Mostrar/Modificar/Apagar um client\n");
        printf("3 - Mostrar dados de todos os clientes\n\n");
        printf("----------------- AREA DO VEICULO -----------------\n");
        printf("11- Inserir Veiculo\n");
        printf("12- Mostrar/Modificar/Apagar um vehicle\n");
        printf("13- Mostrar dados de todos os veiculos\n");
        printf("14- Mostrar localizacao de todos os veiculos\n\n");
        printf("----------------- AREA DO CONTRATO ----------------\n");
        printf("21- Alugar vehicle\n");
        printf("22- Devolver vehicle || Mostrar/Modificar/Apagar um contract\n");
        printf("23- Mostrar dados de todos os contratos\n\n");
        printf("0 - Sair\n");
        printf("Digite opcao:");
        scanf("%d", &op);
    } while (op != 0 &&
             op != 1 && op != 2 && op != 3 &&
             op != 11 && op != 12 && op != 13 && op != 14 &&
             op != 21 && op != 22 && op != 23);
    return op;
}
// Fun��o principal
int main() {
    short int qtd_cli = 0, qtd_vc = 0, qtd_cont = 0, qtd_data, pos_cli = -1, pos_vc = -1, pos_cont = -1;
    client vec_cli[MAX_CLI];
    short int ch, local[MAX_VC][MAX_ESC];
    vehicle veiculos_vec[MAX_VC];
    contract contrato_vec[MAX_CONT];
    date data_vec[MAX_CLI];
    char op;
    limpar_matriz(veiculos_vec, local);
    criarDados(vec_cli, veiculos_vec, &qtd_cli, &qtd_vc, local);
    do {
        ch = formulario();
        switch (ch) {
            case 1: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                inserirCli(vec_cli, &qtd_cli);
                system("pause");
                break;
            }
            case 2: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                pos_cli = mostrarDadosCli(vec_cli, qtd_cli);
                if (pos_cli >= 0) {
                    printf("\n'M'=Modificar 'A'=Apagar\n");
                    op = getchar();
                    if (op == 'M' || op == 'm') {
                        editarCli(vec_cli, contrato_vec, pos_cli);


                        // colocar aqui o c�digo para chamar o m�dulo modificar client
                    } else if (op == 'A' || op == 'a') {
                        apagarCli(vec_cli, contrato_vec, pos_cli, &qtd_cli);
                        // colocar aqui o c�digo para chamar o m�dulo apagar client
                    }
                }
                system("pause");
                break;
            }
            case 3: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                mostrarDadosClis(vec_cli, qtd_cli);
                system("pause");
                break;
            }

            case 11: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                inserirVec(veiculos_vec, &qtd_vc, local);
                // colocar aqui o c�digo para chamar o m�dulo inserir vehicle
                system("pause");
                break;
            }
            case 12: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif// seguindo o sugerido na op��o 2
                pos_vc = mostrarDadosVec(veiculos_vec, qtd_vc);
                if (pos_vc >= 0) {
                    printf("\n'M'=Modificar 'A'=Apagar\n");
                    op = getchar();
                    if (op == 'M' || op == 'm') {
                        editarVec(veiculos_vec, contrato_vec, pos_vc, local);

                    }
                    // colocar aqui o c�digo para chamar o m�dulo modificar vehicle
                    else if (op == 'A' || op == 'a') {
                        apagarVec(veiculos_vec, contrato_vec, pos_vc, &qtd_vc, local);
                    }
                }// colocar aqui o c�digo para chamar o m�dulo apagar vehicle
                system("pause");
                break;
            }
            case 13: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                mostrarDadosVecs(veiculos_vec, qtd_vc);
                // Colocar aqui c�digo para chamar m�dulo mostrar veiculos
                system("pause");
                break;
            }

            case 14: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                mostrar_matriz(veiculos_vec, local, qtd_vc);
                system("pause");
                break;
            }
            case 21: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                inserirContrato(contrato_vec, vec_cli, veiculos_vec, local, data_vec, qtd_cli, qtd_vc, &qtd_cont);
                // Colocar aqui o c�digo para chamar o m�dulo alugar vehicle
                system("pause");
                break;
            }
            case 22: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                // Colocar aqui o c�digo para chamar o m�dulo modificar contract e/ou apagar contract
                pos_cont = mostrarDadosContrato(contrato_vec, data_vec, qtd_cont);
                if (pos_cont >= 0) {
                    printf("\n 'T'=Terminar contract 'M'=Modificar 'A'=Apagar\n");
                    op = getchar();
                    if (op == 'T' || op == 't') {
                        acabarContrato(contrato_vec, pos_cont, data_vec, veiculos_vec, vec_cli, qtd_cli, qtd_vc, qtd_cont, local);
                        //Colocar aqui o c�digo para devolver ve�culo
                    }
                    if (op == 'M' || op == 'm') {
                        editarContrato(contrato_vec, veiculos_vec, pos_cont, data_vec, qtd_cont, qtd_cont);

                        // colocar aqui o c�digo para chamar o m�dulo modificar contract
                    } else if (op == 'A' || op == 'a') {
                        apagarContrato(contrato_vec, pos_cont, &qtd_cont);
                    }
                }
                system("pause");
                break;
            }
            case 23: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                mostrarDadosContratos(contrato_vec, qtd_cont);
                // Colocar aqui o c�digo para chamar o m�dulo mostrar contratos
                system("pause");
                break;
            }
        }
    } while (ch != 0);
    system("PAUSE");
    return 0;
}
