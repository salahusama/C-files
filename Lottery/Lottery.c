/*Assignment 2 - Lotto program with menu gives user the option to: 
                                                                Enter their 6 numbers
                                                                Display the numbers
                                                                Sort the numbers
                                                                Check if numbers match with winning numbers
                                                                Check how frequent each number was entered
  Salaheldin Akl
  17 Feb 2016
*/

#include <stdio.h>
#include <stdlib.h>
#define SIZE 6
#define MAX 42
#define MIN 1
#define BONUS 42

//fxn prototypes
//
void getInput(int *, int *);
void displayInput(int *);
void sort(int *);
int compare(int *, int *);
void frequency(int *);
void exitp(void);

main()
{
	int winning[SIZE] = { 1, 3, 5, 7, 9, 11 }; // winning numbers + bonus

    register int i;
	char option;
	int pickedNumbers[SIZE];
    int freq[MAX+1] = {0}; // max is the highest number user can enter, so only MAX elements are needed in this array - MAX+1 so number is same as position - initially set to 0
    int num_match;
    int numbersEntered = 0; // false
    int b_match = 0; // bonus does not match

	//main program loop
	//
	do
    {
        system("cls");//clears the screen
        printf("Enter 1 - 5, or 0 to select an option from below:\n\n");

        printf("________________________________________________________________________________\n");
        printf("(1) Enter the 6 Numbers ( range: 1 - 42 )\n\n");
        printf("(2) Display the Entered Numbers\n\n");
        printf("(3) Display Numbers in Increasing Order\n\n");
        printf("(4) Did I Win?\n\n");
        printf("(5) Display Frequency of Numbers Entered\n\n");
        printf("(0) Exit Program\n");
        printf("________________________________________________________________________________\n\n");
        
        printf("Enter option:  ");
        scanf("%1s", &option);
        flushall();  // clear buffer
        
        system("cls");//clears the screen

        switch (option)
        {
        	case '1':
        	{
        		//get input
        		getInput(pickedNumbers, freq);
                numbersEntered++;
        		break;
        	}//end case 1
        	case '2':
        	{
                if ( numbersEntered == 0 )
                {
                    printf("**You did not Enter Your Numbers\n\n");
                }//end if

        		else // display numbers
        		{
                    displayInput(pickedNumbers);
        		}//end else
                break;
        	}//end case 2
        	case '3':
        	{
                if ( numbersEntered == 0 )
                {
                    printf("**You did not Enter Your Numbers\n\n");
                }
        		else // sort the numbers
        		{
                    sort(pickedNumbers);
        		}
                break;
        	}//end case 3
        	case '4':
        	{
                if ( numbersEntered == 0 )
                {
                    printf("**You did not Enter Your Numbers\n\n");
                }
        		else // see match
        		{
                    num_match = compare(pickedNumbers, winning);
                    
                    // check bonus
                    //
                    for ( i = 0; i < SIZE; i++ )
                    {
                        if ( *(pickedNumbers + i) == BONUS )
                        {
                            b_match++;
                            break; // dont check rest of numbers 
                        }//end if
                    }//end for

                    switch ( num_match )
                    {
                        case 3:
                        {
                            if ( b_match > 0 )
                                printf("You Won a Cinema Ticket\n");
                            else
                                printf("You Lost :(\n");
                            break;
                        }
                        case 4:
                        {
                            if ( b_match > 0 )
                                printf("You Won a Weekend Away\n");
                            else
                                printf("You Won a Night Out\n");
                            break;
                        }
                        case 5:
                        {
                            if ( b_match > 0 )
                                printf("You Won a New Car\n");
                            else
                                printf("You Won a Holiday\n");
                            break;
                        }
                        case 6:
                        {
                            printf("You Won the JACKPOT!!!\n");
                            break;
                        }
                        default:
                        {
                            printf("You Lost :(\n");
                        }
                    }//end switch
                    
        		}//end else
                break;
        	}//end case 4
        	case '5':
        	{
                if ( numbersEntered == 0 )
                {
                    printf("**You did not Enter Your Numbers\n");
                }//end if
        		else //get frequency
        		{
                    frequency( freq );
                }//end else
                break;
        	}//end case 5
        	case '0':
        	{
        		exitp();
        		break;
        	}//end case 0
        	default:
        	{
                system("cls");//clears the screen
                printf("**Error: Input value not valid\n\n");
            }
        }//end switch

        printf("\n\n**Press Enter to Continue");
        getchar();
    }//end do
    while ( option != '0' );
} //end main


