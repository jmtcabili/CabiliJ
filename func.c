#include "header.h"

void addRecord(struct question[], int*);
void editRecord(struct question[], int*, int*);
void deleteRecord(struct question[], int*, int*);
void importData(struct question[], int*, int*);
void exportData(struct question[], int*);
void play(struct question[], struct player[], int*, int*, char*);
int searchPlayer(struct player[], int*, string20);
void printScoreboard(struct player[], int*, string20);
void sortByScore(struct player[], int*);
void viewScores(struct player[], int*);

void 
mainMenu(char* mode)
{
    printf("\n%14s%s\n\n", " ", "--QuizGeym--");
    printf("%8s%s\n", " ", "Welcome to the main menu!");
    printf("%4s%s", " ", "Choose among the following actions:\n\n");
    printf("-[M]anage Data (Admin)\n-[P]lay the game (Player)\n");
    printf("-[R]eset questions\n-[E]xit the game\n\n I select: ");
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
readQuestion(string150 question, FILE *fp)
{
    //same as getQuestion but in the context of reading strings in files

    char ch = '\0';
    int i = 0; 
    
    do
    { 
        fscanf(fp, "%c", &ch);
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
        Sleep(350);
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
                if (i > 0)
                {
                    printf("\b \b"); //moves cursor and deletes the *
                    i--; //adjust index
                    input[i] = '\0'; 
                }
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
                        printf("Invalid input. Please try again.\n");
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
    int choice; 

    do
    {
        system("cls");
        printf("%8s%s\n", " ", "Welcome to the admin page!");
        printf("%4s%s", " ", "You may choose among the following actions:\n\n");
        printf("1. Add a record\n2. Edit a record\n3. Delete a record\n");
        printf("4. Import data\n5. Export Data\n6. Back to main menu\n\n");
        printf("I select: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <=6)
        {
            system("cls");
            switch (choice)
            {
                case 1:
                    //add a record
                    printf("Add a record:\n");
                    addRecord(list, nQuestions);
                    break;
                case 2:
                    system("cls");
                    printf("Edit a record:\n");
                    do
                    {
                        editRecord(list, nQuestions, &choice);
                    } while(choice == 2);
                    break;
                case 3:
                    printf("Delete a record:\n");
                    do
                    {
                        deleteRecord(list, nQuestions, &choice);
                    } while(choice == 3);
                    break;
                case 4: 
                    printf("Import data:\n");
                    do
                    {
                        importData(list, nQuestions, &choice);
                    } while (choice == 4);
                    break;
                case 5:
                    printf("Export data:\n");
                    exportData(list, nQuestions);
                    break;
                case 6:
                    *mode = 'b';
                    //back to main mene
                    break;
            }
        } else
        {
            printf("Invalid input. Please try again.\n");
            Sleep(750);
            fflush(stdin);
        }
    } while (!(choice == 6));


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

    Sleep(500);
    printf("Scanning database"); dots();
    Sleep(1000);
    printf("No similar records found!\n\n");

    if (*nQuestions == 0 || found == 0)
    {
        fflush(stdin);
        //assigning to the struct
        strcpy(list[*nQuestions].question, questionInput); 
        strcpy(list[*nQuestions].answer, answerInput);

        //getting inputs
        
        
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
        printf("Returning to the admin menu"); dots();

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
editRecord(struct question list[], int * nQuestions, int * mode)
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
    char editChoice, choice; 
    int topicChoice, questionChoice, fieldChoice; 
    int willEdit = 0; 

    if (*nQuestions == 0)
    {
        printf("There are no questions to edit!\n");
        Sleep(500);
        printf("Going back to admin page"); dots();
        Sleep(750);
        *mode = 0;
    }
    else
    {
        system("cls");
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
        printf("\n-----List of topics-----\n");
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

        printf("------------------------\n\n");
        
        //admin decides whether or not to continue editting or go back to manage data

        do
        {
            printf("Would you like to edit any of the topic entries?\n");
            printf("[Y]es\n[N]o, go back to admin menu\nOption: ");
            scanf(" %c", &editChoice);
            if (editChoice == 'y' || editChoice == 'Y')
                willEdit = 1;
            else if (editChoice == 'n' || editChoice == 'N')
            {
                willEdit = 0; 
                *mode = 0; //default case, manage data loop will rerun
            }
            else
            {
                printf("Invalid input. Please try again.\n\n");
            }
            fflush(stdin);

        } while (!(editChoice == 'y' || editChoice == 'Y' ||
                editChoice == 'n' || editChoice == 'N'));
        
        //if admin chooses to edit
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
                fflush(stdin);
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
                printf("Which question number would you like to edit [%d] - [%d]?\n", lowest, highest);
                printf("Enter [0] to cancel\n");
                printf("Question #: ");
                scanf("%d", &questionChoice);
                if(questionChoice == 0)
                    willEdit = 0; 
                else if (questionChoice < lowest || questionChoice > highest)
                    printf("Invalid input. Please try again.\n\n");
                fflush(stdin);
            } while ((questionChoice < lowest && questionChoice != 0) || questionChoice > highest);
            
            //show chosen record and ask which field to edit
            if (willEdit)
            {
                k = 0; //reuse
                printf("\nChosen record to edit:\n\n");
                while (k < *nQuestions && !found && willEdit) 
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
                            updateNum(list, nQuestions, previousTopic);
                            updateNum(list, nQuestions, newTopic);
                                //update question numbers of new topic
                            fieldChoice = 7;
                            break;
                        case 2:
                            printf("New Question: ");
                            fflush(stdin);
                            getQuestion(list[index].question);
                            fieldChoice = 7;
                            break;
                        case 3:
                            //ask which choice hehe
                            printf("Choice 1: "); scanf("%s", list[index].c1);
                            fieldChoice = 7;
                            break;
                        case 4:
                            printf("Choice 2: "); scanf("%s", list[index].c2);
                            fieldChoice = 7;
                            break;
                        case 5: 
                            printf("Choice 3: "); scanf("%s", list[index].c3);
                            fieldChoice = 7;
                            break;
                        case 6:
                            printf("New answer: "); scanf("%s", list[index].answer);
                            fieldChoice = 7;
                            break;
                        default:
                            fflush(stdin);
                            printf("Invalid input. Please try again\n\n");
                            break;
                    }
                } while (fieldChoice != 7);
                
                printf("enter any key to proceed...\n");
                scanf(" %c", &choice);
                fflush(stdin);
            }
            
        }
    }
}

