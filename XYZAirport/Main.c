#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

#define ENTER 13
#define TAB 9
#define BKSP 8


struct node
{
	int passportNo;
	char firstName[20];
	char surname[20];
	int dob;
	char email[30];
	int area;
	int class;
	int frequency;
	int duration;
	struct node* NEXT;
};

// login
void login();

// add passengers
void AddPassengerAtStart(struct node** top);
void AddPassengerAtEnd(struct node* top);

// display
void DisplayPassengers(struct node* top);
void DisplayPassengerDetails(struct node* top);

// edit
void EditPassenger(struct node* top);

// delete passengers
void DeletePassengerAtStart(struct node** top);
void DeletePassengerAtEnd(struct node* top);
void DeletePassengerAtPos(struct node* top, int pos);

// stats
void TravelStats1980(struct node* top);
void TravelClassStats(struct node* top);
void PassengerStats(struct node* top);
void UkPassengers(struct node* top, int size);

// length
int Length(struct node* top);

// files
void PassengerFile(FILE** Database, FILE** Passenger, struct node* top, int size);
struct node* LoadFile(FILE** LoadFile, struct node* top);

// validation
int PassportNoComp(struct node* top, int passport);
char *CheckEmail(char *email);

void main()
{
	// files
	FILE* Passenger;
	FILE* ReportFile;
	FILE* OutFile;

	struct node* headPtr = NULL;

	// variables
	int choice;
	int num = 0;
	int result;
	int pos;
	int menu;
	
	// calling login function
	login();
	
	do
	{
		printf("Welcome to the XYZ Airport Database\n");
		printf("Please choose an option:\n");
		printf("Please enter 1 to load passenger Details from file\n");
		printf("Please enter 2 to start a new database\n");
		printf("Please enter -1 to exit\n");
		scanf("%d", &menu);

	} while (menu < 1 || menu > 2); // do while

	// switch to load or start new file
	switch (menu)
	{
	case 1:
		LoadFile(&PassengerFile, headPtr);
		break;
	case 2:
		break;
	}//switch

	printf("Please choose one of the following options:\n");
	printf("Please enter 1 to add passenger\n");
	printf("Please enter 2 to display all passengers\n");
	printf("Please enter 3 to display passenger details\n");
	printf("Please enter 4 to update passenger details\n");
	printf("Please enter 5 to delete a passenger\n");
	printf("Please enter 6 to generate statistics\n");
	printf("Please enter 7 to print passenger statistics to a report file\n");
	printf("Please enter 8 to list all passengers from the UK\n");
	printf("Please enter -1 to exit\n");
	scanf("%d", &choice);
	
	// while to loop through options
	while (choice != -1)
	{
		switch (choice)
		{
		case 1:
			if (headPtr == NULL)
			{
				AddPassengerAtStart(&headPtr);
			}// if
			else
			{
				AddPassengerAtEnd(headPtr);
			}// else
			break;
		case 2:
			if (headPtr == NULL)
			{
				printf("Sorry your database is empty please select another option\n");
			}// if
			else
			{
				DisplayPassengers(headPtr);
			}// else
			break;
		case 3:
			if (headPtr == NULL)
			{
				printf("Sorry your database is empty please select another option\n");
			}// if
			else
			{
				DisplayPassengerDetails(headPtr);
			}// else
			break;
		case 4:
			if (headPtr == NULL)
			{
				printf("Sorry your database is empty please select another option\n");
			}// if
			else
			{
				EditPassenger(headPtr);
			}// else
			break;
		case 5:
			printf("Please enter the position of the passenger you wish to delete:\n");
			scanf("%d", &pos);

			if (headPtr == NULL)
			{
				printf("Sorry your database is empty please select another option\n");
			}// if
			else
			{
				if (pos < 2)
				{
					DeletePassengerAtStart(&headPtr);
				}// inner if
				else if (pos >= 2 && pos < Length(headPtr))
				{
					DeletePassengerAtPos(headPtr, pos);
				}// inner if else
				else
				{
					DeletePassengerAtEnd(headPtr);
				}// inner else
			}// else
			break;
		case 6:
			if (headPtr == NULL)
			{
				printf("Sorry your database is empty please select another option\n");
			}// if
			else
			{
				PassengerStats(headPtr);
			}// else
			break;
		case 7:
			if (headPtr == NULL)
			{
				printf("Sorry your database is empty please select another option\n");
			}// if
			else
			{
				PassengerFile(&OutFile, &Passenger, headPtr, Length(headPtr));
			}// else
			break;
		case 8:
			if (headPtr == NULL)
			{
				printf("Sorry your database is empty please select another option\n");
			}// if
			else
			{
				UkPassengers(headPtr, Length(headPtr));
			}// else
			break;
		case -1:
			//function to save to file
			PassengerFile(&OutFile, &Passenger, headPtr, Length(headPtr));
			break;
		default:
			printf("Sorry that is an invalid option. Please try again\n");
		}// switch

		printf("\nPlease choose one of the following options:\n");
		printf("Please enter 1 to add passenger\n");
		printf("Please enter 2 to display all passengers\n");
		printf("Please enter 3 to display passenger details\n");
		printf("Please enter 4 to update passenger details\n");
		printf("Please enter 5 to delete a passenger\n");
		printf("Please enter 6 to generate statistics\n");
		printf("Please enter 7 to print passenger statistics to a report file\n");
		printf("Please enter 8 to list all passengers from the UK\n");
		printf("Please enter -1 to exit\n");
		scanf("%d", &choice);
	}

	return 0;
}// main

