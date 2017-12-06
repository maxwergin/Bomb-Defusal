//This program will ask a user to guess a 4 digit code randomly selected by the
//computer. The program will then display whether each number entered is higher,
//lower, or correct. 
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

//Global constant definition
const int MIN_VALUE = 0;
const int MAX_VALUE = 9;
const int CODE_LENGTH = 4;
//Function prototypes
int randNumGen();
bool numCheck(int[], int[]);
int difSelect();

int main()
{
	//Get system time
	srand(time(0));
	//Array definitions
	int code[CODE_LENGTH];
	int guess[CODE_LENGTH];
	//Variable definitions
	int numTries = 0;
	bool debug = false;
	bool correct = false;
	int difficulty = 0;
	//Introductary text
	cout << "You are tasked with defusing a bomb.\nThe bomb can be disarmed with a"
		<< " four digit code.\nLucky for you, the bomb will tell you how close"
		<< " you are with each digit.\nIf you guess correctly, the bomb is defused"
		<< " and you have saved the day.\nIf not, well. There's always next time.\n"
		<< "So, let's get started!\n\n";
	//Loop in which main game is located
	while (difficulty != -1)
	{
		//Function to set difficulty
		difficulty = difSelect();
		if (difficulty == -1)
			return 0;
		//Loop to generate random numbers for array
		for (int count = 0; count < CODE_LENGTH; count++)
		{
			code[count] = randNumGen();
			if (debug) //To have numbers visible
				cout << code[count] << endl;
		}
		//Asking for input
		while (!correct)
		{
			cout << "Enter a guess of 4 digits, with each number separated by a space: ";
			//Loop to assign each number in guess array
			for (int count = 0; count < CODE_LENGTH; count++)
			{
				cin >> guess[count];
			}
			for (int count = 0; count < CODE_LENGTH; count++)
			{
				while (guess[count] > 9) //Input validation
				{
					cout << "Please re-enter digit #" << count + 1 << " (digit has to be"
						<< " from 0 - 9): ";
					cin >> guess[count];
				}
			}
			correct = numCheck(code, guess);
			numTries++;
			if (numTries > difficulty)
			{
				cout << "BOOOM! The bomb exploded. Try again. \n\n";
				break;
			}
			cout << "Attempt #" << numTries << ", with " << (difficulty - numTries)
				<< " remaining.\n\n";
		}
		if (correct)
			cout << "Congratulations! You've defused the bomb in the "
			<< "alloted time.\n\n";
		//Reinitialization of variables
		numTries = 0;
		correct = 0;
		difficulty = 0;
	}
	return 0;
}

//Function randNumGen definition
int randNumGen()
{
	//Returning random number
	return (rand() % MAX_VALUE);
}

//Function difSelect definition
int difSelect()
{
	//Variable definition
	int choice;
	cout << "Select the difficulty from the following options:"
		<< "\n\t1. Easy (20 tries)\n\t2. Medium (15 tries)"
		<< "\n\t3. Hard (10 tries)\n\t4. Impossible!"
		<< " (5 tries)\n\t5. Practice mode (999 tries)"
		<< "\n\t6. Quit program\n\nEnter your selection: ";
	cin >> choice;
	while (choice < 1 || choice > 6) //Input validation
	{
		cout << "Please enter a valid choice: ";
		cin >> choice;
	}
	switch (choice)
	{
	case 1:	return 20;
			break;
	case 2: return 15;
			break;
	case 3: return 10;
			break;
	case 4: return 5;
			break;
	case 5: return 999;
			break;
	case 6: return -1;
	}
}

//Function numCheck definition
bool numCheck(int code[], int guess[])
{
	//Variable
	int trueCount = 0;
	//Loop to check each value against the other
	for (int count = 0; count < CODE_LENGTH; count++)
	{
		if (guess[count] == code[count]) //If both match
		{
			cout << " *";
			trueCount++;
		}
		else if (guess[count] > code[count]) //If guess is higher
			cout << " +";
		else if (guess[count] < code[count]) //If guess is lower
			cout << " -";
	}
	cout << "\n\n";
	if (trueCount == 4)
		return true;
	else
		return 0;
}