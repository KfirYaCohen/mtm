#ifndef MATAMIKYA_PRODUCT_H_
#define MATAMIKYA_PRODUCT_H_

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "matamikya.h"
#include "amount_set.h"

typedef struct Product_t* Product;

char* productGetName(Product product);
// a function to set a name for a given product
void productSetName(Product product, char* name);

// a function to get given product's id
unsigned int productGetId(Product product);
// a function to set an id for a given product
void productSetId(Product product, unsigned int id);

// a function to get a given product's amount type
MatamikyaAmountType productGetAmountType(Product product);

// a function to set an amount type for a given product
void productSetAmountType(Product product, MatamikyaAmountType amountType);

// a function to get a given product's castum Data
MtmProductData productGetCustomData(Product product);
// a function to set a custom data for a given product
void productSetCustomData(Product product, MtmProductData customData);

// a function to get a given product's profit
double productGetProfit(Product product);
// a function to set a profit for a given product
void productSetProfit(Product product, double profit);
// a function to get a given product's copy data function
MtmCopyData productGetCopyData(Product product);
// a function to set a copy data function for a given product
void productSetCopyData(Product product, MtmCopyData CopyData);

// a function to get a given product's free data function
MtmFreeData productGetFreeData(Product product);
// a function to set a free data function for a given product
void productSetFreeData(Product product, MtmFreeData FreeData);

// a function to get a given product's price function
MtmGetProductPrice productGetProdPrice(Product product);
// a function to set a given product's price function
void productSetProdPrice(Product product, MtmGetProductPrice ProdPrice);

// a function to create a product given its properties, returns a MatamikyaResult according to the demands
MatamikyaResult productCreate(Product *adressToReturn, const unsigned int id, const char* name, const MatamikyaAmountType amountType, const MtmProductData customData, MtmCopyData CopyData, MtmFreeData FreeData, MtmGetProductPrice ProdPrice);

// a function to copy a product type and returns the allocated copy

ASElement productCopy(ASElement product);

// a function to free a product type
void productDestroy(ASElement product);

// a function to compare two product types, returns the difference between their ID's
int productCompare(ASElement product1, ASElement product2);

#endif  // MATAMIKYA_PRODUCT_H_