void login()
{
	FILE *pass_file;
	int i;
	char ch;
	char username[30];
	char password[30];
	const char fileName[30];
	const char filePass[30];

	//opens txt file with usernames and passwords
	pass_file = fopen("login.txt", "r");

	// reads in the usernames and passwords
	fscanf(pass_file, "Username: %s Password: %s", fileName, filePass);

	printf("Username: ");
	scanf("%s", username);
	printf("Password: ");
	scanf("%s", password);

	// ***** tried two methods to mask password but none were working ***** //
	
	/*while (1)
	{
		ch = _getch();

		if (ch == ENTER || ch == TAB)
		{
			password[i] = '\0';
			break;
		}
		else if (ch == BKSP)
		{
			if (i > 0)
			{
				i--;
				printf("\b \b");
			}
		}
		else
		{
			password[i++] = ch;
			printf("*");
		}
	}*/

	/*for (i = 0; i<6; i++)
	{
		password[i] = _getch();
		ch = password[i];
		ch = '*';
		printf("%c", ch);
	}
	password[i] = ch;*/
	
	// compares input to file
	if ((strcmp(username, fileName) == 0) && (strcmp(password, filePass) == 0))
	{
		printf("\nLogin Successful !!!");
	}// if
	else
	{
		printf("\nSorry, invalid login details !!!\n\n");
		exit(0);
	}// else

	printf("\n\n");

	// close file
	fclose(pass_file);
	return 0;
} // login

void AddPassengerAtStart(struct node** top)
{
	struct node* newNode;
	newNode = (struct node*)malloc(sizeof(struct node) * 1);
	int passport;
	char tempEmail[30];

	// read in passenger number
	printf("\nPlease enter passengers passport number: ");
	scanf("%d", &passport);
	
	// compares passenegers number with other passengers on file
	if (top != NULL)
	{
		PassportNoComp(top, passport);
	}// if
	else
	{
		passport = newNode->passportNo;
	}// else

	printf("\nPlease enter passengers first name: ");
	scanf("%s", newNode->firstName);
	
	printf("\nPlease enter passengers surname: ");
	scanf("%s", newNode->surname);

	printf("\nPlease enter passengers year of birth (YYYY): ");
	scanf("%d", &newNode->dob);

	do
	{
		printf("\nPlease enter passengers email address: ");
		scanf("%s", tempEmail);

	} while (CheckEmail(tempEmail) == NULL);// do while

	strcpy(newNode->email, tempEmail);

	printf("\nPlease enter where passenger has travelled from: ");
	printf("\nPlease enter 1 if the passenger has travelled from the UK ");
	printf("\nPlease enter 2 if the passenger has travelled from the Rest of Europe ");
	printf("\nPlease enter 3 if the passenger has travelled from Asia ");
	printf("\nPlease enter 4 if the passenger has travelled from the Americas ");
	printf("\nPlease enter 5 if the passenger has travelled from Australasia: ");
	scanf("%d", &newNode->area);

	switch (newNode->area)
	{
	case 1:
		newNode->area = "UK";
		break;
	case 2:
		newNode->area = "Rest of Europe";
		break;
	case 3:
		newNode->area = "Asia";
		break;
	case 4:
		newNode->area = "Americas";
		break;
	case 5:
		newNode->area = "Australasia";
		break;
	default:
		printf("\nSorry that is an invalid option. Please try again\n");
	}// switch

	printf("\nPlease enter passengers travel class: ");
	printf("\nPlease enter 1 if the passenger has travelled in economy class: ");
	printf("\nPlease enter 2 if the passenger has travelled in premium economy: ");
	printf("\nPlease enter 3 if the passenger has travelled in business class: ");
	printf("\nPlease enter 4 if the passenger has travelled in first class: ");
	scanf("%d", &newNode->class);

	switch (newNode->class)
	{
	case 1:
		newNode->class = "Economy";
		break;
	case 2:
		newNode->class = "Premium Economy";
		break;
	case 3:
		newNode->class = "Business";
		break;
	case 4:
		newNode->class = "First Class";
		break;
	default:
		printf("Sorry that is an invalid option. Please try again\n");
	}// switch

	printf("\nPlease enter the frequency of the passengers visits to Ireland: ");
	printf("\nPlease enter 1 if the passenger has travelled less than three times per year: ");
	printf("\nPlease enter 2 if the passenger has travelled less than five times per year: ");
	printf("\nPlease enter 3 if the passenger has travelled more than five times per year: ");
	scanf("%d", &newNode->frequency);

	switch (newNode->frequency)
	{
	case 1:
		newNode->frequency = "Less than three times ";
		break;
	case 2:
		newNode->frequency = "Less than five times ";
		break;
	case 3:
		newNode->frequency = "More than five times ";
		break;
	default:
		printf("Sorry that is an invalid option. Please try again\n");
	}// switch

	printf("\nPlease enter the intended duration of the passengers stay: ");
	printf("\nPlease enter 1 if the passengers stay is one day: ");
	printf("\nPlease enter 2 if the passengers stay is less than three days: ");
	printf("\nPlease enter 3 if the passengers stay is less than seven days: ");
	printf("\nPlease enter 4 if the passenger stay is more than seven days: ");
	scanf("%d", &newNode->duration);

	switch (newNode->duration)
	{
	case 1:
		newNode->duration = "One day";
		break;
	case 2:
		newNode->duration = "Less than three days ";
		break;
	case 3:
		newNode->duration = "Less than seven days ";
		break;
	case 4:
		newNode->duration = "More than seven days ";
		break;
	default:
		printf("Sorry that is an invalid option. Please try again\n");
	}// switch

	newNode->NEXT = *top;
	*top = newNode;

}// AddPassengerAtStart

