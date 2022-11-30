#include <stdio.h>
#include <stdlib.h>
#include "products.h"

int main(void) {
    Products* products = readProductsFile("products.txt");
    freeProducts(products);
    return 0;
}