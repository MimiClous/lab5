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
    int capacity;           
} List;

List* create_list();
void add_product(List* list);
void free_list(List* list);
void print_list(List* list);
void insert_product(List* list, int index);
void search_products(List* list);
void delete_product(List* list);
void edit_product(List* list);

#endif