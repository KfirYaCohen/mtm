//
// Created by Muhammad Biadsy on 29/11/2021.
//

#include "matamikya.h"
#include "tests/test_utilities.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define INVENTORY_OUT_FILE "actual_output/printed_inventory.txt"
#define INVENTORY_TEST_FILE "expected_output/expected_inventory.txt"
#define INVENTORY_OUT_FILE_1 "actual_output/testMtmPrintInventory_1.txt"
#define INVENTORY_TEST_FILE_1 "expected_output/testMtmPrintInventory_1.txt"
#define INVENTORY_OUT_FILE_2 "actual_output/testMtmPrintInventory_2.txt"
#define INVENTORY_TEST_FILE_2 "expected_output/testMtmPrintInventory_2.txt"
#define INVENTORY_OUT_FILE_3 "actual_output/testMtmPrintInventory_3.txt"
#define INVENTORY_TEST_FILE_3 "expected_output/testMtmPrintInventory_3.txt"
#define ORDER_OUT_FILE "actual_output/printed_order.txt"
#define ORDER_TEST_FILE "expected_output/expected_order.txt"
#define ORDER_OUT_FILE_1 "actual_output/testMtmPrintOrder_1.txt"
#define ORDER_TEST_FILE_1 "expected_output/testMtmPrintOrder_1.txt"
#define ORDER_OUT_FILE_2 "actual_output/testMtmPrintOrder_2.txt"
#define ORDER_TEST_FILE_2 "expected_output/testMtmPrintOrder_2.txt"
#define ORDER_OUT_FILE_3 "actual_output/testMtmPrintOrder_3.txt"
#define ORDER_TEST_FILE_3 "expected_output/testMtmPrintOrder_3.txt"
#define ORDER_OUT_FILE_4 "actual_output/testMtmPrintOrder_4.txt"
#define ORDER_TEST_FILE_4 "expected_output/testMtmPrintOrder_4.txt"
#define ORDER_OUT_FILE_5 "actual_output/testMtmPrintOrder_5.txt"
#define ORDER_TEST_FILE_5 "expected_output/testMtmPrintOrder_5.txt"
#define ORDER_OUT_FILE_6 "actual_output/testMtmPrintOrder_6.txt"
#define ORDER_TEST_FILE_6 "expected_output/testMtmPrintOrder_6.txt"
#define BEST_SELLING_OUT_FILE "actual_output/printed_best_selling.txt"
#define BEST_SELLING_TEST_FILE "expected_output/expected_best_selling.txt"
#define BEST_SELLING_OUT_FILE_1 "actual_output/testMtmPrintBestSelling_1.txt"
#define BEST_SELLING_TEST_FILE_1 "expected_output/testMtmPrintBestSelling_1.txt"
#define BEST_SELLING_OUT_FILE_2 "actual_output/testMtmPrintBestSelling_2.txt"
#define BEST_SELLING_TEST_FILE_2 "expected_output/testMtmPrintBestSelling_2.txt"
#define BEST_SELLING_OUT_FILE_3 "actual_output/testMtmPrintBestSelling_3.txt"
#define BEST_SELLING_TEST_FILE_3 "expected_output/testMtmPrintBestSelling_3.txt"
#define BEST_SELLING_OUT_FILE_4 "actual_output/testMtmPrintBestSelling_4.txt"
#define BEST_SELLING_TEST_FILE_4 "expected_output/testMtmPrintBestSelling_4.txt"
#define BEST_SELLING_OUT_FILE_5 "actual_output/testMtmPrintBestSelling_5.txt"
#define BEST_SELLING_TEST_FILE_5 "expected_output/testMtmPrintBestSelling_5.txt"
#define BEST_SELLING_OUT_FILE_6 "actual_output/testMtmPrintBestSelling_6.txt"
#define BEST_SELLING_TEST_FILE_6 "expected_output/testMtmPrintBestSelling_6.txt"
#define NO_SELLING_OUT_FILE "actual_output/printed_no_selling.txt"
#define NO_SELLING_TEST_FILE "expected_output/expected_no_selling.txt"
#define NO_SELLING_OUT_FILE_1 "actual_output/printed_no_selling_1.txt"
#define NO_SELLING_TEST_FILE_1 "expected_output/expected_no_selling_1.txt"
#define REMOVE_NULL_FILE "rm actual_output/testMtmPrint_null.txt"
#define CREATE_NULL_FILE "actual_output/testMtmPrint_null.txt"


#define ASSERT_OR_DESTROY(expr) ASSERT_TEST_WITH_FREE((expr), matamikyaDestroy(mtm))


static long NumTestsPassed = 0;

static void red () {
    printf("\033[1;31m");
    fflush(stdout);
}

static void green() {
    printf("\033[0;32m");
    fflush(stdout);
}

static void blue() {
    printf("\033[0;94m");
}

static void yellow () {
    printf("\033[0;33m");
    fflush(stdout);
}

static void reset () {
    printf("\033[0m");
    fflush(stdout);
}

static void printIfSuccess(long num_tests)
{
    if (0 == NumTestsPassed)
    {
        red();
    }
    if (num_tests == NumTestsPassed)
    {
        green();
    }
    else
    {
        yellow();
    }

    printf("####  Summary: Passed %ld out of %ld ####\n" ,NumTestsPassed, num_tests);
    reset();
}


#define RUN_COLORFULL_TEST(test, name, id)                  \
do {                                 \
blue();      printf("Running test# %ld %s ... ", id + 1, name);  reset(); \
fflush(stdout); \
if (test()) {                    \
green();\
printf("[OK]\n");            \
reset();\
++NumTestsPassed;   \
} else {    \
red();\
printf("[Failed]\n");        \
reset();\
}                                \
} while (0)

/*************************************************************************/


/*return true if same*/

static bool fileEqual(FILE *file1, FILE *file2) {
    int c1, c2;
    do {
        c1 = fgetc(file1);
        c2 = fgetc(file2);
    } while (c1 != EOF && c2 != EOF && c1 == c2);
    return (c1 == EOF && c2 == EOF);
}

static bool wholeFileEqual(const char *filename1, const char *filename2) {
    FILE *file1 = fopen(filename1, "r");
    FILE *file2 = fopen(filename2, "r");
    assert(file1);
    assert(file2);
    bool result = fileEqual(file1, file2);
    fclose(file1);
    fclose(file2);
    return result;
}

/*************************************************************************/

bool testCreateSegel() {
    Matamikya mtm = matamikyaCreate();
    ASSERT_TEST(mtm != NULL);
    matamikyaDestroy(mtm);
    return true;
}

bool testDestroySegel() {
    Matamikya mtm = matamikyaCreate();
    matamikyaDestroy(mtm);
    /* try to elicit undefined behavior in case matamikyaDestroy has bugs */
    Matamikya mtm2 = matamikyaCreate();
    ASSERT_TEST(mtm2 != NULL);
    matamikyaDestroy(mtm2);
    return true;
}

static MtmProductData copyDouble(MtmProductData number) {
    double *copy = malloc(sizeof(*copy));
    if (copy) {
        *copy = *(double*)number;
    }
    return copy;
}

