#include <stdio.h>

typedef char String30[31];

void mainMenu()
{
    printf("\n%14s%s\n\n", " ", "--GenQui--");
    printf("%8s%s\n", " ", "Welcome to the main menu!");
    printf("%4s%s", " ", "Choose among the following modes:\n\n");
    printf("-[M]anage Data (Admin)\n-[P]lay the game (Player)\n");
    printf("-[E]xit the game\n\n I select: ");
}

void manageData()
{
    char password[] = "poginijohan", input[500];
    int i; 
    //use getchar()
    printf("Enter admin password: ");


}