void
deleteRecord(struct question list[], int * nQuestions, int * mode)
{
    int count, num, willDelete; 
    int topicChoice, questionChoice; 
    int uniqueIndexes[*nQuestions];
    int lowest = 1, highest = 1; 
    int k, found = 0, index; 

    char choice; 
    string20 currentTopic, uniqueTopics[*nQuestions];

    char deleteChoice; 

    if (*nQuestions == 0)
    {
        system("cls"); 
        printf("There are no questions to delete!\n");
        Sleep(500);
        printf("Going back to admin page"); dots();
        Sleep(750);
        *mode = 0;
    }
    else
    {
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
        printf("\n-----List of topics-----\n");
        num = 0;//num unique topics

        for (int k = 0; k < *nQuestions; k++)
        {
            if (uniqueIndexes[k] == 1)
            
            {
                strcpy(uniqueTopics[num], list[k].topic);
                num++;
                printf("%d.) %s\n", num, list[k].topic);

            }
        }

        printf("-------------------------------\n\n");
        
        //admin decides whether or not to continue deleting or go back to manage data

        do
        {
            printf("Would you like to delete any of the topic entries?\n");
            printf("[Y]es\n[N]o, go back to admin menu\nOption: ");
            scanf(" %c", &deleteChoice);
            if (deleteChoice == 'y' || deleteChoice == 'Y')
                willDelete = 1;
            else if (deleteChoice == 'n' || deleteChoice == 'N')
            {
                willDelete = 0; 
                *mode = 0; //default case, manage data loop will rerun
            }
            else
                printf("Invalid input. Please try again.\n\n");

        } while (!(deleteChoice == 'y' || deleteChoice == 'Y' ||
                deleteChoice == 'n' || deleteChoice == 'N'));

        if(willDelete)
        {
            do
            {
                printf("\nFrom which topic would you like to delete?\n");
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
                printf("Which question number would you like to delete [%d] - [%d]?\n", lowest, highest);
                printf("Enter [0] to cancel\n");
                printf("Question #: ");
                scanf("%d", &questionChoice);
                if(questionChoice == 0)
                    willDelete = 0; 
                else if (questionChoice < lowest || questionChoice > highest)
                    printf("Invalid input. Please try again.\n\n");
                fflush(stdin);
            } while ((questionChoice < lowest && questionChoice != 0) || questionChoice > highest);
            
            //show chosen record and ask which field to edit
            if (willDelete)
            {
                k = 0; //reuse
                printf("\nChosen record to delete:\n\n");
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

                //deleting
                do
                {
                    printf("Are you sure you want to delete this record (Y/N)?\n");
                    printf("Option: ");
                    scanf(" %c", &choice);
                    if (choice == 'y' || choice == 'Y')
                    {
                        printf("Deleting");
                        dots();
                        choice = 'p';
                    }
                    else if (choice == 'n' || choice == 'N')
                    {
                        printf("Cancelling");
                        dots();
                        willDelete = 0; 
                        choice = 'p';
                    }
                    else
                        printf("Invalid input. Please try again.\n");

                } while (choice != 'p');
                
                if (willDelete)
                {
                    strcpy(list[index].topic, "");
                    strcpy(list[index].question, "");
                    strcpy(list[index].answer, "");
                    strcpy(list[index].c1, "");
                    strcpy(list[index].c2, "");
                    strcpy(list[index].c3, "");
                    list[index].num = 0;

                    for (int i = 0; i < *nQuestions-1; i++)
                    {
                    if (!strcmp(list[index].topic, list[i].topic) && 
                        list[index].num == list[i].num)
                    {
                        for (int j = i; j < *nQuestions-1; j++)
                        {
                            list[j] = list[j+1];
                        }
                    }
                    }
                    *nQuestions = *nQuestions - 1;
                    updateNum(list, nQuestions, list[index].topic);
                    fflush(stdin);
                }
            }
            
            
            
        }
    }
    system("cls");
}

