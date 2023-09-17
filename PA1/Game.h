#pragma once
#include "List.h"

//declaring profile struct
struct Profile {
	std::string profileName;
	int points;
};

template <typename T1, typename T2>
class Game {
private:
	void menu();
	//fill array with profiles from profiles.csv
	void populateArray();
	//accepts the number of questions to be asked and returns score from session
	int askQuestions(int numQuestions);
	Profile profiles[50];
	List<T1, T2> gameList;
public:
	
	//Constructor
	Game();

	//array pointer getter
	//Profile* getArrayPtr();
	//insert a new profile
	void insertProfile(Profile newProfile);
	//check for existing profiles with a given name
	bool isExistingProfile(std::string checkProfile);
};



//Construct Game
template <typename T1, typename T2>
Game<T1, T2>::Game() {
	this->gameList.loadData();
	populateArray();
	menu();
}

//execute the game menu until exited
template <typename T1, typename T2>
void Game<T1, T2>::menu() {

	//index for array position
	int currentPlayer = 0;
	//integer for profile index
	int profileIndex = 0;
	std::string playerName;
	bool isExistingPlayer = 0;
	int choice = 0;
	bool resume = true;
	int sessionScore = 0;
	//two strings for creating a new command
	std::string newCommand;
	std::string newDescription;
	//new command node
	Node<T1, T2>* newCommandNode = new Node<T1, T2>;
	Node<T1, T2>* checkNode = gameList.getPHead();
	bool commandExists = false;
	//integer which helps tell the user they've already inputted that command
	int numRuns = 0;

	//run menu until resume == false
	while (resume == true) {
		choice = 0;

		std::cout << "Please select an option listed below:" << std::endl;
		std::cout << "1. Game Rules" << std::endl;
		std::cout << "2. Play Game" << std::endl;
		std::cout << "3. Load Previous Game" << std::endl;
		std::cout << "4. Add Command" << std::endl;
		std::cout << "5. Remove Command" << std::endl;
		std::cout << "6. Exit" << std::endl;
		while (choice > 6 || choice < 1) {
			std::cin >> choice;
		}

		switch (choice) {
		case 1:
			std::cout << "This program is designed to quiz the user on linux commands. The user\n";
			std::cout << "can choose how many questions to answer, from 5-30. For each question,\n";
			std::cout << "3 descriptions of different commands and one command are listed. The\n";
			std::cout << "player must enter the correct number that corresponds to the command.\n\n";

			break;
		case 2:
			//std::ofstream outfile 
			std::cout << "Enter your name: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
			std::getline(std::cin, playerName);

			isExistingPlayer = isExistingProfile(playerName);

			if (isExistingPlayer == 1) {
				std::cout << "Welcome back! How many questions would you like (5-30)? ";
			}
			else {
				std::cout << "Welcome! How many questions would you like (5-30)? ";
			}

			//run until number between 5 and 30 is chosen
			while (choice < 5 || choice > 30) {
				std::cin >> choice;
			}

			sessionScore = askQuestions(choice);

			//if the player is already in the profiles array
			if (isExistingPlayer == 1) {
				//run until player is found in array
				while (profiles[currentPlayer].profileName != playerName) {
					currentPlayer++;
				}
				profiles[currentPlayer].points += sessionScore;
			}
			else {
				Profile newProfile = { playerName, sessionScore };
				insertProfile(newProfile);
			}

			break;
		case 3:
			//std::cout << "Welcome back! Enter your name: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			do {
				std::cout << "Enter your valid existing profile: ";
				std::getline(std::cin, playerName);
				std::cout << std::endl;
				isExistingPlayer = isExistingProfile(playerName);
			} while (isExistingPlayer == 0);

			isExistingPlayer = isExistingProfile(playerName);

			profileIndex = 0;
			
			while (playerName != profiles[profileIndex].profileName) {
				profileIndex++;
			}

			std::cout << "Welcome back! Number of points on your profile: " << profiles[profileIndex].points << std::endl;

			std::cout << "How many questions would you like (5-30)? ";

			//run until number between 5 and 30 is chosen
			while (choice < 5 || choice > 30) {
				std::cin >> choice;
			}

			sessionScore = askQuestions(choice);

			//run until player is found in array
			while (profiles[currentPlayer].profileName != playerName) {
				currentPlayer++;
			}
			profiles[currentPlayer].points += sessionScore;

			break;
		case 4:
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			numRuns = 0;

			do {
				if (numRuns > 0) {
					std::cout << "Command already exists!\n";
				}
				commandExists = false;
				std::cout << "Type your new command name: ";
				std::getline(std::cin, newCommand);

				checkNode = gameList.getPHead();
				
				while (checkNode != nullptr) {
					if (newCommand == checkNode->getCommand()) {
						commandExists = true;
					}
					checkNode = checkNode->getNextPtr();
				}
				numRuns++;
			} while (commandExists == true);
			std::cout << "Type your new command description: ";
			std::getline(std::cin, newDescription);

			newCommandNode->setCommand(newCommand);
			newCommandNode->setDescription(newDescription);

			gameList.insertAtFront(newCommandNode);

			break;
		case 5:
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			numRuns = 0;

			do {
				if (numRuns > 0) {
					std::cout << "Command does not exist!\n";
				}
				commandExists = false;
				std::cout << "Type the command you would like to delete: ";
				std::getline(std::cin, newCommand);

				checkNode = gameList.getPHead();

				while (checkNode != nullptr) {
					if (newCommand == checkNode->getCommand()) {
						commandExists = true;
					}
					checkNode = checkNode->getNextPtr();
				}
				numRuns++;
			} while (commandExists == false);

			gameList.removeNode(newCommand);

			break;
		case 6:
			std::ofstream commandsOutfile;
			std::ofstream profilesOutfile;

			commandsOutfile.open("../commands.csv");
			profilesOutfile.open("../profiles.csv");

			//reuse newCommandNode
			newCommandNode = gameList.getPHead();
			while (newCommandNode != nullptr) {
				commandsOutfile << newCommandNode->getCommand() << ", \"" << newCommandNode->getDescription() << "\"" << std::endl;

				newCommandNode = newCommandNode->getNextPtr();
			}

			numRuns = 0;
			while (numRuns < 50 && profiles[numRuns].profileName != "*") {
				profilesOutfile << profiles[numRuns].profileName << ", " << profiles[numRuns].points << std::endl;

				//if (profiles[numRuns + 1].profileName != "") {
				//	profilesOutfile << std::endl;
				//}
				numRuns++;
			}
			//profilesOutfile << "this thing working?";

			commandsOutfile.close();
			profilesOutfile.close();

			resume = false;

			gameList.~List();

			//files opened/closed within functions

			break;
		}
	}
}

