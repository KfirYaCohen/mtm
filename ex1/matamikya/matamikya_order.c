#include "matamikya_order.h"

struct Order_t {
    unsigned int id;
    AmountSet items;
};

// a function to get given order's id
unsigned int orderGetId(Order order) { return order->id; }
// a function to set an id for a given order
void orderSetId(Order order, unsigned int id) { order->id = id; }

// a function to get the items of a given order
AmountSet orderGetItems(Order order) { return order->items; }
// a function to set the items of a given order
void orderSetItems(Order order, AmountSet items) { order->items = items; }

// a function to create a new order with a given id and items AmountSet
MatamikyaResult orderCreate(Order *adressToReturn, unsigned int id, AmountSet items){
    Order newOrder = malloc(sizeof(*newOrder));
    if ( newOrder == NULL){
        return MATAMIKYA_OUT_OF_MEMORY;
    }
    newOrder->id = id;
    newOrder->items = items;
    *adressToReturn = newOrder;
    return MATAMIKYA_SUCCESS;
}

// a function to copy an order type and returns the allocated copy.
SetElement orderCopy(SetElement order) {
    if (order == NULL) {
        return NULL;  // null argument
    }
    Order newOrder = malloc(sizeof(*newOrder));
    if (newOrder == NULL) {
        return NULL;  // memory error
    }
    newOrder->id = ((Order)order)->id;
    newOrder->items = asCopy(((Order)order)->items);
    return newOrder;
}

// a function to destroy an order type
void orderDestroy(SetElement order) {
    if (order == NULL) {
        return;  // null argument
    }
    asDestroy(((Order)order)->items);
    free(order);
}

// a function to compare two orders types, returns the difference between their ID's
int orderCompare(SetElement order1, SetElement order2) {
    if (order1 == NULL || order2 == NULL) {
        return false;  // null argument
    }
    return ((Order)order1)->id - ((Order)order2)->id;
}


