#include "matamikya.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "amount_set.h"
#include "matamikya_order.h"
#include "matamikya_print.h"
#include "matamikya_product.h"
#include "set.h"

// a struct to hold the warehouse information
struct Matamikya_t {
    AmountSet inventory;
    Set orders;
    unsigned int lastOrderID;
};

// a function to copy an order element type, returns the allocated copy.
ASElement orderElementCopy(ASElement orderElement) {
    if (orderElement == NULL) {
        return NULL;  // null argument
    }
    unsigned int* newOrderElement = malloc(sizeof(*newOrderElement));
    if (newOrderElement == NULL) {
        return NULL;  // memory error
    }
    *(unsigned int*)newOrderElement = *(unsigned int*)orderElement;
    return newOrderElement;
}

// a function to compare two order element types, returns the difference between their ID's
int orderElementCompare(ASElement orderElement1, ASElement orderElement2) {
    if (orderElement1 == NULL || orderElement2 == NULL) {
        return false;
    }
    return *((unsigned int*)orderElement1) - *((unsigned int*)orderElement2);
}
// a function to destroy an order's element type
void orderElementDestroy(ASElement orderElement) {
    if (orderElement == NULL) {
        return;  // null argument
    }
    free(orderElement);
}

// creates a new warehouse with an empty inventory and an empty orders set and returns it
Matamikya matamikyaCreate() {
    Matamikya newWarehouse = malloc(sizeof(*newWarehouse));
    if (newWarehouse == NULL) {
        return NULL;
    }
    newWarehouse->inventory = asCreate(productCopy, productDestroy, productCompare);
    newWarehouse->orders = setCreate(orderCopy, orderDestroy, orderCompare);
    newWarehouse->lastOrderID = 0;  // no orders yet.

    return newWarehouse;
}

// a function to destory a warehouse type
void matamikyaDestroy(Matamikya matamikya) {
    if (matamikya == NULL) {
        return;  // null argument
    }
    asDestroy(matamikya->inventory);
    setDestroy(matamikya->orders);
    free(matamikya);
}

// a function to check if the str is valid as required
bool strValid(const char* name) {
    if ((*name >= 'a' && *name <= 'z') || (*name >= 'A' && *name <= 'Z') || (*name >= '0' && *name <= '9')) {
        return true;
    }
    return false;
}

// a function to check if the amount is corresponds with the amount type
bool isValidAmount(MatamikyaAmountType amountType, double amount) {
    int flooredAmount = amount;                       // casts the double to int to remove the decimal part. (7.998 -> 7)
    double decimal = amount - (double)flooredAmount;  // gets only the digits after the decimal point (7.998-7 = 0.998)
    if (decimal < 0) {                                // if the amout is negative this will also be nagative. we should check the abs value.
        decimal = -decimal;
    }
    switch (amountType) {
        case MATAMIKYA_INTEGER_AMOUNT:
            if (0.999 <= decimal || decimal <= 0.001) {
                return true;
            }
            break;
        case MATAMIKYA_HALF_INTEGER_AMOUNT:
            if (0.999 <= decimal || decimal <= 0.001) {
                return true;
            } else if (0.499 <= decimal && decimal <= 0.501) {
                return true;
            }
            break;
        case MATAMIKYA_ANY_AMOUNT:
            return true;
    }

    return false;
}
// a function to create a new product and registers it to the given warehouse
MatamikyaResult mtmNewProduct(Matamikya matamikya, const unsigned int id, const char* name, const double amount, const MatamikyaAmountType amountType, const MtmProductData customData, MtmCopyData CopyData, MtmFreeData FreeData, MtmGetProductPrice ProdPrice) {
    if (!(matamikya && name && customData && CopyData && FreeData && ProdPrice)) {  // checks if any of the args is NULL
        return MATAMIKYA_NULL_ARGUMENT;                                             // null argument
    }
    if (!strValid(name)) {  // checks if the name is valid
        return MATAMIKYA_INVALID_NAME;
    }
    if (amount < 0 || isValidAmount(amountType, amount) == false) {  // checks if the amount is valid
        return MATAMIKYA_INVALID_AMOUNT;
    }
    Product newProduct = NULL;
    MatamikyaResult result = productCreate(&newProduct, id, name, amountType, customData, CopyData, FreeData, ProdPrice);
    if (result != MATAMIKYA_SUCCESS) {
        return result;
    }
    if (asContains(matamikya->inventory, newProduct)) {  // checks if such product already exists
        productDestroy(newProduct);
        return MATAMIKYA_PRODUCT_ALREADY_EXIST;
    }
    asRegister(matamikya->inventory, newProduct);              // Add a new element into the inventory
    asChangeAmount(matamikya->inventory, newProduct, amount);  // updating the correct amount
    productDestroy(newProduct);                                // asRegister creates a new allocated copy of newProduct, so our newProduct is no longer needed.

    return MATAMIKYA_SUCCESS;
}