//accepts the number of questions to be asked and returns score from session
template <typename T1, typename T2>
int Game<T1, T2>::askQuestions(int numQuestions) {
	srand(time(NULL));
	//integer for score
	int netScore = 0;
	//size of list of commands
	int listSize = 0;
	//random variables
	int randomNum = 0;
	int randomNum2 = 0;
	//array to determine the random order of descriptions
	int descOrder[3] = { -1, -1, -1 };
	//integer corresponding to the position of the correct answer in the array
	int correctAnswer = -1;
	//array which tracks which questions have been used
	int usedQuestions[30];
	//initialize all array values to -1 (an invalid number)
	for (int i = 0; i < 30; i++) {
		usedQuestions[i] = -1;
	}

	//get size of list of commands
	Node<T1, T2>* pCur = gameList.getPHead();
	while (pCur != nullptr) {
		listSize++;
		pCur = pCur->getNextPtr();
	}

	//for loops runs until correct number of questions have been asked
	for (int i = 0; i < numQuestions; i++) {
		descOrder[0] = -1;
		descOrder[1] = -1;
		descOrder[2] = -1;

		bool isInList = true;
		while (isInList == true) {
			//pick a number between 1 and the size of the list
			randomNum = (rand() % listSize) + 1;
			//run through array to check if the value has been picked
			isInList = false;
			for (int j = 0; j < i; j++) {
				if (randomNum == usedQuestions[j]) {
					isInList = true;
				}
			}
		}
		//FOR TOMORROW: Ask question here
		//create an integer to track which index of the list the loop is on
		int listIndex = 0;
		pCur = gameList.getPHead();
		while (listIndex < randomNum - 1) {
			pCur = pCur->getNextPtr();
			listIndex++;
		}

		std::cout << "\nCommand: " << pCur->getCommand() << std::endl;
		correctAnswer = rand() % 3;
		descOrder[correctAnswer] = randomNum; /*pCur->getCommand()*/

		if (descOrder[0] == -1) {
			do {
				randomNum2 = rand() % listSize + 1;
			} while (descOrder[correctAnswer] == randomNum2);

			pCur = gameList.getPHead();
			for (int l = 0; l < randomNum2 - 1; l++) {
				pCur = pCur->getNextPtr();
			}
			std::cout << "Description 1: " << pCur->getDescription() << std::endl;
		}
		else {
			pCur = gameList.getPHead();
			for (int l = 0; l < descOrder[0] - 1; l++) {
				pCur = pCur->getNextPtr();
			}
			std::cout << "Description 1: " << pCur->getDescription() << std::endl;
		}
		if (descOrder[1] == -1) {
			do {
				randomNum2 = rand() % listSize + 1;
			} while (descOrder[correctAnswer] == randomNum2);

			pCur = gameList.getPHead();
			for (int l = 0; l < randomNum2 - 1; l++) {
				pCur = pCur->getNextPtr();
			}
			std::cout << "Description 2: " << pCur->getDescription() << std::endl;
		}
		else {
			pCur = gameList.getPHead();
			for (int l = 0; l < descOrder[1] - 1; l++) {
				pCur = pCur->getNextPtr();
			}
			std::cout << "Description 2: " << pCur->getDescription() << std::endl;
		}
		if (descOrder[2] == -1) {
			do {
				randomNum2 = rand() % listSize + 1;
			} while (descOrder[correctAnswer] == randomNum2);

			pCur = gameList.getPHead();
			for (int l = 0; l < randomNum2 - 1; l++) {
				pCur = pCur->getNextPtr();
			}
			std::cout << "Description 3: " << pCur->getDescription() << std::endl;
		}
		else {
			pCur = gameList.getPHead();
			for (int l = 0; l < descOrder[2] - 1; l++) {
				pCur = pCur->getNextPtr();
			}
			std::cout << "Description 3: " << pCur->getDescription() << std::endl;
		}
		
		usedQuestions[i] = randomNum;

		pCur = gameList.getPHead();
		for (int l = 0; l < descOrder[correctAnswer] - 1; l++) {
			pCur = pCur->getNextPtr();
		}

		int userAnswer = -1;
		while (userAnswer < 0 || userAnswer > 2) {
			std::cin >> userAnswer;
			userAnswer--;
		}

		if (userAnswer == correctAnswer) {
			std::cout << "Correct! " << pCur->getCommand() << " - " << pCur->getDescription() << std::endl;
			netScore++;
		}
		else {
			std::cout << "Incorrect. " << pCur->getCommand() << " - " << pCur->getDescription() << std::endl;
			netScore--;
		}
	}

	return netScore;
}


