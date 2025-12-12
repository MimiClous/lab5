#ifndef DATABASE_H
#define DATABASE_H

typedef struct Node {
    char name[150];
    float price;
    int kolvo;
    char category[100];
    char description[500];
    struct Node* past;  
    struct Node* next;  
} Node;

typedef struct {
    Node* head;         
    Node* tail;        
    int size;
} List;

List* create_list();
void add_product(List* list);
void free_list(List* list);
void print_list(List* list);
void search_products(List* list);
void delete_product(List* list, char* name);
void search_by_name(List* list, char* name);
void search_by_price(List* list, float price);
void search_by_quantity(List* list, int quantity);

#endif