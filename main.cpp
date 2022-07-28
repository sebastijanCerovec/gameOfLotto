#include <iostream>

const int DRAW = 6;
const int POOL_OF_NUMBERS = 42;

// a comment
// a function that generates a number that is within the scope of the pool of lotto numbers
int generateLottoNumber() {
	return rand() % POOL_OF_NUMBERS + 1;
}

// a function that writes out the opening ASCII image
void writeOutOpeningImage() {
	std::cout << std::endl;
	std::cout << " 88" << std::endl;
	std::cout << " 88              ,d      ,d" << std::endl;
	std::cout << " 88              88      88" << std::endl;
	std::cout << " 88  ,adPPYba, MM88MMM MM88MMM, adPPYba," << std::endl;
	std::cout << " 88 a8*     *8a  88      88   a8*     *8a" << std::endl;
	std::cout << " 88 8b       d8  88      88   8b       d8" << std::endl;
	std::cout << " 88 *8a,   ,a8*  88,     88,  *8a,   ,a8*" << std::endl;
	std::cout << " 88  `*YbbdP*'   *Y888   *Y888 `*YbbdP*'" << std::endl << std::endl;
	std::cout << "WELCOME TO LOTTO " << DRAW << "/" << POOL_OF_NUMBERS << " BY SEBASTIJAN CEROVEC" << std::endl << std::endl;
}

// a function that draws lotto numbers and checks if they have already been drawn
void drawNumbers(int numbersDrawn[], bool numbersChecked[]) {
	for (int i = 0; i < DRAW; i++) {
		int generatedNumber = 0;

		// generate a number and check if its been already drawn
		do {
			generatedNumber = generateLottoNumber();
			numbersDrawn[i] = generatedNumber;
		} while (numbersChecked[generatedNumber - 1]);

		// set true for drawn number
		numbersChecked[generatedNumber - 1] = true;
	}
}

// a function that asks the player to pick numbers and checks the input
void getPick(int numbersPicked[], bool numbersChecked[]) {
	for (int i = 0; i < DRAW; i++) {
		int pick = 0;

		do {
			std::cout << "Pick the " << i + 1 << ". number " << "(1 - " << POOL_OF_NUMBERS << "):" << std::endl;
			std::cin >> pick;

			// check for wrong entries and write out a message
			if (std::cin.fail()) {
				std::cout << "Wrong entry!" << std::endl << std::endl;
				std::cin.clear();
				std::cin.ignore(10, '\n');
				continue;
			}

			// write out a message if an illegal number was picked
			if (pick < 1 || pick > POOL_OF_NUMBERS)
				std::cout << "Illegal pick!" << std::endl << std::endl;

			// write out a message if the number was already picked
			else if (numbersChecked[pick - 1])
				std::cout << "You've picked this number before!" << std::endl << std::endl;
		} while ((pick < 1 || pick > POOL_OF_NUMBERS) || numbersChecked[pick - 1]); // check if a legal number was picked and if the number was already picked

		numbersPicked[i] = pick;

		// set true for drawn number
		numbersChecked[pick - 1] = true;
	}
}

// a function that checks if and how many numbers have been hit by the play and returns a number of how many lotto numbers the player has hit
int checkHits(int numbersDrawn[], int numbersPicked[], bool numbersHit[]) {
	int counter = 0;
	for (int i = 0; i < DRAW; i++) {
		for (int j = 0; j < DRAW; j++) {
			if (numbersPicked[i] == numbersDrawn[j]) {
				numbersHit[i] = true;
				counter++;
			}
		}
	}

	// return number of hit lotto numbers
	return counter;
}

// a function that writes out the players selection of numbers
void writeOutPick(int numbersPicked[]) {
	std::cout << std::endl << std::endl << "YOUR LOTTO 6/42 PICK: ";
	std::cout << "|";
	for (int i = 0; i < DRAW; i++)
	{
		std::cout << numbersPicked[i];
		std::cout << "|";
	}
	std::cout << std::endl << std::endl << std::endl;
}