////////////////////////_Array Functions_/////////////////////////////////

//check for existing profiles with a given name
template <typename T1, typename T2>
bool Game<T1, T2>::isExistingProfile(std::string checkProfile) {
	int i = 0;
	while (i < 50 && profiles[i].profileName != "*") {
		if (profiles[i].profileName == checkProfile) {
			return true;
		}
		i++;
	}
	return false;
}

//Takes a new Profile and inserts it into 0 of the array
template <typename T1, typename T2>
void Game<T1, T2>::insertProfile(Profile newProfile) {
	int i = 49;
	//find the index of the last player in the array
	while (i > 0 && profiles[i - 1].profileName == "*") {
		i--;
	}
	//if the array is empty, insert the profile to the index 0
	if (i == 0) {
		profiles[0] = newProfile;
	}
	else {
		for (int j = i; j > 0; j--) {
			profiles[j] = profiles[j - 1];
		}
		profiles[0] = newProfile;
	}
}

//Populate the array using the profiles.csv data
template <typename T1, typename T2>
void Game<T1, T2>::populateArray() {
	std::ifstream infile;
	//strings for reading lines in profiles.csv and copying the data
	char readString[50];
	char arrayString[50];
	char numString[4];

	for (int i = 0; i < 50; i++) {
		profiles[i].profileName = "*";
	}


	infile.open("../profiles.csv");
	while (!infile.eof()) {
		//index values for reading and inserting
		int index = 0;
		int numIndex = 0;

		//read line
		infile.getline(readString, 50);

		//copy lineString values to arrayString and numString
		while (readString[index] != ',') {
			arrayString[index] = readString[index];
			index++;
		}

		arrayString[index] = '\0';
		index += 2;
		while (readString[index] != '\0') {
			numString[numIndex] = readString[index];
			index++;
			numIndex++;
		}
		numString[numIndex] = '\0';

		//create a new Profile with the values from arrayString and numString 
		Profile newProfile = { arrayString, atoi(numString) };
		//if statement ignores empty line at the end of the csv
		if (readString[0] != '\0') {
			insertProfile(newProfile);
		}

	}

	infile.close();
}

////////////////////////_Array Functions End_////////////////////////////////