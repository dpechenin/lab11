#include "Header.h"

flat *generateData(unsigned int n, int c) {
    flat *arrOfFlats = (flat*)malloc(n * sizeof(flat));
    if (!arrOfFlats) return NULL;
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; ++i) {
        arrOfFlats[i].flatNum = rand()%300;
        arrOfFlats[i].type = rand() % 4;
        for(int j = 0; j < 49; ++j) {
            if (j == 15 || j == 30) {
                arrOfFlats[i].name[j] = ' ';
            }
            else if (j == 0 || j == 16 || j == 31) {
                arrOfFlats[i].name[j] = rand()%26+'A';
            }
            else {
                arrOfFlats[i].name[j] = rand()%26+'a';
            }
        }
        arrOfFlats[i].debtsUtilityBills = rand()%10000;
        arrOfFlats[i].amountResidents = rand()%10;
    }
    
    int tmp = rand() % 10;
    for (int i = 0; i < tmp; i++) {
        int tmp2 = rand() % n;
        arrOfFlats[tmp2] = arrOfFlats[c];
    }
    
    return arrOfFlats;
}

void printHeader(void){
    printf("Номер квартиры | Тип квартиры | ФИО владельца |Сумма задолжности по ЖКХ | Кол-во людей живущих в квартире\n");
}

void printFlat(flat flat1) {
    printf("%u | %d | %s | %u | %u\n", flat1.flatNum, flat1.type, \
           flat1.name, flat1.debtsUtilityBills, flat1.amountResidents);
    printf("\n");
}