static void freeDouble(MtmProductData number) {
    free(number);
}

static double simplePrice(MtmProductData basePrice, const double amount) {
    return (*(double*)basePrice) * amount;
}

static double buy10Get10ForFree(MtmProductData basePrice, const double amount) {
    double realAmount = amount;
    if (amount >= 20) {
        realAmount -= 10;
    } else if (amount >= 10) {
        realAmount = 10;
    }
    return simplePrice(basePrice, realAmount);
}

bool testModifyProductsSegel() {
    Matamikya mtm = matamikyaCreate();
    double basePrice = 8.9;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
                      mtmNewProduct(mtm, 4, "Tomato", 2019.11, MATAMIKYA_ANY_AMOUNT,
                                    &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 5.8;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
                      mtmNewProduct(mtm, 6, "Onion", 1789.75, MATAMIKYA_ANY_AMOUNT,
                                    &basePrice, copyDouble, freeDouble, buy10Get10ForFree));
    basePrice = 2000;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
                      mtmNewProduct(mtm, 10, "Television", 15, MATAMIKYA_INTEGER_AMOUNT,
                                    &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 5000;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
                      mtmNewProduct(mtm, 11, "Television", 4, MATAMIKYA_INTEGER_AMOUNT,
                                    &basePrice, copyDouble, freeDouble, simplePrice));

    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmClearProduct(mtm, 6));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm, 4, 30.5));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm, 4, -12.85));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmount(mtm, 10, 2.25));
    ASSERT_OR_DESTROY(MATAMIKYA_INSUFFICIENT_AMOUNT == mtmChangeProductAmount(mtm, 10, -1000));

    basePrice = 18.5;
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
                      mtmNewProduct(mtm, 7, "Watermelon", 24.54,
                                    MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice, copyDouble,
                                    freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
                      mtmNewProduct(mtm, 7, "Watermelon", 24.5,
                                    MATAMIKYA_HALF_INTEGER_AMOUNT,
                                    &basePrice, copyDouble,
                                    freeDouble, simplePrice));

    matamikyaDestroy(mtm);
    return true;
}

static void makeInventory(Matamikya mtm) {
    double basePrice = 8.9;
    mtmNewProduct(mtm, 4, "Tomato", 2019.11, MATAMIKYA_ANY_AMOUNT, &basePrice, copyDouble,
                  freeDouble, simplePrice);
    basePrice = 5.8;
    mtmNewProduct(mtm, 6, "Onion", 1789.75, MATAMIKYA_ANY_AMOUNT, &basePrice, copyDouble,
                  freeDouble, buy10Get10ForFree);
    basePrice = 2000;
    mtmNewProduct(mtm, 10, "Television", 15, MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice);
    basePrice = 5000;
    mtmNewProduct(mtm, 11, "Smart TV", 4, MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice);
    basePrice = 18.5;
    mtmNewProduct(mtm, 7, "Watermelon", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice);
}

bool testModifyOrdersSegel() {
    Matamikya mtm = matamikyaCreate();
    makeInventory(mtm);

    unsigned int order1 = mtmCreateNewOrder(mtm);
    ASSERT_OR_DESTROY(order1 > 0);
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
                      mtmChangeProductAmountInOrder(mtm, order1, 11, 1.0));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST ==
                      mtmChangeProductAmountInOrder(mtm, order1, 15, 1.0));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
                      mtmChangeProductAmountInOrder(mtm, order1, 11, 1.2));

    unsigned int order2 = mtmCreateNewOrder(mtm);
    ASSERT_OR_DESTROY(order2 > 0);
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
                      mtmChangeProductAmountInOrder(mtm, order2, 6, 10.25));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
                      mtmChangeProductAmountInOrder(mtm, order2, 7, 1.5));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmCancelOrder(mtm, order1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
                      mtmChangeProductAmountInOrder(mtm, order2, 10, 2.0));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmShipOrder(mtm, order2));

    matamikyaDestroy(mtm);
    return true;
}