// a function that simulates the lotto draw
void createDrawingEffect(int numbersDrawn[]) {
	std::cout << "Drawing numbers now..." << std::endl;

	// create a drawing effect
	for (int i = 0; i < DRAW; i++) {
		int random;
		for (int j = 0; j < 15000; j++) {
			random = generateLottoNumber();
			std::cout << random << "    \r";
		}
		std::cout << numbersDrawn[i] << "    \r" << std::endl;
	}
}

// a function that writes out the lotto draw
void writeOutDraw(int numbersDrawn[]) {
	std::cout << std::endl << std::endl << "LOTTO 6/42 DRAW: ";
	std::cout << "|";
	for (int i = 0; i < DRAW; i++)
	{
		std::cout << numbersDrawn[i];
		std::cout << "|";
	}
	std::cout << std::endl << std::endl << std::endl;
}

// a function that writes out a message to the player on how many lotto numbers the player has hit
void writeOutNumberOfHits(int counter) {
	std::cout << "You hit " << counter;

	if (counter == 1)
		std::cout << " number.";
	else if (counter < 1 || counter > 1)
		std::cout << " numbers.";

	if (counter == DRAW)
		std::cout << " YOU HIT THE JACKPOT! CONGRATULATIONS!";

	std::cout << std::endl << std::endl;
}

// a function that writes out the players selection of numbers highlighting hit numbers
void writeOutHits(int numbersPicked[], bool numbersHit[]) {
	std::cout << "YOUR LOTTO 6/42 PICK: ";
	std::cout << "|";
	for (int i = 0; i < DRAW; i++)
	{
		// highlight the hits and remove misses
		if (numbersHit[i])
			std::cout << numbersPicked[i];
		else
			std::cout << (char)178;
		std::cout << "|";
	}
	std::cout << std::endl << std::endl << std::endl;
}

// a function that asks if the player wants another try
bool askPlayerForAnotherTry() {
		char playersChoice;
		do {
			std::cout << "Do you want another try? (y/n): " << std::endl;

			std::cin >> playersChoice;

			switch (playersChoice) {
			case 'N':
			case 'n':
				std::cout << std::endl << "Thank you for playing!" << std::endl;
				return false;
			case 'Y':
			case 'y':
				std::cout << std::endl << "Here we go!" << std::endl;
				return true;
			default:
				std::cout << "Wrong answer!" << std::endl << std::endl;
				break;
			}

		} while (!(playersChoice == 'N' || playersChoice == 'n' || playersChoice == 'y' || playersChoice == 'Y'));
}

int main() {

	// a bool that stores the information if the player wants to try again
	bool tryAgain = false;

	do {

		srand(time(0));

		int outcome[DRAW] = { 0 }; // outcome of the draw
		int selection[DRAW] = { 0 }; // numbers selected by the player	
		bool drawnNumbers[POOL_OF_NUMBERS]; // array that stores information which numbers have been drawn	
		bool pickedNumbers[POOL_OF_NUMBERS]; // array that stores information which numbers have been picked by the player
		bool hitNumbers[DRAW]; // array that stores information which numbers have been hit by the player
		int hitCounter = 0; // number of hit numbers

		// fill bool arrays with values false
		memset(drawnNumbers, 0, sizeof(drawnNumbers));
		memset(pickedNumbers, 0, sizeof(pickedNumbers));
		memset(hitNumbers, 0, sizeof(hitNumbers));

		drawNumbers(outcome, drawnNumbers);
		writeOutOpeningImage();
		getPick(selection, pickedNumbers);

		// get number of hits
		hitCounter = checkHits(outcome, selection, hitNumbers);

		writeOutPick(selection);
		createDrawingEffect(outcome);
		writeOutDraw(outcome);
		writeOutNumberOfHits(hitCounter);
		writeOutHits(selection, hitNumbers);

		// ask if the player wants another try
		tryAgain = askPlayerForAnotherTry();

	} while (tryAgain);

}