void importData(struct question list[], int *nQuestions, int *mode)
{
    FILE *fp;
    string500 filename;
    int option, quesNum;
    char verify = 'n'; 

    string20 topic;
    string150 question; 
    string30 c1, c2, c3, answer; 

    //obtaining filename with verification
    do
    {
        if (verify == 'n' || verify == 'N')
        {
            printf("\nEnter filename of file to import(w/ extension): ");
            scanf("%s", filename);
        }

        printf("You entered: %s\nIs this correct (Y/N)?\nOption: ", filename);
        scanf(" %c", &verify);

        if (verify == 'y' || verify == 'Y')
        {
            printf("Attempting to import file"); 
            dots();
            verify = 'p';
        }
        else if (verify == 'n' || verify == 'N')
            printf("Please enter the filename again. Thank you.\n");
        else 
            printf("Invalid input. Please verify again.\n");

    } while (verify != 'p'); 

    fp = fopen(filename, "r"); //opening file

    if (fp == NULL)  //if file not found
    {
        do
        {
            printf("\nFile not found.\n");
            printf("Would you like to enter another file or go back to admin page?\n");
            printf("[1] Enter another file\n[2] Go back to admin page\n");
            printf("Option: \n");
            scanf("%d", &option);
            if (option == 1)
                verify = 'n';
            else if (option == 2)
                *mode = 0;
            else 
                printf("Invalid input. Please try again.");

        } while (!(option == 1 || option == 2));
    } 

    if (fp)
    {
        //need spaces to account for whitespaces in text file
        while (fscanf(fp, "%s\n%d\n%[^\n]\n%s\n%s\n%s\n%s\n\n", topic,
                                                &quesNum, 
                                                question, 
                                                c1, c2, 
                                                c3, answer) != EOF)
        {
            strcpy(list[*nQuestions].topic, topic);
            list[*nQuestions].num = quesNum;
            strcpy(list[*nQuestions].question, question);
            strcpy(list[*nQuestions].c1, c1);
            strcpy(list[*nQuestions].c2, c2);
            strcpy(list[*nQuestions].c3, c3);
            strcpy(list[*nQuestions].answer, answer);
            *nQuestions+=1;
            updateNum(list, nQuestions, list[*nQuestions-1].topic);
        }

        
        printf("File imported! "); Sleep(500); 
        printf("Going back to admin page"); dots();
        Sleep(1000);
        *mode = 0; 
    }

    fclose(fp);
}

void 
exportData(struct question list[], int * nQuestions)
{
    FILE *fp;
    string30 filename;

    printf("\nEnter a filename where all the records will be exported to!\n");
    printf("*NOTE* Any filename similar to your input will be overwritten\n\n");
    Sleep(1000);
    printf("Filename (at most 30 characters w/extension): ");
    scanf("%s", filename); 

    fp = fopen(filename, "w");

    for (int i = 0; i < *nQuestions; i++)
    {
        fprintf(fp, "%s\n", list[i].topic);
        fprintf(fp, "%d\n", list[i].num);
        fprintf(fp, "%s\n", list[i].question);
        fprintf(fp, "%s\n%s\n%s\n", list[i].c1, list[i].c2, list[i].c3);
        fprintf(fp, "%s\n\n", list[i].answer);
    }
    printf("Exporting"); dots(); 
    
    fclose(fp);
    
}

