#include <stdio.h>
#include "database.h"
#include "files.h"

int menu()
{
    int action;
    int res;

    printf("1. Вывести товары на экран\n");
    printf("2. Добавить новый товар\n");
    printf("3. Поиск товаров\n");
    printf("4. Сохранить в файл\n");
    printf("5. Загрузить из файла\n");
    printf("6. Выход\n");
    printf("Выберите действие: ");

    res = scanf("%d", &action);

    if (res != 1){
        printf("Некорректные данные. Требуется число\n");
        while (getchar() != '\n');
        return 0;
    }
    if (action < 1 || action > 6){
        printf("Некорректные данные\n");
        return 0;
    }

    return action;
}

int main(){
    List* product_list = create_list();
    load(product_list);    
    int action = 0;
    
    while (action == 0){
        action = menu();
        
        if (action == 0) continue;
        
        if (action == 1) {
            print_list(product_list); 
        }
        else if (action == 2) {
            add_product(product_list);
            save(product_list);  
        }
        else if (action == 3) {
            search_products(product_list);
        }
        else if (action == 4) {
            save(product_list);  
        }
        else if (action == 5) {
            load(product_list);      
        }
        else if (action == 6) {
            save(product_list);  
            printf("Выход\n");
            free_list(product_list);
            return 0;
        }
        
        action = 0;  
    }

    return 0;
}