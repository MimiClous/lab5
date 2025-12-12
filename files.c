#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"
#include "database.h"

void load(List* list) {
    FILE* file = fopen("bd.txt", "r");
    if (!file) return;

    if (list->size > 0) free_list(list);
    *list = *(create_list());
    
    int total;
    fscanf(file, "%d:", &total);
    
    for (int i = 0; i < total; i++) {
        Node* node = malloc(sizeof(Node));
        if (!node) break;
        
        int j = 0;
        int c;
        
        while (j < 49 && (c = fgetc(file)) != ':' && c != EOF) {
            node->name[j++] = c;
        }
        node->name[j] = '\0';
        
        fscanf(file, "%f:", &node->price);
        
        fscanf(file, "%d:", &node->kolvo);
        
        j = 0;
        while (j < 29 && (c = fgetc(file)) != ':' && c != EOF) {
            node->category[j++] = c;
        }
        node->category[j] = '\0';
        
        j = 0;
        while (j < 149 && (c = fgetc(file)) != ';' && c != EOF) {
            node->description[j++] = c;
        }
        node->description[j] = '\0';
        
        node->next = NULL;
        node->past = NULL;
        
        if (list->tail == NULL) {
            list->head = node;
            list->tail = node;
        } else {
            node->past = list->head;
            list->head->next = node;
            list->head = node;
        }
        list->size++;
    }
    fclose(file);
}

void save(List* list) {
    FILE* file = fopen("bd.txt", "w");
    if (!file) {
        printf("Файла не существует, либо он недоступен\n");
        return;
    }
    
    fprintf(file, "%d:", list->size);
    
    Node* current = list->tail;  
    int count = 0;
    while (current != NULL) {
        fprintf(file, "%s:%.2f:%d:%s:%s;",
                current->name,
                current->price,
                current->kolvo,
                current->category,
                current->description);
        count++;
        current = current->next;
    }
    
    fclose(file);
}