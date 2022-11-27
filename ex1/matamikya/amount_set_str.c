#include "amount_set_str.h"

#include <string.h>

#include "amount_set_str_list.h"

struct AmountSet_t {
    AmountNode head;
    AmountNode iterator;
};

// a function to create a new amount set with no elements.
AmountSet asCreate() {
    AmountSet new = malloc(sizeof(*new));
    if (new == NULL) {
        return NULL;
    }
    new->head = NULL;
    return new;
}
// a funtion to destroy a given amount set and free all elements
void asDestroy(AmountSet set) {
    if (set == NULL) {
        return;
    }
    destroyList(set->head);
    free(set);
}
// a function to copy a given amount set and returns it
AmountSet asCopy(AmountSet set) {
    if (set == NULL) {
        return NULL;
    }
    AmountSet new = asCreate();
    if (new == NULL) {//memory error
        return NULL;
    }
    AmountNode srcNode = set->head;
    if(srcNode == NULL){//set has an empty list, returning
        return new;
    }

    AmountNode destNode = copyNode(set->head);
    if(destNode == NULL){//memory error
        asDestroy(new);
        return NULL;
    }
    new->head = destNode;
    while (srcNode != NULL) { //copying all nodes
        srcNode = srcNode->next;
        destNode->next = copyNode(srcNode);
        destNode = destNode->next;
    }
    return new;
}

// a function to get the amount of elements in the given set
int asGetSize(AmountSet set) {
    if (set == NULL) {//checks if the argument is null
        return -1;
    }
    AmountNode node = set->head;
    int c = 0;
    while (node != NULL) {
        c++;
        node = node->next;
    }
    return c;
}

// a function to return the element that corresponds with the given name, null if not found
AmountNode asNodeOf(AmountSet set, const char* element) {
    if (set == NULL || element == NULL) { //checks if an argument is null
        return NULL;
    }
    AmountNode temp = set->head;
    while (temp != NULL) {
        if (strcmp(temp->name, element) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;//not found.
}

// a function to check if such element exists in the given set 
bool asContains(AmountSet set, const char* element) {
    if (asNodeOf(set, element) == NULL) {
        return false;
    } else {
        return true;
    }
}

//a function to get the amount of a given element in the set, puts the result in *outAmount
AmountSetResult asGetAmount(AmountSet set, const char* element, double* outAmount) {
    if (set == NULL || element == NULL || outAmount == NULL) {
        return AS_NULL_ARGUMENT;
    }
    AmountNode node = asNodeOf(set, element);// checks if such element exists in the set 
    if (node == NULL) {
        return AS_ITEM_DOES_NOT_EXIST;
    }
    *outAmount = node->amount;

    return AS_SUCCESS;
}
// a function that registers the given element to the set 
AmountSetResult asRegister(AmountSet set, const char* element) {
    if (set == NULL || element == NULL) {
        return AS_NULL_ARGUMENT;
    }
    if (asContains(set, element) == true) {
        return AS_ITEM_ALREADY_EXISTS;
    }
    char* namecpy = malloc(strlen(element) + 1); //allocates char* to hold a copy of the name in our set
    if (namecpy == NULL) {
        return AS_OUT_OF_MEMORY;
    }
    strcpy(namecpy, element);
    AmountNode new = createNode(namecpy, 0);
    if (new == NULL) {
        free(namecpy);
        return AS_OUT_OF_MEMORY;
    }
    if (set->head == NULL) { //if there are no elements, new will be the head
        set->head = new;
    } else if (strcmp(set->head->name, element) >= 0) {//there are elements, check if the new element needs to be inserted at the beggining
        new->next = set->head;
        set->head = new;
    } else {
        AmountNode temp = set->head;
        while (temp->next != NULL && strcmp(temp->next->name, element) < 0) {//new needs to be inserted in the middle or end of the elements list
            temp = temp->next;
        }
        new->next = temp->next;
        temp->next = new;
    }
    return AS_SUCCESS;
}
// a function to update the amount of a given element
AmountSetResult asChangeAmount(AmountSet set, const char* element, const double amount) {
    if (set == NULL || element == NULL) {
        return AS_NULL_ARGUMENT;
    }
    AmountNode node = asNodeOf(set, element);//checks if such element exists in the set 
    if (node == NULL) {
        return AS_ITEM_DOES_NOT_EXIST;
    }
    if ((node->amount + amount) < 0) {//checks if after the update the amount is vaild 
        return AS_INSUFFICIENT_AMOUNT;
    }
    node->amount += amount;
    return AS_SUCCESS;
}
  // a function to delete the given element from the set 
AmountSetResult asDelete(AmountSet set, const char* element) {
    if (set == NULL || element == NULL) {
        return AS_NULL_ARGUMENT;
    }
    if (asContains(set, element) == false) {
        return AS_ITEM_DOES_NOT_EXIST;
    }
    AmountNode tempNode = set->head;
    if (strcmp(tempNode->name, element) == 0) {  //handling deleting first node
        set->head = set->head->next;
        free(tempNode->name);
        free(tempNode);
        return AS_SUCCESS;
    }
    while (strcmp(tempNode->next->name, element) != 0) { //needs to delete a node from the middle or end of the list
        tempNode = tempNode->next;
    }
    //deleting tempNode->next
    AmountNode toDelete = tempNode->next;
    tempNode->next = tempNode->next->next;
    free(toDelete->name);
    free(toDelete);
    return AS_SUCCESS;
}
// a function to clear a given set from all it's elements 
AmountSetResult asClear(AmountSet set) {
    if (set == NULL) {
        return AS_NULL_ARGUMENT;
    }
    destroyList(set->head);//frees all the elements
    set->head = NULL;
    return AS_SUCCESS;
}

// a function to move the iterator to the first element and return it's name
char* asGetFirst(AmountSet set) {
    if (set == NULL) {
        return NULL;
    }
    if (set->head == NULL) {
        return NULL;//no items in the set
    }
    set->iterator = set->head; //sets the iterator to the beggining of the list
    return set->iterator->name; //returns the name of the first element
}
// a function to move the iterator to the next element and return it's name
char* asGetNext(AmountSet set) {
    if (set == NULL) {
        return NULL;
    }
    if (set->iterator == NULL) {  //invalid state
        return NULL;
    }
    set->iterator = set->iterator->next;
    if (set->iterator == NULL) {  //end of elements
        return NULL;
    }
    return set->iterator->name;
}
