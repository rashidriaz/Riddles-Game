/*
 *   Copyright (c) 2019 
 *   All rights reserved.
 */

/**
 * --------------------
 * 
 * INCLUDING LIBRARIES
 * 
 * --------------------
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
/**
 * ------------------------
 * 
 * END INCLUDING LIBRARIES
 * 
 * ------------------------
 */

/**
 * ------------------------------
 * 
 * Initializing Custom Function.
 * 
 * ------------------------------
 */
int main_menu();
int login();
void signup();
void play();
int get_no_of_riddles();
int get_no_of_riddles_played();
void update_user_record();
void suggest_a_riddle();
void review();
/**
 * --------------------------------
 * 
 * END Initializing Custom Function
 * 
 * --------------------------------
 */

/**
 * ----------------------------
 * 
 * Definition of Struct
 * 
 * ----------------------------
 */
/**
 * @struct: user
 * The struct of user have attributes
 * name, email, password success points
 * and ID of riddle which they have answered.
 */
typedef struct
{
    char have_name[50];
    char have_email[50];
    char require_password[50];
    char gender[20];
    int success;
    int riddle_number[1000];
} user;
/**
 * @struct: riddle
 * The struct of riddle have attributes
 * 1. Statement of Riddle.
 * 2. Option 1 of Riddle.
 * 3. Option 2 of Riddle.
 * 4. Option 3 of Riddle.
 * 5. Option 4 of Riddle.
 * 6. Correct Option of Riddle.
 * 7. Riddle Number
 * 8. status
 */
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
/**
 * @struct: suggested_riddle
 * The STruct of Suggested riddle have attributes
 * 1. Statement of Riddle.
 * 2. Option 1 of Riddle.
 * 3. Option 2 of Riddle.
 * 4. Option 3 of Riddle.
 * 5. Option 4 of Riddle.
 * 6. Correct Option of Riddle.
 * 7. User's Email ID
 */
typedef struct
{
    char email[50];
    char statement[1000];
    char option1[50];
    char option2[50];
    char option3[50];
    char option4[50];
    int correct_option;
    int status;
} suggested_riddle;
/**
 * @struct: review
 * This struct includes following attributes:
 * 1. Rating
 * 2. Review
 * 3. Email ID
 */
typedef struct
{
    int rating;
    char comment[1000];
    char email[50];
} reviews;
/**
 * ----------------------------
 * 
 * END Definition of Struct
 * 
 * ----------------------------
 */
/**
 * ----------------------------
 * 
 * Global Variables
 * 
 * ----------------------------
 */
user active_user;
/**
 * ----------------------------------
 * 
 * END Definition Of Global Variable
 * 
 * ----------------------------------
 */
/**
 * ---------------------------
 * 
 * Main Function
 * 
 * ---------------------------
 */

int main()
{
    main_menu();
    return 0;
}

/**
 * ---------------------------
 * 
 * END Main Function.
 * 
 * ---------------------------
 */

/**
 * ------------------------------
 * 
 * Definition of Custom FUnction
 * 
 * ------------------------------
 */
/**
 * @function: main_menu();
 * This Function prints the
 * menu on the screen and ask
 * user to select one option!
 * @param: NULL;
 * @return: int;
 */
int main_menu()
{
    int option;
    printf("\n\n_________________________________________________________________________________________________________\n\n");
    printf("\nPress \"1\" For LogIn:");
    printf("\nPress \"2\" For SignUp:\t");
    printf("\n\n_________________________________________________________________________________________________________\n\n");
    scanf(" %d", &option);
    if (option == 1)
    {
        int login_status = login();
        if (login_status == 1)
        {
            for (int i = 0; i < 100; i++)
            {
                if (active_user.riddle_number[i] != 0)
                {
                    printf("\n %d \n", i);
                }
            }

            printf("\n\t\t\t\tPress Enter to Play:");
            getchar();
            printf("\n\n_________________________________________________________________________________________________________\n\n");
            printf("\n\n\t\t\t\t\t\tRiddles Game!!!\n\n");

            play();
        }
        else
        {
            printf("\n\t\t\tLogIn Failed!\tTry Again!\n\n");
            printf("\n\n_________________________________________________________________________________________________________\n\n");
            main_menu();
        }
    }
    else if (option == 2)
    {
        signup();
    }
    else
    {
        printf("\n\n\t\t\t\t\tThis Option Does not Exist:\n\n");
        printf("\n\n_________________________________________________________________________________________________________\n\n");
        main_menu();
    }
}
/**
 * ------------------------------------------------------------------------------------------------------
 */
/**
 * @function: login();
 * This function asks for 
 * email id and password 
 * and checks whether the
 * user exists or not
 * @param: NULL;
 * @return: int;
 */
