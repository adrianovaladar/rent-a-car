#include "customer.h"

int searchCodeClient(customer cli[], int qtd, int cod) {
    int i, enc = -1;

    for (i = 0; i <= qtd && enc == -1; i++)
        if (cli[i].code == cod)
            enc = i;

    return enc;
}
