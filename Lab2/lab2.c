#include <stdio.h>
#include <stdlib.h> 			// для exit
#include <time.h>
#include <string.h>				// strcat
#include <stdbool.h>

#include "lab2.h"

#define UPPER_LIMIT 1			// task3

#define CHECK_TIMES 2			// task5

#define CIRCLE_LIMIT 100		// task6
#define CIRCLE_COUNT 10		


#define ROOMS_COUNT 10			// task7
#define CITY_FREQUENCY 0.5		// частота встречаемости номеров с названием отеля, начинающимся на "City"
#define HOTEL_NAME_SIZE 20
#define MAX_ROOM_NUMBER 1000
#define MAX_ROOM_CAPACITY 5
#define MAX_ACCOMODATION_COST 1000000

void task1(void){
    /*
        Ввести значение 2-х целых переменных а и b. Направить два указателя на эти
        переменные. С помощью указателя увеличить значение переменной а в 2 раза. Затем
        поменять местами значения переменных а и b через их указатели.
    */
    int a, b, temp;
    int *p1, *p2;

    printf("Enter integer values for a and b: ");
    scanf("%d %d", &a,&b);

    p1 = &a;    // направляем указатели
    p2 = &b;

    *p1 *= 2;

    temp = *p1;     // меняем значения местами
    *p1 = *p2;
    *p2 = temp;

    printf("a: %d\nb: %d", *p1,*p2);
}

void task2(void){
    /*
        Описать 2 указателя на целый тип. Выделить для них динамическую память. Ввести
        значения в выделенную память с клавиатуры. Уменьшить в 2 раза 1-ую переменную.
    */
    int *p1 = (int*)calloc(1, sizeof(int));			// выделяем память под указатели
    if(p1 == NULL){
        printf("Can't allocate memory\n");
        exit(0);
    }
    int *p2 = (int*)calloc(1, sizeof(int));
    if(p2 == NULL){
        printf("Can't allocate memory\n");
        exit(0);
    }
    
    printf("Enter integer values for a and b: ");	
    scanf("%d %d", p1,p2);						// считываем значения

    *p1 /= 2;
    printf("a: %d\nb: %d", *p1,*p2);

	free(p1);
	free(p2);
}

void task3(void){
    /*
        Создать динамические массивы, используя указатели. Задан одномерный массив а
        (n). Найти количество, все номера и произведение элементов массива меньших 1.
    */
    int n, count;
    double product;
    count = 0;
    product = 1.0;

    do{														// считываем размер массива
        printf("\nEnter the size of array: ");
        scanf("%d", &n);
        if(n <= 0){
            printf("Array size should be positive integer");
        }
    }while(n <= 0);

    double *a1 = (double*)calloc(n, sizeof(double));
    if(a1 == NULL){
        printf("Can't allocate memory\n");
        exit(0);
    }

    int *less1_indexes = (int*)calloc(n, sizeof(int));		// создаем массив для элементов, меньших 1
    if(less1_indexes == NULL){
        printf("Can't allocate memory\n");
        exit(0);
    }

    for(int i = 0; i < n; i++){								// ищем элементы, считаем количество и произведение 
        printf("\nEnter element №%d of the array: ", i+1);
        scanf("%lf", a1+i);
        if(a1[i] < UPPER_LIMIT){
            less1_indexes[count] = i;
            product *= a1[i];
            ++count;
        }
    }

    printf("\n\nThe entered array is:\n");
    for(int i = 0; i < n; i++){
        printf("%lf ",a1[i]);
    }

    if(count == 0){
        printf("\n\nThere are no numbers less than 1\n\n");
    }
    else{
        printf("\n\nElements less than 1 have sequence numbers:\n");		// если элементы есть, выводим
        for(int i = 0; i < count; i++){
            printf("%d ", less1_indexes[i]+1);
        }
        printf("\n\nAmount of numbers less than 1 is: %d\nProduct of numbers less than 1: %lf\n\n", count, product);
		free(less1_indexes);
	}

	free(a1);
}

