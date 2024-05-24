#include "Header.h"

int main(void) {
    unsigned int amountsOfData[] = {1000, 5000, 10000, 20000, 50000, 100000, 1000000}; // количество генирируеммых данных
    double timeTreeSearch[7]; // сюда запишем время поиска с помощью дерева
    double timeHashSearch[7]; // сюда запишем время поиска с помощью хэщ таблицы
    // в цикле делаем все тесты
    for (int i = 0; i < 7; i++) {
        clock_t t1, t2, t3, t4;
        system("clear");
        printf("Попытка номер: %d\n", i + 1);
        printf("Количество элементов: %d\n", amountsOfData[i]);
        srand((unsigned)time(NULL));
        int c = rand() % amountsOfData[i];
        flat *arrOfFlats = generateData(amountsOfData[i], c);
        tree *testTree = NULL;
        testTree = treeFromArray(arrOfFlats, amountsOfData[i]);
        printf("Поиск с помощью бинарного дерева:\n");
        char *nameToFind = arrOfFlats[c].name;
        printf("Нужно найти квартиры с ФИО владельца: %s\n", nameToFind);
        printHeader();
        t1 = clock();
        searchTree(testTree, nameToFind);
        t2 = clock();
        timeTreeSearch[i] = (double)(t2 - t1) / CLOCKS_PER_SEC;
        freeTree(testTree);
                
        printf("Поиск хэш-таблицей:\n");
        t3 = clock();
        
        t4 = clock();
        timeHashSearch[i] = (double)(t4 - t3) / CLOCKS_PER_SEC;
        free(arrOfFlats);
        printf("Нажмите пробел, чтобы продолжить тест дальше:\n");
        getchar();
    }
    system("clear");
    printf("Получившиеся результаты:\n");
    printf("Количесвто данных | Время поиска с помощью дерева | Время поиска с помощью хэш-таблицы\n");
    for (int i = 0; i < 7; i++) {
        printf("%u \t\t\t\t\t %f \t\t\t\t\t %f\n", amountsOfData[i], timeTreeSearch[i], timeHashSearch[i]);
    }
    return 0;
}
