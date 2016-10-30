/*
Program to combine and sort 3 lists of students - All students sorted by their ID - only IDs are sorted, need fix
Salaheldin AKl
21 April 2016
*/

#include <stdio.h>
#include <string.h>

#define SIZE_I 10 // number of international
#define SIZE_F 20 // number of funded
#define SIZE_N 6  // number of non-funded
#define LENGTH 15 // length of each name

// structure of student ID. example: C 15124122
struct ID {
	char letter;
	int num;
};

// structure for student information
struct student {
	char name[LENGTH];
	char surname[LENGTH];
	struct ID id;
};

// define arrays of students
struct student international[SIZE_I];
struct student nonFunded[SIZE_N];
struct student funded[SIZE_F];
// all
struct student allStudents[SIZE_I + SIZE_N + SIZE_F];

// fxn prototypes
void student_information(void);
void insertionSort(struct student *, int);
void mergeSort(struct student *, int, int);
void merge(struct student *, int, int, int);
void combine(void);

main()
{
	// load student data
	student_information();
	// sort international students
	insertionSort(international, SIZE_I);
	// sort non-funded array
	insertionSort(nonFunded, SIZE_N);
	// sort funded array
	mergeSort(funded, 0, SIZE_F-1);
	// combine all in 1 list
	combine();

	char target[21];
	char choose = 'a';
	int found = 0;
	int i;

	while (choose != '0')
	{
		system("cls");

		printf("Pick an option or 0 to exit Program:\n\n");
		printf("____________________________________________________________________________\n\n");
		printf("1 - Display combined sorted list\n\n");
		printf("2 - Display only International Students\n\n");
		printf("3 - Search for a student by Surname\n\n");
		printf("____________________________________________________________________________\n\n");
		printf("Option:  ");
		scanf("%1s", &choose);
		
		system("cls");

		switch (choose) {
			case '1':
				// display full list
				for (i = 0; i < SIZE_I + SIZE_F + SIZE_N; i++) {
					printf("%c%d - %s %s\n", allStudents[i].id.letter, allStudents[i].id.num, allStudents[i].name, allStudents[i].surname);
				}
				break;

			case '2':
				for (i = 0; i < SIZE_I + SIZE_F + SIZE_N; i++) {
					if (allStudents[i].id.letter == 'D') {
						printf("%c%d - %s %s\n", allStudents[i].id.letter, allStudents[i].id.num, allStudents[i].name, allStudents[i].surname);
					}
				}
				break;

			case '3':
				printf("Enter a surname to search for:  ");
				scanf("%20s", target);
				for (i = 0; i < SIZE_I + SIZE_F + SIZE_N; i++) {
					if ( strcmp(allStudents[i].surname, target) == 0) {
						printf("%c%d - %s %s\n", allStudents[i].id.letter, allStudents[i].id.num, allStudents[i].name, allStudents[i].surname);
						found++;
					}
				}
				if (found == 0) // not found
					printf("Student not found\n");
				break;
		}
		getchar();
		printf("Enter to Continue\n");
		getchar();
	}
}//end main()

// fxn Implementation
//

void insertionSort(struct student *A, int N)
{
    register int i, j;
    int temp;
    
    for ( i = 1; i < N; i++ )
    {
        temp = A[i].id.num;
        j = i;
        while ( A[j-1].id.num > temp && j > 0 )
        {
            A[j].id.num = A[j-1].id.num;
            j--;
        }//end while
        A[j].id.num = temp;
    }//end for i

}//end insertion()

void mergeSort(struct student A[], int low, int high)
{
    if (low == high)
        return;
    else
    {
        int mid = (low + high) / 2;
        mergeSort(A, low, mid);
        mergeSort(A, mid + 1, high);
        merge(A, low, mid, high);
    }//end else
}//end sort()

