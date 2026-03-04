#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NAME_LENGTH 40
#define SEAT_CHARACTER_SIZE 2

typedef struct node {
    char name[NAME_LENGTH];
    int row_number;
    char seat_character[SEAT_CHARACTER_SIZE];
    struct node *next;
} PASSENGER_INFO;

bool menu();
bool ask_name_and_seat(PASSENGER_INFO *new_passenger, PASSENGER_INFO *head);
bool open_file(FILE *file, PASSENGER_INFO *new_passenger);
bool add_passenger_to_file();
bool print_passengers();
bool print_seat_map();
bool print_seats();

//main file
int main() {

    FILE *my_file;
    PASSENGER_INFO *head = NULL;
    char *end_loop;
    int status = true;

    //print menu for user that he knows what to do
    menu();
    //create new passenger
    PASSENGER_INFO *new_passenger = (PASSENGER_INFO *)malloc(sizeof(PASSENGER_INFO));
    //checks if malloc fails
    if (new_passenger == NULL) {
        printf("Memory allocation failed");
        return 1;
    }

    //ask name of passenger and seat where passenger wants to sit
    while (status) {
        status = ask_name_and_seat(new_passenger, head);
    }

}
bool menu() {
    printf("In this program you can reserve place form our amazing airplane.\n\n"
           "In this airplane we have 26 rows of seats and every row has 6 seat which are named by letters A-F.\n"
           "A and F seats are by the window! Best seat I think! ;)\n"
           "B and E are in the middle!! Not worth, as you know. :(\n"
           "C and D are by the aisle, which is not bad at all.\n\n\n"
           "Here you can see current reservation status: \n\n");
    if (print_seat_map() == false) {

    }
}

bool ask_name_and_seat(PASSENGER_INFO *new_passenger, PASSENGER_INFO *head) {
    char temporary_answer[NAME_LENGTH];
    new_passenger->next = NULL;
    if (head == NULL) {
        head = new_passenger;
    }
    printf("Write 'stop' to stop entering passengers,\n"
           "or give your LASTNAME and FIRSTNAME to reserve seat (example 'Meikalainen Matti'.");
    printf(">> ");
    if (fgets(temporary_answer, NAME_LENGTH, stdin) == NULL) {
        printf("Memory allocation failed");
        return false;
    }
    if (strcmp(temporary_answer, "stop") == 0) {
        return false;
    }
    return true;



    return 0;
}

bool open_file(FILE *file, PASSENGER_INFO *new_passenger) {

    return 1;
}


bool add_passenger_to_file() {

}

bool print_seat_map() {

}

bool print_passengers() {

}