void task4(void){
    /*
        Создать динамические массивы, используя указатели. Дан массив b (n). Переписать в
        массив C(n) положительные элементы массива b(n), умноженные на 5 (со сжатием,
        без пустых элементов внутри) Затем упорядочить методом «выбора и перестановки»
        по возрастанию новый массив.
    */
    int n, positive_counter, c_ind;
    double *b, *C;

    do{
        printf("\nEnter the size of array: ");
        scanf("%d", &n);
        if(n <= 0){
            printf("Array size should be positive integer");
        }
    }while(n <= 0);

    b = (double*)calloc(n, sizeof(double));
    if(b == NULL){
        printf("Can't allocate memory\n");
        exit(0);
    }

    positive_counter = 0;
    for(int i = 0; i < n; i++){
        printf("\nEnter element №%d of the array: ", i+1);
        scanf("%lf", b+i);
        if(b[i] > 0){
            ++positive_counter;
        }
    }
    if(positive_counter == 0){
		printf("\n\nThere are no positive elements in the array!\n");
	}
	else{
    	C = (double*)calloc(positive_counter, sizeof(double));
    	if(C == NULL){
    	    printf("Can't allocate memory\n");
    	    exit(0);
    	}
	
    	c_ind = 0;
    	for(int i = 0; i < n; i++){
    	    if(b[i] > 0){
    	        C[c_ind] = 5 * b[i];
    	        ++c_ind;
    	    }
		}
    	selection_sort(C, positive_counter);				

    	printf("\n\nThe result array(positive * 5): \n");
    	for(int i = 0; i < positive_counter; i++){
    	    printf("%lf ", C[i]);
    	}
		free(C);
	}

	free(b);
}

void selection_sort(double *C, int n){
    double temp;

    for (int i = 0; i < n - 1; i++)
    {
        int min_ind = i;
        for (int j = i + 1; j < n; j++)		// ищем индекс очередного минимального элемента
        {
            if (C[j] < C[min_ind])			
            {
                min_ind = j;
            }
        }
        if (min_ind != i)					// если минимальный не на своем месте, переставляем с текущим
        {
            temp = C[i];
            C[i] = C[min_ind];
            C[min_ind] = temp;
        }
    }
}

void task5(void){
    /*
        Необходимо реализовать функции таким образом, чтобы значение возвращалось не через return,
        а через аргументы функции по указателю. Для создаваемой функции необходимо: подобрать имя;
        указать тип функции; выбрать имена и типы входных параметров; описать тело функции с
        обязательным оператором в конце; в главной программе вызвать созданную функцию два раза с
        различными входными данными. Вывести результаты в главной программе
    
        1. Создать функцию, которая возвращает меньшее из двух данных чисел. 
    */ 
    double d1,d2,min_d;

    for(int i = 0; i < CHECK_TIMES; i++){
        printf("\nEnter two numbers: ");
        scanf("%lf %lf", &d1, &d2);

        min_of_two(d1,d2,&min_d);
        printf("\nSmaller of %lf and %lf is %lf", d1, d2, min_d);
    }
}

void min_of_two(double a, double b, double *res){
    *res = a < b ? a : b;
}

void task6(void){
    /*
        Определить комбинированный (структурный) тип, описывающий окружность и
        состоящий из двух полей: «радиус» и «центр». Поле «центр» в свою очередь состоит
        еще из двух полей: «координата X» и «координата Y». Ввести информацию по 10
        окружностям. Вывести координаты центра окружности, чей радиус самой большой
    */
    srand(time(NULL));

    CIRCLE** family = NULL;
    double temp_radius, max_radius = 0.0;
    int max_circle_index = 0;
    
    family = (CIRCLE**)calloc(CIRCLE_COUNT, sizeof(CIRCLE*));

    for (int i = 0; i < CIRCLE_COUNT; i++) {
        add_circle(&family[i], CIRCLE_LIMIT);
    }

    printf("\n------ %d GENERATED CIRCLES ----------", CIRCLE_COUNT);

    for (int i = 0; i < CIRCLE_COUNT; i++) {
        print_circle_info(family[i]);
        temp_radius = get_circle_radius(family[i]);
        if(temp_radius > max_radius){
            max_radius = temp_radius;
            max_circle_index = i;
        }
    }

    printf("\n------- CIRCLE WITH MAX RADIUS -------");
    print_circle_info(family[max_circle_index]);

    for (int i = 0; i < CIRCLE_COUNT; i++) {
        release_circle_info(family[i]);
    }
    free(family);
}