void 
game(struct question list[], struct player profileList[],
     int *nQuestions, int *nPlayers, char * mode)
{  
    
    system("cls");

    int control = 0; 
    char playMode; 
    printf("%8s%s\n", " ", "Welcome to the play menu!");
    printf("%4s%s", " ", "Choose among the following actions:\n\n");
    printf("-[P]lay\n-[V]iew scores\n-[E]xit\n\n");
    printf("DESCRIPTIONS:\n");
    printf("    Play    - Participate in a quiz game where each player receives a\n");
    printf("              random question from a chosen topic. Once a question is\n");
    printf("              is answered, no other player can answer the same question.\n\n");
    printf("View scores - The ranking and the scoreboard are displayed on the\n");
    printf("              on the console and are exported to a file of your choice.\n\n");
    printf("    Exit    - Back to the starting menu. Player and question records\n");
    printf("              will be cleared. \n\n");
    printf("I select: ");
    scanf("%c", &playMode);

    while (!control)
    {   
        switch (playMode)
        {
            case 'p':
            case 'P':
                play(list, profileList, nQuestions, nPlayers, mode);
                control = 1; 
                break;
            case 'v':
            case 'V':
                viewScores(profileList, nPlayers);
                control = 1; 
                break;
            case 'e':
            case 'E':
                control = 1;
                *mode = 'b';
            default:
                fflush(stdin);
                printf("Invalid input. Please try again.\n\n");
                break;
        }
        fflush(stdin);
    }

    
}

void 
play(struct question list[], struct player profileList[],
     int *nQuestions, int *nPlayers, char * mode)
{
    int num, count, k = 0, pos = 0;
    int end = 0, highest = 1, number = 0, found = 0;
    int foundPlayer, playerIndex; 

    int uniqueIndexes[*nQuestions];
    int topicChoice;
    string20 currentTopic;
    string20 uniqueTopics[*nQuestions];
    string30 choices[3], answer, name;

    if (*nPlayers)
    {
        printf("\nCurrent players: \n");
        for (int i = 0; i < *nPlayers; i++)
        {
            printf("Player %d: %s\n", i+1, profileList[i].name);
        }
        printf("\nPlayer names can't be the same!\n");
    }

    printf("Enter player name (max 20 characters): ");
    scanf("%s", name);

    foundPlayer = searchPlayer(profileList, nPlayers, name);

    if (foundPlayer >= 0)
    {
        playerIndex = foundPlayer;
    } else
    {
        playerIndex = *nPlayers; 
        strcpy(profileList[playerIndex].name, name);
        profileList[playerIndex].score = 0; 
        *nPlayers+=1; 
    }
    
    //run while !end && there are questions not yet answered
    //ask questions until player chooses to end turn 
        // should be given option to end turn during topic select
    while (!end)
    {  
        fflush(stdin);
        system("cls");
        sortByScore(profileList, nPlayers);
        printScoreboard(profileList, nPlayers, name);
        end = 0;
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
        printf("\n-----List of topics-----\n");
        num = 0;//num unique topics

        for (int k = 0; k < *nQuestions; k++)
        {
            if (uniqueIndexes[k] == 1)
            
            {
                strcpy(uniqueTopics[num], list[k].topic);
                num++;
                printf("%d.) %s\n", num, list[k].topic);

            }
        }
        printf("-----------------------\n");

        topicChoice = 0;
        do
        {
            printf("\nFrom which topic would you like to answer?\n");
            printf("Enter the number beside the topic as indicated in the list above.\n");
            printf("Enter [0] to back to the menu\nOption: ");
            scanf("%d", &topicChoice);
            if (topicChoice >= 1 && topicChoice <= num)
            {
                printf("\nLoading a question from: %s\n", uniqueTopics[topicChoice-1]);
                dots();
                Sleep(500);
                fflush(stdin);
            }
            else if (!topicChoice)
            {
                fflush(stdin);
                end = 1;
            }
            else
            {
                fflush(stdin);
                printf("Invalid input. Please try again\n\n");
            }

        } while ((topicChoice < 1 && topicChoice != 0) || topicChoice > num);
        fflush(stdin);
        //finding highest question#
        highest = 0; 
        if (!end)
        {
            for (int i = 0; i < *nQuestions; i++)
            {
                if (strcmp(list[i].topic, uniqueTopics[topicChoice-1]) == 0)
                {
                    if (list[i].num > highest)
                        highest = list[i].num; 
                }
            }
        
                //printing random question
                number = rand()%highest+1;


                printf("-----------------------------\n");
                printf("Question #%d: ", number);
                
                k = 0; found = 0; //re-initializing variables for next attempts
                //search for question with given topic and number
                while(k < *nQuestions && !found)
                {
                    if (!strcmp(list[k].topic,uniqueTopics[topicChoice-1]) &&
                        list[k].num == number)
                    {
                        printf("%s\n", list[k].question);
                        found = 1;
                        k--;
                    }
                    k++;
                }

                strcpy(choices[0], list[k].c1);
                strcpy(choices[1], list[k].c2);
                strcpy(choices[2], list[k].c3);

                int usedIndices[3] =  {-1, -1, -1};

                printf("Choices:\n");
                for (int i = 0; i < 3; i++)
                {
                    do
                    {
                        pos = rand()%3;
                    } while (pos == usedIndices[0] || pos == usedIndices[1]);
                    usedIndices[i] = pos;
                    printf("- %s\n", choices[pos]);
                }        

                printf("Your answer(Type in the choice): ");
                scanf("%s", answer);

                //if correct
                if (strcmp(answer, list[k].answer) == 0)
                {
                    printf("Correct!\n");
                    Sleep(500);
                    printf("Adding your score"); dots();
                    playerIndex = searchPlayer(profileList, nPlayers, name); //because you sorted struct
                    profileList[playerIndex].score += 1; 
                    Sleep(500);
                    list[k].answered = 1; 
                }
                else 
                {
                    printf("Incorrect. Try again!\n");
                    Sleep(2000);
                }
            }
        }    
}

