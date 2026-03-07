#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arplane_protos_and_struct.h"


int user_input_name(char *ptr, const char *str_type) {

    if (strcmp(str_type, "firstname") == 0) {
        printf("\nGive your firstname, or 'stop' to exit from program.\n");
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




int check_seat(passenger *ptr) {
    int current_row = 1;
    char line[LINE_SIZE];
    FILE *fp = fopen(FILE_MAP, "r");
    FILE *fp2 = fopen("test.txt", "w");

    if (fp == NULL || fp2 == NULL) {
        printf("\nCan't open file.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (current_row == ptr->number) {
            if (strchr(line, ptr->seat_character) == 0) {
                printf("Seat is already booked.");
                printf("Try another seat.");
                fclose(fp);
                printf("%s\n", line);
                return 1;
            }
            for (int i = 0; i < strlen(line); i++) {
                if (line[i] == ptr->seat_character) {
                    line[i] = 'x';
                }
            }
            printf("Seat is available.");
            printf("%s\n", line);
        }
        fputs(line, fp2);
        current_row++;
    }
    fclose(fp);
    fclose(fp2);
    remove(FILE_MAP);
    rename("test.txt", FILE_MAP);
    return 0;
}



int add_in_passenger_list(passenger *ptr) {
    FILE *fp = fopen(FILE_LIST, "a");
    if (fp == NULL) {
        printf("\nCan't open file.\n");
        return 1;
    }

    fprintf(fp, "\n%s,%s,%d,%c",ptr->firstname, ptr->lastname, ptr->number, ptr->seat_character);
    fclose(fp);
    return 0;
}

void print_map() {
    char line[LINE_SIZE];
    FILE *fp = fopen(FILE_MAP, "r");
    if (fp == NULL) {
        printf("\nCan't open file.\n");
    }
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
    fclose(fp);
}