bool testPrintInventorySegel() {
    Matamikya mtm = matamikyaCreate();
    makeInventory(mtm);
    FILE *outputFile = fopen(INVENTORY_OUT_FILE, "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(mtmPrintInventory(mtm, outputFile) == MATAMIKYA_SUCCESS);
    fclose(outputFile);
    ASSERT_OR_DESTROY(wholeFileEqual(INVENTORY_TEST_FILE, INVENTORY_OUT_FILE));
    matamikyaDestroy(mtm);
    return true;
}

static unsigned int makeOrder(Matamikya mtm) {
    makeInventory(mtm);
    unsigned int id = mtmCreateNewOrder(mtm);
    mtmChangeProductAmountInOrder(mtm, id, 6, 10.25);
    mtmChangeProductAmountInOrder(mtm, id, 10, 2);
    mtmChangeProductAmountInOrder(mtm, id, 7, 1.5);
    return id;
}

bool testPrintOrderSegel() {
    Matamikya mtm = matamikyaCreate();
    unsigned int orderId = makeOrder(mtm);
    FILE *outputFile = fopen(ORDER_OUT_FILE, "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(mtmPrintOrder(mtm, orderId, outputFile) == MATAMIKYA_SUCCESS);
    fclose(outputFile);
    FILE *expected = fopen(ORDER_TEST_FILE, "r");
    FILE *printed = fopen(ORDER_OUT_FILE, "r");
    assert(expected);
    assert(printed);

    /* test that prefix and printed orderId is correct */
    const char *expectedPrefix = "Order ";
    int size = strlen(expectedPrefix);
    for (int i = 0; i < size; ++i) {
        ASSERT_OR_DESTROY(fgetc(printed) == expectedPrefix[i]);
    }
    unsigned int printedId;
    fscanf(printed, "%u", &printedId);
    ASSERT_OR_DESTROY(orderId == printedId);

    /* skip the rest of the header line */
    while (fgetc(printed) != '\n');
    while (fgetc(expected) != '\n');

    ASSERT_OR_DESTROY(fileEqual(expected, printed));
    fclose(expected);
    fclose(printed);
    matamikyaDestroy(mtm);
    return true;
}

bool testPrintBestSellingSegel() {
    Matamikya mtm = matamikyaCreate();
    makeInventory(mtm);

    FILE *outputFile = fopen(NO_SELLING_OUT_FILE, "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(mtmPrintBestSelling(mtm, outputFile) == MATAMIKYA_SUCCESS);
    fclose(outputFile);
    ASSERT_OR_DESTROY(wholeFileEqual(NO_SELLING_TEST_FILE, NO_SELLING_OUT_FILE));

    unsigned int order = mtmCreateNewOrder(mtm);
    mtmChangeProductAmountInOrder(mtm, order, 10, 3.0);
    mtmShipOrder(mtm, order);

    order = mtmCreateNewOrder(mtm);
    mtmChangeProductAmountInOrder(mtm, order, 6, 10.25);
    mtmChangeProductAmountInOrder(mtm, order, 7, 1.5);
    mtmChangeProductAmountInOrder(mtm, order, 11, 1.0);
    mtmShipOrder(mtm, order);

    outputFile = fopen(BEST_SELLING_OUT_FILE, "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(mtmPrintBestSelling(mtm, outputFile) == MATAMIKYA_SUCCESS);
    fclose(outputFile);
    ASSERT_OR_DESTROY(wholeFileEqual(BEST_SELLING_TEST_FILE, BEST_SELLING_OUT_FILE));

    matamikyaDestroy(mtm);
    return true;
}

bool testMtmNewProduct() {
    Matamikya mtm = matamikyaCreate();
    double basePrice = 8.9;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 4, "Tomato", 2019.11, MATAMIKYA_ANY_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 5.8;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 6, "Onion", 1789.75, MATAMIKYA_ANY_AMOUNT,
                  &basePrice, copyDouble, freeDouble, buy10Get10ForFree));
    basePrice = 2000;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 10, "Television", 15, MATAMIKYA_INTEGER_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 5000;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 11, "Television", 4, MATAMIKYA_INTEGER_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 18.5;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 7, "Watermelon", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));


    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT ==
    mtmNewProduct(NULL, 7, "Watermelon", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT ==
    mtmNewProduct(mtm, 7, NULL, 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT ==
    mtmNewProduct(mtm, 7, "Watermelon", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, NULL,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT ==
    mtmNewProduct(mtm, 7, "Watermelon", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  NULL, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT ==
    mtmNewProduct(mtm, 7, "Watermelon", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, NULL, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT ==
    mtmNewProduct(mtm, 7, "Watermelon", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, NULL));


    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, "", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, "%", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, "@", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, "/", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, "-", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, "&", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, "#", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, "!", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, "$", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, "^", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, "*", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, "(", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, ")", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, "}", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, "{", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, "~", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, "'", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, "?", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, "<", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, ">", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, ".", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, ",", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, "`", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, "[", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, "]", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_NAME ==
    mtmNewProduct(mtm, 7, "|", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));


    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
    mtmNewProduct(mtm, 7, "Iphone", -10, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
    mtmNewProduct(mtm, 7, "Iphone", -10.001, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
    mtmNewProduct(mtm, 7, "Iphone", 1.503, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
    mtmNewProduct(mtm, 7, "Iphone", 1.498, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
    mtmNewProduct(mtm, 7, "iphone", 1.002, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
    mtmNewProduct(mtm, 7, "iphone", 2.99899, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
    mtmNewProduct(mtm, 7, "iphone", 1.503, MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
    mtmNewProduct(mtm, 7, "iphone", 1.0011, MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
    mtmNewProduct(mtm, 7, "iphone", 0.0011, MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
    mtmNewProduct(mtm, 7, "iphone", 0.99899, MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
    mtmNewProduct(mtm, 7, "iphone", -5, MATAMIKYA_ANY_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
    mtmNewProduct(mtm, 7, "iphone", 1.6, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
    mtmNewProduct(mtm, 7, "iphone", 2.7, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
    mtmNewProduct(mtm, 7, "iphone", 1.2, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
    mtmNewProduct(mtm, 7, "iphone", 1.4, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
    mtmNewProduct(mtm, 7, "iphone", 1.2, MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
    mtmNewProduct(mtm, 7, "iphone", 1.8, MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
    mtmNewProduct(mtm, 7, "iphone", 1.9, MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
    mtmNewProduct(mtm, 7, "iphone", 2.2, MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
    mtmNewProduct(mtm, 7, "iphone", 2.1, MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
    mtmNewProduct(mtm, 7, "iphone", 1.03, MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
    mtmNewProduct(mtm, 7, "iphone", 1.04, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
    mtmNewProduct(mtm, 7, "iphone", 0.9, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
    mtmNewProduct(mtm, 7, "iphone", 1.05, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));


    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_ALREADY_EXIST ==
    mtmNewProduct(mtm, 7, "iphone", 1.501, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_ALREADY_EXIST ==
    mtmNewProduct(mtm, 6, "iphone", 1.501, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_ALREADY_EXIST ==
    mtmNewProduct(mtm, 4, "iphone", 1.501, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_ALREADY_EXIST ==
    mtmNewProduct(mtm, 10, "iphone", 1.501, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_ALREADY_EXIST ==
    mtmNewProduct(mtm, 11, "iphone", 1.501, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));

    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 90, "iphone", 1.501, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_ALREADY_EXIST ==
    mtmNewProduct(mtm, 90, "iphone", 1.501, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));

    matamikyaDestroy(mtm);
    return true;
}

bool testMtmChangeProductAmount() {
    Matamikya mtm = matamikyaCreate();
    double basePrice = 8.9;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 4, "Tomato", 2019.11, MATAMIKYA_ANY_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 5.8;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 6, "Onion", 1789.75, MATAMIKYA_ANY_AMOUNT,
                  &basePrice, copyDouble, freeDouble, buy10Get10ForFree));
    basePrice = 2000;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 10, "Television", 15, MATAMIKYA_INTEGER_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 5000;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 11, "Television", 4, MATAMIKYA_INTEGER_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 18.5;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 7, "Watermelon", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 90, "Iphone", 1.501, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 1000, "Melki", 1.499, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 111, "Kinder", 1.500, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 114, "Blue", 1.000, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 115, "Red Bull", 1.001, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 116, "Monster", 0.9999, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 121, "Magnum White",12 , MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 122, "Magnum Black",12.000 , MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 123, "Magnum classic",11.9999 , MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));


    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT == mtmChangeProductAmount(NULL, 4, -12.85));


    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmChangeProductAmount(mtm, -1, -12.85));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmChangeProductAmount(mtm,2000, -12.85));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmChangeProductAmount(mtm,900, -12.85));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmChangeProductAmount(mtm,129, -12.85));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmChangeProductAmount(mtm,60000, -12.85));


    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmount(mtm, 10,0.998));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmount(mtm, 10,0.0011));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmount(mtm, 10,1.00101));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmount(mtm, 90,0.998));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmount(mtm, 90,0.0011));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmount(mtm, 90,2.00101));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmount(mtm, 90,1.4989));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmount(mtm, 90,0.5011));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmount(mtm, 90,2.50101));

    /*checks segel update*/
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmount(mtm,115, 1.001));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmount(mtm,1000, 1.499));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmount(mtm,90, 1.501));

    ASSERT_OR_DESTROY(MATAMIKYA_INSUFFICIENT_AMOUNT == mtmChangeProductAmount(mtm,121, -13));
    ASSERT_OR_DESTROY(MATAMIKYA_INSUFFICIENT_AMOUNT == mtmChangeProductAmount(mtm,122, -13));
    ASSERT_OR_DESTROY(MATAMIKYA_INSUFFICIENT_AMOUNT == mtmChangeProductAmount(mtm,123, -23));
    ASSERT_OR_DESTROY(MATAMIKYA_INSUFFICIENT_AMOUNT == mtmChangeProductAmount(mtm,121, -113.0001));
    ASSERT_OR_DESTROY(MATAMIKYA_INSUFFICIENT_AMOUNT == mtmChangeProductAmount(mtm,116, -1.5));
    ASSERT_OR_DESTROY(MATAMIKYA_INSUFFICIENT_AMOUNT == mtmChangeProductAmount(mtm,115, -2.00));
    ASSERT_OR_DESTROY(MATAMIKYA_INSUFFICIENT_AMOUNT == mtmChangeProductAmount(mtm,115, -3.00));
    ASSERT_OR_DESTROY(MATAMIKYA_INSUFFICIENT_AMOUNT == mtmChangeProductAmount(mtm,114, -3.999));

    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,4, -12));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,4, 12));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,6, -111.09888));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,7,-1.5));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,7, 1.5));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,7, -1.0002));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,7, -1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,7, -0.9999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,7, -0.0001));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,1000, -1.499));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,1000, 15));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,115, 1112));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,115, -12.5));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,115, -12.501));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,115, -12.499));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,115, 12.5));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,115, 14.500));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,115, 113.4999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,116, 120.5));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,116, 0.001));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,116, 0.9999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,116, 0));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,116, 3));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,4, 0));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,122, 5000));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,122, -112.000));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,122, -113.9999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,122, -122));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,122, 1222.000));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,122, 13.999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,123, 122));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,123, 0));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,121, 0));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm,6, 0));


    matamikyaDestroy(mtm);
    return true;
}

