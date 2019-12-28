/*
 *   Copyright (c) 2019 
 *   All rights reserved.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/**
 * ------------------------------
 * 
 * Initializing Custom Function.
 * 
 * ------------------------------
 */
int login();
int main_menu();
int riddle_menu();
void signup();
void add_riddle();
void update_riddle();
int get_no_of_riddles();
void latest_suggestions();
void all_suggestions();
void bad_reviews();
void all_reviews();
/**
 * --------------------------------
 * 
 * END Initializing Custom Function
 * 
 * --------------------------------
 */
/**
 * --------------------
 *
 * Defining Struct
 * 
 * --------------------
 */
typedef struct
{
    char have_name[50];
    char have_email[50];
    char require_password[50];
} admin;
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
 * --------------------
 *
 * END Defining Struct
 * 
 * --------------------
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
    int login_status;
    //LogIn
    printf("\n\n_________________________________________________________________________________________________________\n\n");
    printf("\n\t\t\t\t\t\t\t\t Admin Portal\n LogIn Here!\n");
    printf("\n\n_________________________________________________________________________________________________________\n\n");
    while ((login_status = login()) != 1)
    {
        printf("\n\n_________________________________________________________________________________________________________\n\n");
        printf("\n\t\t\t\tWrong Email or password, Try Again!\n");
        printf("\n\n_________________________________________________________________________________________________________\n\n");
    }
    // Main Menu
    switch (main_menu())
    {
    case 1:
        signup();
        break;
    case 2:
        riddle_menu();
        break;
    case 3:
        latest_suggestions();
        break;
    case 4:
        all_suggestions();
        break;
    case 5:
        // bad_reviews();
        break;
    case 6:
        // all_reviews();
        break;
    }

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
 * @function: login();
 * This function asks for 
 * email id and password 
 * and checks whether the
 * admin exists or not
 * @param: NULL;
 * @return: int;
 */

int login()
{
    // File Pointers
    FILE *adminptr;

    //opening file
    if ((adminptr = fopen("admin.dat", "rb")) == NULL)
    {
        printf("\nCannot Open File: admin.dat\n");
    }
    else
    {
        // rewind(adminptr);
        char email[50], password[50];
        admin retrievedinfo;
        // Asking User to Enter Data
        printf("\nEnter email:\t");
        scanf(" %[^\n]%*c", email);
        printf("\nEnter password:\t");
        scanf(" %[^\n]%*c", password);
        printf("\n\n_________________________________________________________________________________________________________\n\n");

        fread(&retrievedinfo, sizeof(admin), 1, adminptr);
        while (!feof(adminptr))
        {
            bool emailbool = strcmp(email, retrievedinfo.have_email);
            bool passwordbool = strcmp(password, retrievedinfo.require_password);

            if (emailbool == 0 && passwordbool == 0)
            {
                fclose(adminptr);
                printf("\n\n_________________________________________________________________________________________________________\n\n");
                printf("\n\t\t\t\t\t Login Successfully! \n\n\t\t\t\t\t\t WELCOME %s! \n", retrievedinfo.have_name);
                printf("\n\n_________________________________________________________________________________________________________\n\n");
                return 1;
            }
            fread(&retrievedinfo, sizeof(admin), 1, adminptr);
        }
        fclose(adminptr);
        return 0;
    }
}
/**
 * ------------------------------------------------------------------------------------------------------
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
    printf("\n Press \"1\" To add another Admin:");
    printf("\n Press \"2\" To change the riddles:");
    printf("\n Press \"3\" To see latest suggestions");
    printf("\n Press \"4\" To see All suggestions");
    printf("\n Press \"5\" For latest Reviews");
    printf("\n Press \"6\" FOr all Reviews:\t");
    scanf("%d", &option);
    printf("\n\n_________________________________________________________________________________________________________\n\n");
    if (option >= 1 && option <= 6)
    {
        return option;
    }
    printf("\n\n\t\t\t\t\tThis Option Does not Exist:\n\n");
    printf("\n\n_________________________________________________________________________________________________________\n\n");
    main_menu();
}
/**
 * ------------------------------------------------------------------------------------------------------
 */
