


typedef struct COORDINATES{
    double x, y;
}COORDINATES;

typedef struct CIRCLE{
    COORDINATES * center;
    double radius;
}CIRCLE;


typedef enum COMFORT_LEVEL{
    ECONOM,
    STANDARD,
    JUNIOR_SUITE,
    SUITE,
}COMFORT_LEVEL;

typedef struct APARTMENT{
    char * hotel_name;
    unsigned int number;
    COMFORT_LEVEL comfortability;
    unsigned char capacity;
    unsigned int accomodation_cost;
}APARTMENT;


void task1(void);
void task2(void);
void task3(void);

void task4(void);
void selection_sort(double *C, int n);

void task5(void);
void min_of_two(double a, double b, double *res);

void task6(void);
void add_circle(CIRCLE **circle, int created, int count);
void print_circle_info(CIRCLE * circle);
double get_circle_radius(CIRCLE *circle);
void release_circle_info(CIRCLE * circle);

void release_circles(CIRCLE **family, int amount);

void task7(void);
void create_rooms(APARTMENT *** rooms, int amount);
void add_room(APARTMENT ** room, int created);
void display_rooms(APARTMENT ** rooms, int amount);
void print_room_info(APARTMENT * room);
int copy_city_rooms(APARTMENT ** rooms, APARTMENT *** city_rooms);
void sort_rooms(APARTMENT *** rooms, int amount);
void release_rooms(APARTMENT ** rooms, int amount);
void release_room_info(APARTMENT * room);
