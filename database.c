#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

List* create_list() {
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void add_product(List* list) {
    Node* new_Node = (Node*)malloc(sizeof(Node));
    
    printf("\nДобавление нового товара\n");
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("Введите название товара: ");
    fgets(new_Node->name, 150, stdin);
    new_Node->name[strcspn(new_Node->name, "\n")] = '\0';
    
    printf("Введите цену товара: ");
    scanf("%f", &new_Node->price);
    
    printf("Введите количество: ");
    scanf("%d", &new_Node->kolvo);
    
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("Введите категорию: ");
    fgets(new_Node->category, 100, stdin);
    new_Node->category[strcspn(new_Node->category, "\n")] = '\0';
    
    printf("Введите описание: ");
    fgets(new_Node->description, 500, stdin);
    new_Node->description[strcspn(new_Node->description, "\n")] = '\0';
    
    new_Node->next = NULL;
    new_Node->past = NULL;

    if (list->tail == NULL) {
        list->head = new_Node;
        list->tail = new_Node;
    } else {
        new_Node->past = list->head;
        list->head->next = new_Node;
        list->head = new_Node;
    }
    list->size++;
    printf("\nТовар успешно добавлен!\n");
}

void free_list(List* list){
    if (list == NULL) return;

    Node* curr = list->tail;
    while (curr != NULL){
        Node* next = curr->next;
        free(curr);
        curr = next;
    }
    free(list);
}

void print_list(List* list) {
    if (list->size == 0) {
        printf("Список товаров пуст!\n");
        return;
    }
    printf("\nСписок товаров:\n");
    
    Node* current = list->tail;
    int i = 1;
    
    while (current != NULL) {
        printf("#%d  Наименование товара:%s\nЦена:%f Кол-во:%d\nКатегория:%s\nОписание:%s\n\n", i, current->name, current->price, current->kolvo, current->category, current->description);
        current = current->next;
        i++;
    }
}

void search_products(List* list) {
    if (list->size == 0) {
        printf("Список товаров пуст!\n");
        return;
    }
    
    int search;
    printf("\nПОИСК ТОВАРОВ\n");
    printf("1. Поиск по цене\n");
    printf("2. Поиск по количеству\n");
    scanf("%d", &search);
    
    Node* current = list->tail;
    int found = 0;
    
    if (search == 1) {
        float price;
        printf("Введите цену для поиска: ");
        scanf("%f", &price);
        
        printf("\nТовары с ценой %f:\n", price);
        while (current != NULL) {
            if (current->price == price) {
                printf("\nНайден товар:\n");
                printf("  Наименование: %s\n", current->name);
                printf("  Цена: %f\n", current->price);
                printf("  Кол-во: %d\n", current->kolvo);
                printf("  Категория: %s\n", current->category);
                found++;
            }
            current = current->next;
        }
    }
    else if (search == 2) {
        int quantity;
        printf("Введите количество для поиска: ");
        scanf("%d", &quantity);
        
        printf("\nТовары с количеством %d:\n", quantity);
        while (current != NULL) {
            if (current->kolvo == quantity) {
                printf("\nНайден товар:\n");
                printf("  Наименование: %s\n", current->name);
                printf("  Цена: %.2f\n", current->price);
                printf("  Кол-во: %d\n", current->kolvo);
                printf("  Категория: %s\n", current->category);
                found++;
            }
            current = current->next;
        }
    }
    else {
        printf("Неправильные данные");
        return;
    }
    
    if (!found) {
        printf("\nТовары не найдены по заданным критериям.\n");
    } else {
        printf("\nВсего найдено товаров: %d\n", found);
    }
}

void delete_product(List* list, char* name){
    if (list->size == 0) {
        printf("Список товаров пуст!\n");
        return;
    }
    
    Node* current = list->tail;
    int deleted = 0;
    
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (current->past == NULL) {
                list->tail = current->next;
                if (list->tail != NULL) {
                    list->tail->past = NULL;
                }
            } else {
                current->past->next = current->next;
            }
            
            if (current->next == NULL) {
                list->head = current->past;
                if (list->head != NULL) {
                    list->head->next = NULL;
                }
            } else {
                current->next->past = current->past;
            }
            
            Node* to_delete = current;
            current = current->next;
            free(to_delete);
            list->size--;
            deleted = 1;
            printf("Товар '%s' удален\n", name);
            break;
        } else {
            current = current->next;
        }
    }
    
    if (!deleted) {
        printf("Товар с именем '%s' не найден\n", name);
    }
}
void edit_product(List* list){
    if (list->size == 0) {
        printf("Список товаров пуст!\n");
        return;
    }
    
    print_list(list);
    
    int product_num;
    printf("\nВведите номер товара для редактирования (1-%d): ", list->size);
    scanf("%d", &product_num);
    
    if (product_num < 1 || product_num > list->size) {
        printf("Некорректный номер товара!\n");
        return;
    }
    
    Node* current = list->tail;
    for (int i = 1; i < product_num; i++) {
        current = current->next;
    }
    
    int choice;
    int c;
    
    printf("\n1. Наименование: %s\n", current->name);
    printf("2. Цена: %.2f\n", current->price);
    printf("3. Количество: %d\n", current->kolvo);
    printf("4. Категория: %s\n", current->category);
    printf("5. Описание: %s\n", current->description);
    printf("6. Выйти\n");
    printf("Выберите поле для редактирования: ");
    scanf("%d", &choice);
    
    while ((c = getchar()) != '\n' && c != EOF);
    
    if (choice == 1) {
        printf("Введите новое наименование: ");
        fgets(current->name, sizeof(current->name), stdin);
        current->name[strcspn(current->name, "\n")] = '\0';
    }
    else if (choice == 2) {
        printf("Введите новую цену: ");
        scanf("%f", &current->price);
        while ((c = getchar()) != '\n' && c != EOF);
    }
    else if (choice == 3) {
        printf("Введите новое количество: ");
        scanf("%d", &current->kolvo);
        while ((c = getchar()) != '\n' && c != EOF);
    }
    else if (choice == 4) {
        printf("Введите новую категорию: ");
        fgets(current->category, sizeof(current->category), stdin);
        current->category[strcspn(current->category, "\n")] = '\0';
    }
    else if (choice == 5) {
        printf("Введите новое описание: ");
        fgets(current->description, sizeof(current->description), stdin);
        current->description[strcspn(current->description, "\n")] = '\0';
    }
    
    if (choice >= 1 && choice <= 5) {
        printf("Изменения сохранены!\n");
    }
}