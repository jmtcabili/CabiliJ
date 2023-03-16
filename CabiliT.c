#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>

#include "func.c"


int
main()
{
    char choice; 

    while (!(choice == 'e' || choice == 'E'))
    {
        mainMenu();
        scanf("%c", &choice);

        switch (choice)
        {
            case 'm':
            case 'M':
                manageData();
                break;
            
            default:
                break;
        }
    }

    system("cls");
    printf("Thank you for playing!");   
    
    

    return 0; 
}