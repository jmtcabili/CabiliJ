/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The
program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
Cabili, Johan Marlo T., DLSU ID# 12274348
*********************************************************************************************************/


#include <stdio.h> //standard input-output library
#include <string.h> //for string functions
#include <windows.h> //for system commands
#include <stdlib.h> //for rand and srand
#include <time.h> //for time(NULL)
#include <conio.h> //for getch()

#include "func.c"


int
main()
{

    /*
        main() serves as the main menu for the program 
        @return 0 if the user exits the game
    */

    char mode = 'b'; //start the game mode at the main menu
    int nQuestions = 0, nPlayers = 0; //numbers of questions and players
    struct question list[listSize]; //struct array for 50 questions 
    struct player profileList[listSize]; //struct array for 50 players

    srand(time(NULL));

    do
    {
        fflush(stdin);
        switch (mode)
        {
            case 'b': 
            case 'B':
                system("cls");
                mainMenu(&mode); //prints the main menu prompt
                break;
            case 'm':
            case 'M':
                system("cls");
                //if password is correct, will run manageData()
                if (getPassword(&mode) == 2) 
                    manageData(&mode, list, &nQuestions);
                break;
            case 'p':
            case 'P':
                //runs the quiz game
                game(profileList, &nPlayers, &mode);
                break;
            default:
                //in case of invalid input
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