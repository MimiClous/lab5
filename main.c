#include <stdio.h>
#include "database.h"
#include "files.h"
#include "menu.h"


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
        else if (action == 3){
            char name_prod[150];
            printf("Удалить товар под именем: ");

            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            
            int i = 0;
            while (i < 149 && (c = getchar()) != '\n' && c != EOF) {
                name_prod[i++] = c;
            }
            name_prod[i] = '\0';
            
            delete_product(product_list, name_prod);
            save(product_list);
        }
        else if (action == 4) {
            search_products(product_list);
        }
        else if (action == 5) {
            save(product_list);  
        }
        else if (action == 6) {
            load(product_list);      
        }
        else if (action == 7) {
            save(product_list);  
            printf("Выход\n");
            free_list(product_list);
            return 0;
        }
        
        action = 0;  
    }

    return 0;
}