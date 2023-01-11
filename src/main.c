#include "constants.h"
#include "contract.h"
#include "date.h"
#include "input.h"
#include "vehicle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct client {
    int code;
    char name[30];
    char address[40];
    int type;
    char driverLicense[11];
} client;

char category[][10] = {"capucine", "integral", "perfilada", "furgao", "citadina", "utilitaria", "familiar"};

int searchCodeClient(client cli[], int qtd, int cod) {
    int i, enc = -1;

    for (i = 0; i <= qtd && enc == -1; i++)
        if (cli[i].code == cod)
            enc = i;

    return enc;
}

//Esta fun��o pesquisa a date para a op��o 22, onde � pedida a date e o carro para encontrar a posi��o pedida
int procurarData(contract cont[], date data[], int qtd) {
    int i, enc = -1;
    date dataux[0];
    validateDate(data);
    for (i = 0; i <= qtd; i++)
        if (cont[i].startDate.day == data[0].day && cont[i].startDate.month == data[0].month && cont[i].startDate.year == data[0].year)
            enc = i;

    return enc;
}

// L� dados de um client e guarda no vetor
void inserirCli(client cli[], int *qtd) {
    int n, i, encontrou = -1;
    char valor[MAX_TXT];

    if (*qtd == MAX_CLI)
        printf("\nDe momento nao admitimos mais clientes!!\n");
    else {
        printf("\n--- Dados do client ---");
        n = readInt(1000, 9999);
        encontrou = searchCodeClient(cli, *qtd, n);
        printf("\n\t\t encontrou %hd e *qtd %hd ", encontrou, *qtd);
        while (encontrou >= 0)// Significa que � repetido e n�o pode acontecer!!!
        {
            n = readInt(1000, 9999);
            encontrou = searchCodeClient(cli, *qtd, n);
        }
        printf("\n\t\t Fora: ");
        cli[*qtd].code = n;
        readChars(valor, 30, "\nNome (max 30 caracteres):");
        printf("\n\t %s ", valor);
        strcpy(cli[*qtd].name, valor);
        readChars(valor, 40, "\nMorada (max 40 caracteres):");
        printf("\n\t %s ", valor);
        strcpy(cli[*qtd].address, valor);
        readChars(valor, 5, "\nCarta de conducao (max 5 caracteres):");
        printf("\n\t %s \n", valor);
        strcpy(cli[*qtd].driverLicense, valor);
        cli[*qtd].type = 0;
        getchar();
    }
    (*qtd)++;// Incrementa a quantidade de clientes existentes no vector
}

