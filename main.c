#include <stdio.h>
#include <stdlib.h>
#include "products.h"

/**
 * @brief Print the menu with the user options
 * 
 */
void printMenu() {

  print()
};

/**
 * @brief Print the system information
 * 
 * @return int 
 */
void printSystemInfo() {

};

int main(void) {
  Products* products = readProductsFile("products.txt");
  freeProducts(products);
  return 0;
}