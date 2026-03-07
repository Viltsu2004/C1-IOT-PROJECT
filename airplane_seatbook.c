#include <string.h>
#include "arplane_protos_and_struct.h"

//main file
int main() {
    passenger pas = {0};
    passenger *ptr = &pas;

    //ask name of passenger and seat where passenger wants to sit
    while (strcmp(ptr->firstname, "stop") != 0) {
        while (user_input_name(ptr->firstname, "firstname") != 0) {}
        if (strcmp(ptr->firstname, "stop") != 0) {
            while (user_input_name(ptr->lastname, "lastname") != 0) {}

            do {
                while (user_input_number(ptr) != 0) {}
                while (user_input_seat(ptr) != 0){}
            }while (check_seat(ptr) != 0);
            add_in_passenger_list(ptr);
            print_map();
        }
    }
}