void merge(struct student arr[], int min, int mid, int max)
{
    static int temp[SIZE_F] = {0};
    int i, left_i, right_i, j;
    left_i = min;
    right_i = mid + 1;

    for (i = min; left_i <= mid && right_i <= max; i++)
    {
        if (arr[left_i].id.num <= arr[right_i].id.num)
        {
            temp[i] = arr[left_i].id.num;
            left_i++;
        }
        else
        {
            temp[i] = arr[right_i].id.num;
            right_i++;
        }
    }
    if (left_i > mid)
    {
        for (j = right_i; j <= max; j++)
        {
            temp[i] = arr[j].id.num;
            i++;
        }
    }
    else
    {
        for (j = left_i; j <= mid; j++)
        {
            temp[i] = arr[j].id.num;
            i++;
        }
    }
    for (j = min; j <= max; j++)
        arr[j].id.num = temp[j];

}//end merge()

void combine(void)
{
	int all_i = 0;
	int n_i = 0;
	int f_i = 0;
	int i;
	// copy non-funded and funded while comparing (similar to merge)
	//
	while (all_i < SIZE_F + SIZE_N) {
		// if one list reached the end, just copy the other list
		if (n_i == SIZE_N) { // nonfunded list all copied
			// copy funded list
			while (f_i < SIZE_F) {
				allStudents[all_i] = funded[f_i];
				all_i++;
				f_i++;
			}
		}
		else if (f_i == SIZE_F) { // funded list all copied
			// copy non-funded list
			while (n_i < SIZE_N) {
				allStudents[all_i] = funded[n_i];
				all_i++;
				n_i++;
			}
		}
		// if not above, neither list ended - check whick id is smaller
		else if ( nonFunded[n_i].id.num < funded[f_i].id.num ) {
			// copy nonFunded[n_i] to combined list
			allStudents[all_i] = nonFunded[n_i];
			all_i++;
			n_i++;
		}
		else { // last option is funded ID is smaller
			allStudents[all_i] = funded[f_i];
			all_i++;
			f_i++;
		}
	}// end while

	// after while loop, funded and non-funded copied to list. Just copy the internnational list to combined list
	for (i = 0; i < SIZE_I; i++) {
		allStudents[all_i] = international[i];
		all_i++;
	}
}





