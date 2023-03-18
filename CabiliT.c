#include <stdio.h> //standard input-output library
#include <string.h> //for string functions
#include <windows.h> //for system commands
#include <conio.h> //for getch()

#include "func.c"


int
main()
{
    char mode = 'b'; //start the game mode at the main menu


    do //make main menu a mode, include it in one of the cases
    {
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
                    manageData(&mode);
                break;
            default:
                break;
        }

    } while (!(mode == 'e' || mode == 'E'));
    
    //exit 

    system("cls");
    printf("Thank you for playing!");   
    
    

    return 0; 
}