int login()
{
    // File Pointers
    FILE *userptr;

    //opening file
    if ((userptr = fopen("user.dat", "rb")) == NULL)
    {
        printf("\nFile Doesn't Exist\n");
    }
    else
    {

        rewind(userptr);
        char password[50], email[50];
        user retrievedinfo = {"", "", "", "", 0, 0};
        // Asking User to Enter Data
        printf("\n\n_________________________________________________________________________________________________________\n\n");
        printf("\nEnter Email:\t");
        scanf(" %[^\n]%*c", email);
        printf("\nEnter Password:\t");
        scanf(" %[^\n]%*c", password);
        printf("\n\n_________________________________________________________________________________________________________\n\n");
        fread(&retrievedinfo, sizeof(user), 1, userptr);
        while (!feof(userptr))
        {
            bool emailbool = strcmp(email, retrievedinfo.have_email);
            bool passwordbool = strcmp(password, retrievedinfo.require_password);

            if (emailbool == 0 && passwordbool == 0)
            {
                fclose(userptr);
                strcpy(active_user.have_email, retrievedinfo.have_email);
                strcpy(active_user.have_name, retrievedinfo.have_name);
                strcpy(active_user.require_password, retrievedinfo.require_password);
                strcpy(active_user.gender, retrievedinfo.gender);

                for (int i = 0; i < 1000; i++)
                {
                    active_user.riddle_number[i] = retrievedinfo.riddle_number[i];
                }

                active_user.success = retrievedinfo.success;

                printf("\n\t\t\t\t\tLogin Successfully!\n\n\t\t\t\t\t\tWELCOME %s!\n", retrievedinfo.have_name);
                printf("\n\n_________________________________________________________________________________________________________\n\n");
                return 1;
            }
            fread(&retrievedinfo, sizeof(user), 1, userptr);
        }
        fclose(userptr);
        return 0;
    }
}
/**
 * ------------------------------------------------------------------------------------------------------
 */
/**
 * @function: signup();
 * This function triggers 
 * when a user choose to 
 * Create a new account!
 * @param: NULL
 * @return: NULL;
 */
void signup()
{
    // File Pointers
    FILE *userptr;

    //opening file
    if ((userptr = fopen("user.dat", "rb")) == NULL)
    {
        printf("Cannot Open File: User.dat");
    }
    else
    {
        printf("\n\n_________________________________________________________________________________________________________\n\n");
        user new_user;
        user existing_user;
        printf("\n\t\t\t\t\t SignUp Here!\n\n");
        printf("\n\n_________________________________________________________________________________________________________\n\n");

        printf("\n Enter Your Name:\t");
        scanf(" %[^\n]%*c", new_user.have_name);
        printf("\n Enter Your email:\t");
        scanf(" %[^\n]%*c", new_user.have_email);
        fread(&existing_user, sizeof(user), 1, userptr);
        while (!feof(userptr))
        {
            bool email_exists = strcmp(existing_user.have_email, new_user.have_email);
            if (email_exists == 0)
            {
                printf("\nError!!!\n\n Email Address Already in Use. Please Try Again\n");
                printf("\n\n_________________________________________________________________________________________________________\n\n");
                fclose(userptr);
                signup(userptr);
            }
            fread(&existing_user, sizeof(user), 1, userptr);
        }
    gender:
        printf("\n Select Gender\n\nPress\t\t\t M - Male\t F - Female\t R - Rather Not Say:\t");
        scanf("%s", new_user.gender);
        if (new_user.gender[0] == 'M' || new_user.gender[0] == 'm')
        {
            strcpy(new_user.gender, "Male");
        }
        else if (new_user.gender[0] == 'F' || new_user.gender[0] == 'f')
        {
            strcpy(new_user.gender, "Female");
        }
        else if (new_user.gender[0] == 'R' || new_user.gender[0] == 'r')
        {
            strcpy(new_user.gender, "Not Specified");
        }
        else
        {
            printf("\n\n_________________________________________________________________________________________________________\n\n");
            printf("\n\t\t\t\t Wrong Option Selected! Try Again!!\n\n");
            printf("\n\n_________________________________________________________________________________________________________\n\n");
            goto gender;
        }

        printf("\n Enter Your Password:\t");
        scanf(" %[^\n]%*c", new_user.require_password);
        printf("\n\n_________________________________________________________________________________________________________\n\n");
        fclose(userptr);
        //  Initializing riddle_number array with 0
        for (int i = 0; i < 1000; i++)
        {
            new_user.riddle_number[i] = 0;
        }
        new_user.success = 0;
        //opening file
        userptr = fopen("user.dat", "ab");
        fwrite(&new_user, sizeof(user), 1, userptr);
        fclose(userptr);
        printf("\n\n_________________________________________________________________________________________________________\n\n");
        printf("\n\t\t\t\t SignedUp Successfully!\n Login as a user");
        printf("\n\n_________________________________________________________________________________________________________\n\n");

        // LogIn
        int login_status;
    login:
        login_status = login();

        if (login_status == 1)
        {
            printf("\n\t\t\t\tPress Enter to Play:");
            printf("\n\n_________________________________________________________________________________________________________\n\n");
            getchar();
            printf("\n\n_________________________________________________________________________________________________________\n\n");
            printf("\n\n\t\t\t\t\t\tRiddles Game!!!\n\n");
            printf("\n\n_________________________________________________________________________________________________________\n\n");
            play();
        }
        else
        {
            printf("\n\t\t\tLogIn Failed!\tTry Again!\n\n");
            printf("\n\n_________________________________________________________________________________________________________\n\n");
            goto login;
        }
    }
}
/** @function: play();
 * This FUnction Triggers
 * When User wants to play
 * the game!
 * @param: NULL;
 * @return: Null;
 */