void add_circle(CIRCLE **circle, int limit){						
    *circle = (CIRCLE*)calloc(1, sizeof(CIRCLE));
    if(*circle == NULL){
        printf("Can't allocate memory\n");
        exit(0);
    }
    (*circle)->center = (COORDINATES*)calloc(1, sizeof(COORDINATES));
    if((*circle)->center == NULL){
        printf("Can't allocate memory\n");
        exit(0);
    }
    (*circle)->radius = (double)rand()/RAND_MAX * limit;
    (*circle)->center->x = ((double)rand()/RAND_MAX*2.0-1.0)*limit;	// генерим координаты от -limit до +limit
    (*circle)->center->y = ((double)rand()/RAND_MAX*2.0-1.0)*limit;
}

void print_circle_info(CIRCLE *circle){
    printf("\nThe radius of the circle is: %lf", circle->radius);
    printf("\nX coordinate of the circle center: %lf", circle->center->x);
    printf("\nY coordinate of the circle center: %lf\n", circle->center->y);
}

double get_circle_radius(CIRCLE *circle){
    return circle->radius;
}

void release_circle_info(CIRCLE *circle){
    free(circle->center);				// освобождаем память
    free(circle);
}


void task7(void){
    /*
        Определить структурный тип, описывающий гостиничный номер (название
        гостиницы, номер, комфортность (люкс, полулюкс стандарт, эконом), количество
        человек, стоимость). Заполнить структурный массив 10-ю записями. Переписать из
        исходного массива в другой массив, информацию только о тех гостиничных номерах,
        название гостиницы которых начинается с сочетания букв «City». Затем новый
        массив отсортировать по номеру. (рационально переставлять все поля структуры
        разом)
    */
    APARTMENT ** rooms = NULL;
	APARTMENT ** city_rooms = NULL;

    create_rooms(&rooms, ROOMS_COUNT);

	printf("\n------------- GENERATED ROOMS ----------------");
	display_rooms(rooms, ROOMS_COUNT);

	int city_amount = copy_city_rooms(rooms, &city_rooms);

	printf("\n\n------------- \"CITY\" ROOMS ----------------");
	display_rooms(city_rooms, city_amount);

	sort_rooms(&city_rooms, city_amount);

	printf("\n\n----- SORTED BY NUMBER \"CITY\" ROOMS ---------");
	display_rooms(city_rooms, city_amount);

	release_rooms(rooms, ROOMS_COUNT);			// освобождаем память
	release_rooms(city_rooms, city_amount);
}

void create_rooms(APARTMENT *** rooms, int amount){

	srand(time(NULL));											// выделяем память под массив и заполняем
	*rooms = (APARTMENT**)calloc(amount, sizeof(APARTMENT*));
	if(rooms == NULL){
    	printf("Can't allocate memory\n");
    	exit(0);
	}

	for (int i = 0; i < amount; i++) {
		add_room(&((*rooms)[i]));
	}
}

