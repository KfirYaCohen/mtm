#include "amount_set_str_list.h"

#include <string.h>

//a function to create a new amount list node with a given name and amount.
AmountNode createNode(char* name, double amount) {
    AmountNode new = malloc(sizeof(*new));
    if (new == NULL) {
        return NULL;
    }
    new->name = name;
    new->amount = amount;
    new->next = NULL;
    return new;
}

//a function to destroy list 
void destroyList(AmountNode ptr) {
    while (ptr) {
        AmountNode toDelete = ptr;

        ptr = ptr->next;
        free(toDelete->name);
        free(toDelete);
    }
}

//a function to copy a given node and return the new allocated copy
AmountNode copyNode(AmountNode node) {
    if (node == NULL) {
        return NULL;
    }
    char* namecpy = malloc(strlen(node->name) + 1);
    if (namecpy == NULL) {
        return NULL;
    }
    strcpy(namecpy, node->name);
    AmountNode new = createNode(namecpy, node->amount);
    if (new == NULL) {
        return NULL;
    }
    return new;
}