bool testMtmClearProduct() {
    Matamikya mtm = matamikyaCreate();
    double basePrice = 8.9;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 4, "Tomato", 2019.11, MATAMIKYA_ANY_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 5.8;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 6, "Onion", 1789.75, MATAMIKYA_ANY_AMOUNT,
                  &basePrice, copyDouble, freeDouble, buy10Get10ForFree));
    basePrice = 2000;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 10, "Television", 15, MATAMIKYA_INTEGER_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 5000;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 11, "Television", 4, MATAMIKYA_INTEGER_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 18.5;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 7, "Watermelon", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 90, "Iphone", 1.501, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 1000, "Melki", 1.499, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 111, "Kinder", 1.500, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 114, "Blue", 1.000, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 115, "Red Bull", 1.001, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 116, "Monster", 0.9999, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 121, "Magnum White",12 , MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 122, "Magnum Black",12.001 , MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 123, "Magnum classic",11.999 , MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));


    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT == mtmClearProduct(NULL, 4));


    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmClearProduct(mtm, 5000));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmClearProduct(mtm, 127));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmClearProduct(mtm, 0));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmClearProduct(mtm, 10001));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmClearProduct(mtm, 119));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmClearProduct(mtm, 1));


    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmClearProduct(mtm, 4));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmClearProduct(mtm, 4));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmClearProduct(mtm, 6));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmClearProduct(mtm, 6));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmClearProduct(mtm, 7));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmClearProduct(mtm, 7));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmClearProduct(mtm, 10));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmClearProduct(mtm, 10));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmClearProduct(mtm, 11));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmClearProduct(mtm, 11));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmClearProduct(mtm, 90));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmClearProduct(mtm, 90));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmClearProduct(mtm, 1000));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmClearProduct(mtm, 1000));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmClearProduct(mtm, 111));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmClearProduct(mtm, 111));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmClearProduct(mtm, 114));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmClearProduct(mtm, 114));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmClearProduct(mtm, 115));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmClearProduct(mtm, 115));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmClearProduct(mtm, 116));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmClearProduct(mtm, 116));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmClearProduct(mtm, 121));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmClearProduct(mtm, 121));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmClearProduct(mtm, 122));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmClearProduct(mtm, 122));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmClearProduct(mtm, 123));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmClearProduct(mtm, 123));


    matamikyaDestroy(mtm);
    return true;
}

bool testMtmCreateNewOrder() {
    Matamikya mtm = matamikyaCreate();
    
    for (int i = 1; i < 20; i++){
        ASSERT_OR_DESTROY(0 < mtmCreateNewOrder(mtm));
    }


    ASSERT_OR_DESTROY(0 == mtmCreateNewOrder(NULL));


    matamikyaDestroy(mtm);
    return true;
}

bool testMtmChangeProductAmountInOrder() {
    Matamikya mtm = matamikyaCreate();

    
    double basePrice = 8.9;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 4, "Tomato", 2019.11, MATAMIKYA_ANY_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 111, "Kinder", 100.500, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 114, "Blue", 221.000, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 115, "Red Bull", 15.501, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 116, "Monster", 900.999, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 121, "Magnum White",128 , MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 122, "Magnum Black",1244.001 , MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 123, "Magnum classic",11.999, MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));


    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmChangeProductAmountInOrder(mtm, 0,4,4));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmChangeProductAmountInOrder(mtm, 4,4,4));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmChangeProductAmountInOrder(mtm, 5,4,4));


    unsigned int order_1, order_2, order_3;
    order_1 = mtmCreateNewOrder(mtm);
    order_2 = mtmCreateNewOrder(mtm);
    order_3 = mtmCreateNewOrder(mtm);


    ASSERT_OR_DESTROY(0 < order_1);
    ASSERT_OR_DESTROY(0 < order_2);
    ASSERT_OR_DESTROY(0 < order_3);


    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT == mtmChangeProductAmountInOrder(NULL, 1,4,4));
    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT == mtmChangeProductAmountInOrder(NULL, 2,7,5));
    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT == mtmChangeProductAmountInOrder(NULL, 3,6,9));


    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmChangeProductAmountInOrder(mtm, 0,4,4));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmChangeProductAmountInOrder(mtm, -4,4,4));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmChangeProductAmountInOrder(mtm, -5,4,4));


    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmChangeProductAmountInOrder(mtm, order_1,5,4));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmChangeProductAmountInOrder(mtm, order_2,5,4));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmChangeProductAmountInOrder(mtm, order_3,5,4));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmChangeProductAmountInOrder(mtm, order_1,50000,4));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmChangeProductAmountInOrder(mtm, order_2,900,4));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmChangeProductAmountInOrder(mtm, order_3,71,4));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmChangeProductAmountInOrder(mtm, order_1,22,4));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmChangeProductAmountInOrder(mtm, order_2,30,4));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST == mtmChangeProductAmountInOrder(mtm, order_3,0,4));


    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmountInOrder(mtm, order_1,111,1.502));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmountInOrder(mtm, order_2,111,1.4989));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmountInOrder(mtm, order_3,111,1.9989));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmountInOrder(mtm, order_1,111,1.0011));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmountInOrder(mtm, order_2,111,-0.4989));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmountInOrder(mtm, order_3,111,-0.9989));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmountInOrder(mtm, order_1,114,-0.502));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmountInOrder(mtm, order_2,114,-0.0011));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmountInOrder(mtm, order_3,114,1.9989));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmountInOrder(mtm, order_1,123,1.0011));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmountInOrder(mtm, order_2,122,1.9989));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmountInOrder(mtm, order_3,121,0.9989));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmountInOrder(mtm, order_1,123,0.502));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmountInOrder(mtm, order_2,122,0.4989));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmountInOrder(mtm, order_3,121,0.0011));

    /*checks segel update*/
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmount(mtm,115, 1.001));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmount(mtm,123, 1.999));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmount(mtm,116, 1.499));


    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,4,-200));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,4,0.502));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,4,0.4989));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,4,0.0011));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,4,1011.5992));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,4,50.4789));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,4,70.0011));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,4,0));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,111,1.5009));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,111,0.4999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,111,0.500));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,111,-0.5009));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,111,-0.4999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,111,-0.500));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,111,0.001));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,111,0.9999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,111,0));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,111,-0.001));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,111,-0.9999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,111,-1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,111,0.5001));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,111,0.4999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,111,0.000999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,111,1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,111,4));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,111,-7));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,111,0));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,114,0.5009));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,114,0.4999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,114,0.500));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,114,-0.5009));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,114,-0.4999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,114,-0.500));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,114,0.001));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,114,0.9999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,114,0));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,114,-0.001));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,114,-0.9999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,114,-1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,114,0.5001));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,114,0.4999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,114,0.000999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,114,1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,114,4));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,114,-15));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,114,0));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,123,0.001));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,123,0.9999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,123,0));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,123,-0.001));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,123,-2.9999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,123,-1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,123,0.000999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,123,1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,123,4));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,123,-27));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,123,0));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,121,0.001));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,121,0.9999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,121,0));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,121,-0.001));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,121,-2.9999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,121,-1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,121,0.000999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,121,1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,121,4));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,121,-2));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,121,0));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,121,0));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,121,0));


    matamikyaDestroy(mtm);
    return true;
}