void add_room(APARTMENT ** room){
	int start_ind;

	*room = (APARTMENT*)calloc(1, sizeof(APARTMENT));			// выделяем память под структуру
	if(*room == NULL){
	    printf("Can't allocate memory\n");
	    exit(0);
	}

	(*room)->hotel_name = (char*)calloc(HOTEL_NAME_SIZE, sizeof(char));	// память для названия отеля
	if((*room)->hotel_name == NULL){
	    printf("Can't allocate memory\n");
	    exit(0);
	}

	start_ind = 0;
	if((double)rand()/RAND_MAX < CITY_FREQUENCY){								
		strcat((*room)->hotel_name,"City");					// если карта легла, добавляем City в начало названия отеля
		start_ind = 4;
	}

	for (int i = start_ind; i < HOTEL_NAME_SIZE; i++) {
		(*room)->hotel_name[i] = '0' + rand() % 72;			// генерим остаток названия отеля
	}
	(*room)->hotel_name[HOTEL_NAME_SIZE - 1] = '\0';		// последний штрих

	(*room)->number = rand()%MAX_ROOM_NUMBER;				// генерим остальные поля
	(*room)->capacity = rand()%(MAX_ROOM_CAPACITY-1) + 1;		
	(*room)->accomodation_cost = rand()% MAX_ACCOMODATION_COST;
	
	switch(rand()%4){
		case 0:
			(*room)->comfortability = ECONOM;
			break;
		case 1:
			(*room)->comfortability = STANDARD;
			break;
		case 2:
			(*room)->comfortability = JUNIOR_SUITE;
			break;
		case 3:
			(*room)->comfortability = SUITE;
			break;
	}
}

void display_rooms(APARTMENT ** rooms, int amount){
	for (int i = 0; i < amount; i++) {
		print_room_info(rooms[i]);
	}
}

int copy_city_rooms(APARTMENT ** rooms, APARTMENT *** city_rooms){
	int counter = 0;
	const char c[] = "City";
	int * city_indexes = (int*)calloc(ROOMS_COUNT, sizeof(int));	// массив для индексов комнат 
																	// с названием отеля, начинающегося на "City"
	for(int i = 0; i < ROOMS_COUNT; i++){				
		bool is_equal = true;							// ищем комнаты, считаем количество, заносим индексы

		for(int j = 0; j < 4;j++){
			if(c[j] != (rooms[i]->hotel_name)[j]){		// сравниваем названия отелей
				is_equal = false;
			}
		}
		if(is_equal){
			city_indexes[counter] = i;
			++counter;
		}
	}

	*city_rooms = (APARTMENT**)calloc(counter, sizeof(APARTMENT*));
	if(city_rooms == NULL){
		printf("Can't allocate memory\n");
		exit(0);
	}

	for (int i = 0; i < counter; i++) {					// переставляем все поля структуры
		(*city_rooms)[i] = rooms[city_indexes[i]];
	}
	return counter;
}

void sort_rooms(APARTMENT *** rooms, int n){
	APARTMENT * temp;
	for (int i = 0; i < n - 1; i++)					// сортировка выбором, только в профиль
	{
	    int min_ind = i;
	    for (int j = i + 1; j < n; j++)
	    {
	        if ((*rooms)[j]->number < (*rooms)[min_ind]->number)
	        {
	            min_ind = j;
	        }
	    }
	    if (min_ind != i)
	    {
	        temp = (*rooms)[i];
	        (*rooms)[i] = (*rooms)[min_ind];
	        (*rooms)[min_ind] = temp;
	    }
	}
}

void print_room_info(APARTMENT * room){
	printf("\n\nHotel name: %s", room->hotel_name);		// вывод информации о комнате
	printf("\nRoom number: %u", room->number);
	printf("\nRoom type: ");

	switch(room->comfortability){
		case ECONOM:
			printf("\"Econom\"");
			break;
		case STANDARD:
			printf("\"Standard\"");
			break;
		case JUNIOR_SUITE:
			printf("\"Junior suite\"");
			break;
		case SUITE:
			printf("\"Suite\"");
			break;
	}

	printf("\nRoom capacity: %d", room->capacity);
	printf("\nAccomodation cost: %u", room->accomodation_cost);

}

void release_rooms(APARTMENT ** rooms, int amount){			// освобождаем память
	for(int i = 0; i < amount; i++){
		release_room_info(rooms[i]);
	}
	free(rooms);
}

void release_room_info(APARTMENT * room){
	free(room->hotel_name);
	free(room);
}