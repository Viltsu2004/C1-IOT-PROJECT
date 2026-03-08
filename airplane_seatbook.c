#include <string.h>
#include "arplane_protos_and_struct.h" //h file where is protos and struct and defines

//main file
int main() {
    passenger pas = {0}; //first no data is included
    passenger *ptr = &pas; //creates pointer that can bee send to functions

    //print menu
    print_menu();

    //ask name of passenger and seat where passenger wants to sit
    while (strcmp(ptr->firstname, "stop") != 0) { //if user enters stop in first name program stops
        while (user_input_name(ptr->firstname, "firstname") != 0) {} //do ass long ass user enters valid input
        if (strcmp(ptr->firstname, "stop") != 0) {
            while (user_input_name(ptr->lastname, "lastname") != 0) {} //do ass long ass user enters valid input

            do {
                while (user_input_number(ptr) != 0) {} //do ass long ass user enters valid input
                while (user_input_seat(ptr) != 0){} //do ass long ass user enters valid input
            }while (check_seat(ptr) != 0); //ask seat again if it's already taken
            add_in_passenger_list(ptr); //add passenger to list
            print_map(); // print seat map
            sort_passenger_list(); // sort passengers and print sorted list
        }
    }
}