bool testMtmShipOrder() {
    Matamikya mtm = matamikyaCreate();


    double basePrice = 8.9;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 4, "Tomato", 2019.11, MATAMIKYA_ANY_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 5.8;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 6, "Onion", 1789.75, MATAMIKYA_ANY_AMOUNT,
                  &basePrice, copyDouble, freeDouble, buy10Get10ForFree));
    basePrice = 2000;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 10, "Television", 15, MATAMIKYA_INTEGER_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 5000;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 11, "Television", 20, MATAMIKYA_INTEGER_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 18.5;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 90, "Iphone", 3.501, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));


    unsigned int order_1, order_2, order_3, order_4;
    order_1 = mtmCreateNewOrder(mtm);
    order_2 = mtmCreateNewOrder(mtm);
    order_3 = mtmCreateNewOrder(mtm);
    order_4 = mtmCreateNewOrder(mtm);


    ASSERT_OR_DESTROY(0 < order_1);
    ASSERT_OR_DESTROY(0 < order_2);
    ASSERT_OR_DESTROY(0 < order_3);
    ASSERT_OR_DESTROY(0 < order_4);


    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT == mtmShipOrder(NULL, order_1));
    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT == mtmShipOrder(NULL, order_2));
    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT == mtmShipOrder(NULL, order_3));
    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT == mtmShipOrder(NULL, order_4));


    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmShipOrder(mtm, 0));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmShipOrder(mtm, -5));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmShipOrder(mtm, -6));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmShipOrder(mtm, -7));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmShipOrder(mtm, -1000));


    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,4,0.502));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,6,0.4989));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,10,0.001));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,11,1011));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,90,0.5009));

    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,4,6));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,6,2));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,10,0.9999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,11,1.0009));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,90,0.001));

    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,4,50));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,6,700.1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,10,3.001));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,11,14.9991));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,90,0.9991));

    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,4,0.502));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,6,0.4989));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,10,4.0001));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,11,10.00001));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,90,1));

    ASSERT_OR_DESTROY(MATAMIKYA_INSUFFICIENT_AMOUNT == mtmShipOrder(mtm, order_1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmShipOrder(mtm, order_2));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmShipOrder(mtm, order_3));
    ASSERT_OR_DESTROY(MATAMIKYA_INSUFFICIENT_AMOUNT == mtmShipOrder(mtm, order_4));


    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmCancelOrder(mtm, order_1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmCancelOrder(mtm, order_4));


    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmShipOrder(mtm, order_1));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmShipOrder(mtm, order_2));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmShipOrder(mtm, order_3));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmShipOrder(mtm, order_4));


    order_1 = mtmCreateNewOrder(mtm);
    order_2 = mtmCreateNewOrder(mtm);
    order_3 = mtmCreateNewOrder(mtm);
    order_4 = mtmCreateNewOrder(mtm);


    ASSERT_OR_DESTROY(0 < order_1);
    ASSERT_OR_DESTROY(0 < order_2);
    ASSERT_OR_DESTROY(0 < order_3);
    ASSERT_OR_DESTROY(0 < order_4);


    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,4,0.502));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,6,0.4989));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,10,0.001));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,11,0));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,90,0.5009));

    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,4,6));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,6,2));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,10,0.9999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,11,5.0009));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,90,0.001));

    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,4,50));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,6,700.1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,10,3.001));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,11,1.9991));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,90,0.9991));

    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,4,0.502));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,6,0.4989));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,10,4.0001));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,11,0.00001));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,90,1));

    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmShipOrder(mtm, order_3));

    ASSERT_OR_DESTROY(0 < mtmCreateNewOrder(mtm));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmShipOrder(mtm, order_3));

    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmShipOrder(mtm, order_4));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmShipOrder(mtm, order_4));
    ASSERT_OR_DESTROY(MATAMIKYA_INSUFFICIENT_AMOUNT == mtmShipOrder(mtm, order_2));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmShipOrder(mtm, order_1));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmShipOrder(mtm, order_1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmCancelOrder(mtm, order_2));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmShipOrder(mtm, order_2));


    matamikyaDestroy(mtm);
    return true;
}