void AddPassengerAtEnd(struct node* top)
{
	struct node* curr;
	struct node* newNode;

	newNode = (struct node*)malloc(sizeof(struct node) * 1);

	printf("\nPlease enter passengers passport number: ");
	scanf("%d", &newNode->passportNo);

	printf("\nPlease enter passengers first name: ");
	scanf("%s", newNode->firstName);

	printf("\nPlease enter passengers surname: ");
	scanf("%s", newNode->surname);

	printf("\nPlease enter passengers date of birth (YYYY): ");
	scanf("%d", &newNode->dob);

	printf("\nPlease enter passengers email address: ");
	scanf("%s", newNode->email);

	printf("\nPlease enter where passenger has travelled from: ");
	printf("\nPlease enter 1 if the passenger has travelled from the UK ");
	printf("\nPlease enter 2 if the passenger has travelled from the Rest of Europe ");
	printf("\nPlease enter 3 if the passenger has travelled from Asia ");
	printf("\nPlease enter 4 if the passenger has travelled from the Americas ");
	printf("\nPlease enter 5 if the passenger has travelled from Australasia: ");
	scanf("%d", &newNode->area);

	switch (newNode->area)
	{
	case 1:
		newNode->area = "UK";
		break;
	case 2:
		newNode->area = "Rest of Europe";
		break;
	case 3:
		newNode->area = "Asia";
		break;
	case 4:
		newNode->area = "Americas";
		break;
	case 5:
		newNode->area = "Australasia";
		break;
	default:
		printf("\nSorry that is an invalid option. Please try again\n");
	}// switch

	printf("\nPlease enter passengers travel class: ");
	printf("\nPlease enter 1 if the passenger has travelled in economy class: ");
	printf("\nPlease enter 2 if the passenger has travelled in premium economy: ");
	printf("\nPlease enter 3 if the passenger has travelled in business class: ");
	printf("\nPlease enter 4 if the passenger has travelled in first class: ");
	scanf("%d", &newNode->class);

	switch (newNode->class)
	{
	case 1:
		newNode->class = "Economy ";
		break;
	case 2:
		newNode->class = "Premium Economy ";
		break;
	case 3:
		newNode->class = "Business ";
		break;
	case 4:
		newNode->class = "First Class ";
		break;
	default:
		printf("Sorry that is an invalid option. Please try again\n");
	}// switch

	printf("\nPlease enter the frequency of the passengers visits to Ireland: ");
	printf("\nPlease enter 1 if the passenger has travelled less than three times per year: ");
	printf("\nPlease enter 2 if the passenger has travelled less than five times per year: ");
	printf("\nPlease enter 3 if the passenger has travelled more than five times per year: ");
	scanf("%d", &newNode->frequency);

	switch (newNode->frequency)
	{
	case 1:
		newNode->frequency = "Less than three times ";
		break;
	case 2:
		newNode->frequency = "Less than five times ";
		break;
	case 3:
		newNode->frequency = "More than five times ";
		break;
	default:
		printf("Sorry that is an invalid option. Please try again\n");
	}// switch

	printf("\nPlease enter the intended duration of the passengers stay: ");
	printf("\nPlease enter 1 if the passengers stay is one day: ");
	printf("\nPlease enter 2 if the passengers stay is less than three days: ");
	printf("\nPlease enter 3 if the passengers stay is less than seven days: ");
	printf("\nPlease enter 4 if the passenger stay is more than seven days: ");
	scanf("%d", &newNode->duration);

	switch (newNode->duration)
	{
	case 1:
		newNode->duration = "One day";
		break;
	case 2:
		newNode->duration = "Less than three days ";
		break;
	case 3:
		newNode->duration = "Less than seven days ";
		break;
	case 4:
		newNode->duration = "More than seven days ";
		break;
	default:
		printf("Sorry that is an invalid option. Please try again\n");
	}// switch

	curr = top;

	while (curr->NEXT != NULL)
	{
		curr = curr->NEXT;
	}// while

	curr->NEXT = newNode;
	newNode->NEXT = NULL;

}// AddPassengerAtEnd

