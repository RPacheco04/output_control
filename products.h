#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 1000

typedef struct product {
  char name[MAX_LENGTH];
  int id;
} Product;

typedef struct products {
  Product** list;
  int size;
} Products;

/**
 * @brief Reads a file containing products and returns a Products struct
 * @param filename 
 * @return Products* 
 */
Products * _readProductsFile(char *filename) {
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

/**
 * @brief Free the memory allocated for a Products struct
 * @param products 
 */
void _freeProducts(Products *products) {
  for (int i = 0; i < products->size; i++) {
    free(products->list[i]);
  }
  free(products);
}

/**
 * @brief Check if the given id is from a valid product
 * @param products 
 * @param id 
 * @return bool
 */
bool _productExists(Products *products, int id) {
  for (int i = 0; i < products->size; i++) {
    if (products->list[i]->id == id) {
      return true;
    }
  }
  return false;
}

/**
 * @brief Get the product object by id
 * @param products 
 * @param id 
 */
Product* _getProductById(Products *products, int id) {
  for (int i = 0; i < products->size; i++) {
    if (products->list[i]->id == id) {
      return products->list[i];
    }
  }
  return NULL;
}

/**
 * @brief Return the product name of the product with the given id
 * @param products 
 */
char* _getProductName(Products *products, int id) {
  Product *product = _getProductById(products, id);
  if (product == NULL) {
    return NULL;
  }
  return product->name;
}