/**
 * @function: signup();
 * This FUnction 
 * @param: NULL
 * @return: NULL;
 */
void signup()
{
    // File Pointers
    FILE *adminptr;

    //opening file
    if ((adminptr = fopen("admin.dat", "rb")) == NULL)
    {
        printf("\nCannot Open File: admin.dat\n");
    }
    else
    {
        admin new_admin;
        admin existing_admin;
        printf("\n\n_________________________________________________________________________________________________________\n\n");
        printf("\n\t\t\t\t\t SignUp Here!\n\n");
        printf("\n\n_________________________________________________________________________________________________________\n\n");

        printf("\n Enter Your Name:\t");
        scanf(" %[^\n]%*c", new_admin.have_name);
        printf("\n Enter Your email:\t");
        scanf(" %[^\n]%*c", new_admin.have_email);
        fread(&existing_admin, sizeof(admin), 1, adminptr);
        while (!feof(adminptr))
        {
            bool email_exists = strcmp(existing_admin.have_email, new_admin.have_email);
            if (email_exists == 0)
            {
                printf("\nError!!!\n\n Email Address Already in Use. Please Try Again\n");
                printf("\n\n_________________________________________________________________________________________________________\n\n");
                fclose(adminptr);
                signup(adminptr);
            }
            fread(&existing_admin, sizeof(admin), 1, adminptr);
        }
        fclose(adminptr);
        printf("\n Enter Your Password:\t");
        scanf(" %[^\n]%*c", new_admin.require_password);
        printf("\n\n_________________________________________________________________________________________________________\n\n");

        //opening file
        adminptr = fopen("admin.dat", "ab");
        fwrite(&new_admin, sizeof(admin), 1, adminptr);
        printf("\n\t\t\t\t SignedUp Successfully!\n Login as an Admin");
        printf("\n\n_________________________________________________________________________________________________________\n\n");
        fclose(adminptr);
        main();
    }
}
/**
 * ------------------------------------------------------------------------------------------------------
 */

/**
 * @function: riddle_menu();
 * This Function is triggered
 * when user Selects to make 
 * changes in riddle'S Files.
 * @param: Null
 * @return: int;
 */
int riddle_menu()
{
    int option;
    printf("\n\n_________________________________________________________________________________________________________\n\n");
    printf("\nPress \"1\" To Add a new Riddle:\n");
    printf("\nPress \"2\" To update an existing Riddle:\n");
    printf("\nPress \"3\" To GO Back:");
    scanf(" %d", &option);
    printf("\n\n_________________________________________________________________________________________________________\n\n");
    if (option == 1)
    {
        add_riddle();
    }
    else if (option == 2)
    {
        update_riddle();
    }
    else if (option == 3)
    {
        main_menu();
    }
    else
    {
        printf("\n\t\t\t\tThis Option Does NOt Exist\n\n");
        printf("\n\n_________________________________________________________________________________________________________\n\n");
        riddle_menu();
    }
}

/**
 * ------------------------------------------------------------------------------------------------------
 */

/**
 * @function: add_riddle();
 * This Function triggers when
 * admin choose to add a new riddle
 * in riddle's file.
 * @param: Null
 * @return: NULL;
 */
