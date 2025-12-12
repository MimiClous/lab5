#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

List* create_list() {
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->capacity = 0;
    return list;
}

void add_product(List* list) {
    Node* new_Node = (Node*)malloc(sizeof(Node));
    
    printf("\nДобавление нового товара\n");
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("Введите название товара: ");
    int i = 0;
    int error = 0;
    while (i < 149 && (c = getchar()) != '\n' && c != EOF) {
        if (c == ':' || c == ';' || c == '\\') {
            printf("\nОшибка! Нельзя использовать символы : ; \\ в названии\n");
            error = 1;
            break;
        }
        new_Node->name[i++] = c;
    }
    new_Node->name[i] = '\0';
    
    if (error) {
        free(new_Node);
        return;
    }
    
    printf("Введите цену товара: ");
    if (scanf("%f", &new_Node->price) != 1) {
        printf("\nОшибка ввода цены!\n");
        free(new_Node);
        return;
    }
    
    printf("Введите количество: ");
    if (scanf("%d", &new_Node->kolvo) != 1) {
        printf("\nОшибка ввода количества!\n");
        free(new_Node);
        return;
    }
    
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("Введите категорию: ");
    i = 0;
    error = 0;
    while (i < 99 && (c = getchar()) != '\n' && c != EOF) {
        if (c == ':' || c == ';' || c == '\\') {
            printf("\nОшибка! Нельзя использовать символы : ; \\ в категории\n");
            error = 1;
            break;
        }
        new_Node->category[i++] = c;
    }
    new_Node->category[i] = '\0';
    
    if (error) {
        free(new_Node);
        return;
    }
    
    printf("Введите описание: ");
    i = 0;
    error = 0;
    while (i < 499 && (c = getchar()) != '\n' && c != EOF) {
        if (c == ';' || c == '\\') {
            printf("\nОшибка! Нельзя использовать символы ; \\ в описании\n");
            error = 1;
            break;
        }
        new_Node->description[i++] = c;
    }
    new_Node->description[i] = '\0';
    
    if (error) {
        free(new_Node);
        return;
    }
    
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