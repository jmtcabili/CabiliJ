

typedef char string30[31];
typedef char string500[501];
typedef char string150[151];

struct question{
    int num; 
    string150 question; 
    string30 c1, c2, c3, answer;
};

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
    char password[30] = "poginijohan";
    string500 input; 

    int i = 0; 
    int ch; 

    printf("Enter admin password: ");

    while (strcmp(input, password) != 0)
    {
        while((ch = getch()) != 13)
        {
            if(ch != '\b')
            {
                input[i] = ch; 
                i++;
                input[i] = '\0';
                printf("*");
            } else
            {
                printf("\b \b");                
                i--;
                input[i] = '\0';
            }
            
        }
        if (strcmp(input, password) != 0)
        {
            printf("\nPlease try again: \n");
            strcpy(input, "");
            i = 0; 
        }
    
    }

    printf("Welcome to the page!\n");

    fflush(stdin);



}