void add_riddle()
{
    // defining struct
    riddle new_riddle = {0, "", "", "", "", "", 0}, existing_riddle = {0, "", "", "", "", "", 0};
    //file pointer
    FILE *riddleptr;

    //opening file
    if ((riddleptr = fopen("riddles.dat", "rb")) == NULL)
    {
        printf("\nFile Does Not Exist\n");
    }
    else
    {
        //To get the last riddle number from the file riddle.dat
        fread(&existing_riddle, sizeof(riddle), 1, riddleptr);
        while (!feof(riddleptr))
        {
            fread(&existing_riddle, sizeof(riddle), 1, riddleptr);
        }
        fclose(riddleptr);

        new_riddle.number = existing_riddle.number + 1;
        //opening file
        riddleptr = fopen("riddles.dat", "rb");
        // getting data for new riddle from user
        printf("\n\n_________________________________________________________________________________________________________\n\n");
        printf("\n Enter Riddle's Statement:\t");
        scanf(" %[^\n]%*c", new_riddle.statement);
        printf("\n\n_________________________________________________________________________________________________________\n\n");
        // Comparing new riddle with riddles from files
        fread(&existing_riddle, sizeof(riddle), 1, riddleptr);
        while (!feof(riddleptr))
        {
            bool riddle_exists = strcmp(new_riddle.statement, existing_riddle.statement);
            if (riddle_exists == 0)
            {
                printf("\n\t\t\t\tRiddle already exists!\n");
                printf("\n\n_________________________________________________________________________________________________________\n\n");
                riddle_menu();
            }
            fread(&existing_riddle, sizeof(riddle), 1, riddleptr);
        }
        fclose(riddleptr);
        printf("\n Enter Option 1:\t");
        scanf(" %[^\n]%*c", new_riddle.option1);
        printf("\n Enter Option 2:\t");
        scanf(" %[^\n]%*c", new_riddle.option2);
        printf("\n Enter Option 3:\t");
        scanf(" %[^\n]%*c", new_riddle.option3);
        printf("\n Enter Option 4:\t");
        scanf(" %[^\n]%*c", new_riddle.option4);
        printf("\n Enter Correct Option:\t");
        scanf(" %d", &new_riddle.correct_option);
        printf("\n\n_________________________________________________________________________________________________________\n\n");
        riddleptr = fopen("riddles.dat", "ab");
        fwrite(&new_riddle, sizeof(riddle), 1, riddleptr);
        fclose(riddleptr);
        riddle_menu();
    }
}

/**
 * ------------------------------------------------------------------------------------------------------
 */

/**
 * @function: update_riddle();
 * This Function triggers when 
 * admin choose to update an 
 * existing riddle
 * @param: NULL
 * @return: NULL;
 */
void update_riddle()
{
    int riddle_number = 0;
    // defining struct
    riddle existing_riddle = {0, "", "", "", "", "", 0};
    //file pointer
    FILE *riddleptr;
    printf("\n\n_________________________________________________________________________________________________________\n\n");
    printf("Enter Riddle Number You Want to update:\t");
    scanf(" %d", &riddle_number);
    printf("\n\n_________________________________________________________________________________________________________\n\n");
    //opening file
    if ((riddleptr = fopen("riddles.dat", "rb+")) == NULL)
    {
        printf("Riddles file does Not exist!");
    }
    else
    {
        fseek(riddleptr, (riddle_number - 1) * sizeof(riddle), SEEK_SET);
        fread(&existing_riddle, sizeof(riddle), 1, riddleptr);
        if (existing_riddle.number != riddle_number)
        {
            printf("\nRiddle Doesn't exist!\n");
            printf("\n\n_________________________________________________________________________________________________________\n\n");
            fclose(riddleptr);
        }
        else
        {

            printf("\n Enter Riddle's Updated Statement:\t");
            scanf(" %[^\n]%*c", existing_riddle.statement);
            printf("\n Enter Option 1:\t");
            scanf(" %[^\n]%*c", existing_riddle.option1);
            printf("\n Enter Option 2:\t");
            scanf(" %[^\n]%*c", existing_riddle.option2);
            printf("\n Enter Option 3:\t");
            scanf(" %[^\n]%*c", existing_riddle.option3);
            printf("\n Enter Option 4:\t");
            scanf(" %[^\n]%*c", existing_riddle.option4);
            printf("\n Enter Correct Option:\t");
            scanf(" %d", &existing_riddle.correct_option);
            printf("\n\n_________________________________________________________________________________________________________\n\n");
            fseek(riddleptr, (existing_riddle.number - 1) * sizeof(riddle), SEEK_SET);
            fwrite(&existing_riddle, sizeof(riddle), 1, riddleptr);
            fclose(riddleptr);
            riddle_menu();
        }
    }
}