void
viewScores(struct player profileList[], int *nPlayers)
{
    //assume currentName in printScoreboard is leading scorer -> sorted array
    int i;

    FILE *fp, *fp2;
    fp = fopen("score.txt", "w");

    for(i = 0; i < *nPlayers; i++)
    {
        fprintf(fp, "%s\n", profileList[i].name);
        fprintf(fp, "%d\n\n", profileList[i].score);
    }

    fp2 = fopen("hat.txt", "w");
    fprintf(fp2, "%s", "23");


    system("cls");
    printf("Current scoreboard: \n");
    printScoreboard(profileList, nPlayers, profileList[0].name);
    printf("Exporting record"); dots();
    printf("score.txt exported!\n\n");
    printf("Heading back to main menu"); dots();
    fclose(fp); fclose(fp2);

}

int 
searchPlayer(struct player profileList[], int *nPlayers, string20 name)
{
    int i = 0, index = -1; 

    while (i < *nPlayers && index == -1)
    {
        if (!strcmp(profileList[i].name, name))
            index = i; 
        i++;
    }

    return index;     
}

void
printScoreboard(struct player profileList[], int *nPlayers, string20 currentName)
{
    int i; 

    printf("*--------------------------------*\n");
    for (i = 0; i < *nPlayers; i++)
    {   
        printf("|%-2d", i+1);
        printf("|Player: ");
        if (!strcmp(profileList[i].name, currentName))
        {
            printf("\033[0;32m");
            printf("%-20s ", profileList[i].name);
            printf("\033[0m|");
        } else
            printf("%-20s |", profileList[i].name);
        if (i == 0 && *nPlayers > 1)
            printf(" -> LEADING SCORER!");
        printf("\n|  |Score: %-2d %19s|\n", profileList[i].score, "");
        printf("*--------------------------------*\n");
    }
}

void
sortByScore(struct player profileList[], int *nPlayers)
{
    int i, j, max;
    struct player temp; 
    for (i = 0; i < *nPlayers-1; i++)
    {
        max = i; 
        for (j = i+1; j < *nPlayers; j++)
        {
            if (profileList[j].score > profileList[max].score)
                max = j;
        }
        if (max != i)
        {
            temp = profileList[max];
            profileList[max] = profileList[i];
            profileList[i] = temp; 
        }
    }
    
}

void
initializeQuestions(struct question list[], int *nQuestions)
{
    int i; 
    for (i = 0; i < *nQuestions; i++)
        list[i].answered = 0;
}
