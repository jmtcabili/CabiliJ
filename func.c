#include "header.h"

void addRecord(struct question[], int*);
void editPrompt(struct question[], int*, char*);

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
    
    do
    { 
        scanf("%c", &ch);
        if (ch !='\n')
        {
            question[i] = ch; 
            i++;
            question[i] = '\0';
        }
    }while (ch != '\n' && i < quessSize-1);
}

void 
updateNum(struct question list[], int *nQuestions, string20 topic)
{
    int num = 0; 
    for (int i = 0; i < *nQuestions; i++)
    {
        if (!strcmp(list[i].topic, topic))
        {
            num++;
            list[i].num = num; 
        }
    }
}

void dots()
{
    for (int i = 0; i < 3; i++)
    {
        Sleep(250);
        printf(".");
    }
    printf("\n");
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
        scanf(" %c", &choice);

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
                do
                {
                    editPrompt(list, nQuestions, &choice);
                } while(choice == 'e' || choice == 'E');
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

void 
addRecord(struct question list[], int * nQuestions)
{
    fflush(stdin);
    char buffer = '\0';
    string150 questionInput; 
    string30 answerInput; 
    string20 topic; 
    int found = 0, topicQ = 0, index; 

    printf("Enter question: ");
    getQuestion(questionInput);
    printf("Enter the correct answer: ");
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
        Sleep(500);
        printf("Scanning database"); dots();
        Sleep(1000);
        printf("No similar records found!\n\n");
        
        printf("Input remaining details for:\nQuestion: %s\n", questionInput);
        printf("Answer: %s\n\n", answerInput);

        //gets topic and stores to struct array
        printf("Topic: ");
        scanf("%s", topic);
        strcpy(list[*nQuestions].topic, topic);

        //gets chocie and stores to struct array
        printf("3 choices: (only one word per choice): \n");
        printf("Choice 1: ");
        scanf("%s", list[*nQuestions].c1);
        printf("Choice 2: ");
        scanf("%s", list[*nQuestions].c2);
        printf("Choice 3: ");
        scanf("%s", list[*nQuestions].c3);

        *nQuestions+=1;
        //sort through struct array and count num questions with similar topic
        ///to the one that was just added 
        for (int i = 0; i < *nQuestions; i++)
            if (strcmp(list[i].topic, topic) == 0)
                topicQ++;
    
        list[*nQuestions-1].num = topicQ;

        printf("\nRecord successfully added!\n"); 
        printf("Returning to manage data menu"); dots();

    }else 
    {
        printf("\n---------------------------------------------------------------\n");
        printf("A record with the entered Question and Answer already exists:\n");
        printf("Topic: %s\n", list[index].topic);
        printf("Question #: %d\n", list[index].num);
        printf("Question: %s\n", questionInput);
        printf("Choice 1: %s\n", list[index].c1);
        printf("Choice 2: %s\n", list[index].c2);
        printf("Choice 3: %s\n", list[index].c3); 
        printf("Answer: %s \n\n", answerInput);
        printf("\n---------------------------------------------------------------\n");
        do
        {
            printf("Press any key then enter to proceed...\n");
        } while (!(scanf(" %c", &buffer)));
        
    } 
}