/**
 * ------------------------------------------------------------------------------------------------------
 * ------------------------------------------------------------------------------------------------------
 */

/**
 * @function: latest_suggestions()
 * This function Shows all the latest suggestions
 * on the screen.
 * @param: NULL
 * @return: NULL
 */
void latest_suggestions(){
    FILE *suggestedptr;
    riddle new_riddle;
    suggested_riddle existing;
    int count = 0;
    if ((suggestedptr = fopen("suggested_riddles.dat", "rb")) == NULL)
    {
        printf("\n Cannot Open File\n");
    }
    else
    {
        fread(&existing, sizeof(suggested_riddle), 1, suggestedptr);
        while (!feof(suggestedptr))
        {
            if (existing.status == 1)
            {
                char option;
                printf("\n Suggestion from:\t%s", existing.email);
                printf("\n Riddle Statement:\t%s", existing.statement);
                printf("\n Option 1:\t %s", existing.option1);
                printf("\n Option 2:\t %s", existing.option2);
                printf("\n Option 3:\t %s", existing.option3);
                printf("\n Option 4:\t %s", existing.option4);
                printf("\nCorrect Option:\t %d", existing.correct_option);
                printf("\n\nWould You Like to add this riddle:\n\n \"y\" - Yes\t\"N\" - No:\t");
                scanf(" %c", &option);
                if (option == 'y' || option == 'Y')
                {
                    FILE *riddleptr;
                    
                    if ((riddleptr = fopen("riddles.dat", "ab")) == NULL)
                    {
                        printf("\n Cannot Open File\n");
                    }
                    else
                    {
                        new_riddle.number = get_no_of_riddles() + 1;
                        strcpy(new_riddle.statement, existing.statement);
                        strcpy(new_riddle.option1, existing.option1);
                        strcpy(new_riddle.option2, existing.option2);
                        strcpy(new_riddle.option3, existing.option3);
                        strcpy(new_riddle.option4, existing.option4);
                        new_riddle.correct_option = existing.correct_option;
                        fwrite(&new_riddle, sizeof(riddle), 1, riddleptr);
                        fclose(riddleptr);
                    }
                }

                existing.status = 0;
                fseek(suggestedptr, ((-1) * sizeof(suggested_riddle)), SEEK_CUR);
                fwrite(&existing, sizeof(suggested_riddle), 1, suggestedptr);
            }
            count++;
            fread(&existing, sizeof(suggested_riddle), 1, suggestedptr);
        }
    }
    fclose(suggestedptr);
}
/**
 * ------------------------------------------------------------------------------------------------------------------------------
 * ------------------------------------------------------------------------------------------------------------------------------
 */
/**
 * @function: latest_suggestions()
 * This function Shows all the latest suggestions
 * on the screen.
 * @param: NULL
 * @return: NULL
 */
void all_suggestions()
{
    FILE *suggestedptr;
    suggested_riddle existing;
    int count = 0;
    if ((suggestedptr = fopen("suggested_riddles.dat", "rb")) == NULL)
    {
        printf("\n Cannot Open File\n");
    }
    else
    {
        fread(&existing, sizeof(suggested_riddle), 1, suggestedptr);
        while (!feof(suggestedptr))
        {
            printf("\n Suggestion from:\t%s", existing.email);
            printf("\n Riddle Statement:\t%s", existing.statement);
            printf("\n Option 1:\t %s", existing.option1);
            printf("\n Option 2:\t %s", existing.option2);
            printf("\n Option 3:\t %s", existing.option3);
            printf("\n Option 4:\t %s", existing.option4);
            printf("\nCorrect Option Number:\t %d", existing.correct_option);
        }
    }
    fclose(suggestedptr);
}
/**
 * -----------------------------------------------------------------------------------------------------------
 * -----------------------------------------------------------------------------------------------------------
 */
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
 * ---------------------------------
 * 
 * END Definition of Custom Function
 * 
 * ---------------------------------
 */