// a function that returns the product that corrsponds to the given id, returns null if not found.
Product getProductWithID(AmountSet inventory, unsigned int id) {
    AS_FOREACH(Product, iterator, inventory) {
        if (productGetId(iterator) == id) {
            return iterator;
        }
    }
    return NULL;  // returns null if not found
}

// a function to change a product's amount in the warehouse
MatamikyaResult mtmChangeProductAmount(Matamikya matamikya, const unsigned int id, const double amount) {
    if (matamikya == NULL) {
        return MATAMIKYA_NULL_ARGUMENT;  // null argument
    }
    // get the Product with the given id
    Product product = getProductWithID(matamikya->inventory, id);
    if (product == NULL) {  // product not found in inventory
        return MATAMIKYA_PRODUCT_NOT_EXIST;
    }
    // checks if amount is valid for the product's amountType
    double currentAmount = 0;
    asGetAmount(matamikya->inventory, product, &currentAmount);
    if (isValidAmount(productGetAmountType(product), amount) == false) {
        return MATAMIKYA_INVALID_AMOUNT;
    }
    if (isValidAmount(productGetAmountType(product), currentAmount + amount) == false) {
        return MATAMIKYA_INVALID_AMOUNT;
    }
    // updating the product's amount if possible
    if (asChangeAmount(matamikya->inventory, product, amount) == AS_INSUFFICIENT_AMOUNT) {
        return MATAMIKYA_INSUFFICIENT_AMOUNT;
    }

    return MATAMIKYA_SUCCESS;
}
// a function that clears a product from all orders
void clearProductFromAllOrders(Set orders, unsigned int id) {
    SET_FOREACH(Order, iterator, orders) {
        // delete the product
        asDelete(orderGetItems(iterator), &id);
    }
}
// a function that removes a product from the warehouse's inventory completely
MatamikyaResult mtmClearProduct(Matamikya matamikya, const unsigned int id) {
    if (matamikya == NULL) {
        return MATAMIKYA_NULL_ARGUMENT;  // null argument
    }
    // getting the Product with the given id
    Product iterator = getProductWithID(matamikya->inventory, id);
    if (iterator == NULL) {  // product not found in inventory
        return MATAMIKYA_PRODUCT_NOT_EXIST;
    }
    asDelete(matamikya->inventory, iterator);
    clearProductFromAllOrders(matamikya->orders, id);  // after removing the product, we need to remove it from all of the existing orders.
    return MATAMIKYA_SUCCESS;
}
// a function to create a new empty order and returns the ID
unsigned int mtmCreateNewOrder(Matamikya matamikya) {
    if (matamikya == NULL) {
        return 0;  // null argument
    }
    matamikya->lastOrderID++;  // creating a new order, increasing last order id

    AmountSet items = asCreate(orderElementCopy, orderElementDestroy, orderElementCompare);
    if (items == NULL) {
        return 0;  // memory error
    }

    Order newOrder = NULL;
    MatamikyaResult result = orderCreate(&newOrder,matamikya->lastOrderID, items);
    if (result != MATAMIKYA_SUCCESS) {
        asDestroy(items);
        matamikya->lastOrderID--;
        return 0;  // memory error
    }

    setAdd(matamikya->orders, newOrder);
    orderDestroy(newOrder);  // setAdd creates a new allocated copy of newOrder, our newOrder is not needed anymore.
    return matamikya->lastOrderID;
}
// a function that returns the order that corrsponds to the given id, returns null if not found.
Order getOrderWithID(Set orders, unsigned int id) {
    SET_FOREACH(Order, iterator, orders) {
        if (orderGetId(iterator) == id) {
            return iterator;
        }
    }
    return NULL;  // returns null if not found
}
// a function that checks if a product ID exists in the given order
bool productIdExistInOrder(Order order, const unsigned int id) {
    if (order == NULL) {
        return false;
    }
    AS_FOREACH(unsigned int*, iterator, orderGetItems(order)) {
        if (*iterator == id) {
            return true;
        }
    }
    return false;  // returns false if order does not inculde such product
}