void DisplayPassengers(struct node* top)
{
	struct node* curr;
	
	curr = top;

	while (curr != NULL)
	{
		printf("Passport Number: %d Name: %s %s\n", curr->passportNo, curr->firstName, curr->surname);
		curr = curr->NEXT;
	}// while
}// DisplayPassengers

void DisplayPassengerDetails(struct node* top)
{
	int number;

	struct node* curr;

	curr = top;

	printf("Please enter the passport number of the passenger you wish to display: ");
	scanf("%d", &number);

	while (curr != NULL)
	{
		if (number == curr->passportNo)
		{
			printf("Name: %s %s\n", curr->firstName, curr->surname);
			printf("Date of Birth: %d\n", curr->dob);
			printf("Email: %s\n", curr->email);
			printf("Travelled from: %s\n", curr->area);
			printf("Class: %s\n", curr->class);
			printf("Frequency: %s\n", curr->frequency);
			printf("Duration: %s\n", curr->duration);
			return;
		}// inner if
		
		curr = curr->NEXT;
	}// while

	if (number != curr->passportNo)
	{
		printf("Sorry passenger does not exist\n");
	}// if
	
}// DisplayPassengerDetails

void EditPassenger(struct node* top)
{
	int number;

	struct node* curr;

	curr = top;

	printf("Please enter the passport number of the passenger you wish to edit: ");
	scanf("%d", &number);

	while (curr != NULL)
	{
		if (number == curr->passportNo)
		{
			printf("\nPlease enter where passenger has travelled from: ");
			printf("\nPlease enter 1 if the passenger has travelled from the UK ");
			printf("\nPlease enter 2 if the passenger has travelled from the Rest of Europe ");
			printf("\nPlease enter 3 if the passenger has travelled from Asia ");
			printf("\nPlease enter 4 if the passenger has travelled from the Americas ");
			printf("\nPlease enter 5 if the passenger has travelled from Australasia: ");
			scanf("%d", &curr->area);

			switch (curr->area)
			{
			case 1:
				curr->area = "UK";
				break;
			case 2:
				curr->area = "Rest of Europe";
				break;
			case 3:
				curr->area = "Asia";
				break;
			case 4:
				curr->area = "Americas";
				break;
			case 5:
				curr->area = "Australasia";
				break;
			default:
				printf("\nSorry that is an invalid option. Please try again\n");
			}// switch

			printf("\nPlease enter the intended duration of the passengers stay: ");
			printf("\nPlease enter 1 if the passengers stay is one day: ");
			printf("\nPlease enter 2 if the passengers stay is less than three days: ");
			printf("\nPlease enter 3 if the passengers stay is less than seven days: ");
			printf("\nPlease enter 4 if the passenger stay is more than seven days: ");
			scanf("%d", &curr->duration);

			switch (curr->duration)
			{
			case 1:
				curr->duration = "One day";
				break;
			case 2:
				curr->duration = "Less than three days ";
				break;
			case 3:
				curr->duration = "Less than seven days ";
				break;
			case 4:
				curr->duration = "More than seven days ";
				break;
			default:
				printf("Sorry that is an invalid option. Please try again\n");
			}// switch
			return;
		}// if

		curr = curr->NEXT;

	}// while

	if (number != curr->passportNo)
	{
		printf("Sorry passenger does not exist\n");
	}// if
}// EditPassenger