// Esta fun��o serve para alugar um ve�culo. Serve-se das fun��es searchCodeClient e searchCodeVehicle, por�m, neste caso, o que interessa � que ele exista, logo faz-se while(encontrou<0)
void inserirContrato(contract cont[], client cli[], vehicle vec[], int local[][MAX_ESC], date data[], int qtdcli, int qtdvec, int *qtd) {
    if (*qtd == MAX_CONT)
        printf("De momento n�o aceitamos mais contratos...");
    else {
        int n, encontrou = -1, aux = 0, i;
        char valor[MAX_TXT], valor2;
        if (qtdvec == 0 || qtdcli == 0)
            printf("N�o existem clientes/veiculos para efectuar o contract\n");
        else {
            printf("\nInsira o n�mero de client\n");
            n = readInt(1000, 9999);
            encontrou = searchCodeClient(cli, qtdcli, n);
            printf("\n\t\t encontrou %hd e *qtd %hd ", encontrou, *qtd);
            while (encontrou < 0) {
                n = readInt(1000, 9999);
                encontrou = searchCodeClient(cli, qtdcli, n);
                printf("\n\t\t encontrou %hd e *qtd %hd ", encontrou, *qtd);
            }
            if (cli[encontrou].type == 1)
                printf("\nO client � de risco pelo que n�o lhe � poss�vel efectuar contratos\n");
            else {
                printf("\n\t\t Fora: ");
                cont[*qtd].codeClient = n;
                printf("\nInsira o n�mero do ve�culo\n");
                n = readInt(10, 99);
                encontrou = searchCodeVehicle(vec, qtdvec, n);
                printf("\n\t\t encontrou %hd e *qtd %hd ", encontrou, *qtd);
                while (encontrou < 0) {
                    n = readInt(10, 99);
                    encontrou = searchCodeVehicle(vec, qtdvec, n);
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
                        cont[*qtd].priceDay = readFloat(0.01, 9999);
                    } else {
                        printf("\nIndique o pre�o por km\n");
                        cont[*qtd].priceKm = readFloat(0.01, 9999);
                    }
                    validateDate(data);
                    cont[*qtd].startDate = data[0];
                    for (i = 0; i < *qtd; i++)
                        while ((cont[*qtd].codeVehicle == cont[i].codeVehicle && cont[*qtd].startDate.day >= cont[i].startDate.day && cont[*qtd].startDate.day < cont[*qtd].endDate.day && cont[*qtd].startDate.month == cont[i].startDate.month && cont[*qtd].startDate.month == cont[i].endDate.month && cont[*qtd].startDate.year == cont[i].startDate.year && cont[*qtd].startDate.year == cont[i].endDate.year) || (cont[*qtd].codeVehicle == cont[i].codeVehicle && cont[*qtd].startDate.month >= cont[i].startDate.month && cont[*qtd].startDate.month < cont[i].endDate.month && cont[*qtd].startDate.year == cont[i].startDate.year && cont[*qtd].startDate.year == cont[i].endDate.year) || (cont[*qtd].codeVehicle == cont[i].codeVehicle && cont[*qtd].startDate.year >= cont[i].startDate.year && cont[*qtd].startDate.year < cont[i].endDate.year)) {
                            //Nota: Este while faz o seguinte: No caso de existir um contract de 1/1/2000 a 1/1/2001, como este ja foi finalizado, o vehicle passaria a 'd' e seria possivel outra vez alug�-lo. Por�m, este while n�o permite que hajam alugueres entre as datas de outro aluguer do mesmo vehicle, logo, por exemplo, a date 22/2/2000 ser� impossivel para o mesmo vec.
                            printf("\nO ve�culo em quest�o esteve alugado na date em que inseriu, pelo que seria imposs�vel alug�-lo pois este estava indispon�vel\n");
                            validateDate(data);
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
void acabarContrato(contract cont[], int pos, date data[], vehicle vec[], client cli[], int qtdcli, int qtdvec, int qtdcont, int local[][MAX_ESC]) {
    if (cont[pos].endDate.day != 0)
        printf("\n O contract j� foi finalizado!!!\n");
    else {
        char valor2 = '?';
        int i, aux, encontrou;
        float custo;
        printf("\nO ve�culo foi devolvido em bom state? Sim(s) N�o(n)\n");
        valor2 = '?';
        while (valor2 != 's' && valor2 != 'S' && valor2 != 'n' && valor2 != 'N') {
            scanf("%c", &valor2);
        }
        if (valor2 == 'n' || valor2 == 'N') {
            aux = searchCodeClient(cli, qtdcli, cont[pos].codeClient);
            cli[aux].type = 1;
        }
        encontrou = searchCodeVehicle(vec, qtdvec, cont[pos].codeVehicle);
        vec[encontrou].state = 'd';
        if (vec[encontrou].codeCategory < 4) {
            printf("\n Indique a quantidade de kms\n");
            cont[pos].quantityKm = readFloat(0.01, 5000);
            vec[encontrou].km = cont[pos].quantityKm + vec[encontrou].km;
            custo = cont[pos].quantityKm * cont[pos].priceKm;
            printf("\nO custo � %.2f\n", custo);
        }
        validateDate(data);
        cont[pos].endDate = data[0];
        for (i = 0; i < qtdcont; i++)
            //Nota: Este while faz o seguinte: No caso de existir um contract de 1/1/2000 a 1/1/2001, como este ja foi finalizado, o vehicle passaria a 'd' e seria possivel outra vez alug�-lo. Por�m, este while n�o permite que hajam alugueres entre as datas de outro aluguer do mesmo vehicle, logo, por exemplo, a date 22/2/2000 ser� impossivel para o mesmo vec.
            while ((cont[pos].codeVehicle == cont[i].codeVehicle && cont[pos].endDate.day > cont[i].startDate.day && cont[pos].endDate.day < cont[pos].endDate.day && cont[pos].endDate.month == cont[i].startDate.month && cont[pos].startDate.month == cont[i].endDate.month && cont[pos].endDate.year == cont[i].startDate.year && cont[pos].endDate.year == cont[i].endDate.year) || (cont[pos].codeVehicle == cont[i].codeVehicle && cont[pos].endDate.month >= cont[i].startDate.month && cont[pos].endDate.month < cont[i].endDate.month && cont[pos].endDate.year == cont[i].startDate.year && cont[pos].endDate.year == cont[i].endDate.year) || (cont[pos].codeVehicle == cont[i].codeVehicle && cont[pos].endDate.year >= cont[i].startDate.year && cont[pos].endDate.year < cont[i].endDate.year)) {
                printf("\nO ve�culo em quest�o esteve alugado na date em que inseriu, pelo que seria imposs�vel alug�-lo pois este estava indispon�vel\n");
                validateDate(data);
                cont[pos].startDate = data[0];
            }
        //Este while verifica se a date final � menor que a inicial. Enquanto for, ir� sempre pedir datas novas, estando a date final e a inicial validadas consoante o month e o year.
        while ((cont[pos].startDate.day > cont[pos].endDate.day && cont[pos].startDate.month == cont[pos].endDate.month && cont[pos].startDate.year == cont[pos].endDate.year) || (cont[pos].startDate.month > cont[pos].endDate.month && cont[pos].startDate.year == cont[pos].endDate.year) || cont[pos].startDate.year > cont[pos].endDate.year) {
            printf("\n A date � inv�lida! Insira outra vez...\n");
            validateDate(data);
            cont[pos].endDate = data[0];
        }
        // Volta a escrever a nova posi��o da caravana na matriz, que ao ter sido alugada passou a estar num local desconhecido
        printf("\nEscritorio onde se encontra o vehicle:");
        printf("\n0 Braga 1 Coimbra 2 Guarda 3 Faro 4 Lisboa 5 Porto");
        aux = readInt(0, 5);
        //O escritorio final ser� igual a localiza��o depois deste contract
        cont[pos].endOffice = aux;
        (local[encontrou][aux])++;
    }
}
// Esta fun��o difere da fun��o inserirContrato pois esta baseia-se em qualquer posi��o da fun��o, modificando-a, logo nao altera o valor da quantidade.
void editarContrato(contract cont[], vehicle vec[], int pos, date data[], int qtdvec, int qtd) {
    if (cont[pos].endDate.year != 0)
        printf("\n N�o � poss�vel editar o contract pois este j� se encontra finalizado\n");
    else {
        int i, encontrou;
        char valor2;
        encontrou = searchCodeVehicle(vec, qtdvec, cont[pos].codeVehicle);
        if (vec[encontrou].codeCategory > 3) {
            printf("\nIndique o pre�o por day\n");
            cont[pos].priceDay = readFloat(0.01, 9999);
        } else {
            printf("\nIndique o pre�o por km\n");
            cont[pos].priceKm = readFloat(0.01, 9999);
        }
        validateDate(data);
        cont[pos].startDate = data[0];
        for (i = 0; i < qtd; i++)
            while ((cont[pos].codeVehicle == cont[i].codeVehicle && cont[pos].startDate.day >= cont[i].startDate.day && cont[pos].startDate.day < cont[pos].endDate.day && cont[pos].startDate.month == cont[i].startDate.month && cont[pos].startDate.month == cont[i].endDate.month && cont[pos].startDate.year == cont[i].startDate.year && cont[pos].startDate.year == cont[i].endDate.year) || (cont[pos].codeVehicle == cont[i].codeVehicle && cont[pos].startDate.month >= cont[i].startDate.month && cont[pos].startDate.month < cont[i].endDate.month && cont[pos].startDate.year == cont[i].startDate.year && cont[pos].startDate.year == cont[i].endDate.year) || (cont[pos].codeVehicle == cont[i].codeVehicle && cont[pos].startDate.year >= cont[i].startDate.year && cont[pos].startDate.year < cont[i].endDate.year)) {
                printf("\nO ve�culo em quest�o esteve alugado na date em que inseriu, pelo que seria imposs�vel alug�-lo pois este estava indispon�vel\n");
                validateDate(data);
                cont[pos].startDate = data[0];
            }
    }
}

// Esta fun��o difere da fun��o inserirCli pois esta baseia-se em qualquer posi��o da fun��o, modificando-a, logo nao altera o valor da quantidade.
void editarCli(client cli[], contract cont[], int pos) {
    int i, aux = 0;
    for (i = 0; i < MAX_CONT; i++) {
        if (cont[i].codeClient == cli[pos].code && cont[i].endDate.day == 0) {
            printf("\n O client encontra-se em contract pelo que n�o � poss�vel modific�-lo\n");
            aux++;
        }
    }
    if (aux == 0) {
        int n;
        printf("\n--- Dados do client ---");
        char valor[MAX_TXT];
        readChars(valor, 30, "\nNome (max 30 caracteres):");
        printf("\n\t %s ", valor);
        strcpy(cli[pos].name, valor);
        readChars(valor, 40, "\nMorada (max 40 caracteres):");
        printf("\n\t %s ", valor);
        strcpy(cli[pos].address, valor);
        readChars(valor, 5, "\nCarta de conducao (max 5 caracteres):");
        printf("\n\t %s \n", valor);
        strcpy(cli[pos].driverLicense, valor);
    }
}

// Esta fun��o difere da fun��o insertVehicle pois esta baseia-se em qualquer posi��o da fun��o, modificando-a, logo nao altera o valor da quantidade.


// Apaga a posi��o desejada pelo utilizador, decrementando a quantidade 1 vez
void apagarCli(client cli[], contract cont[], int pos, int *qtd) {
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
void apagarContrato(contract contrato[], int pos, int *qtd) {
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
    int i, cat;
    printf("\n--- Dados do client ---\n");
    printf("\n Codigo: %hd", cli.code);
    printf("\n Nome: %s", cli.name);
    printf("\n Morada: %s", cli.address);
    printf("\n Tipo: %d", cli.type);
    printf("\n Carta de condu��o: %s\n", cli.driverLicense);
}

// Recebe um ve�culo por par�metro e mostra os seus dados
void mostrarVec(vehicle vec) {
    int i, cat;
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
    int i, cat;
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
int mostrarDadosCli(client cli[], int qtd) {
    int i, n, encontrou = -1;

    if (qtd == 0)
        printf("\nNao existem clientes registados!!\n");
    else {
        n = readInt(1000, 9999);
        encontrou = searchCodeClient(cli, qtd, n);
        if (encontrou >= 0)
            mostrarCli(cli[encontrou]);
        else
            printf("\nNao existe nenhum client com codigo = %hd\n", n);
    }
    getchar();
    return encontrou;
}
// Procura um ve�culo e mostra todos os seus dados
int mostrarDadosVec(vehicle vec[], int qtd) {
    int i, n, encontrou = -1;

    if (qtd == 0)
        printf("\nNao existem ve�culos registados!!\n");
    else {
        n = readInt(10, 99);
        encontrou = searchCodeVehicle(vec, qtd, n);
        if (encontrou >= 0)
            mostrarVec(vec[encontrou]);
        else
            printf("\nNao existe nenhum ve�culo com codigo = %hd\n", n);
    }
    getchar();
    return encontrou;
}
// Procura um contract e mostra todos os seus dados
int mostrarDadosContrato(contract contrato[], date data[], int qtd) {
    int i, n, encontrou = -1, aux = -1, codvec = -1;

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
void mostrarDadosClis(client cli[], int qtd) {
    int n, i;
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
void mostrarDadosVecs(vehicle vec[], int qtd) {
    int n, i;
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
void mostrarDadosContratos(contract cont[], int qtd) {
    int n, i, j;
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


void limpar_matriz(vehicle vec[], int local[][MAX_ESC]) {

    int l, c;
    for (l = 0; l < MAX_VC; l++) {
        vec[l].code = 0;
        for (c = 0; c < MAX_ESC; c++)
            local[l][c] = 0;
    }
}

void mostrar_matriz(vehicle vec[], int local[][MAX_ESC], int qtd) {

    int l, c;
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
void criarDados(client cli[], vehicle vec[], int *qtdcli, int *qtdvec, int local[][MAX_ESC]) {
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
    int qtd_cli = 0, qtd_vc = 0, qtd_cont = 0, qtd_data, pos_cli = -1, pos_vc = -1, pos_cont = -1;
    client vec_cli[MAX_CLI];
    int ch, local[MAX_VC][MAX_ESC];
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
                insertVehicle(veiculos_vec, &qtd_vc, local);
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
                        editVehicle(veiculos_vec, contrato_vec, pos_vc, local);

                    }
                    // colocar aqui o c�digo para chamar o m�dulo modificar vehicle
                    else if (op == 'A' || op == 'a') {
                        deleteVehicle(veiculos_vec, contrato_vec, pos_vc, &qtd_vc, local);
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
