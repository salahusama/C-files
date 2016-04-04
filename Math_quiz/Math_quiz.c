/**Math Quiz Program 5.0 - Asks user to play a math quiz - Generates random equations - Checks results and displays them
   Salaheldin Akl
   10-11-2015
*/


#include <stdio.h>
#include <stdlib.h> //standard library - used here to generate random number

main()
{
    char option = '1'; //char to avoid errors
    int round = 0;
    char q; //number of questions - char for validation
    int num_q = 0; //number of questions since q is a char
    

    int i;//used in the for loop
    int error;//for validation


    //could use an array here, think about it
    //
    int r_num1; // First number in question generated randomly
    int r_num2; // Second number in question generated randomly
    int r_num3; // Third number in question generated randomly

    char sign[4] = {'+','-','/','*'}; //this is to specify the operation needed *** no need for symbolic variable, only 4 operations anyway

    int r_sign1; //use to pick random operations for the questions
    int r_sign2; //as there will be 2 operations in each question

    float sol; //this is the solution, it is float as answer may be a decimal number

    float answer; //this is the user's answer
    int score; //set to 0 at the start of every round ** score is kept in memory till next round starts -> allows user to view result more than once


    do
    {
        system("cls");//clears the screen
        printf("Enter 1, 2, 3 or 0 to select an option from below:\n\n");

        printf("________________________________________________________________________________\n");
        printf("(1) Enter the number of questions to be asked for this round of the quiz\n    (maximum of 5 questions allowed)\n\n");
        printf("(2) Start Quiz\n\n");
        printf("(3) Display the number of questions that were answered correctly and incorrectly for this round\n\n");
        printf("(0) Exit Program\n");
        printf("________________________________________________________________________________\n\n");

        
        printf("Enter option:  ");
        scanf("%1s", &option);
        flushall();


        /*****Switch statement to check which option selected*****/
        //
        switch (option)
        {

        //If 1 selected, ask for number of questions
        //
        case '1':
        {
            system("cls");//clears the screen

            do //validation of number of questions
            {
                error = 0;//initially
                printf("Number of Questions: ");
                scanf("%1s", &q);
                flushall();
                round = 0; //when no. of questions entered, player can no longer view results of previous round
                
                //q is char, to use in loop, change to int
                //
                switch (q)
                {
                    case '1':
                        num_q = 1;
                        break;
                    case '2':
                        num_q = 2;
                        break;
                    case '3':
                        num_q = 3;
                        break;
                    case '4':
                        num_q = 4;
                        break;
                    case '5':
                        num_q = 5;
                        break;
                    default:
                        printf("**Error: Number of Questions need to be from 1 - 5\n\n");
                        error = 1;
                }//end switch
            }//end do
            while (error); //error is either 0 or 1, if 1, condition is true

            //When number taken as valid input, display the number of questions this round will contain
            //
            printf("\nYour next Round will consist of %d Question(s)\n\n", num_q);
            printf("*Press Enter to Continue\n");
            getchar();
            break;
        }//end case 1


        //If 2 selected, start quiz
        //
        case '2':
        {
            system("cls");//clears the screen
            if (num_q == 0) //if q == 0, user will not have entered a value for it yet
            {
                printf("**Error: You did not specify the number of questions for this round\n\n");
                printf("**Press Enter to Continue\n");
                getchar();
            }//end if

            else
            {
                round++;//first line in quiz -> signifies round has started
                score = 0;//set score back to zero

                /**quiz starts*/
                printf("\n\t\t\tThis round has started!\n\n");
                printf("PLEASE ONLY TYPE IN THE WHOLE NUMBER PART OF YOUR ANSWER (ex: 8.7 -> 8)\n\n");
                printf("This Round has %d Question(s)\n\n", num_q);
                printf("**Press Enter to Continue\n");
                getchar();
                //system("cls");//clears the screen
                
                for (i=0 ; i < num_q ; i++)
                {
                    //Next few lines will pick signs & numbers for current question
                    //
                    r_num1 = rand() % 100;
                    r_num2 = rand() % 100;
                    r_num3 = rand() % 100;

                    r_sign1 = rand() % 4;
                    r_sign2 = rand() % 4;

                    //next line will print current question
                    //
                    system("cls");//clears te screen
                    printf("Question %d:\n\n", i+1);
                    printf("\t(%d %c %d) %c %d = ?\n" ,r_num1 , sign[r_sign1], r_num2, sign[r_sign2], r_num3);
                    
                    //next lines will calculate the answer of the current question
                    //
                    switch (r_sign1)
                    {
                        case 0:
                            sol = r_num1 + r_num2;
                            break;
                        case 1:
                            sol = r_num1 - r_num2;
                            break;
                        case 2:
                            sol = (float)r_num1 / r_num2;
                            break;
                        case 3:
                            sol = r_num1 * r_num2;
                            break;
                    }//end switch r_sign1

                    switch (r_sign2)
                    {
                        case 0:
                            sol = sol + r_num3;
                            break;
                        case 1:
                            sol = sol - r_num3;
                            break;
                        case 2:
                            sol = (float)sol / r_num3;
                            break;
                        case 3:
                            sol = sol * r_num3;
                            break;
                    }//end switch r_sign2

                    //Now We have the solution of our question :D

                    //Next line we take answer from user
                    //
                    printf("\t");
                    scanf("%f", &answer);
                    flushall();
                    
                    //checking answer
                    //
                    if ((int)answer == (int)sol)
                    {
                        printf("\t      Correct! :)\n\n");
                        score++;
                    }//end if
                    else
                    {
                        printf("\t      Wrong  -  The correct answer is %.1f\n\n", sol);
                    }//end else
                    
                    if (i < (num_q - 1)) //wont print after last question
                    {
                        printf("Press Enter to go to the next Question\n");
                        getchar();
                    }//end if
                }//end for
                /*quiz ends*/
                printf("\nYou completed this round\n\n");
                num_q = 0;//after quiz ends -> so it asks for no. of questions each round
                printf("**Press Enter to Continue\n");
                getchar();
            }//end else
            break;
        }//end case 2
        
        //show results
        //
        case '3':
        {
            system("cls");//clears the screen
            if (round == 0)
            {
                printf("**Error: You have not played yet!\n\n");
                printf("**Press Enter to Continue\n");
                getchar();
            }//end if

            else
            {
                //Display Results
                //
                printf("\nYou got %d Questions Right, and", score);
                printf("\nYou got %d Questions Wrong\n\n", i - score); //i will be the same value as q after the round

                //round = 0; //do this if Michael wants the score to be viewed once only

                printf("**Press Enter to Continue\n");
                getchar();
            }//end else
            break;
        }//end case 3
        
        case '0':
        {
            break;//to break, so default does not execute if 0 was entered
        }//end case 0
        
        default:
		{
			system("cls");//clears the screen
            printf("**Error: Input value not valid\n\n");
            printf("**Press Enter to Continue\n");
            getchar();
		}

        }//end switch

    }//end do
    while (option != '0');//program will run till 0 is entered

    //When 0 is entered, following code will execute
    //
    system("cls");//clears the screen
    printf("\n\n\n\t\t\tTHANK YOU FOR PLAYING\n\n\n");
    printf("**Press Enter to Continue\n");
    getchar();
}//end main
