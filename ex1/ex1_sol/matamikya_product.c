#include "matamikya_product.h"

struct Product_t {
    char* name;
    unsigned int id;
    MatamikyaAmountType amountType;
    MtmProductData customData;
    double profit;
    // function
    MtmCopyData CopyData;
    MtmFreeData FreeData;
    MtmGetProductPrice ProdPrice;
};

// a function to get given product's name
char* productGetName(Product product) { return product->name; }
// a function to set a name for a given product
void productSetName(Product product, char* name) { product->name = name; }

// a function to get given product's id
unsigned int productGetId(Product product) { return product->id; }
// a function to set an id for a given product
void productSetId(Product product, unsigned int id) { product->id = id; }

// a function to get a given product's amount type
MatamikyaAmountType productGetAmountType(Product product) { return product->amountType; }
// a function to set an amount type for a given product
void productSetAmountType(Product product, MatamikyaAmountType amountType) { product->amountType = amountType; }

// a function to get a given product's castum Data
MtmProductData productGetCustomData(Product product) { return product->customData; }
// a function to set a custom data for a given product
void productSetCustomData(Product product, MtmProductData customData) { product->customData = customData; }

// a function to get a given product's profit
double productGetProfit(Product product) { return product->profit; }
// a function to set a profit for a given product
void productSetProfit(Product product, double profit) { product->profit = profit; }

// a function to get a given product's copy data function
MtmCopyData productGetCopyData(Product product) { return product->CopyData; }
// a function to set a copy data function for a given product
void productSetCopyData(Product product, MtmCopyData CopyData) { product->CopyData = CopyData; }

// a function to get a given product's free data function
MtmFreeData productGetFreeData(Product product) { return product->FreeData; }
// a function to set a free data function for a given product
void productSetFreeData(Product product, MtmFreeData FreeData) { product->FreeData = FreeData; }

// a function to get a given product's price function
MtmGetProductPrice productGetProdPrice(Product product) { return product->ProdPrice; }
// a function to set a given product's price function
void productSetProdPrice(Product product, MtmGetProductPrice ProdPrice) { product->ProdPrice = ProdPrice; }

// a function to create a product given its properties, returns a MatamikyaResult according to the demands
MatamikyaResult productCreate(Product *adressToReturn, const unsigned int id, const char* name, const MatamikyaAmountType amountType, const MtmProductData customData, MtmCopyData CopyData, MtmFreeData FreeData, MtmGetProductPrice ProdPrice) {
    Product newProduct = malloc(sizeof(*newProduct));
    if (newProduct == NULL) {
        return MATAMIKYA_OUT_OF_MEMORY;  // memory error
    }

    char* namecpy = malloc(strlen(name) + 1);
    if (namecpy == NULL) {
        free(newProduct);
        return MATAMIKYA_OUT_OF_MEMORY;  // memory error
    }
    strcpy(namecpy, name);  // copying the name
    newProduct->name = namecpy;
    MtmProductData newProductData = CopyData(customData);
    if (newProductData == NULL) {
        free(newProduct);
        free(namecpy);
        return MATAMIKYA_OUT_OF_MEMORY;  // memory error
    }

    newProduct->id = id;
    newProduct->customData = newProductData;
    newProduct->amountType = amountType;
    newProduct->ProdPrice = ProdPrice;
    newProduct->CopyData = CopyData;
    newProduct->FreeData = FreeData;
    newProduct->profit = 0;

    *adressToReturn = newProduct;

    return MATAMIKYA_SUCCESS;
}

// a function to copy a product type and returns the allocated copy
ASElement productCopy(ASElement element) {
    if (element == NULL) {
        return NULL;  // null argument
    }
    Product product = (Product)element;
    Product newProduct = NULL;
    MatamikyaResult result = productCreate(&newProduct, product->id, product->name, product->amountType, product->customData, product->CopyData, product->FreeData, product->ProdPrice);
    if (result != MATAMIKYA_SUCCESS) {
        return NULL;
    }
    return newProduct;
}

// a function to free a product type
void productDestroy(ASElement product) {
    if (product == NULL) {
        return;  // null argument
    }
    free(((Product)product)->name);
    ((Product)product)->FreeData(((Product)product)->customData);
    free(product);
}

// a function to compare two product types, returns the difference between their ID's
int productCompare(ASElement product1, ASElement product2) {
    if (product1 == NULL || product2 == NULL) {
        return false;
    }
    return ((Product)product1)->id - ((Product)product2)->id;
}
