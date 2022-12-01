#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

/**
 * @brief Get the Current Date object and return it as a string formatted in portuguese (dd/mm/yyyy)
 * @return char* 
 */
char* getCurrentDate() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char *date = malloc(sizeof(char) * 11);
    sprintf(date, "%d/%d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    return date;
};


/**
 * @brief Get the Shift string based on the shift number (1,2 or 3)
 * @param shift 
 * @return char* 
 */
char *getShiftByNumber(int shift) {
  switch (shift) {
    case 1:
      return "Manhã";
    case 2:
      return "Tarde";
    case 3:
      return "Noite";
    default:
      return "Turno inválido";
  }
}

/**
 * @brief Get the Current Shift object and return it as a string formatted in portuguese (
 * "Manhã", "Tarde" ou "Noite")
 * @return char* 
 */
char* getCurrentShift() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char *shift = malloc(sizeof(char) * 3);
    if (tm.tm_hour < 12 && tm.tm_hour > 6) {
        strcpy(shift, "Manhã");
    } else if (tm.tm_hour < 18 && tm.tm_hour > 12) {
        strcpy(shift, "Tarde");
    } else {
        strcpy(shift, "Noite");
    }
    return shift;
};

/**
 * @brief Get the Current Date and Shift object and return it as a string formatted in portuguese (dd/mm/yyyy Manhã/Tarde/Noite)
 * @return char* 
 */
char* getCurrentDateAndShift() {
    char *date = getCurrentDate();
    char *shift = getCurrentShift();
    char *dateAndShift = malloc(sizeof(char) * (strlen(date) + strlen(shift) + 1));
    strcpy(dateAndShift, date);
    strcat(dateAndShift, " ");
    strcat(dateAndShift, shift);
    return dateAndShift;
};