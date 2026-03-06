#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define FILE_MAP "airplane_map.txt"
#define FILE_LIST "passenger_list.csv"

#define NAME_LENGTH 40
#define SEATS 157
#define LINE_SIZE 100

typedef struct {
    char firstname[NAME_LENGTH];
    char lastname[NAME_LENGTH];
    char seat_character;
    int number;
}passenger;

int user_input_name(char *ptr, const char *str_type);
int user_input_number(passenger *ptr);
int user_input_seat(passenger *ptr);

//main file
int main() {
    passenger pas = {0};
    passenger *ptr = &pas;

    //ask name of passenger and seat where passenger wants to sit
    while (strcmp(ptr->firstname, "stop") != 0) {
        while (user_input_name(ptr->firstname, "firstname") != 0) {}
        if (strcmp(ptr->firstname, "stop") != 0) {
            while (user_input_name(ptr->lastname, "lastname") != 0) {}
            while (user_input_number(ptr) != 0) {}
            while (user_input_seat(ptr) != 0){}
            printf("\n");
            printf("%s\n", ptr->firstname);
            printf("%s\n", ptr->lastname);
            printf("%d\n", ptr->number);
            printf("%c\n", ptr->seat_character);

        }
    }
}

int user_input_name(char *ptr, const char *str_type) {

    if (strcmp(str_type, "firstname") == 0) {
        printf("Give your firstname, or 'stop' to exit from program.\n");
    }
    if (strcmp(str_type, "lastname") == 0) {
        printf("Give your lastname.\n");
    }
    printf(">> ");
    if (fgets(ptr, NAME_LENGTH, stdin) == NULL) {
        printf("\nCan't read input.\n\n");
        return 1;
    }

    if (ptr[strlen(ptr) - 1] != '\n') {
        printf("\nThe name is too long.\n\n");
        while (getchar() != '\n'){}
        return 1;
    }
    if (ptr[0] == '\n') {
        printf("\nName has to be given to get continue.\n\n");
        return 1;
    }

    if (ptr[strlen(ptr) - 1] == '\n') {
        ptr[strlen(ptr) - 1] = '\0';
    }

    for (int i = 0; i < strlen(ptr); i++) {
        if (!isalpha(ptr[i])) {
            printf("Name can't include numbers or special characters including å, ä, ö.\n\n");
            return 1;
        }
    }

    if (strcmp(ptr, "stop") == 0) {
        printf("%s\n", ptr);
        return 0;
    }
    return 0;
}

int user_input_number(passenger *ptr) {
    char line[LINE_SIZE];
    FILE *fp = fopen(FILE_MAP, "r");

    if (fp == NULL) {
        printf("\nCan't open file.\n");
        fclose(fp);
        return 1;
    }

    printf("Give number of row where you want to sit.\n");
    printf(">> ");
    if (fgets(line, sizeof(line), stdin) == NULL) {
        printf("\nCan't read input.\n\n");
        fclose(fp);
        return 1;
    }
    //if user enter too long input then we clear buffer
    if (strchr(line, '\n') == NULL) {
        while (getchar() != '\n') {}
        fclose(fp);
        return 1;
    }
    //if input is not numbers then we send error
    if (sscanf(line, "%d", &ptr->number) != 1) {
        printf("Invalid input\n");
        fclose(fp);
        return 1;
    }
    if (ptr->number < 1 || ptr->number > 26) {
        printf("Number has to be 1-26\n");
        fclose(fp);
        return 1;
    }
    /*
    while (!feof(fp)) {
        if (fgets(line, sizeof(line), fp) == NULL) {
            printf("\nCan't read input.\n\n");
            fclose(fp);
            return 1;
        }
        if (strchr(line, '\n') == NULL) {
            while (getchar() != '\n') {}
        }
    }*/


    return 0;
}

int user_input_seat(passenger *ptr) {
    char line[LINE_SIZE];

    printf("Give your seat (A-F).\n");
    printf(">> ");
    if (fgets(line, LINE_SIZE, stdin) != NULL) {
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        if (strlen(line) != 1) {
            printf("Invalid seat.\n");
            printf("Seat has to have exactly one character.\n");
            return 1;
        }
        char seat = line[0];
        seat = toupper(seat);
        if (seat < 'A' || seat > 'F') {
            printf("Invalid seat.\n");
            return 1;
        }

        ptr->seat_character = seat;
    }
    return 0;
}