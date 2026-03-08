#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arplane_protos_and_struct.h"

//print welcome text and call print_map function to show reservation status
int print_menu() {
    printf("\nWelcome to our seat reservation program.\n\n"
           "We ask your first name and last name, see that if you make some mistakes when reserving the seat.\n"
           "Our airplane company is not capable to do any changes, we will check some corrections,\n"
           "but wrong names or big letters are not corrected.");

    printf("\n\nHere is our current reservation status, right is seat row and after row is seats marked as A-F\n"
           "If there is 'x' it means that seat is already booked.\n");

    print_map();
    printf("\n");
    return 0;
}

//ask input
int user_input_name(char *ptr, const char *str_type) {

    if (strcmp(str_type, "firstname") == 0) { //different text if asked first name
        printf("\nGive your first name, or 'stop' to exit from program.\n");
    }
    if (strcmp(str_type, "lastname") == 0) { //ask last name
        printf("Give your last name.\n");
    }
    printf(">> "); //where input is given
    if (fgets(ptr, NAME_LENGTH, stdin) == NULL) {
        printf("\nCan't read input.\n\n");
        return 1; //error if input can't be read.
    }

    if (ptr[strlen(ptr) - 1] != '\n') {
        printf("\nThe name is too long.\n\n");
        while (getchar() != '\n'){}
        return 1; // error if name is too long
    }
    if (ptr[0] == '\n') {
        printf("\nName has to be given to get continue.\n\n");
        return 1; // error if user enters enter
    }

    if (ptr[strlen(ptr) - 1] == '\n') {
        ptr[strlen(ptr) - 1] = '\0';
    } // newline off


    for (int i = 0; i < strlen(ptr); i++) {
        if (!isalpha(ptr[i])) { //name can't include anything else than letters A-Z
            printf("Name can't include numbers or special characters including å, ä, ö.\n\n");
            return 1; //error if not A-Z
        }
    }

    //if first name input stop, user stop entering new passengers and program closes
    if (strcmp(ptr, "stop") == 0) {
        printf("%s\n", ptr);
        return 0;
    }
    return 0;
}



//ask row number
int user_input_number(passenger *ptr) {
    char line[LINE_SIZE];
    FILE *fp = fopen(FILE_MAP, "r");

    if (fp == NULL) {
        printf("\nCan't open file.\n");
        return 1; //error if file not opening
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

    //error if number is smaller than 1 or bigger than 26
    if (ptr->number < 1 || ptr->number > 26) {
        printf("Number has to be 1-26\n");
        fclose(fp);
        return 1;
    }

    return 0;
}



//ask seat char A-F
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
            return 1; //inout can't be smaller or bigger than 1
        }
        char seat = line[0];
        seat = toupper(seat);
        if (seat < 'A' || seat > 'F') {
            printf("Invalid seat.\n");
            return 1; //input has to be A - F
        }

        ptr->seat_character = seat; //pointer to seat_char is set
    }
    return 0;
}

//check if seat is avalable
int check_seat(passenger *ptr) {
    int current_row = 1;
    char line[LINE_SIZE];
    FILE *fp = fopen(FILE_MAP, "r");
    FILE *fp2 = fopen(FILE_TEMPORARY, "w");

    //error if files are not opened
    if (fp == NULL || fp2 == NULL) {
        printf("\nCan't open file.\n");
        return 1;
    }


    while (fgets(line, sizeof(line), fp) != NULL) {
        if (sscanf(line, "%d", &current_row) == 1) {
            if (current_row == ptr->number) {
                if (strchr(line, ptr->seat_character) == 0) {  //seat is not found form airplane_map.txt
                    printf("Seat is already booked.\n");
                    printf("Try another seat.\n");
                    fclose(fp);
                    return 1;
                }
                printf("Seat is available.\n"); //seat is free

                //writes x where user wants to sit
                for (int i = 0; i < strlen(line); i++) {
                    if (line[i] == ptr->seat_character) {
                        line[i] = 'x';
                    }
                }
            }
        }
        fputs(line, fp2); // copy line to temporary file
    }
    fclose(fp);
    fclose(fp2);
    remove(FILE_MAP); //delete file
    rename("test.txt", FILE_MAP); //rename temporary file and it cames new file with that x in it
    return 0;
}


//open passenger list and add passenger end of the file
int add_in_passenger_list(passenger *ptr) {
    FILE *fp = fopen(FILE_LIST, "a");
    if (fp == NULL) {
        printf("\nCan't open file.\n");
        return 1; //error
    }

    fprintf(fp, "\n%s,%s,%d,%c",ptr->firstname, ptr->lastname, ptr->number, ptr->seat_character);
    fclose(fp);
    return 0;
}


//print airplane_map where reserved seats yms
void print_map() {
    char line[LINE_SIZE];
    FILE *fp = fopen(FILE_MAP, "r");
    if (fp == NULL) {
        printf("\nCan't open file.\n");
        return;
    }
    printf("\n|-----------------|\n");
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        if (line[0] != '\0') {
            printf("|  %s  |\n", line);
        }
    }
    printf("|-----------------|");

    fclose(fp);
}


//sort passengers A - Z smaller are after bigger started letters
int sort_passenger_list() {
    char line[SEATS][LINE_LENGTH];
    int count = 0;

    FILE *fp = fopen(FILE_LIST, "r");
    if (fp == NULL) {
        printf("\nCan't open file.\n");
        return 1; //error
    }
    if (fgets(line[count], sizeof(line), fp) == NULL) {
        fclose(fp);
        return 1; //open file and read first line so we don't sort header
    }

    while (!feof(fp)) {
        if (fgets(line[count], sizeof(line), fp) != NULL) {
            if (line[count][strlen(line[count]) - 1] == '\n') {
                line[count][strlen(line[count]) - 1] = '\0';
            } // remove new line
            count++;
        }
        else {
            printf("Reading was not successful.");
            return 1;
        }
    }
    fclose(fp);

    //sort names using int_cmp function
    qsort(line, count, LINE_LENGTH, int_cmp);

    printf("\n");
    for (int i = 0; i < count; i++) {
        if (line[i][0] != '\0') { //if line is empty don't print
            printf("%s\n", line[i]);
        }
    }
    return 0;

}

//used to sort array in correct form
int int_cmp(const void *a, const void *b) {
    char ca = *(const char *)a;
    char cb = *(const char *)b;
    if (ca < cb)
        return -1;
    else if (ca > cb)
        return 1;
    else
        return 0;
}

