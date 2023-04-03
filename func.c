#include "header.h"

void addRecord(struct question[], int*);

void 
mainMenu(char* mode)
{
    printf("\n%14s%s\n\n", " ", "--QuizGeym--");
    printf("%8s%s\n", " ", "Welcome to the main menu!");
    printf("%4s%s", " ", "Choose among the following modes:\n\n");
    printf("-[M]anage Data (Admin)\n-[P]lay the game (Player)\n");
    printf("-[E]xit the game\n\n I select: ");
    scanf("%c", mode);
}

void
getQuestion(string150 question)
{
    /*
       questions will contain multiple words; hence, the need for a function
       such as this one that can take string inputs and account for spaces
       and will only end the input once a newline is entered
    */
    char ch = '\0';
    int i = 0; 
    
    while (ch != '\n' && i < quessSize-1)
    {
        scanf("%c", &ch);
        question[i] = ch; 
        i++;
        question[i] = '\0';
    }
}



int getPassword(char* mode)
{
    char password[30] = "password";
    string500 input; 

    int i = 0, result = 0;
    int ch; 
    char choice;  

    printf("\nWelcome to the admin page!\n");

    /*
        loop runs until password entered is wrong, result is still 0, and 
        until mode is not changed to the main menu
    */

    while ((strcmp(input, password) != 0) && !result && *mode != 'b')
    {
        printf("Please enter admin password: \n");
        while((ch = getch()) != 13) //gets password per char
        {
            if(ch != '\b') //if char entered not backspace
            {
                input[i] = ch; 
                i++;
                input[i] = '\0';
                printf("*");
            } else
            {
                printf("\b \b"); //moves cursor and deletes the *
                i--; //adjust index
                input[i] = '\0'; 
            }
            
        }
        if (strcmp(input, password) != 0) //if password is wrong
        {
            do
            {
                /*
                    to clear unusual inputs from menu and future attempts at 
                    password input
                */
               
                fflush(stdin);
                printf("\n\nPassword entered is incorrect. Would you like to:\n");
                printf("[T]ry again or go\n[B]ack to the menu\nChoice: ");
                scanf("%c", &choice);
                switch (choice)
                {
                    case 't':
                    case 'T':
                        strcpy(input, ""); //clears password input
                        i = 0; 
                        break;
                    case 'b':
                    case 'B':
                        *mode = 'b'; //goes back to main menu
                        result = 1; //1 to stop the loop
                        fflush(stdin);
                        break;
                    default:
                        printf("Wrong input. Please try again.\n");
                        break;
                }
            } while (!(choice == 't' || choice == 'T' ||
                       choice == 'b' || choice == 'B'));
        }else //password is right 
            result = 2;  //2 for correct password
    
    }
    fflush(stdin);
    return result; 
}



void manageData(char * mode, struct question list[], int * nQuestions)
{
    char choice; 

    do
    {
        system("cls");
        printf("%8s%s\n", " ", "Welcome to the admin page!");
        printf("%4s%s", " ", "You may choose among the following actions:\n\n");
        printf("-[A]dd a record\n-[E]dit a record\n-[D]elete a record\n");
        printf("-[I]mport data\n-[E]xport Data\n-[B]ack to main menu\n\n");
        printf("I select: ");
        scanf("%c", &choice);

        switch (choice)
        {
            case 'a':
            case 'A':
                //add a record
                addRecord(list, nQuestions);
                break;
            case 'e':
            case 'E':
                //edit a record
                break;
            case 'd':
            case 'D':
                //delete a record
                break;
            case 'b':
            case 'B':
                *mode = 'b';
                //back to main menu
            default:
                break;
        }
    } while (!(choice == 'b' || choice == 'B'));
    
    
    fflush(stdin);

}

void addRecord(struct question list[], int * nQuestions)
{
    fflush(stdin);
    char buffer = '\0';
    string150 questionInput; 
    string30 answerInput, choice; 
    string20 topic; 
    int found = 0, topicQ = 0, index; 

    printf("Enter question: ");
    getQuestion(questionInput);
    printf("Enter the correct answer to the question: ");
    scanf("%s", answerInput);
    
    //call function to find pair in list[]
    for (int i = 0; i < *nQuestions; i++)
        if (!strcmp(questionInput, list[i].question) && !strcmp(answerInput, list[i].answer))
        {
            found = 1;
            index = i; 
        } 

    if (*nQuestions == 0 || found == 0)
    {
        //assigning to the struct
        strcpy(list[*nQuestions].question, questionInput); 
        strcpy(list[*nQuestions].answer, answerInput);

        //getting inputs
        printf("No similar records found...\n\n");
        printf("Details for:\nQuestion: %s", questionInput);
        printf("Answer: %s\n\n", answerInput);

        //gets topic and stores to struct array
        printf("Topic: ");
        scanf("%s", topic);
        strcpy(list[*nQuestions].topic, topic);

        //gets chocie and stores to struct array
        printf("\n3 choices: (only one word per choice): \n");
        for (int i = 1; i <= 3; i++)
        {
            printf("Choice %d: ", i);
            scanf("%s", choice);
            switch (i)
            {
                case 1: 
                    strcpy(list[*nQuestions].c1, choice);
                    break;
                case 2: 
                    strcpy(list[*nQuestions].c2, choice);
                    break;
                case 3: 
                    strcpy(list[*nQuestions].c3, choice);
                    break;
                default:
                    break;
            }
            strcpy(choice, "");
        }

        *nQuestions+=1;
        //sort through struct array and count num questions for a certain topic 
        for (int i = 0; i < *nQuestions; i++)
            if (strcmp(list[i].topic, topic) == 0)
                topicQ++;
    
        list[*nQuestions-1].num = topicQ;

    }else 
    {
        printf("A record with the entered Question and Answer already exists:\n");
        printf("Topic: %s\n", list[index].topic);
        printf("Question #: %d\n", list[index].num);
        printf("Question: %s\n", questionInput);
        printf("Choice 1: %s\n", list[index].c1);
        printf("Choice 2: %s\n", list[index].c2);
        printf("Choice 3: %s\n", list[index].c3);
        printf("Answer: %s \n\n", answerInput);
        do
        {
            printf("Press any key to proceed...\n");
        } while (!(scanf(" %c", &buffer)));
        
    }
}