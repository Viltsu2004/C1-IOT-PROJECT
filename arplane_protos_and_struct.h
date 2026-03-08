#ifndef C1_IOT_PROJECT_ARPLANE_PROTOS_AND_STRUCT_H
#define C1_IOT_PROJECT_ARPLANE_PROTOS_AND_STRUCT_H

#define FILE_MAP "airplane_map.txt" //first airplane seat map
#define FILE_LIST "passenger_list.csv"  // passenger data
#define FILE_TEMPORARY "test.txt" //file airplane_map.txt with nuw marks
#define NAME_LENGTH 40 //both names can be max
#define LINE_LENGTH 100
#define SEATS 157
#define LINE_SIZE 100 //one line can be max, used when copying lines from one another file

//asked things about one passenger
typedef struct {
    char firstname[NAME_LENGTH];
    char lastname[NAME_LENGTH];
    char seat_character;
    int number;
}passenger;

int int_cmp(const void *a, const void *b); //sorted by first name
int user_input_name(char *ptr, const char *str_type); //ask firstname and lastname -> errors if not correct
int user_input_number(passenger *ptr); //ask row number
int user_input_seat(passenger *ptr); //ask set letter A-F
int check_seat(passenger *ptr); //check if seat is available
void print_map(); //print seat map
int add_in_passenger_list(passenger *ptr); //add passenger to list
int sort_passenger_list(); //start sorting passengers
int print_menu(); //welcome text and airplane seat map

#endif //C1_IOT_PROJECT_ARPLANE_PROTOS_AND_STRUCT_H