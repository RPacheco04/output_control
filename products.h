#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000

typedef struct product {
  char name[MAX_LENGTH];
  int id;
} Product;

typedef struct products {
  Product** list;
  int size;
} Products;

Products *readProductsFile(char *filename);
void printProducts(Products *products);
void freeProducts(Products *products);


/**
 * @brief Reads a file containing products and returns a Products struct
 * @param filename 
 * @return Products* 
 */
Products * readProductsFile(char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("Não foi possível abrir o arquivo %s", filename);
    exit(1);
  }
  Products *products = malloc(sizeof(Products));
  products->size = 0;
  char line[MAX_LENGTH];

  while (fgets(line, MAX_LENGTH, file) != NULL) {
    Product *product = malloc(sizeof(Product));
    // Divide the line into name and id
    char *token = strtok(line, "|");
    product->id = atoi(token);
    token = strtok(NULL, "|");
    strcpy(product->name, token);
    // Add the product to the list of products
    products->list = realloc(products->list, (products->size + 1) * sizeof(Product));
    products->list[products->size] = product;
    products->size++;
  }
  fclose(file);
  return products;
}

void freeProducts(Products *products) {
  for (int i = 0; i < products->size; i++) {
    free(products->list[i]);
  }
  free(products);
}

void printProducts(Products *products) {
  for (int i = 0; i < products->size; i++) {
    printf("%d - %s", products->list[i]->id, products->list[i]->name);
  }
}