void play()
{
    int count = 1; //loop control variables
    int total_riddles_played;
    int no_of_riddles = get_no_of_riddles(), choosen_option = 0;
    float points = 0;
    riddle retrieved = {0, "", "", "", "", "", 0};
    FILE *riddleptr;
    riddleptr = fopen("riddles.dat", "rb");
    printf("\n\n_________________________________________________________________________________________________________\n\n");
    printf("\n\t\t\tEnter Option Number to answer\n");
    printf("\n\n_________________________________________________________________________________________________________\n\n");
    while (count <= 5)
    {
        srand(time(0));
        int riddle_number = (rand() % (no_of_riddles - 0 + 1)) + 1;

        if (active_user.riddle_number[riddle_number] == 1)
        {
            play();
        }
        active_user.riddle_number[riddle_number] = 1;
        fseek(riddleptr, (riddle_number - 1) * sizeof(riddle), SEEK_SET);
        fread(&retrieved, sizeof(riddle), 1, riddleptr);
        printf("\n\n_________________________________________________________________________________________________________\n\n");
        printf("\n%s\n", retrieved.statement);
        printf("1. %s\n", retrieved.option1);
        printf("2. %s\n", retrieved.option2);
        printf("3. %s\n", retrieved.option3);
        printf("4. %s\t", retrieved.option4);
        scanf(" %d", &choosen_option);
        if (choosen_option == retrieved.correct_option)
        {
            printf("\n\t\t\t\tCorrect !!\n");
            printf("\n\n_________________________________________________________________________________________________________\n\n");
            points++;
        }
        else
        {
            printf("\n\t\t\t\t Wrong !!\n\n");
            printf("\n Correct Option is:%d", retrieved.correct_option);
            printf("\n\n_________________________________________________________________________________________________________\n\n");
        }
        count++;
    }
    total_riddles_played = get_no_of_riddles_played();
    active_user.success += points;
    update_user_record();
    points = (((float)active_user.success / (float)total_riddles_played) * 100);
    printf("\n\n_________________________________________________________________________________________________________\n\n");

    printf("\nYour Current Success Percentage is:%.2f", points);

    printf("\n\n_________________________________________________________________________________________________________\n\n");
    int play_again = 0;
    printf("\n Do you want to play again?\n\n \"1\" - Yes!\t\"2\" - No!\n");
    scanf("%d", &play_again);
    if (play_again == 1)
    {
        play();
    }
    else
    {
        int suggest = 0;
        printf("Would you Like to Suggest a riddle?\n\n\"1\" - Yes\t\"2\" - No!");
        scanf("%d", &suggest);
        if (suggest == 1)
        {
            suggest_a_riddle();
        }
    }
    // review();
}

/**
 * @function: get_no_of_riddles();
 * This FUnction COunts the number
 * of riddles from a file Riddle.dat
 * @param: NULL
 * @return: int
 */
int get_no_of_riddles()
{
    FILE *riddleptr;
    riddle get_riddle = {0, "", "", "", "", "", 0};
    riddleptr = fopen("riddles.dat", "rb.dat");
    fread(&get_riddle, sizeof(riddle), 1, riddleptr);
    while (!feof(riddleptr))
    {
        fread(&get_riddle, sizeof(riddle), 1, riddleptr);
    }
    return get_riddle.number;
}
/**
 * --------------------------------------------------------------------------------------------------
 * --------------------------------------------------------------------------------------------------
 */
/**
 * @function: get_no_of_riddles_played()
 * This function gets the total number of
 * riddles user have attempted!
 * @param: NULL
 * @return: int
 */
