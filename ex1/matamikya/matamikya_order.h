#ifndef MATAMIKYA_ORDER_H_
#define MATAMIKYA_ORDER_H_

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "amount_set.h"
#include "set.h"

#include "matamikya.h"

// a struct to hold an order's information
typedef struct Order_t * Order;


// a function to get given order's id
unsigned int orderGetId(Order order);
// a function to set an id for a given order
void orderSetId(Order order, unsigned int id);

// a function to get the items of a given order
AmountSet orderGetItems(Order order);
// a function to set the items of a given order
void orderSetItems(Order order, AmountSet items);

// a function to create a new order with a given id and items AmountSet
MatamikyaResult orderCreate(Order *adressToReturn, unsigned int id, AmountSet items);

// a function to copy an order type and returns the allocated copy.
SetElement orderCopy(SetElement order);

// a function to destroy an order type
void orderDestroy(SetElement order);

// a function to compare two orders types, returns the difference between their ID's
int orderCompare(SetElement order1, SetElement order2);




#endif  // MATAMIKYA_ORDER_H_