void DeletePassengerAtStart(struct node** top)
{
	struct node* curr;

	curr = *top;

	*top = curr->NEXT;

	free(curr);

}// DeletePassengerAtStart

void DeletePassengerAtEnd(struct node* top)
{
	struct node* curr;
	struct node* prev;

	curr = top;
	prev = NULL;

	while (curr->NEXT != NULL)
	{
		prev = curr;
		curr = curr->NEXT;
	}//while

	prev->NEXT = NULL;

	free(curr);

}// DeletePassengerAtEnd

void DeletePassengerAtPos(struct node* top, int pos)
{
	int number, i;

	struct node* curr;
	struct node* prev_curr;

	curr = top;
	prev_curr = NULL;
	
		for (i = 0; i < pos - 1; i++)
		{
			prev_curr = curr;
			curr = curr->NEXT;
		}// for
	
	prev_curr->NEXT = curr->NEXT;
	free(curr);
}// DeletePassengerAtPos

void PassengerStats(struct node* top)
{
	int option;

	printf("Please enter an option to generate statistics:\n");
	printf("Please enter 1 to generate stats based on Travel Class");
	printf("Please enter 2 to generate stats based on passengers Born Before 1980");
	scanf("%d", &option);

	switch (option)
	{
	case 1:
		TravelClassStats(top);
		break;
	case 2:
		TravelStats1980(top);
		break;
	default:
		printf("\nInvalid option !!\n");
	}//switch

}// PassengerStats

void TravelClassStats(struct node* top)
{
	struct node* curr;

	int listCount = 0, choice;
	int statCount1 = 0, statCount2 = 0, statCount3 = 0;
	int statCount4 = 0, statCount5 = 0, statCount6 = 0;
	int statCount7 = 0, statCount8 = 0, statCount9 = 0;

	char travelClass[30];
	float perCent;

	curr = top;

	while (curr != NULL)
	{
		listCount++;
		curr = curr->NEXT;
	}// while

	curr = top;

	do
	{
		printf("\nPlease Select Travel Class to Generate Statistics\n");
		printf("1. Economy\n");
		printf("2. Premium Economy\n");
		printf("3. Business Class\n");
		printf("4. First Class\n");
		scanf("%d", &choice);

	} while (choice < 1 || choice > 4);// do while

	switch (choice)
	{
	case 1:
		strcpy(travelClass, "Economy");
		break;
	case 2:
		strcpy(travelClass, "Premium Economy");
		break;
	case 3:
		strcpy(travelClass, "Business Class");
		break;
	case 4:
		strcpy(travelClass, "First Class");
		break;
	default:
		printf("Invalid option !!\n");
	}//switch

	while (curr != NULL)
	{
		if (strcmp(curr->area, "UK") == 0 && strcmp(curr->class, travelClass) == 0)
		{
			statCount1++;
		}// inner if

		curr = curr->NEXT;

	}//while

	perCent = ((float)statCount1 / listCount) * 100;

	printf("\nPercentage of Passengers in Database who travel from the UK & in Travel class %s is %.2f %%\n", travelClass, perCent);

	while (curr != NULL)
	{
		if (strcmp(curr->area, "Rest of Europe") == 0 && strcmp(curr->class, travelClass) == 0)
		{
			statCount2++;
		}//if

		curr = curr->NEXT;

	}//while

	perCent = ((float)statCount2 / listCount) * 100;

	printf("\nPercentage of Passengers in Database who travel from the Rest of Europe & in Travel class %s is %.2f %%\n", travelClass, perCent);

	while (curr != NULL)
	{
		if (strcmp(curr->area, "Asia") == 0 && strcmp(curr->class, travelClass) == 0)
		{
			statCount3++;
		}// inner if

		curr = curr->NEXT;

	}//while

	perCent = ((float)statCount3 / listCount) * 100;

	printf("\nPercentage of Passengers in Database who travel from Asia & in Travel class %s is %.2f %%\n", travelClass, perCent);

	while (curr != NULL)
	{
		if (strcmp(curr->area, "Americas") == 0 && strcmp(curr->class, travelClass) == 0)
		{
			statCount4++;
		}// inner if

		curr = curr->NEXT;

	}//while

	perCent = ((float)statCount4 / listCount) * 100;

	printf("\nPercentage of Passengers in Database who travel from the Americas & in Travel class %s is %.2f %%\n", travelClass, perCent);

	while (curr != NULL)
	{
		if (strcmp(curr->area, "Australasia") == 0 && strcmp(curr->class, travelClass) == 0)
		{
			statCount5++;
		}// inner if

		curr = curr->NEXT;

	}//while

	perCent = ((float)statCount5 / listCount) * 100;

	printf("\nPercentage of Passengers in Database who travel from the Australasia & in Travel class %s is %.2f %%\n", travelClass, perCent);

	while (curr != NULL)
	{
		if (strcmp(curr->duration, "One Day") == 0 && strcmp(curr->class, travelClass) == 0)
		{
			statCount6++;
		}// inner if

		curr = curr->NEXT;

	}//while

	perCent = ((float)statCount6 / listCount) * 100;

	printf("\nPercentage of Passengers in Database who spent on Average one day in Ireland & in Travel class %s is %.2f %%\n", travelClass, perCent);

	while (curr != NULL)
	{
		if (strcmp(curr->duration, "Less than 3 Days") == 0 && strcmp(curr->class, travelClass) == 0)
		{
			statCount7++;
		}//inner if

		curr = curr->NEXT;

	}//while

	perCent = ((float)statCount7 / listCount) * 100;

	printf("\nPercentage of Passengers in Database who spent on Average less than 3 days in Ireland & in Travel class %s is %.2f %%\n", travelClass, perCent);

	while (curr != NULL)
	{
		if (strcmp(curr->duration, "Less than 7 Days") == 0 && strcmp(curr->class, travelClass) == 0)
		{
			statCount8++;
		}// inner if

		curr = curr->NEXT;

	}//while

	perCent = ((float)statCount8 / listCount) * 100;

	printf("\nPercentage of Passengers in Database who spent on Average less than 7 days in Ireland & in Travel class %s is %.2f %%\n", travelClass, perCent);

	while (curr != NULL)
	{
		if (strcmp(curr->duration, "More than 7 Days") == 0 && strcmp(curr->class, travelClass) == 0)
		{
			statCount9++;
		}// inner if

		curr = curr->NEXT;

	}//while

	perCent = ((float)statCount9 / listCount) * 100;

	printf("\nPercentage of Passengers in Database who spent on Average more than 7 days in Ireland & in Travel class %s is %.2f %%\n", travelClass, perCent);

}// TravelClassStats

