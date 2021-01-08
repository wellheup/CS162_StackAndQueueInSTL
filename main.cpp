
/*********************************************************************
** Author: Phillip Wellheuser							CS 162-400
** Date: 6/2/19
** Description: Runs a buffer queue simulation and a stack simulation
**		which prints a palindrome both using STL
*********************************************************************/
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <stack>
#include "menuShell.hpp"

unsigned int seed;

//prototypes
void runBuffer();
void runPalindrome();

int main() {
	seed = std::time(0);
	const int numOptions = 4;
	std::string chooseOptions[numOptions];
	chooseOptions[0] = "Welcome to Phillip Wellheuser's Lab 9: Stack and Queue STL Containers";
	chooseOptions[1] = "\t1. Run random Buffer QUEUE simulation (randomly adds/removes numbers from a buffer)";
	chooseOptions[2] = "\t2. Run Palindrome STACK simulation (makes a palindrome)";
	chooseOptions[3] = "\t3. Exit the program";

	int choice = 0;
	while (choice != numOptions-1) {
		choice = choiceMenuMulti(chooseOptions, numOptions);
		switch (choice) {
		case 1:
			runBuffer();
			break;
		case 2:
			runPalindrome();
			break;
		case 3:
			std::cout << "Exiting program" << std::endl;
			break;
		default:
			std::cout << "Error in choosing options" << std::endl;
			break;
		}
	}
	return 0;
}

/*********************************************************************
** Description: runPalindrome(), asks the user for a string input
**		pushes that string into a stack while printing it and then 
**		immediately prints it again in reverse order while popping
**		each char off of the stack again
*********************************************************************/
void runPalindrome() {
	std::string askUserInStr = "Please enter a string to create a palindrome of: ",
		userInStr;
	std::stack <char> userInStack;

	//ask for userIn string
	userInStr = enterStringWithinRange(askUserInStr, 1, 100);
	
	std::cout << "Your palindrome is: ";

	//push all chars in string to stack while printing
	for (char x : userInStr) {
		std::cout << x;
		userInStack.push(x);
	}

	//pop all chars from stack while printing
	while (!userInStack.empty()) {
		std::cout << userInStack.top();
		userInStack.pop();
	}
	std::cout << "\n" << std::endl;
}

/*********************************************************************
** Description: runBuffer(), asks the user how many rounds to run for
**		and the chances of adding/removing a number to/from the buffer
**		then runs a loop of adding/removing while printing results
**		to the console
*********************************************************************/
void runBuffer() {
	int maxRounds,
		currentRound = 1,
		chanceAdd = 0, 
		chanceRemove = 0;
	
	double avgLength = 0;

	std::string intro_Buffer = "The buffer program requires 3 user inputs: \n"
		"\t1. A number of rounds to run\n"
		"\t2. The chance of adding to the buffer\n"
		"\t3. The chance of removing from the buffer\n",
		askNumRounds = "How many rounds would you like to run?",
		askChanceAdd = "What is the percent chance of adding to the buffer?",
		askChanceRemove = "What is the percent chance of removing from the buffer?",
		currentBufferStr = "The current buffer is: ";

	std::queue<int> buffer;

	//initialize buffer
	std::cout << intro_Buffer << std::endl;
	maxRounds = chooseIntInRange(askNumRounds, 1, 100000);
	chanceAdd = chooseIntInRange(askChanceAdd, 1, 100);
	chanceRemove = chooseIntInRange(askChanceRemove, 1, 100);

	//run round
	while (currentRound <= maxRounds) {
		int N = rand() % 1001;
		if (rand() % 101 <= chanceAdd) {
			buffer.push(N);
		}
		if (rand() % 101 <= chanceRemove) {
			buffer.pop(); 
		}
		
		//print queue
		//#include <iterator> std::copy(buffer.front(), buffer.back()+1, std::ostream_iterator<int>(std::cout, ", "));
		std::cout << currentBufferStr;
		for (unsigned int i = 0; i < buffer.size(); i++) {
			std::cout << buffer.front()+i;
			if (i != buffer.size() - 1) {
				std::cout << ", ";
			}
		}
		std::cout << std::endl;

		//print queue length
		std::cout << "Buffer is currently " << buffer.size() << " elements long." << std::endl;

		//print avg length
		avgLength = (avgLength * (currentRound - 1) + buffer.size())/ currentRound;
		std::cout << "Average buffer length is: " << avgLength << "\n" << std::endl;
		currentRound++;
	}
}
