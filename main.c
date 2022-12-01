#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include "outputs.h"

enum Options {
  EXIT = 0,
  ADD_OUTPUT = 1,
  CONFIRM_RETURN,
  SEARCH_PRODUCT,
  SHOW_HISTORY,
  INFO,
};

/**
 * @brief Print the menu with the user options
 */
void printMenu() {
  printf("Escolha uma opção: \n");
  printf("1 - Registrar saída de produto \n");
  printf("2 - Confirmar retorno de produto \n");
  printf("3 - Buscar produto \n");
  printf("4 - Mostrar histórico de saídas \n");
  printf("5 - Informações do sistema \n");
  printf("0 - Sair \n");
  printf("Opção escolhida: ");
}

/**
 * @brief Print the first messages to the user
 */
void printWelcome() {
  printf("================================================================================================\n");
  printf("Bem-vindo ao sistema de  \n\n");
  // Elena
}

/**
 * @brief Print the system information
 */
void printSystemInfo() {
  printf("================================================================================================\n");
  // Thyrson
}


/**
 * @brief Get the user iformation to add a new output
 * Get the user input of the products ids, the return date prevision (date and shift)
 * @param products 
 * @param outputs 
 */
void addOutput(Products * products, Outputs * outputs) {
  printf("\n================================================================================================\n");
  // Get the user input of the product id
  int productId;
  printf("Digite o código do produto: ");
  scanf("%d", &productId);
  // Get the product
  if (!_productExists(products, productId)) {
    printf("Produto não encontrado. \n");
    printf("================================================================================================\n\n");
    return;
  };
  // Get the user input of the return date prevision
  char * returnDate = malloc(sizeof(char) * 11);
  printf("Digite a data prevista de retorno (dd/mm/aaaa): ");
  scanf("%s", returnDate);

  // Get the user input of the return shift prevision
  int returnShift;
  printf("Digite o turno previsto de retorno (1 - manhã, 2 - tarde, 3 - noite): ");
  scanf("%d", &returnShift);

  // Get the destination of the output
  char * destination = malloc(sizeof(char) * 100);
  printf("Digite o destino do produto: ");
  scanf("%s", destination);

  // Add the output to the outputs list
  Output * output = _createOutput(productId, returnDate, getShiftByNumber(returnShift), outputs->size + 1, destination);
  _addOutput(outputs, output);

  printf("\n================================================================================================\n\n");
}



/**
 * @brief Search on the outputs for outputs with the product id and print the results
 * Get the user input of product_id. Calls _getOutputsByProductId and calls _printOutputList on the result
 * @param products 
 * @param outputs 
 * @param showDividers 
 * @return Outputs* 
 */
Outputs *searchProduct(Products * products, Outputs * outputs, bool showDividers) {
  if (showDividers) printf("\n================================================================================================\n");
  // Get the user input of the product id
  int productId;
  printf("Digite o código do produto: ");
  scanf("%d", &productId);
  // Get the product
  Outputs *outputsWithId = _getOutputsByProductId(outputs, productId);

  if (outputsWithId->size == 0) {
    printf("Produto não encontrado.");
    if (showDividers) printf("\n================================================================================================\n\n");
    return NULL;
  }
  printf("Saídas encontradas para este produto: \n\n");
  _printOutputList(products, outputsWithId);
  if (showDividers) printf("\n================================================================================================\n");
  return outputsWithId;
}

/**
 * @brief Get the user input to confirm the return of a product
 * @param outputs 
 */
void confirmReturn(Products * products, Outputs * outputs) {
  printf("\n================================================================================================\n");
  Outputs *outputsWithId = searchProduct(products, outputs, false);
  if (outputsWithId == NULL) {
    printf("\n================================================================================================\n\n");
    return;
  }
  int outputId;
  printf("\nDigite o id da saída que deseja confirmar o retorno: ");
  scanf("%d", &outputId);
  _confirmReturn(outputs, outputId);
  printf("\n================================================================================================\n\n");
}

/**
 * @brief Show all the outputs
 * @param products 
 * @param outputs 
 */
void showHistory(Products * products, Outputs * outputs) {
  printf("\n================================================================================================\n");
  printf("Histórico de saídas: \n\n");
  _printOutputList(products, outputs);
  printf("\n================================================================================================\n");
}

int main(void) {
  setlocale(LC_ALL, "Portuguese");
  Products *products = _readProductsFile("products.txt");
  Outputs *outputs = _createOutputRegister();

  int option = 1;
  while (option != EXIT) {
    printMenu();
    scanf("%d", &option);
    switch (option) {
      case ADD_OUTPUT:
        addOutput(products, outputs);
        break;
      case CONFIRM_RETURN:
        confirmReturn(products, outputs);
        break;
      case SEARCH_PRODUCT:
        searchProduct(products, outputs, true);
        break;
      case SHOW_HISTORY:
        showHistory(products, outputs);
        break;
      case INFO:
        printSystemInfo();
        break;
      case EXIT:
        break;
      default:
        printf("Opção inválida. \n");
        break;
      }
  }
  return 0;
}