void TravelStats1980(struct node* top)
{
	struct node* curr;

	int listCount = 0, choice;
	int statCount1 = 0, statCount2 = 0, statCount3 = 0;
	int statCount4 = 0, statCount5 = 0, statCount6 = 0;
	int statCount7 = 0, statCount8 = 0, statCount9 = 0;

	char travelClass[30];
	float perCent;

	curr = top;

	while (curr != NULL)
	{
		listCount++;
		curr = curr->NEXT;

	}//while

	curr = top;

	while (curr != NULL)
	{
		if (strcmp(curr->area, "UK") == 0 && curr->dob < 1980)
		{
			statCount1++;
		}// inner if

		curr = curr->NEXT;

	}//while

	perCent = ((float)statCount1 / listCount) * 100;

	printf("\nPercentage of Passengers born before 1980 who travel from the UK is %.2f %%\n", perCent);

	while (curr != NULL)
	{
		if (strcmp(curr->area, "Rest of Europe") == 0 && curr->dob < 1980)
		{
			statCount2++;
		}// inner if

		curr = curr->NEXT;

	}//while

	perCent = ((float)statCount2 / listCount) * 100;

	printf("\nPercentage of Passengers born before 1980 who travel from the Rest of Europe is %.2f %%\n", perCent);

	while (curr != NULL)
	{
		if (strcmp(curr->area, "Asia") == 0 && curr->dob < 1980)
		{
			statCount3++;
		}// inner if

		curr = curr->NEXT;

	}//while

	perCent = ((float)statCount3 / listCount) * 100;

	printf("\nPercentage of Passengers born before 1980 who travel from Asia is %.2f %%\n", perCent);

	while (curr != NULL)
	{
		if (strcmp(curr->area, "Americas") == 0 && curr->dob < 1980)
		{
			statCount4++;
		}// inner if

		curr = curr->NEXT;

	}//while

	perCent = ((float)statCount4 / listCount) * 100;

	printf("\nPercentage of Passengers born before 1980 who travel from the Americas is %.2f %%\n", perCent);

	while (curr != NULL)
	{
		if (strcmp(curr->area, "Australasia") == 0 && curr->dob < 1980)
		{
			statCount5++;
		}// inner if

		curr = curr->NEXT;

	}//while

	perCent = ((float)statCount5 / listCount) * 100;

	printf("\nPercentage of Passengers born before 1980 who travel from the Australasia is %.2f %%\n", perCent);

	while (curr != NULL)
	{
		if (strcmp(curr->duration, "One Day") == 0 && curr->dob < 1980)
		{
			statCount6++;
		}// inner if

		curr = curr->NEXT;

	}//while

	perCent = ((float)statCount6 / listCount) * 100;

	printf("\nPercentage of Passengers born before 1980 who spent on Average one day in Ireland is %.2f %%\n", perCent);

	while (curr != NULL)
	{
		if (strcmp(curr->duration, "Less than 3 Days") == 0 && curr->dob < 1980)
		{
			statCount7++;
		}// inner if

		curr = curr->NEXT;

	}//while

	perCent = ((float)statCount7 / listCount) * 100;

	printf("\nPercentage of Passengers born before 1980 who spent on Average less than 3 days in Ireland is %.2f %%\n", perCent);

	while (curr != NULL)
	{
		if (strcmp(curr->duration, "Less than 7 Days") == 0 && curr->dob < 1980)
		{
			statCount8++;
		}// inner if

		curr = curr->NEXT;

	}//while

	perCent = ((float)statCount8 / listCount) * 100;

	printf("\nPercentage of Passengers born before 1980 who spent on Average less than 7 days in Ireland is %.2f %%\n", perCent);

	while (curr != NULL)
	{
		if (strcmp(curr->duration, "More than 7 Days") == 0 && curr->dob < 1980)
		{
			statCount9++;
		}// inner if

		curr = curr->NEXT;

	}//while

	perCent = ((float)statCount9 / listCount) * 100;

	printf("\nPercentage of Passengers born before 1980 who spent on Average more than 7 days in Ireland is %.2f %%\n", perCent);

}// TravelStats1980