// a function that changes a product's amount in a given order
MatamikyaResult mtmChangeProductAmountInOrder(Matamikya matamikya, const unsigned int orderId, const unsigned int productId, const double amount) {
    if (matamikya == NULL) {
        return MATAMIKYA_NULL_ARGUMENT;
    }
    Order order = getOrderWithID(matamikya->orders, orderId);
    if (order == NULL) {
        return MATAMIKYA_ORDER_NOT_EXIST;
    }
    Product product = getProductWithID(matamikya->inventory, productId);
    if (product == NULL) {
        return MATAMIKYA_PRODUCT_NOT_EXIST;
    }
    // checks if amount is valid for the product's amountType
    if (isValidAmount(productGetAmountType(product), amount) == false) {
        return MATAMIKYA_INVALID_AMOUNT;
    }
    if (productIdExistInOrder(order, productId) == true) {  // product exists in the current order
        unsigned int* idToChange = malloc(sizeof(*idToChange));
        *idToChange = productId;

        double currentAmount = 0;
        asGetAmount(orderGetItems(order), idToChange, &currentAmount);                                // get the current amount for the product in the order
        if (isValidAmount(productGetAmountType(product), currentAmount + amount) == false) {  // check if the amount after the change is valid
            orderElementDestroy(idToChange);
            return MATAMIKYA_INVALID_AMOUNT;
        }

        if (asChangeAmount(orderGetItems(order), idToChange, amount) == AS_INSUFFICIENT_AMOUNT) {
            asDelete(orderGetItems(order), idToChange);  // if the amount will be negative, remove the product from the order
        }
        orderElementDestroy(idToChange);
    } else {               // product does not exists in the current order
        if (amount > 0) {  // need to add the product to the Order's amount set
            unsigned int* idToInsert = malloc(sizeof(*idToInsert));
            *idToInsert = productId;
            asRegister(orderGetItems(order), idToInsert);              // insert the product to the order
            asChangeAmount(orderGetItems(order), idToInsert, amount);  // update the amount
            orderElementDestroy(idToInsert);                   // asRegister creates an allocated copy of idToInsert, our idToInsert is no longer needed.
        }
    }
    return MATAMIKYA_SUCCESS;
}
//  a function that ships a given order and updates the inventory's stock accordingly
MatamikyaResult mtmShipOrder(Matamikya matamikya, const unsigned int orderId) {
    if (matamikya == NULL) {
        return MATAMIKYA_NULL_ARGUMENT;
    }
    Order order = getOrderWithID(matamikya->orders, orderId);  // checks if such order ID exists
    if (order == NULL) {
        return MATAMIKYA_ORDER_NOT_EXIST;
    }
    AS_FOREACH(unsigned int*, iterator, orderGetItems(order)) {  // iterate on all products in the order, check if the amounts are available in the inventory.
        Product currentProduct = getProductWithID(matamikya->inventory, *iterator);
        double inventoryAmount = 0;
        double wantedAmount = 0;
        asGetAmount(matamikya->inventory, currentProduct, &inventoryAmount);
        asGetAmount(orderGetItems(order), iterator, &wantedAmount);
        if (inventoryAmount < wantedAmount) {  // checks if the inventory can supply the order
            return MATAMIKYA_INSUFFICIENT_AMOUNT;
        }
    }
    // inventory can supply the order
    AS_FOREACH(unsigned int*, iterator, orderGetItems(order)) {  // iterate on all products in the order, deduct the amounts from the inventory
        Product currentProduct = getProductWithID(matamikya->inventory, *iterator);
        double wantedAmount = 0;
        asGetAmount(orderGetItems(order), iterator, &wantedAmount);
        double priceToPay = productGetProdPrice(currentProduct)(productGetCustomData(currentProduct), wantedAmount);
        productSetProfit(currentProduct, productGetProfit(currentProduct) + priceToPay);
        productGetProdPrice(currentProduct)(productGetCustomData(currentProduct), wantedAmount);
        asChangeAmount(matamikya->inventory, currentProduct, (-1) * wantedAmount);  //-1*wantedAmount to deduct.
    }

    setRemove(matamikya->orders, order);

    return MATAMIKYA_SUCCESS;
}
// a function that cancels an order
MatamikyaResult mtmCancelOrder(Matamikya matamikya, const unsigned int orderId) {
    if (matamikya == NULL) {
        return MATAMIKYA_NULL_ARGUMENT;
    }
    Order order = getOrderWithID(matamikya->orders, orderId);  // checks if such order exists
    if (order == NULL) {
        return MATAMIKYA_ORDER_NOT_EXIST;
    }
    setRemove(matamikya->orders, order);  // removes the order
    return MATAMIKYA_SUCCESS;
}
// a function that prints the inventory status
MatamikyaResult mtmPrintInventory(Matamikya matamikya, FILE* output) {
    if (matamikya == NULL || output == NULL) {  // checks if any of the args is NULL
        return MATAMIKYA_NULL_ARGUMENT;
    }
    // prints the headline "Inventory Status:
    fprintf(output, "Inventory Status:\n");
    AS_FOREACH(Product, iterator, matamikya->inventory) {  // iterate on all products in the inventory and print them
        double outAmount;
        asGetAmount(matamikya->inventory, iterator, &outAmount);
        double price = productGetProdPrice(iterator)(productGetCustomData(iterator), 1);
        mtmPrintProductDetails(productGetName(iterator), productGetId(iterator), outAmount, price, output);
    }

    return MATAMIKYA_SUCCESS;
}
// a function to print order's details
MatamikyaResult mtmPrintOrder(Matamikya matamikya, const unsigned int orderId, FILE* output) {
    if (matamikya == NULL || output == NULL) {  // checks if any of the args is NULL
        return MATAMIKYA_NULL_ARGUMENT;
    }
    double sum = 0;  // will sum the costs
    // prints the order's id
    Order order = getOrderWithID(matamikya->orders, orderId);
    if(order == NULL){
        return MATAMIKYA_ORDER_NOT_EXIST;
    }
    mtmPrintOrderHeading(orderId, output);
    AS_FOREACH(unsigned int*, iterator, orderGetItems(order)) {  // iterate on all products in the order and print them
        Product product = getProductWithID(matamikya->inventory, *iterator);
        double amountInOrder;
        asGetAmount(orderGetItems(order), iterator, &amountInOrder);
        double price = productGetProdPrice(product)(productGetCustomData(product), amountInOrder);
        sum += price;  // sum all prices
        mtmPrintProductDetails(productGetName(product), productGetId(product), amountInOrder, price, output);
    }

    mtmPrintOrderSummary(sum, output);

    return MATAMIKYA_SUCCESS;
}

// a function that prints the best selling product's details
MatamikyaResult mtmPrintBestSelling(Matamikya matamikya, FILE* output) {
    if (matamikya == NULL || output == NULL) {  // checks if any of the args is NULL
        return MATAMIKYA_NULL_ARGUMENT;
    }
    char* bestProductName;
    unsigned int bestProductId = 0;
    double bestProductProfit = -1.0;
    // prints the headline "Best Selling Product"
    fprintf(output, "Best Selling Product:\n");
    AS_FOREACH(Product, iterator, matamikya->inventory) {
        double currentProfit = productGetProfit(iterator);
        // need to update bestProduct if the current profit is larger or if its the same but the id is smaller
        if (currentProfit > bestProductProfit || (currentProfit == bestProductProfit && bestProductId > productGetId(iterator))) {
            bestProductProfit = currentProfit;
            bestProductName = productGetName(iterator);
            bestProductId = productGetId(iterator);
        }
    }
    if (bestProductProfit <= 0.0) {  // checks if there were any sales
        fprintf(output, "none\n");
    } else {
        mtmPrintIncomeLine(bestProductName, bestProductId, bestProductProfit, output);
    }
    return MATAMIKYA_SUCCESS;
}