void student_information()
{
	int index;

	// International Students:
	//

	// set all ID letters to 'D'
	for (index = 0; index < SIZE_I; index++)
	{
		international[index].id.letter = 'D';
	}

	strcpy(international[0].name, "Willie");
	strcpy(international[0].surname, "Rick");
	international[0].id.num  = 86744948;

	strcpy(international[1].name, "Allegra");
	strcpy(international[1].surname, "Marlin");
	international[1].id.num  = 38754698;

	strcpy(international[2].name, "Rosanna");
	strcpy(international[2].surname, "Nicky");
	international[2].id.num  = 93705477;

	strcpy(international[3].name, "Jacquelyn");
	strcpy(international[3].surname, "Joe");
	international[3].id.num  = 69426869;

	strcpy(international[4].name, "Sadie");
	strcpy(international[4].surname, "Arnoldo");
	international[4].id.num  = 76017626;

	strcpy(international[5].name, "Tomoko");
	strcpy(international[5].surname, "Morgan");
	international[5].id.num  = 70704541;

	strcpy(international[6].name, "Elsy");
	strcpy(international[6].surname, "Sherman");
	international[6].id.num  = 43372395;

	strcpy(international[7].name, "Tarah");
	strcpy(international[7].surname, "Milford");
	international[7].id.num  = 57894261;

	strcpy(international[8].name, "Jenna");
	strcpy(international[8].surname, "Dong");
	international[8].id.num  = 27306001;

	strcpy(international[9].name, "Francene");
	strcpy(international[9].surname, "Sang");
	international[9].id.num  = 86628417;


	// Non Funded Students
	//

	// set all ID letters to 'C'
	for (index = 0; index < SIZE_N; index++)
	{
		nonFunded[index].id.letter = 'C';
	}

	strcpy(nonFunded[0].name, "Rossie");
	strcpy(nonFunded[0].surname, "Lonny");
	nonFunded[0].id.num  = 14155318;

	strcpy(nonFunded[1].name, "Evie");
	strcpy(nonFunded[1].surname, "Harris");
	nonFunded[1].id.num  = 71258614;

	strcpy(nonFunded[2].name, "Alethea");
	strcpy(nonFunded[2].surname, "Dannie");
	nonFunded[2].id.num  = 44649640;

	strcpy(nonFunded[3].name, "Cristie");
	strcpy(nonFunded[3].surname, "Claude");
	nonFunded[3].id.num  = 29031652;

	strcpy(nonFunded[4].name, "Celine");
	strcpy(nonFunded[4].surname, "Lemuel");
	nonFunded[4].id.num  = 41248377;

	strcpy(nonFunded[5].name, "Chia");
	strcpy(nonFunded[5].surname, "Lauren");
	nonFunded[5].id.num  = 85436792;


	// Funded Students
	//

	// set all ID letters to 'C'
	for (index = 0; index < SIZE_F; index++)
	{
		funded[index].id.letter = 'C';
	}

	strcpy(funded[0].name, "Sheena");
	strcpy(funded[0].surname, "Luke");
	funded[0].id.num  = 53989712;

	strcpy(funded[1].name, "Darcy");
	strcpy(funded[1].surname, "Maynard");
	funded[1].id.num  = 16159764;

	strcpy(funded[2].name, "Ilse");
	strcpy(funded[2].surname, "Hugh");
	funded[2].id.num  = 19220175;

	strcpy(funded[3].name, "Elyse");
	strcpy(funded[3].surname, "Christopher");
	funded[3].id.num  = 52340557;

	strcpy(funded[4].name, "Raquel");
	strcpy(funded[4].surname, "Santo");
	funded[4].id.num  = 77703516;

	strcpy(funded[5].name, "Melinda");
	strcpy(funded[5].surname, "Edison");
	funded[5].id.num  = 45765434;

	strcpy(funded[6].name, "Carmine");
	strcpy(funded[6].surname, "Fabian");
	funded[6].id.num  = 31997488;

	strcpy(funded[7].name, "Yevette");
	strcpy(funded[7].surname, "Jean");
	funded[7].id.num  = 47943702;

	strcpy(funded[8].name, "Claudio");
	strcpy(funded[8].surname, "Virgil");
	funded[8].id.num  = 70664866;

	strcpy(funded[9].name, "Kayla");
	strcpy(funded[9].surname, "Emerson");
	funded[9].id.num  = 26067319;

	strcpy(funded[10].name, "Holli");
	strcpy(funded[10].surname, "Clifton");
	funded[10].id.num  = 11980054;

	strcpy(funded[11].name, "Pilar");
	strcpy(funded[11].surname, "Lazaro");
	funded[11].id.num  = 99278820;

	strcpy(funded[12].name, "Liana");
	strcpy(funded[12].surname, "Jacob");
	funded[12].id.num  = 84692135;

	strcpy(funded[13].name, "Billie");
	strcpy(funded[13].surname, "Ryan");
	funded[13].id.num  = 49841428;

	strcpy(funded[14].name, "Faith");
	strcpy(funded[14].surname, "Lucio");
	funded[14].id.num  = 23981038;

	strcpy(funded[15].name, "Keven");
	strcpy(funded[15].surname, "Armand");
	funded[15].id.num  = 53489967;

	strcpy(funded[16].name, "Stevie");
	strcpy(funded[16].surname, "Jerrold");
	funded[16].id.num  = 37306589;

	strcpy(funded[17].name, "Annalee");
	strcpy(funded[17].surname, "Aldo");
	funded[17].id.num  = 50661519;

	strcpy(funded[18].name, "Joel");
	strcpy(funded[18].surname, "Fausto");
	funded[18].id.num  = 53661519;

	strcpy(funded[19].name, "Hubert");
	strcpy(funded[19].surname, "Roderick");
	funded[19].id.num  = 77062226;
}// end student_information()