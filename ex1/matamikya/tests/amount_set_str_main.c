#include <stdio.h>

#include "../amount_set_str.h"
#include "string.h"
int main() {
    AmountSet nullSet = NULL;
    AmountSet emptySet = asCreate();

    // printf("Test asCreate\n");
    AmountSet set1 = asCreate();
    if (set1 == NULL) {
        printf("Test 1 failed, got null from asCreate\n");
    } else {
        printf("Test 1 passed\n");
    }

    //printf("Test asGetFirst\n");
    if (asGetFirst(set1) != NULL) {
        printf("Test 2 failed, set's head is not null after asCreate\n");
    } else {
        printf("Test 2 passed\n");
    }

    // printf("Test asRegister\n");
    if (asRegister(set1, "B") != AS_SUCCESS) {
        printf("Test 3 failed, asRegister returned an error\n");
    } else {
        printf("Test 3 passed\n");
    }

    // printf("Test asRegister\n");
    if (asRegister(set1, "D") != AS_SUCCESS) {
        printf("Test 4 failed, asRegister returned an error\n");
    } else {
        printf("Test 4 passed\n");
    }

    // printf("Test asRegister\n");
    if (asRegister(set1, "C") != AS_SUCCESS) {
        printf("Test 5 failed, asRegister returned an error\n");
    } else {
        printf("Test 5 passed\n");
    }

    // printf("Test asGetFirst\n");
    if (strcmp(asGetFirst(set1), "B") != 0) {
        printf("Test 6 failed, asGetFirst did not return the expected element in lexicographic order\n");
    } else {
        printf("Test 6 passed\n");
    }

    // printf("Test asGetNext\n");
    if (strcmp(asGetNext(set1), "C") != 0) {
        printf("Test 7 failed, asGetFirst did not return the expected element in lexicographic order\n");
    } else {
        printf("Test 7 passed\n");
    }

    // printf("Test asGetNext\n");
    if (strcmp(asGetNext(set1), "D") != 0) {
        printf("test 8 failed, asGetFirst did not return the expected element in lexicographic order\n");
    } else {
        printf("Test 8 passed\n");
    }

    // printf("Test asGetFirst\n");
    if (strcmp(asGetFirst(set1), "B") != 0) {
        printf("test 9 failed, asGetFirst did not set the internal iterator to the first element\n");
    } else {
        printf("Test 9 passed\n");
    }

    // printf("Test asGetSize\n");
    if (asGetSize(set1) != 3) {
        printf("Test 10 failed, asGetSize returned a wrong value\n");
    } else {
        printf("Test 10 passed\n");
    }

    // printf("Test asGetAmount\n");
    double result;
    if (asGetAmount(set1, "C", &result) != AS_SUCCESS) {
        printf("Test 11 failed, asGetAmount returned an error\n");
    } else if (result != 0) {
        printf("Test 11 failed, asGetAmount returned a wrong amount\n");
    } else {
        printf("Test 11 passed\n");
    }

    // printf("Test asChangeAmount && asGetAmount\n");
    if (asChangeAmount(set1, "C", 7.7) != AS_SUCCESS) {
        printf("Test 12 failed, asChangeAmount returned an error\\n");
    } else if (asGetAmount(set1, "C", &result) != AS_SUCCESS) {
        printf("Test 12 failed, asGetAmount returned an error\\n");
    } else if (result != 7.7) {
        printf("Test 12 failed, asGetAmount returned a wrong amount\n");
    } else {
        printf("Test 12 passed\n");
    }

    // printf("Test asCopy\n");
    AmountSet nullSetCpy = asCopy(nullSet);
    if (nullSetCpy != NULL) {
        printf("Test 13 failed, asCopy got a NULL argument but did not return NULL\n");
    } else {
        printf("Test 13 passed\n");
    }
    asDestroy(nullSetCpy);  //Tested with valgrind to find memory leaks

    // printf("Test asCopy && asGetFirst\n");
    AmountSet emptySetCpy = asCopy(emptySet);
    if (emptySetCpy == NULL) {
        printf("Test 14 failed, asCopy got a set but returned NULL\n");
    } else if (asGetFirst(emptySetCpy) != NULL) {
        printf("Test 14 failed, the first element should have been NULL if the empty set was sent\n");
    } else {
        printf("Test 14 passed\n");
    }
    asDestroy(emptySetCpy);  //Tested with valgrind to find memory leaks

    // printf("Test asCopy\n");
    AmountSet set1cpy = asCopy(set1);
    if (set1cpy == NULL) {
        printf("Test 15 failed, asCopy returned a NULL\n");
    } else {
        printf("Test 15 passed\n");
    }

    // printf("Test asCopy && asGetSize\n");
    if (asGetSize(set1cpy) != 3) {
        printf("Test 16 failed, asGetSize returned a wrong value\n");
    } else {
        printf("Test 16 passed\n");
    }

    // printf("Test asGetSize\n");
    if (asGetSize(nullSet) != -1) {
        printf("Test 17 failed, asGetSize returned a wrong value for null set\n");
    } else {
        printf("Test 17 passed\n");
    }

    // printf("Test asGetSize\n");
    if (asGetSize(emptySet) != 0) {
        printf("Test 18 failed, asGetSize returned a wrong value for empty set\n");
    } else {
        printf("Test 18 passed\n");
    }

    // printf("Test asCopy && asGetFirst\n");
    if (strcmp(asGetFirst(set1cpy), "B") != 0) {
        printf("Test 19 failed, asCopy didnt copy set1 correctly\n");
    } else {
        printf("Test 19 passed\n");
    }

    //printf("Test asCopy && asGetNext\n");
    if (strcmp(asGetNext(set1), "C") != 0) {
        printf("Test 20 failed, asCopy didnt copy set1 correctly\n");
    } else {
        printf("Test 20 passed\n");
    }

    //printf("Test asCopy && asGetNext\n");
    if (strcmp(asGetNext(set1), "D") != 0) {
        printf("Test 21 failed, asCopy didnt copy set1 correctly\n");
    } else {
        printf("Test 21 passed\n");
    }

    // printf("Test asGetAmount\n");
    if (asGetAmount(set1, "C", &result) != AS_SUCCESS) {
        printf("Test 22 failed, asGetAmount returned an error\n");
    } else if (result != 7.7) {
        printf("Test 22 failed, asGetAmount returned a wrong amount\n");
    } else {
        printf("Test 22 passed\n");
    }

    // printf("Test asGetAmount\n");
    if (asGetAmount(nullSet, "C", &result) != AS_NULL_ARGUMENT) {
        printf("Test 23 failed, asGetAmount should have returned AS_NULL_ARGUMENT\n");
    } else if (asGetAmount(set1, "C", NULL) != AS_NULL_ARGUMENT) {
        printf("Test 23 failed, asGetAmount should have returned AS_NULL_ARGUMENT\n");
    } else if (asGetAmount(set1, "E", &result) != AS_ITEM_DOES_NOT_EXIST) {
        printf("Test 23 failed, asGetAmount should have returned AS_ITEM_DOES_NOT_EXIST\n");
    } else {
        printf("Test 23 passed\n");
    }

    // printf("Test asGetAmount\n");
    if (asGetAmount(nullSet, "C", &result) != AS_NULL_ARGUMENT) {
        printf("Test 24 failed, asGetAmount should have returned AS_NULL_ARGUMENT\n");
    } else if (asGetAmount(set1, NULL, &result) != AS_NULL_ARGUMENT) {
        printf("Test 24 failed, asGetAmount should have returned AS_NULL_ARGUMENT\n");
    } else {
        printf("Test 24 passed\n");
    }

    // printf("Test asChangeAmount\n");
    if (asChangeAmount(emptySet, "C", 0.0) != AS_ITEM_DOES_NOT_EXIST) {
        printf("Test 25 failed, asChangeAmount should have returned AS_ITEM_DOES_NOT_EXIST\n");
    } else if (asChangeAmount(nullSet, "C", 0.0) != AS_NULL_ARGUMENT) {
        printf("Test 25 failed, asChangeAmount should have returned AS_NULL_ARGUMENT\n");
    } else if (asChangeAmount(set1, NULL, 0.0) != AS_NULL_ARGUMENT) {
        printf("Test 25 failed, asChangeAmount should have returned AS_NULL_ARGUMENT\n");
    } else {
        printf("Test 25 passed\n");
    }

    // printf("Test asChangeAmount\n");
    if (asChangeAmount(set1, "C", -17.7) != AS_INSUFFICIENT_AMOUNT) {
        printf("Test 26 failed, asChangeAmount should have returend AS_INSUFFICIENT_AMOUNT\n");
    } else if (asGetAmount(set1, "C", &result) != AS_SUCCESS) {
        printf("Test 26 failed, asGetAmount returned an error\n");
    } else if (result != 7.7) {
        printf("Test 26 failed, asGetAmount returned a wrong amount after attempting to remove too much\n");
    } else {
        printf("Test 26 passed\n");
    }

    // printf("Test asContains\n");
    if (asContains(set1, "C") != true) {
        printf("Test 27 failed, asContains should have returend false\n");
    } else if (asContains(set1, "E") != false) {
        printf("Test 27 failed, asContains should have returend true\n");
    } else if (asContains(set1, NULL) != false) {
        printf("Test 27 failed, asContains should have returend false\n");
    } else if (asContains(nullSet, "C") != false) {
        printf("Test 27 failed, asContains should have returend false\n");
    } else {
        printf("Test 27 passed\n");
    }

    // printf("Test asDelete\n");
    if (asDelete(set1cpy, NULL) != AS_NULL_ARGUMENT) {
        printf("Test 28 failed, asChangeAmount should have returend AS_NULL_ARGUMENT\n");
    } else if (asDelete(nullSet, "C") != AS_NULL_ARGUMENT) {
        printf("Test 28 failed, asChangeAmount should have returend AS_NULL_ARGUMENT\n");
    } else if (asDelete(emptySet, "C") != AS_ITEM_DOES_NOT_EXIST) {
        printf("Test 28 failed, asChangeAmount should have returend AS_ITEM_DOES_NOT_EXIST\n");
    } else if (asDelete(set1cpy, "E") != AS_ITEM_DOES_NOT_EXIST) {
        printf("Test 28 failed, asChangeAmount should have returend AS_ITEM_DOES_NOT_EXIST\n");
    } else if (asDelete(set1cpy, "C") != AS_SUCCESS) {
        printf("Test 28 failed, asChangeAmount should have returend AS_SUCCESS\n");
    } else if (asDelete(set1cpy, "C") != AS_ITEM_DOES_NOT_EXIST) {
        printf("Test 28 failed, asChangeAmount should have returend AS_ITEM_DOES_NOT_EXIST\n");
    } else if (asGetSize(set1cpy) != 2) {
        printf("Test 28 failed, asGetsize returned a wrong size after removing elements\n");
    } else if (asDelete(set1cpy, "B") != AS_SUCCESS) {
        printf("Test 28 failed, asChangeAmount should have returend AS_SUCCESS\n");
    } else if (asGetSize(set1cpy) != 1) {
        printf("Test 28 failed, asGetsize returned a wrong size after removing elements\n");
    } else if (asDelete(set1cpy, "D") != AS_SUCCESS) {
        printf("Test 28 failed, asChangeAmount should have returend AS_SUCCESS\n");
    } else if (asGetSize(set1cpy) != 0) {
        printf("Test 28 failed, asGetsize returned a wrong size after removing elements\n");
    } else {
        printf("Test 28 passed\n");
    }
    asDestroy(set1cpy);  //Tested with valgrind to find memory leaks

    // printf("Test asRegister\n");
    if (asRegister(set1, NULL) != AS_NULL_ARGUMENT) {
        printf("Test 29 failed, asRegister should have returend AS_NULL_ARGUMENT\n");
    } else if (asRegister(nullSet, "C") != AS_NULL_ARGUMENT) {
        printf("Test 29 failed, asRegister should have returend AS_NULL_ARGUMENT\n");
    } else if (asRegister(set1, "C") != AS_ITEM_ALREADY_EXISTS) {
        printf("Test 29 failed, asRegister should have returend AS_ITEM_ALREADY_EXISTS\n");
    } else if (asRegister(set1, "A") != AS_SUCCESS) {
        printf("Test 29 failed, asRegister should have returend AS_SUCCESS\n");
    } else if (strcmp(asGetFirst(set1), "A") != 0) {
        printf("Test 29 failed, asGetFirst should have returned A\n");
    } else {
        printf("Test 29 passed\n");
    }

    // printf("Test asClear\n");
    if (asClear(NULL) != AS_NULL_ARGUMENT) {
        printf("Test 30 failed, asClear should have returend AS_NULL_ARGUMENT\n");
    } else if (asClear(emptySet) != AS_SUCCESS) {
        printf("Test 30 failed, asClear should have returend AS_SUCCESS\n");
    } else if (asClear(set1) != AS_SUCCESS) {
        printf("Test 30 failed, asClear should have returend AS_SUCCESS\n");
    } else if (asGetSize(set1) != 0) {
        printf("Test 30 failed, asGetSize should have returend 0\n");
    } else {
        printf("Test 30 passed\n");
    }

    asDestroy(nullSet);  //should not crash if sent null

    //printf("Test asDestroy\n");
    asDestroy(emptySet);  //Tested with valgrind to find memory leaks
    asDestroy(set1);      //Tested with valgrind to find memory leaks
    return 0;
}