bool testMtmCancelOrder() {
    Matamikya mtm = matamikyaCreate();


    double basePrice = 20;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 4, "Tomato", 2019.11, MATAMIKYA_ANY_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 10;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 6, "Onion", 1789.75, MATAMIKYA_ANY_AMOUNT,
                  &basePrice, copyDouble, freeDouble, buy10Get10ForFree));
    basePrice = 2;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 10, "Television", 15, MATAMIKYA_INTEGER_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 5;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 11, "Television", 16, MATAMIKYA_INTEGER_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 18;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 90, "Iphone", 3.501, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));


    unsigned int order_1, order_2, order_3, order_4;
    order_1 = mtmCreateNewOrder(mtm);
    order_2 = mtmCreateNewOrder(mtm);
    order_3 = mtmCreateNewOrder(mtm);
    order_4 = mtmCreateNewOrder(mtm);


    ASSERT_OR_DESTROY(0 < order_1);
    ASSERT_OR_DESTROY(0 < order_2);
    ASSERT_OR_DESTROY(0 < order_3);
    ASSERT_OR_DESTROY(0 < order_4);


    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT == mtmCancelOrder(NULL, order_1));
    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT == mtmCancelOrder(NULL, order_2));
    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT == mtmCancelOrder(NULL, order_3));
    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT == mtmCancelOrder(NULL, order_4));


    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmCancelOrder(mtm, 0));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmCancelOrder(mtm, -20));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmCancelOrder(mtm, -500));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmCancelOrder(mtm, -777));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmCancelOrder(mtm, -10001));


    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmCancelOrder(mtm, order_1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmCancelOrder(mtm, order_2));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmCancelOrder(mtm, order_3));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmCancelOrder(mtm, order_4));


    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmCancelOrder(mtm, order_1));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmCancelOrder(mtm, order_2));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmCancelOrder(mtm, order_3));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmCancelOrder(mtm, order_4));


    order_1 = mtmCreateNewOrder(mtm);
    order_2 = mtmCreateNewOrder(mtm);
    order_3 = mtmCreateNewOrder(mtm);
    order_4 = mtmCreateNewOrder(mtm);


    ASSERT_OR_DESTROY(0 < order_1);
    ASSERT_OR_DESTROY(0 < order_2);
    ASSERT_OR_DESTROY(0 < order_3);
    ASSERT_OR_DESTROY(0 < order_4);

    
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,4,0.502));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,6,0.499));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,10,-1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,11,1011));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,90,0.500));

    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,4,0.501));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,6,1.002));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,10,1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,11,1.000));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,90,0));

    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,4,50));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,6,700.1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,10,3.000));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,11,14.000));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,90,0.9991));

    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,4,0.502));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,6,0.4989));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,10,4.000));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,11,1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,90,1));


    FILE *outputFile = fopen(ORDER_OUT_FILE_5, "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(mtmPrintOrder(mtm,order_1, outputFile) == MATAMIKYA_SUCCESS);
    fclose(outputFile);
    FILE *expected = fopen(ORDER_TEST_FILE_5, "r");
    FILE *printed = fopen(ORDER_OUT_FILE_5, "r");
    assert(expected);
    assert(printed);

    /* test that prefix and printed orderId is correct */
    const char *expectedPrefix = "Order ";
    int size = strlen(expectedPrefix);
    for (int i = 0; i < size; ++i) {
        ASSERT_OR_DESTROY(fgetc(printed) == expectedPrefix[i]);
    }
    unsigned int printedId;
    fscanf(printed, "%u", &printedId);
    ASSERT_OR_DESTROY(order_1 == printedId);

    /* skip the rest of the header line */
    while (fgetc(printed) != '\n');
    while (fgetc(expected) != '\n');

    ASSERT_OR_DESTROY(fileEqual(expected, printed));
    fclose(expected);
    fclose(printed);


    ASSERT_OR_DESTROY(MATAMIKYA_INSUFFICIENT_AMOUNT == mtmShipOrder(mtm, order_1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmShipOrder(mtm, order_2));



    outputFile = fopen(BEST_SELLING_OUT_FILE_5, "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(mtmPrintBestSelling(mtm,outputFile) == MATAMIKYA_SUCCESS);
    fclose(outputFile);
    ASSERT_OR_DESTROY(wholeFileEqual(BEST_SELLING_TEST_FILE_5, BEST_SELLING_OUT_FILE_5));


    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmShipOrder(mtm, order_3));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmShipOrder(mtm, order_4));


    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmCancelOrder(mtm, order_1));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmCancelOrder(mtm, order_2));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmCancelOrder(mtm, order_3));
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmCancelOrder(mtm, order_4));


    matamikyaDestroy(mtm);
    return true;
}

bool testMtmPrintInventory() {
    Matamikya mtm = matamikyaCreate();

    FILE *outputFile = fopen(CREATE_NULL_FILE, "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT == mtmPrintInventory(NULL,outputFile));
    fclose(outputFile);
    system(REMOVE_NULL_FILE);
    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT == mtmPrintInventory(mtm,NULL));


    double basePrice = 8.9;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 4, "Tomato", 2019.11, MATAMIKYA_ANY_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 5.8;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 6, "Onion", 1789.75, MATAMIKYA_ANY_AMOUNT,
                  &basePrice, copyDouble, freeDouble, buy10Get10ForFree));
    basePrice = 2000;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 10, "Television", 15, MATAMIKYA_INTEGER_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 5000;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 11, "Television", 4, MATAMIKYA_INTEGER_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 18.5;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 7, "Watermelon", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    basePrice = 5200.7;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 90, "Iphone", 1.501, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 1000, "Melki", 1.499, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    basePrice = 520.7;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 111, "Kinder", 1.500, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));


    outputFile = fopen(INVENTORY_OUT_FILE_1, "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(mtmPrintInventory(mtm, outputFile) == MATAMIKYA_SUCCESS);
    fclose(outputFile);
    ASSERT_OR_DESTROY(wholeFileEqual(INVENTORY_TEST_FILE_1, INVENTORY_OUT_FILE_1));


    basePrice = 96.8;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 114, "Blue", 1.000, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    basePrice = 700.000;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 115, "Red Bull", 1.001, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    basePrice = 123;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 116, "Monster", 1.999, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    basePrice = 566666.901;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 121, "Magnum White",12 , MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    basePrice = 4444.444;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 122, "Magnum Black",12.001 , MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    basePrice = 123;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 123, "Magnum classic",11.999 , MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));


    outputFile = fopen(INVENTORY_OUT_FILE_2, "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(mtmPrintInventory(mtm, outputFile) == MATAMIKYA_SUCCESS);
    fclose(outputFile);
    ASSERT_OR_DESTROY(wholeFileEqual(INVENTORY_TEST_FILE_2, INVENTORY_OUT_FILE_2));


    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmClearProduct(mtm, 11));


    outputFile = fopen(INVENTORY_OUT_FILE_3, "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(mtmPrintInventory(mtm, outputFile) == MATAMIKYA_SUCCESS);
    fclose(outputFile);
    ASSERT_OR_DESTROY(wholeFileEqual(INVENTORY_TEST_FILE_3, INVENTORY_OUT_FILE_3));


    matamikyaDestroy(mtm);
    return true;
}

