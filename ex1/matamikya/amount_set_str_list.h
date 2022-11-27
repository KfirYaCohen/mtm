#ifndef AMOUNT_SET_STR_LIST_H_
#define AMOUNT_SET_STR_LIST_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct node_t {
    char* name;
    double amount;
    struct node_t* next;
} * AmountNode;

AmountNode createNode(char* name, double amount);

int getListLength(AmountNode list);

void destroyList(AmountNode ptr);

AmountNode copyNode(AmountNode node);

#endif  //_AMOUNT_LIST_H
