#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "products.h"

typedef struct output {
    int output_id;
    int product_id;
    bool returned;
    char * forecast_date;
    char * output_date;
} Output;

typedef struct outputs {
    Output** list;
    int size;
} Outputs;


Outputs * _createOutputRegister() {
  Outputs * outputs = malloc(sizeof(Outputs));
  outputs->size = 0;
  return outputs;
};

Output* _createOutput(int productId, char * returnDate, char * returnShift, int outputId) {
  Output * output = malloc(sizeof(Output));
  // set output date as concatenation of returnDate and returnShift separated by space
  output->forecast_date = malloc(sizeof(char) * (strlen(returnDate) + strlen(returnShift) + 1));
  strcpy(output->forecast_date, returnDate);
  strcat(output->forecast_date, " ");
  strcat(output->forecast_date, returnShift);
  output->product_id = productId;
  output->output_id = outputId;
  output->output_date = "teste data"; // TODO Get current date and shift

  return output;
}

void _addOutput(Outputs *outputs, Output *output) {
  outputs->size++;
  outputs->list = realloc(outputs->list, sizeof(Output) * outputs->size);
  outputs->list[outputs->size - 1] = output;
}

Outputs * _getOutputsByProductId(Outputs *outputs, int productId) {
  Outputs * outputsByProductId = _createOutputRegister();
  for (int i = 0; i < outputs->size; i++) {
    if (outputs->list[i]->product_id == productId) {
      _addOutput(outputsByProductId, outputs->list[i]);
    }
  }
  return outputsByProductId;
}

void _printOutputList(Products *products, Outputs *outputs) {
  for (int i = 0; i < outputs->size; i++) {
    printf("%d - ", i + 1);
    printf(
      "Data de saída: %s, Data prevista de retorno: %s, Retornado: %s, Produto: %s",
      outputs->list[i]->output_date,
      outputs->list[i]->forecast_date,
      outputs->list[i]->returned ? "Sim" : "Não",
      _getProductName(products, outputs->list[i]->product_id)
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