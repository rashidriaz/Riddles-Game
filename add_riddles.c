/*
 *   Copyright (c) 2019
 *   All rights reserved.
 */
#include <stdio.h>
typedef struct
{
    int number;
    char statement[1000];
    char option1[50];
    char option2[50];
    char option3[50];
    char option4[50];
    int correct_option;
} riddle;

int main()
{

    FILE *fptr;
    riddle new = {1, "", "", "", "", "", 0};
    fptr = fopen("riddles.dat", "rb");
    fread(&new, sizeof(riddle), 1, fptr);
    while (!feof(fptr))
    {
        fread(&new, sizeof(riddle), 1, fptr);
    }
    fclose(fptr);
    new.number++;
    fptr = fopen("riddles.dat", "ab");
    while (!feof(stdin))
    {
        printf("\nEnter Riddles Statement:\t");
        scanf(" %[^\n]%*c", new.statement);
        printf("\nEnter Riddles option1:\t");
        scanf(" %[^\n]%*c", new.option1);
        printf("\nEnter Riddles option2:\t");
        scanf(" %[^\n]%*c", new.option2);
        printf("\nEnter Riddles option3:\t");
        scanf(" %[^\n]%*c", new.option3);
        printf("\nEnter Riddles option4:\t");
        scanf(" %[^\n]%*c", new.option4);
        printf("\nEnter Riddles Correct option:\t");
        scanf(" %d", &new.correct_option);
        fwrite(&new, sizeof(riddle), 1, fptr);
        new.number++;
    }
    fclose(fptr);
    return 0;
}