void UkPassengers(struct node* top, int size)
{
	struct node* curr;
	int *ptr, count = 0, temp;

	curr = top;

	ptr = (int*)malloc(size * sizeof(int));

	while (curr != NULL)
	{
		if (strcmp(curr->area, "UK") == 0)
		{
			*(ptr + count) = curr->dob;
			count++;
		}// inner if

		curr = curr->NEXT;

	}//while

	curr = top;

	for (int i = 0; i < count; i++)
	{
		for (int j = i + 1; j < count; j++)
		{
			if (*(ptr + i) > *(ptr + j))
			{
				temp = *(ptr + i);
				*(ptr + i) = *(ptr + j);
				*(ptr + j) = temp;
			}// inner if
		}// inner for

	}//for

	for (int i = 0; i < count; i++)
	{
		while (curr != NULL)
		{
			if (strcmp(curr->area, "UK") == 0 && *(ptr + i) == curr->dob)
			{
				printf("\nPassport Number: %d Passenger Name: %s %s Year of Birth: %d\n", curr->passportNo, curr->firstName, curr->surname, curr->dob);
			}// inner if

			curr = curr->NEXT;

		}// inner while

		curr = top;

	}//for

	free(ptr);

}// UkPassengers

struct node* LoadFile(FILE** LoadFile, struct node* top)
{
	//***** file could not load and not 100% sure why ***** //

		/*LoadFile = fopen("Passenger.txt", "r");

		if (LoadFile == NULL)
		{
			printf("\nFile could not be opened !!\n");
			return;
		}// if
		else
		{
			while (!feof(LoadFile))
			{

				if (top == NULL)
				{
					top = (struct node*)malloc(sizeof(struct node));

					fscanf(LoadFile, "%d", &top->passportNo);
					fscanf(LoadFile, "%30s", top->firstName);
					fscanf(LoadFile, "%30s", top->surname);
					fscanf(LoadFile, "%d", &top->dob);
					fscanf(LoadFile, "%30s", top->email);
					fscanf(LoadFile, "%30s", top->area);
					fscanf(LoadFile, "%30s", top->class);
					fscanf(LoadFile, "%30s", top->frequency);
					fscanf(LoadFile, "%30s", top->duration);

					top->NEXT = NULL;

					printf("Passport Number: %d", top->passportNo);
					printf("Name: %s %s\n", top->firstName, top->surname);
					printf("Date of Birth: %d\n", top->dob);
					printf("Email: %s\n", top->email);
					printf("Travelled from: %s\n", top->area);
					printf("Class: %s\n", top->class);
					printf("Frequency: %s\n", top->frequency);
					printf("Duration: %s\n", top->duration);

				}// inner if
				else
				{
					struct node* temp = top;

					struct node* curr = (struct node*)malloc(sizeof(struct node));

					fscanf(LoadFile, "%d", &top->passportNo);
					fscanf(LoadFile, "%30s", top->firstName);
					fscanf(LoadFile, "%30s", top->surname);
					fscanf(LoadFile, "%d", &top->dob);
					fscanf(LoadFile, "%30s", top->email);
					fscanf(LoadFile, "%30s", top->area);
					fscanf(LoadFile, "%30s", top->class);
					fscanf(LoadFile, "%30s", top->frequency);
					fscanf(LoadFile, "%30s", top->duration);

					while (temp->NEXT != NULL)
					{
						temp = temp->NEXT;
					}// inner while

					temp->NEXT = curr;

					curr->NEXT = NULL;

					printf("Passport Number: %d", top->passportNo);
					printf("Name: %s %s\n", top->firstName, top->surname);
					printf("Date of Birth: %d\n", top->dob);
					printf("Email: %s\n", top->email);
					printf("Travelled from: %s\n", top->area);
					printf("Class: %s\n", top->class);
					printf("Frequency: %s\n", top->frequency);
					printf("Duration: %s\n", top->duration);
				}// inner if

			}//while

			fclose(LoadFile);

			return top;

		}//if
		*/
	}// LoadFile

