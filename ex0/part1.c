#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Enter size of input:\n");
    int size;
    if (scanf("%d", &size) != 1 || size <= 0) {
        printf("Invalid size\n");
        return 0;
    }
    int *arr = malloc(size * sizeof(int));
    if (arr == NULL) {
        return 0;
    }
    printf("Enter numbers:\n");
    for (int i = 0; i < size; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid number\n");
            free(arr);
            return 0;
        }
    }

    int sum = 0;
    for (int i = 0; i < size; i++) {
        int exp = 0;
        int base = 1;
        while (base < arr[i]) {
            exp++;
            base *= 2;
        }
        if (base == arr[i]) {
            sum += exp;
            printf("The number %d is a power of 2: %d = 2^%d\n", arr[i], arr[i], exp);
        }
    }

    free(arr);
    printf("Total exponent sum is %d\n", sum);
    return 0;
}