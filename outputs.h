#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "products.h"
#include "dates.h"

typedef struct output {
    int output_id;
    int product_id;
    bool returned;
    char * forecast_date;
    char * output_date;
    char * destination;
} Output;

typedef struct outputs {
    Output** list;
    int size;
} Outputs;

/**
 * @brief Alloc memory for a new Outputs struct
 * @return Outputs* 
 */
Outputs * _createOutputRegister() {
  Outputs * outputs = malloc(sizeof(Outputs));
  outputs->size = 0;
  return outputs;
};

/**
 * @brief Alloc memory and create a new output with the information provided as params
 * @param productId
 * @param returnDate 
 * @param returnShift
 * @param outputId 
 * @param destination 
 * @return Output* 
 */
Output* _createOutput(int productId, char * returnDate, char * returnShift, int outputId, char * destination) {
  Output * output = malloc(sizeof(Output));
  // Alloc correct memory for forecast_date
  output->forecast_date = malloc(sizeof(char) * (strlen(returnDate) + strlen(returnShift) + 1));
  // Use strcpy to concatenate the date and shift
  strcpy(output->forecast_date, returnDate);
  strcat(output->forecast_date, " ");
  strcat(output->forecast_date, returnShift);
  output->product_id = productId;
  output->output_id = outputId;
  output->destination = destination;
  output->output_date = getCurrentDateAndShift(); // Get the current date and shift formatted as string
  return output;
}

/**
 * @brief Get the Output object and the Outputs struct and add the output to the list of outputs
 * @param outputs 
 * @param output 
 */
void _addOutput(Outputs *outputs, Output *output) {
  outputs->size++;
  outputs->list = realloc(outputs->list, sizeof(Output) * outputs->size); // Realloc memory
  outputs->list[outputs->size - 1] = output;
}

/**
 * @brief Free all the allocated memory for the outputs list
 * freeEachOutput should be true if you want to free the memory allocated for each output (cannot be used anymore)
 * @param outputs 
 * @param freeEachOutput  
 */
void _freeOutputsList(Outputs *outputs, bool freeEachOutput) {
  if (freeEachOutput) {
    for (int i = 0; i < outputs->size; i++) {
      free(outputs->list[i].forecast_date);
      free(outputs->list[i]);
    }
  }
  free(outputs);
}

/**
 * @brief This function filter the outputs list based on the product_id received as param
 * @param outputs 
 * @param productId 
 * @return Outputs* 
 */
Outputs * _getOutputsByProductId(Outputs *outputs, int productId) {
  // Creates new outputs list
  Outputs * outputsByProductId = _createOutputRegister();
  for (int i = 0; i < outputs->size; i++) {
    if (outputs->list[i]->product_id == productId) {
      _addOutput(outputsByProductId, outputs->list[i]);
    }
  }
  return outputsByProductId;
}

/**
 * @brief Receive a list of outputs and print them formatted in the console
 * The products list is needed to get the product name
 * 
 * @param products 
 * @param outputs 
 */
void _printOutputList(Products *products, Outputs *outputs) {
  for (int i = 0; i < outputs->size; i++) {
    printf("%d - ", outputs->list[i]->output_id);
    printf(
      "Produto: %s  Data de saída: %s, Destino: %s \n  Data prevista de retorno: %s, Retornado: %s\n\n",
      _getProductName(products, outputs->list[i]->product_id),
      outputs->list[i]->output_date,
      outputs->list[i]->destination,
      outputs->list[i]->forecast_date,
      outputs->list[i]->returned ? "Sim" : "Não"
    );
  }
}

/**
 * @brief Get the outputs and the output id to confirm. Print the message (success or error)
 * @param outputs 
 * @param outputId 
 */
void _confirmReturn(Outputs *outputs, int outputId) {
  bool found = false;
  for (int i = 0; i < outputs->size; i++) {
    if (outputs->list[i]->output_id == outputId) {
      found = true;
      if (outputs->list[i]->returned) {
        printf("Este produto já foi retornado!\n");
      } else {
        outputs->list[i]->returned = true;
        printf("Produto retornado com sucesso!\n");
      }
    }
  }
  if (!found) printf("Não foi possível encontrar o produto com o id %d\n", outputId);
}