bool testMtmPrintOrder() {
    Matamikya mtm = matamikyaCreate();

    FILE *outputFile = fopen(CREATE_NULL_FILE, "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT == mtmPrintOrder(NULL,1,outputFile));
    fclose(outputFile);
    system(REMOVE_NULL_FILE);
    outputFile = fopen(CREATE_NULL_FILE, "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(MATAMIKYA_ORDER_NOT_EXIST == mtmPrintOrder(mtm,1,outputFile));
    fclose(outputFile);
    system(REMOVE_NULL_FILE);
    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT == mtmPrintOrder(mtm,1,NULL));


    double basePrice = 8.9;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 4, "Tomato", 2019.11, MATAMIKYA_ANY_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 5.8;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 6, "Onion", 1789.75, MATAMIKYA_ANY_AMOUNT,
                  &basePrice, copyDouble, freeDouble, buy10Get10ForFree));
    basePrice = 2000;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 10, "Television", 15, MATAMIKYA_INTEGER_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 5000;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 11, "Television", 4, MATAMIKYA_INTEGER_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 18.5;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 7, "Watermelon", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    basePrice = 5200;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 90, "Iphone", 1.501, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 1000, "Melki", 1.499, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    basePrice = 520.7;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 111, "Kinder", 1.500, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    basePrice = 96.8;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 114, "Blue", 1.000, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    basePrice = 700.0001;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 115, "Red Bull", 1.001, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    basePrice = 123;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 116, "Monster", 1.999, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    basePrice = 566666.9011;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 121, "Magnum White",12 , MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    basePrice = 4444.4444;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 122, "Magnum Black",12.001 , MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    basePrice = 123;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 123, "Magnum classic",11.999 , MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));


    unsigned int order_1, order_2, order_3, order_4;
    order_1 = mtmCreateNewOrder(mtm);
    order_2 = mtmCreateNewOrder(mtm);
    order_3 = mtmCreateNewOrder(mtm);
    order_4 = mtmCreateNewOrder(mtm);


    ASSERT_OR_DESTROY(0 < order_1);
    ASSERT_OR_DESTROY(0 < order_2);
    ASSERT_OR_DESTROY(0 < order_3);
    ASSERT_OR_DESTROY(0 < order_4);


    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,4,0.7));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,6,1.3));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,10,1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,11,1011));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,90,1.500));

    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,4,6));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,6,2));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,10,2));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,11,1.000));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,90,2.5));

    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,4,50));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,6,700.1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,10,3.00));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,11,14.999));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,90,1.5));
    
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,4,0.5));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,6,0.4));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,10,4.000));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,11,0));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,90,1));

    outputFile = fopen(ORDER_OUT_FILE_1, "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(mtmPrintOrder(mtm,order_1, outputFile) == MATAMIKYA_SUCCESS);
    fclose(outputFile);
    FILE *expected = fopen(ORDER_TEST_FILE_1, "r");
    FILE *printed = fopen(ORDER_OUT_FILE_1, "r");
    assert(expected);
    assert(printed);

    /* test that prefix and printed orderId is correct */
    const char *expectedPrefix = "Order ";
    int size = strlen(expectedPrefix);
    for (int i = 0; i < size; ++i) {
        ASSERT_OR_DESTROY(fgetc(printed) == expectedPrefix[i]);
    }
    unsigned int printedId;
    fscanf(printed, "%u", &printedId);
    ASSERT_OR_DESTROY(order_1 == printedId);

    /* skip the rest of the header line */
    while (fgetc(printed) != '\n');
    while (fgetc(expected) != '\n');

    ASSERT_OR_DESTROY(fileEqual(expected, printed));
    fclose(expected);
    fclose(printed);


    outputFile = fopen(ORDER_OUT_FILE_2, "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(mtmPrintOrder(mtm,order_2, outputFile) == MATAMIKYA_SUCCESS);
    fclose(outputFile);
    expected = fopen(ORDER_TEST_FILE_2, "r");
    printed = fopen(ORDER_OUT_FILE_2, "r");
    assert(expected);
    assert(printed);

    /* test that prefix and printed orderId is correct */
    for (int i = 0; i < size; ++i) {
        ASSERT_OR_DESTROY(fgetc(printed) == expectedPrefix[i]);
    }
    
    fscanf(printed, "%u", &printedId);
    ASSERT_OR_DESTROY(order_2 == printedId);

    /* skip the rest of the header line */
    while (fgetc(printed) != '\n');
    while (fgetc(expected) != '\n');

    ASSERT_OR_DESTROY(fileEqual(expected, printed));
    fclose(expected);
    fclose(printed);


    outputFile = fopen(ORDER_OUT_FILE_3, "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(mtmPrintOrder(mtm,order_3, outputFile) == MATAMIKYA_SUCCESS);
    fclose(outputFile);
    expected = fopen(ORDER_TEST_FILE_3, "r");
    printed = fopen(ORDER_OUT_FILE_3, "r");
    assert(expected);
    assert(printed);

    /* test that prefix and printed orderId is correct */
    for (int i = 0; i < size; ++i) {
        ASSERT_OR_DESTROY(fgetc(printed) == expectedPrefix[i]);
    }

    fscanf(printed, "%u", &printedId);
    ASSERT_OR_DESTROY(order_3 == printedId);

    /* skip the rest of the header line */
    while (fgetc(printed) != '\n');
    while (fgetc(expected) != '\n');

    ASSERT_OR_DESTROY(fileEqual(expected, printed));
    fclose(expected);
    fclose(printed);


    outputFile = fopen(ORDER_OUT_FILE_4, "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(mtmPrintOrder(mtm,order_4, outputFile) == MATAMIKYA_SUCCESS);
    fclose(outputFile);
    expected = fopen(ORDER_TEST_FILE_4, "r");
    printed = fopen(ORDER_OUT_FILE_4, "r");
    assert(expected);
    assert(printed);

    /* test that prefix and printed orderId is correct */
    for (int i = 0; i < size; ++i) {
        ASSERT_OR_DESTROY(fgetc(printed) == expectedPrefix[i]);
    }

    fscanf(printed, "%u", &printedId);
    ASSERT_OR_DESTROY(order_4 == printedId);

    /* skip the rest of the header line */
    while (fgetc(printed) != '\n');
    while (fgetc(expected) != '\n');

    ASSERT_OR_DESTROY(fileEqual(expected, printed));
    fclose(expected);
    fclose(printed);


    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmClearProduct(mtm, 90));


    outputFile = fopen(ORDER_OUT_FILE_6, "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(mtmPrintOrder(mtm,order_4, outputFile) == MATAMIKYA_SUCCESS);
    fclose(outputFile);
    expected = fopen(ORDER_TEST_FILE_6, "r");
    printed = fopen(ORDER_OUT_FILE_6, "r");
    assert(expected);
    assert(printed);

    /* test that prefix and printed orderId is correct */
    for (int i = 0; i < size; ++i) {
        ASSERT_OR_DESTROY(fgetc(printed) == expectedPrefix[i]);
    }

    fscanf(printed, "%u", &printedId);
    ASSERT_OR_DESTROY(order_4 == printedId);

    /* skip the rest of the header line */
    while (fgetc(printed) != '\n');
    while (fgetc(expected) != '\n');

    ASSERT_OR_DESTROY(fileEqual(expected, printed));
    fclose(expected);
    fclose(printed);


    matamikyaDestroy(mtm);
    return true;
}

bool testMtmPrintBestSelling() {
    Matamikya mtm = matamikyaCreate();

    FILE *outputFile = fopen(CREATE_NULL_FILE, "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT == mtmPrintBestSelling(NULL,outputFile));
    fclose(outputFile);
    system(REMOVE_NULL_FILE);
    ASSERT_OR_DESTROY(MATAMIKYA_NULL_ARGUMENT == mtmPrintBestSelling(mtm,NULL));


    double basePrice = 8.9;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 4, "Tomato", 2019.11, MATAMIKYA_ANY_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 5.8;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 6, "Onion", 1789.75, MATAMIKYA_ANY_AMOUNT,
                  &basePrice, copyDouble, freeDouble, buy10Get10ForFree));
    basePrice = 2000;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 10, "Television", 15, MATAMIKYA_INTEGER_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 5000;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 11, "Television", 4, MATAMIKYA_INTEGER_AMOUNT,
                  &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 18.5;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 7, "Watermelon", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    basePrice = 5200;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 90, "Iphone", 2.50, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    basePrice = 3;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 1000, "Melki", 15.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    basePrice = 520.7;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 111, "Kinder", 16.500, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    basePrice = 96.8;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 114, "Blue", 17.000, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    basePrice = 7000.001;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 115, "Red Bull", 19.000, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    basePrice = 123;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 116, "Monster", 17.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    basePrice = 566666.90;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 121, "Magnum White",12 , MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    basePrice = 4444.4444;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 122, "Magnum Black",12.00 , MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));
    basePrice = 123;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
    mtmNewProduct(mtm, 123, "Magnum classic",13 , MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice));


    unsigned int order_1, order_2, order_3, order_4;
    order_1 = mtmCreateNewOrder(mtm);
    order_2 = mtmCreateNewOrder(mtm);
    order_3 = mtmCreateNewOrder(mtm);
    order_4 = mtmCreateNewOrder(mtm);


    ASSERT_OR_DESTROY(0 < order_1);
    ASSERT_OR_DESTROY(0 < order_2);
    ASSERT_OR_DESTROY(0 < order_3);
    ASSERT_OR_DESTROY(0 < order_4);


    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,4,0.502));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,6,0.4989));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,10,0.001));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,11,1011));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,90,1.501));

    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,4,6));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,6,2));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,10,0));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,11,1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,90,1.5));

    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,4,50));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,6,700.1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,10,15));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,11,3.00));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,90,1));
    
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,4,0.502));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,6,0.4989));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,10,4.00));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,11,0));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_4,90,1.5));


    outputFile = fopen(NO_SELLING_OUT_FILE_1 , "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(mtmPrintBestSelling(mtm,outputFile) == MATAMIKYA_SUCCESS);
    fclose(outputFile);
    ASSERT_OR_DESTROY(wholeFileEqual(NO_SELLING_TEST_FILE_1 , NO_SELLING_OUT_FILE_1 ));


    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmShipOrder(mtm, order_2));


    outputFile = fopen(BEST_SELLING_OUT_FILE_1, "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(mtmPrintBestSelling(mtm,outputFile) == MATAMIKYA_SUCCESS);
    fclose(outputFile);
    ASSERT_OR_DESTROY(wholeFileEqual(BEST_SELLING_TEST_FILE_1, BEST_SELLING_OUT_FILE_1));

   
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmShipOrder(mtm, order_3));


    outputFile = fopen(BEST_SELLING_OUT_FILE_2, "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(mtmPrintBestSelling(mtm,outputFile) == MATAMIKYA_SUCCESS);
    fclose(outputFile);
    ASSERT_OR_DESTROY(wholeFileEqual(BEST_SELLING_TEST_FILE_2, BEST_SELLING_OUT_FILE_2));


    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmCancelOrder(mtm, order_1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmCancelOrder(mtm, order_4));


    order_1 = mtmCreateNewOrder(mtm);
    order_2 = mtmCreateNewOrder(mtm);
    order_3 = mtmCreateNewOrder(mtm);
    order_4 = mtmCreateNewOrder(mtm);


    ASSERT_OR_DESTROY(0 < order_1);
    ASSERT_OR_DESTROY(0 < order_2);
    ASSERT_OR_DESTROY(0 < order_3);
    ASSERT_OR_DESTROY(0 < order_4);


    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,7,15));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,1000,15));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,111,15));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,114,15));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_1,115,15));

    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,116,8.001));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,121,6));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,122,7.000));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,123,7.000));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_2,10,0));

    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,4,50));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,6,700.1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,10,14.9991));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,11,3.001));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmountInOrder(mtm, order_3,90,0.9991));


    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmShipOrder(mtm, order_1));


    outputFile = fopen(BEST_SELLING_OUT_FILE_3, "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(mtmPrintBestSelling(mtm,outputFile) == MATAMIKYA_SUCCESS);
    fclose(outputFile);
    ASSERT_OR_DESTROY(wholeFileEqual(BEST_SELLING_TEST_FILE_3, BEST_SELLING_OUT_FILE_3));


    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmShipOrder(mtm, order_2));


    outputFile = fopen(BEST_SELLING_OUT_FILE_4, "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(mtmPrintBestSelling(mtm,outputFile) == MATAMIKYA_SUCCESS);
    fclose(outputFile);
    ASSERT_OR_DESTROY(wholeFileEqual(BEST_SELLING_TEST_FILE_4, BEST_SELLING_OUT_FILE_4));

    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmClearProduct(mtm, 121));

    outputFile = fopen(BEST_SELLING_OUT_FILE_6, "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(mtmPrintBestSelling(mtm,outputFile) == MATAMIKYA_SUCCESS);
    fclose(outputFile);
    ASSERT_OR_DESTROY(wholeFileEqual(BEST_SELLING_TEST_FILE_6, BEST_SELLING_OUT_FILE_6));


    ASSERT_OR_DESTROY(MATAMIKYA_INSUFFICIENT_AMOUNT == mtmShipOrder(mtm, order_3));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmShipOrder(mtm, order_4));


    matamikyaDestroy(mtm);
    return true;
}