int Length(struct node* top)
{
	struct node* curr;

	int count = 1;

	curr = top;

	while (curr->NEXT != NULL)
	{
		count++;
		curr = curr->NEXT;
	}// while

	return count;

}// Length

void PassengerFile(FILE** Database, FILE** Passenger, struct node* top, int size)
{
	Database = fopen("Database.txt", "w");

	Passenger = fopen("Passenger.txt", "w");

	struct node* curr;

	int counter = 0, temp, *ptr;

	ptr = (int*)malloc(size * sizeof(int));

	curr = top;

	if (Database == NULL && Passenger == NULL)
	{
		printf("Sorry, file could not be opened...\n");
	}// if
	else
	{
		while (curr != NULL)
		{
			*(ptr + counter) = curr->passportNo;
			counter++;
			curr = curr->NEXT;
		}// inner while

		for (int i = 0; i < size; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if (*(ptr + i) > *(ptr + j))
				{
					temp = *(ptr + i);
					*(ptr + i) = *(ptr + j);
					*(ptr + j) = temp;
				}// inner if
			}// inner for

		}//for

		curr = top;

		for (int i = 0; i < size; i++)
		{
			while (curr != NULL)
			{
				if (*(ptr + i) == curr->passportNo)
				{
					fprintf(Database, "Passenger Name: %s %s\n", top->firstName, top->surname);
					fprintf(Database, "Passport Number: %d\n", top->passportNo);
					fprintf(Database, "Passenger Year of Birth: %d\n", top->dob);
					fprintf(Database, "Passenger E-mail: %s\n", top->email);
					fprintf(Database, "Passenger Area Travelled from: %s\n", top->area);
					fprintf(Database, "Passenger Travel Class: %s\n", top->class);
					fprintf(Database, "Trips to Ireland per year: %s\n", top->frequency);
					fprintf(Database, "Passenger Average duration of stay: %s\n\n", top->duration);

					fprintf(Passenger, "%d %s %s %d %s %s %s %s %s\n", curr->passportNo, curr->firstName, curr->surname, curr->dob, curr->email, curr->area, curr->class, curr->frequency, curr->duration);
				
				}// inner if

				curr = curr->NEXT;

			}// inner while

			curr = top;

		}//for

		fclose(Database);

		fclose(Passenger);

	}//if

}// PassengerFile

int PassportNoComp(struct node* top, int passport)
{
	struct node* curr;

	curr = top;

	while (curr != NULL)
	{
		if (curr->passportNo == passport)
		{
			printf("\nSorry passport number already exists please try again...\n");
		}// inner if

		curr = curr->NEXT;

	}//while

	return passport;

}// PassportNoComp

char *CheckEmail(char *email)
{
	char atSymbol = '@', dotSymbol = '.', com[10] = ".com";

	char temp[30];

	int size, at = 0, atCounter = 0, dotCounter = 0;

	size = strlen(email);

	strcpy(temp, email);

	for (int i = 0; i < size; i++)
	{
		if (temp[i] == atSymbol)
		{
			atCounter++;
		}// inner if

		if (temp[i] == dotSymbol)
		{
			dotCounter++;
		}// inner if

	}//for

	if (strchr(email, atSymbol) && strstr(email, com))
	{
		at = 1;
	}//if

	if (at == 1 && atCounter == 1 && dotCounter == 1)
	{
		return email;
	}// if
	else
	{
		printf("Sorry, that is not a valid address...");
		return NULL;
	}// else

}// CheckEmail