/*IMPLEMENT FUNCTIONS*/

void getInput( int *num, int *freq )
{
    register int i, j;
    int before;

    for ( i = 0; i < SIZE; i++ )
    {
        before = 0; // not found before each time
        do
        {
            printf("Enter Number %d:  ", i+1);
            scanf("%d", (num+i) );
            flushall();  // clear buffer
            
            // validate
            //
            if ( *(num+i) < MIN || *(num+i) > MAX )
            {
                printf("**Number must be between ( 1 - 42 )\n\n");
            }//end if
        }
        while( *(num+i) < MIN || *(num+i) > MAX );

        //check if number entered before - (2nd check)
        //
        for ( j = 0; j < i; j++ )
        {
            if ( *(num+i) == *(num+j) )
            {
                printf("**Number Already Entered\n\n");
                before = 1; // entered before
                i--;   // ask for previos number again
                break; // break out of loop
            }//end if
        }//end for j

        if ( before == 0 ) // if before == 0, not found before - number passed second check
        {
            //increment frequency
            //
            ( *( freq + num[i] ) )++; // ( *( freq + *(num+i) ) )++ // num[i] is the number, same as position
        }

    }//end for i
}//end getInput()

void displayInput( int *num )
{
	register int i;
    printf("You Entered:\n\n");
    for ( i = 0; i < SIZE; i++ )
    {
        printf("%d  ", *(num+i) );
    }//end for
}//end displayInput()

void sort(int *num)
{
	register int i, j;
    for ( i = 0; i < SIZE; i++ )
        for ( j = 0; j < SIZE-1-i; j++)
        {
            if ( *(num+j) > *(num+(j+1)) )
            {
                // swap
                //
                *( num+(j+1) ) = *( num+(j+1) ) + *( num + j );
                *( num + j )   = *( num+(j+1) ) - *( num + j );
                *( num+(j+1) ) = *( num+(j+1) ) - *( num + j );

                //same as:
                /*
                                num[j+1] = num[j+1] + num[j];
                                num[j]   = num[j+1] - num[j];
                                num[j+1] = num[j+1] - num[j];
                                */
            }//end if
        }//end for j

    displayInput(num); // display array after it is sorted
}//end sort()

int compare(int *num, int *win)
{
	// see if match
    //
    int match = 0; // not matched yet
    register int i, j;
    
    for ( i = 0; i < SIZE; i++ )
    {
        for ( j = 0; j < SIZE; j++ )
        {
            if ( *(num+i) == *(win+j) )
                match++; // found 1 match
        }//end for j
    }//end for i
    
    // return number of elements that matched
    //
    return match;
}//end compare()

void frequency( int *freq )
{
    // print table of numbers and frequency
    //
    register int i;
    printf("Number\t| Frequency\n");
    printf("_____________________\n");
    for ( i = 1; i < MAX+1; i++ )
    {
        if ( *(freq + i) > 0 )
            printf("%d\t| %d\n", i, *(freq+i) );
    }//end for
}//end frequency()

void exitp( void )
{
    printf("\n\n\n");
    printf("________________________________________________________________________________\n");
    printf("\t\t\tThank You For Participating\n");
    printf("________________________________________________________________________________\n\n");
}//end exitp()