/*The functions for the tests should be added here*/
bool (*tests[]) (void) = {
        testMtmNewProduct,
        testMtmChangeProductAmount,
        testMtmClearProduct,
        testMtmCreateNewOrder,
        testMtmChangeProductAmountInOrder,
        testMtmShipOrder,
        testMtmCancelOrder,
        testMtmPrintInventory,
        testMtmPrintOrder,
        testMtmPrintBestSelling,
        testCreateSegel,
        testDestroySegel,
        testModifyProductsSegel,
        testModifyOrdersSegel,
        testPrintInventorySegel,
        testPrintOrderSegel,
        testPrintBestSellingSegel,
        };

#define NUMBER_TESTS ((long)(sizeof(tests)/sizeof(*tests)))

/*The names of the test functions should be added here*/
const char* testNames[NUMBER_TESTS] = {
        "testMtmNewProduct",
        "testMtmChangeProductAmount",
        "testMtmClearProduct",
        "testMtmCreateNewOrder",
        "testMtmChangeProductAmountInOrder",
        "testMtmShipOrder",
        "testMtmCancelOrder",
        "testMtmPrintInventory",
        "testMtmPrintOrder",
        "testMtmPrintBestSelling",
        "testCreateSegel",
        "testDestroySegel",
        "testModifyProductsSegel",
        "testModifyOrdersSegel",
        "testPrintInventorySegel",
        "testPrintOrderSegel",
        "testPrintBestSellingSegel",
        };

int main(int argc, char *argv[])
{
    long number_tests = NUMBER_TESTS;
    if (argc == 1)
    {
        fprintf(stdout, "Running %ld tests:\n", number_tests);
        for (long test_idx = 0; test_idx < number_tests; test_idx++)
        {
            RUN_COLORFULL_TEST(tests[test_idx], testNames[test_idx], test_idx);
        }
        printIfSuccess(number_tests);
    }
    else if (argc != 2)
    {
        fprintf(stdout, "Usage: matamikya <test index>\n");
        return 0;
    }
    else
    {
        long test_idx = strtol(argv[1], NULL, 10);
        if (test_idx < 1 || test_idx > NUMBER_TESTS)
        {
            fprintf(stderr, "Invalid test index %ld\n", test_idx);
            return 0;
        }
        number_tests = 1;
        RUN_COLORFULL_TEST(tests[test_idx - 1], testNames[test_idx - 1], test_idx - 1);
    }

    return 0;
}
