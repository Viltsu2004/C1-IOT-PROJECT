#ifndef C1_IOT_PROJECT_ARPLANE_PROTOS_AND_STRUCT_H
#define C1_IOT_PROJECT_ARPLANE_PROTOS_AND_STRUCT_H

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
int check_seat(passenger *ptr);
void print_map();
int add_in_passenger_list(passenger *ptr);

#endif //C1_IOT_PROJECT_ARPLANE_PROTOS_AND_STRUCT_H