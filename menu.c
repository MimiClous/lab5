#include <stdio.h>

int menu()
{
    int action;
    int res;

    printf("1. Вывести товары на экран\n");
    printf("2. Добавить новый товар в базу\n");
    printf("3. Удалить товар из базы\n");
    printf("4. Поиск товаров\n");
    printf("5. Сохранить в файл\n");
    printf("6. Загрузить из файла\n");
    printf("7. Выход\n");
    printf("Выберите действие: ");

    res = scanf("%d", &action);

    if (res != 1){
        printf("Некорректные данные. Требуется число\n");
        while (getchar() != '\n');
        return 0;
    }
    if (action < 1 || action > 7){
        printf("Некорректные данные\n");
        return 0;
    }

    return action;
}