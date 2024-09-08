#include <stdio.h>
#include <stdlib.h>         // для rand()
#include <stdbool.h>        // для bool
#include <math.h>           // для abs()
#include <time.h>           // для обновления базы ГПСЧ

#include "lab1.h"

#define DIFF(a,b) (abs(a-b))    // к заданию 1
#define NAME_MAX_LEN 30
#define SURNAME_MAX_LEN 30

#define ARR_LEN 20              // 3.1
#define ARR_MAX_VAL 10

#define MAT_LEN 6               // 3.2
#define MAT_WIDTH 8
#define MAT_MAX_VAL 20
#define K 10

#define MAX_TEXT_LEN 200        // 5

void task1(void){
    /*
        Объявить переменные, необходимые для выполнения задания.
        «Фамилия и имя» вводить с клавиатуры, остальные значения могу быть захардкожены. 
        
        ’A’; ’Меня зовут <фамилия и имя>’; 315, –27; 127.361, –574.953; 2124.
    */

    char name[NAME_MAX_LEN], surname[SURNAME_MAX_LEN];
    int v1,v2,v5;
    double v3,v4;

    printf("Enter your name and surname: ");
    scanf("%s %s", name, surname);

    v1 = 315;
    v2 = -27;
    v3 = 127.361;
    v4 = -574.953;
    v5 = 2124;

    printf("’A’;’Меня зовут %s %s’; %d, %d; %lf, %lf; %d.", name, surname, v1, v2, v3, v4, v5);
}

void task2(void){
    /*
        С клавиатуры вводятся 4 целых числа: a, b, c, d. Найти среди них пару чисел с
        минимальной по модулю разностью. Операторы цикла в программе не использовать.
    */
    int a, b, c, d, d1, d2, minDiff, t;

    printf("Enter values for a,b,c,d: ");
    scanf("%d %d %d %d", &a,&b,&c,&d);
    minDiff = DIFF(a,b);
    d1 = a;
    d2 = b;

    if ((t = DIFF(a,c))< minDiff)
    {
        d1 = a;
        d2 = c;
        minDiff = t;
    }
    else if((t = DIFF(a,d)) < minDiff)
    {
        d1 = a;
        d2 = d;
        minDiff = t;
    }
    else if((t = DIFF(b,c)) < minDiff)
    {
        d1 = b;
        d2 = c;
        minDiff = t;
    }
    else if((t = DIFF(b,d)) < minDiff)
    {
        d1 = b;
        d2 = d;
        minDiff = t;
    }
    else if((t = DIFF(c,d)) < minDiff)
    {
        d1 = c;
        d2 = d;
        minDiff = t;
    }
    printf("The minimum modulo difference between %d and %d is: %d", d1, d2, minDiff);
}

void task3_1(void){
    /* 
        a) Задан массив А(20). Определить знакопеременную сумму а1 – а2 + а3 – а4 + ….
    */

    int a[ARR_LEN];
    int total = 0;

    srand(time(NULL));      // обновляем базу для ГПСЧ

    for(int i = 0; i < ARR_LEN; i++)
    {
        a[i] = rand() % ARR_MAX_VAL;
        if(i % 2 == 0)
            total += a[i];
        else
            total -= a[i];
    }

    printf("\nThe generated array is: \n");
    for(int i = 0; i < ARR_LEN; i++)
    {
        printf("%d ", a[i]);
    }

    printf("\n\nThe value of expression is: %d\n\n", total);
}   



void task3_2(void){
    /*
        б) Просуммировать элементы матрицы Х(6,8), сумма индексов которых равна
            заданной константе К.
    */
    srand(time(NULL));
    int x[MAT_LEN][MAT_WIDTH];
    int total = 0;

    printf("\nThe generated matrix is: \n");
    for(int i = 0;i < MAT_LEN; i++)
    {
        for(int j = 0; j < MAT_WIDTH; j++)
        {
            x[i][j] = rand() % MAT_MAX_VAL;
            printf("%4d ", x[i][j]);

            if(j == MAT_WIDTH - 1)
                printf("\n");
        }
    }

    if(K < 0 || K > (MAT_WIDTH + MAT_LEN - 2))
        printf("Invalid value for K");
    else
    {
        if(K < MAT_WIDTH)
        {
            for(int i = 0, j = K; i <= (K <= MAT_LEN ? K : MAT_LEN - 1); i++, j--)
            {
                total += x[i][j];
            }
        }
        else if(K < MAT_LEN)
        {
            for(int i = K, j = 0; j <= (K <= MAT_WIDTH ? K : MAT_WIDTH - 1); i--, j++)
            {
                total += x[i][j];
            }
        }
        else
        {
            for(int i = MAT_LEN-1, j = K - i; j < MAT_WIDTH; i--, j++)
            {
                total += x[i][j];
            }
        }
    }
    
    printf("\n\nThe total sum is: %d\n\n", total);
}

void task4(void)
{
    /*
        Среди чисел 1, 1 + 1/2, 1 + 1/2 + 1/3, … найти первое, большее числа 𝑛.
    */

    double n;
    double total = 0.0;
    unsigned long long int i = 1;

    do{
        printf("Enter the value of n(n should be less than 20): ");
        scanf("%lf", &n);
    }while(n >= 20);

    while((total += 1.0/i) <= n){
        i++;
    }

    printf("\nThe last ration in sum is: 1/%llu\nThe first number greater than %lf is: %lf", i, n, total);
}

void task5(void)
{
    /*
        В произвольном тексте найти и отпечатать все слова, начинающиеся с буквы а.
    */

    char text[MAX_TEXT_LEN];
    bool scanning_a_word = false;
    bool is_letter, prev_is_letter;

    printf("Enter the text: ");
    fgets(text, MAX_TEXT_LEN, stdin);
    printf("Entered text is:\n%s", text);
    printf("\n\nWords started with 'a':\n");

    for(int i = 0; text[i] != '\0'; i++){

        is_letter = text[i] >= 'a' && text[i]<='z' || text[i] >= 'A' && text[i] <= 'Z';

        if(scanning_a_word){
            if(is_letter){
                printf("%c", text[i]);
            }
            else{
                scanning_a_word = false;
                printf(" ");
            }
        }
        else if((text[i]=='a' || text[i] == 'A')&& !prev_is_letter){ 
            // если текущий символ - 'a/A', а предыдущий не буквенный
            scanning_a_word = true;
            printf("%c", text[i]);
        }
        prev_is_letter = is_letter;
    }
}