int get_no_of_riddles_played()
{
    int count = 0;
    for (int i = 0; i < 1000; i++)
    {
        if (active_user.riddle_number[i] == 1)
        {
            count++;
        }
    }
    return count;
}

/**
 * ----------------------------------------------------------------------------------------
 * ----------------------------------------------------------------------------------------
 */
/**
 * @function: update_user_record()
 * This function update user's record
 * in file: user.dat
 * @param: NULL
 * @return: Null
 */
void update_user_record()
{
    FILE *userptr;
    user existing;
    if ((userptr = fopen("user.dat", "rb+")) == NULL)
    {
        printf("\nCannot Open fILE: USER.DAT\n");
    }
    else
    {
        fread(&existing, sizeof(user), 1, userptr);
        while (!feof(userptr))
        {
            bool email_match = strcmp(existing.have_email, active_user.have_email);
            if (email_match == 0)
            {
                for (int i = 0; i < 1000; i++)
                {
                    existing.riddle_number[i] = active_user.riddle_number[i];
                }
                existing.success = active_user.success;

                fseek(userptr, ((-1) * (sizeof(user))), SEEK_CUR);
                fwrite(&existing, sizeof(user), 1, userptr);
                break;
            }
            fread(&existing, sizeof(user), 1, userptr);
        }
        fclose(userptr);
    }
}
/**
 * @function: suggest_a_riddle()
 * This function allow user to suggest a
 * riddle.
 * @param: NULL
 * @return: NULL
 */
void suggest_a_riddle()
{
    FILE *suggestptr, *riddleptr;
    if ((suggestptr = fopen("suggested_riddles.dat", "ab")) == NULL)
    {
        printf("\nCannot Open This FIle\n");
    }
    else
    {

        suggested_riddle new_riddle;
        riddle existing;
        strcpy(new_riddle.email, active_user.have_email);

        printf("\nEnter Riddle statement:\t");
        scanf(" %[^\n]%*c", new_riddle.statement);
        if ((riddleptr = fopen("riddles.dat", "rb")) == NULL)
        {
            printf("\nCannot Open This FIle\n");
        }
        else
        {
            fread(&existing, sizeof(riddle), 1, riddleptr);
            while (!feof(riddleptr))
            {
                if (strcmp(new_riddle.statement, existing.statement) == 0)
                {
                    new_riddle.status = 0;
                }
                else
                {
                    new_riddle.status = 1;
                }
                fread(&existing, sizeof(riddle), 1, riddleptr);
            }
            fclose(riddleptr);
        }

        printf("\nEnter Option 1:\t");
        scanf(" %[^\n]%*c", new_riddle.option1);
        printf("\nEnter Option 2:\t");
        scanf(" %[^\n]%*c", new_riddle.option2);
        printf("\nEnter Option 3:\t");
        scanf(" %[^\n]%*c", new_riddle.option3);
        printf("\nEnter Option 4:\t");
        scanf(" %[^\n]%*c", new_riddle.option4);
        printf("\nEnter Correct Option Number:\t");
        scanf(" %d", &new_riddle.correct_option);
        fwrite(&new_riddle, sizeof(suggested_riddle), 1, suggestptr);
        fclose(suggestptr);
        printf("\n \t\t\t\t\tThanks For your kind suggestion!!!\n");
    }
}
/**
 * @function: review()
 * This function allow user to
 * review/rate this product!
 * @param: NULL
 * @return: NULL
 */
void review()
{
    FILE *reviewptr;
    reviews new = {0, " ", " "}, existing;
    int count = 0;
    if ((reviewptr = fopen("review.dat", "rb+")) == NULL)
    {
        printf("\nCannot Open This File\n");
    }
    else
    {
        strcpy(new.email, active_user.have_email);
        fread(&existing, sizeof(reviews), 1, reviewptr);
        while (!feof(reviewptr))
        {
            if (strcmp(new.email, existing.email) == 0)
            {
                break;
            }
            count++;
        }
    rating:
        printf("\nRate Us Between 1 - 5:\n");
        scanf("%d", &new.rating);
        if (new.rating < 1 || new.rating > 5)
        {
            printf("\nNumber Out of Range\n");
            goto rating;
        }
        printf("\n ENter Your Comments here:\t");
        scanf(" %[^\n]%*c", new.comment);
        fseek(reviewptr, (count * sizeof(reviews)), SEEK_SET);
        fwrite(&new, sizeof(reviews), 1, reviewptr);
        fclose(reviewptr);
    }
}
/**
 * ---------------------------------
 * 
 * END Definition of Custom Function
 * 
 * ---------------------------------
 */
