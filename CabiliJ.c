#include <stdio.h> //standard input-output library
#include <string.h> //for string functions
#include <windows.h> //for system commands
#include <conio.h> //for getch()

#include "func.c"


int
main()
{
    char mode = 'b'; //start the game mode at the main menu
    int nQuestions = 0;
    struct question list[listSize]; //struct array for 50 questions

    do //make main menu a mode, include it in one of the cases
    {
        fflush(stdin);
        switch (mode)
        {
            case 'b': 
            case 'B':
                system("cls");
                mainMenu(&mode);
                break;
            case 'm':
            case 'M':
                if (getPassword(&mode) == 2)
                    manageData(&mode, list, &nQuestions);
                break;
            case 'p':
            case 'P':
                //for play
                break;
            default:
                printf("Invalid input. Please Try again.\n");
                Sleep(1000);
                mode = 'b';
                break;
        }

    } while (!(mode == 'e' || mode == 'E'));
    
    //exit 

    system("cls");
    printf("Thank you for playing!");   
    
    

    return 0; 
}