void
editPrompt(struct question list[], int * nQuestions, char * mode)
{
    /*
        In manageData(), editPrompt will continue to run until you change 
        the choice used to switch modes in manageData()
    */

    string20 currentTopic; //to find unique topics and identify topic being editted
    string20 uniqueTopics[*nQuestions]; //list of unique topics
    string20 newTopic, previousTopic; //when editting a topic


    int uniqueIndexes[*nQuestions]; //occurences of topics in list[k].topics
    int count, k, num, index;  //topic count, while iterator, list count, question index in list[]
    int found = 0;
    int lowest = 1, highest = 1; 
    char editChoice; 
    int topicChoice, questionChoice, fieldChoice; 
    int willEdit = 0; 

    for (int i = 0; i < *nQuestions; i++)
    {
        count = 0;
        strcpy(currentTopic, list[i].topic);
        for (int j = 0; j < *nQuestions; j++)
        {
            if(strcmp(currentTopic, list[j].topic) == 0)
            {
                count++;
                uniqueIndexes[j] = count;
            }
        }   
    }        
    Sleep(1000);
    system("cls");
    printf("\n-----List of unique topics-----\n");
    num = 0;//num unique topics

    for (k = 0; k < *nQuestions; k++)
    {
        if (uniqueIndexes[k] == 1)
        
        {
            strcpy(uniqueTopics[num], list[k].topic);
            num++;
            printf("%d.) %s\n", num, list[k].topic);

        }
    }

    printf("-------------------------------\n\n");
    
    //admin decides whether or not to continue editting or go back to manage data

    do
    {
        printf("Would you like to edit any of the topic entries?\n");
        printf("- [Y]es\n- [N]o, go back to admin menu\nOption: ");
        scanf(" %c", &editChoice);
        if (editChoice == 'y' || editChoice == 'Y')
            willEdit = 1;
        else if (editChoice == 'n' || editChoice == 'N')
        {
            willEdit = 0; 
            *mode = '\0'; //default case, manage data loop will rerun
        }
        else
            printf("Invalid input. Please try again.\n\n");

    } while (!(editChoice == 'y' || editChoice == 'Y' ||
             editChoice == 'n' || editChoice == 'N'));
    

    if(willEdit)
    {
        do
        {
            printf("\nFrom which topic would you like to edit?\n");
            printf("Enter the number beside the topic as indicated in the list above: ");
            scanf("%d", &topicChoice);
            if (topicChoice >= 1 && topicChoice <= num)
                printf("\nPrinting questions under the topic: %s\n\n", uniqueTopics[topicChoice-1]);
            else
                printf("Invalid input. Please try again\n\n");

        } while (topicChoice < 1 || topicChoice > num);

        //show questions in topic
        printf("------------------------------------\n");
        for (int i = 0; i < *nQuestions; i++)
        {
            if (strcmp(list[i].topic, uniqueTopics[topicChoice-1]) == 0)
            {
                
                printf("%d.) %s\n", list[i].num, list[i].question);
                printf("Answer: %s\n", list[i].answer);
                printf("Choices:\n");
                printf("- %s\n", list[i].c1);
                printf("- %s\n", list[i].c2);
                printf("- %s\n", list[i].c3);
                printf("------------------------------------\n");
                if (list[i].num > highest)
                    highest = list[i].num; //finding highest question#
            }
        }
        //ask for question number to be editted
        do
        {
            //maybe add cancel option -- too hassle if nagkamali pala sa option
            printf("Which question number would you like to edit?\nQuestion #: ");
            scanf("%d", &questionChoice);
            if (questionChoice < lowest || questionChoice > highest)
                printf("Invalid input. Please try again.\n\n");
        } while (questionChoice < lowest || questionChoice > highest);
        
        //show chosen record and ask which field to edit
        k = 0; //reuse
        printf("\nChosen record to edit:\n\n");
        while (k < *nQuestions && !found) 
        {
            if (list[k].num == questionChoice &&
                !strcmp(list[k].topic, uniqueTopics[topicChoice-1]))
            {
                printf("Topic: %s\n", list[k].topic);
                printf("Question #%d: %s\n", list[k].num, list[k].question);
                printf("Answer: %s\n", list[k].answer);
                printf("Choices:\n");
                printf("- %s\n", list[k].c1);
                printf("- %s\n", list[k].c2);
                printf("- %s\n", list[k].c3);
                found = 1; 
                index = k; 
            }
            k++;
        }
        Sleep(500);
        //if changing topic, make sure to update question number#
        do
        { 
            printf("\n+++++++++++++++++++++++++++++++++++++++++++\n");
            printf("Which field would you like to edit?\n");
            printf("1.) Topic\n2.) Question\n3.) Choice 1\n4.) Choice 2\n");
            printf("5.) Choice 3\n6.) Answer\n");
            
             
            printf("Option: ");
            scanf("%d", &fieldChoice);
            switch (fieldChoice)
            {
                case 1:
                    printf("New topic: ");
                    scanf("%s", newTopic);
                    strcpy(previousTopic, list[index].topic);
                    strcpy(list[index].topic, newTopic);
                    for (int i = 0; i < *nQuestions; i++)
                    {
                        //update question numbers of previous topic
                        //list[index].topic -> topic chosen to edit/change
                        //list[i].topic -> occurence of topic in list[]
                        updateNum(list, nQuestions, previousTopic);
                        updateNum(list, nQuestions, newTopic);
                        //update question numbers of new topic
                    }
                    fieldChoice = 5;
                    break;
                case 2:
                    printf("New Question: ");
                    fflush(stdin);
                    getQuestion(list[index].question);
                    fieldChoice = 5;
                    break;
                case 3:
                    //ask which choice hehe
                    printf("Choice 1: "); scanf("%s", list[index].c1);
                    fieldChoice = 5;
                    break;
                case 4:
                    printf("Choice 2: "); scanf("%s", list[index].c2);
                    fieldChoice = 5;
                    break;
                case 5: 
                    printf("Choice 3: "); scanf("%s", list[index].c3);
                    fieldChoice = 5;
                    break;
                case 6:
                    printf("New answer: "); scanf("%s", list[index].answer);
                    fieldChoice = 5;
                    break;
                default:
                    fflush(stdin);
                    printf("Invalid input. Please try again\n\n");
                    break;
            }
        } while (fieldChoice != 5);
        
        printf("enter any key to proceed...\n");
        scanf(" %c", &editChoice);
    }
}



