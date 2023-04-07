#include <stdio.h> //standard input-output library
#include <string.h> //for string functions
#include <windows.h> //for system commands
#include <conio.h> //for getch()

#include "func.c"


int
main()
{
    char mode = 'b'; //start the game mode at the main menu
    int nQuestions = 0, nPlayers = 0;
    struct question list[listSize]; //struct array for 50 questions 
    struct player profileList[listSize]; //struct array for 50 players

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
                play(list, profileList, &nQuestions, &nPlayers);
                //for play
                //shuffle choices
                //sort scores
                //add element in structs to determine if question is already answered
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
    
    
    /*
    To-do
        1. Fix edit and import
            - edit (account for same q and a)
                - if changing q/a, loop through list to verify if valid q and a
            - import (account for same q and a)
                - do not import if there is similar record
                - give warning message "some messages not imported"
        2. Export (done) 
        3. Quiz Game
            a. Play game - add other element to struct if answered
                - when displaying questions, check if already answered
            b. View Scores - sort scores
            c. Exit
    
    */
    
    return 0; 
}