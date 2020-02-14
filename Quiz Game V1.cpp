#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

string name = "USER";

class Question {
public:
	// This is just the constructor that takes values by val and assigns them to private variables in the class
	Question(string question, string correctChoice, string choice2, string choice3, string choice4, int ID) {
		_question = question; _correctChoice = correctChoice; _choice2 = choice2; _choice3 = choice3; _choice4 = choice4; _ID = ID;
	}

	// This function prints out the question
	void PrintQuestion() {
		cout << _question << endl;
	}

	// This function prints out the choices depending on a random number
	void PrintChoices(int n) {
		switch (n) {
		case 1:
			cout << _correctChoice;
			break;
		case 2:
			cout << _choice2;
			break;
		case 3:
			cout << _choice3;
			break;
		case 4:
			cout << _choice4;
			break;
		}
	}

	// This function returns the ID of the question
	int GetID() {
		return _ID;
	}

private:
	string _question;
	string _correctChoice;
	string _choice2;
	string _choice3;
	string _choice4;
	int _ID;
};

// This function reads the text file, makes the questions and its choices into objects, then adds them to the vector
void loadQuestions(int& lastID, vector<Question>& allQuestions, string filename, vector<int>& IDs) {
	string temp, question, correctC, c2, c3, c4;
	int line = 1;
	ifstream QFile;
	QFile.open(filename.c_str());
	while (getline(QFile, temp)) {
		switch (line) {
		case 1:
			question = temp;
			break;
		case 2:
			correctC = temp;
			break;
		case 3:
			c2 = temp;
			break;
		case 4:
			c3 = temp;
			break;
		case 5:
			c4 = temp;
			lastID++;
			Question newQuestion(question, correctC, c2, c3, c4, lastID);
			IDs.push_back(lastID);
			allQuestions.push_back(newQuestion);
			line = 0;
			break;
		}
		line++;
	}
	QFile.close();
}

// Prints a question with the choices in a random order, can be used both to view all questions and in game
char PrintQuestion(int ID, vector<Question> allQuestions, bool game) {
	bool done, choices[4];
	int num, character = 97; // This is the ascii value of the character
	char answer;

	allQuestions[ID].PrintQuestion();
	done = false;
	for (int x = 0; x < 4; x++) {
		choices[x] = false;
	}
	while (done == false) {
		num = rand() % 4 + 1;
		if (choices[num - 1] == false) { // This if statement checks if the number is taken or not
			if (num == 1) {
				if (game == false) { cout << "*"; }	// This is to highlight the correct choice, only in the admin menu
				answer = (char)character;
			}
			cout << "[" << (char)character << "] ";
			allQuestions[ID].PrintChoices(num);
			cout << "   ";
			choices[num - 1] = true; // minus 1 here because of the index
			character++;
		}
		for (int j = 0; j < 4; j++) {
			done = true;
			if (choices[j] == false) {
				done = false;
				break;
			}
		}
	}
	cout << endl;

	return answer;
}
// This function will delete a question from the vector
void DeleteQuestion(vector<Question>& allQuestions, vector<int>& IDs) {
	int ID;
	cout << "Enter the question number: ";
	cin >> ID;
	for (unsigned int i = 0; i < allQuestions.size(); i++) {
		if (allQuestions[i].GetID() == ID) {
			allQuestions.erase(allQuestions.begin() + i);
		}
	}
	for (unsigned int j = 0; j < IDs.size(); j++) {
		if (IDs[j] == ID) {
			IDs.erase(IDs.begin() + j);
		}
	}
	cout << endl << "Question " << ID << " has been deleted" << endl;
}

// This function will add a new question to the vector
void AddQuestion(int& lastID, vector<Question>& allQuestions, string fileName, vector<int>& IDs) {
	string question, c1, c2, c3, c4;
	char input;
	do {
		cout << endl << "Enter the question: ";
		cin.ignore();
		getline(cin, question);
		cout << "The correct choice: ";
		getline(cin, c1);
		cout << "Second choice: ";
		getline(cin, c2);
		cout << "Third choice: ";
		getline(cin, c3);
		cout << "Fourth choice: ";
		getline(cin, c4);
		lastID++;
		Question newQuestion(question, c1, c2, c3, c4, lastID);
		IDs.push_back(lastID);
		allQuestions.push_back(newQuestion);

		ofstream questionFile; // Adds the question to the file
		questionFile.open(fileName.c_str(), fstream::app);
		questionFile << endl << question << endl;
		questionFile << c1 << endl;
		questionFile << c2 << endl;
		questionFile << c3 << endl;
		questionFile << c4;
		questionFile.close();

		cout << "Enter q to add another question or any other key to go back to the menu: ";
		cin >> input;
	} while (input == 'q' || input == 'Q');
}

//Console menu to get a correct choice from user
int menu() {
	int iChoice = 0;
	cout << "Welcome " << name << ", please choose from the following options:" << endl
		<< "\t[1] Go to administration menu" << endl
		<< "\t[2] Update your name" << endl
		<< "\t[3] Start a new quiz" << endl
		<< "\t[4] Display your scores statistics" << endl
		<< "\t[5] Display all your scores" << endl
		<< "\t[6] Exit" << endl
		<< "Enter the choice: ";
	cin >> iChoice;
	system("CLS");
	if (cin.fail()) {
		cout << "You should enter correct value" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		return menu();
	}
	else return iChoice;
}

//this function is to get a correct choice for the admin menu
int AdministrationCorrectChoice() {
	int iChoice = 0;
	cout << "Welcome to the administration menu, please choose from the following options:" << endl
		<< "\t[1] View all questions" << endl
		<< "\t[2] Add new question" << endl
		<< "\t[3] Load questions from file" << endl
		<< "\t[4] Go back to main menu" << endl
		<< "My choice: ";
	cin >> iChoice;
	system("CLS");
	if (cin.fail()) {
		cout << "You should enter correct value" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		return AdministrationCorrectChoice();
	}
	else return iChoice;
}

void adminMenu(int& lastID, vector<Question>& allQuestions, string& fileName, vector<int> &IDs) {
	bool game = false; // I want to use the PrintQuestion function both in game and when viewing all questions.
			   // This variable is to differentiate between both states as there is a slight difference
	string nameEntered;
	char erase, erase2;
Admin:
	int choice = AdministrationCorrectChoice();
	switch (choice) {
	case 1:
		for (unsigned int i = 0; i < allQuestions.size(); i++) {
			cout << endl << "[" << allQuestions[i].GetID() << "] ";
			PrintQuestion(i, allQuestions, game);
		}
		cout << endl << " ---------------------------------------";
		cout << endl << "Enter d to delete a question or any other key to go back to the main menu: ";
		cin >> erase;
		if (erase == 'd' || erase == 'D') {
			do {
				DeleteQuestion(allQuestions, IDs);
				cout << " ---------------------------------------" << endl;
				for (unsigned int i = 0; i < allQuestions.size(); i++) {
					cout << endl << "[" << allQuestions[i].GetID() << "] ";
					PrintQuestion(i, allQuestions, game);
				}
				cout << endl << "Enter d to delete another question or any key to go back to the main menu: ";
				cin >> erase2;
			} while (erase2 == 'd' || erase2 == 'D');
		}
		break;
	case 2:
		AddQuestion(lastID, allQuestions, fileName, IDs);
		break;
	case 3:
		cout << "Enter the name of the file: ";
		cin >> nameEntered;
		fileName = nameEntered + ".txt";
		allQuestions.clear(); // Erase all questions in vector to add the new question from the new file
		IDs.clear();
		lastID = 0; // Resetting the IDs
		loadQuestions(lastID, allQuestions, fileName, IDs);
		break;
	case 4:
		break;
	}
	system("CLS"); // This is to clear the console
}
void updateName() {
	string newName;
	cout << "Enter your name: ";
	cin.ignore();
	getline(cin, newName);
	name = newName;

	system("CLS"); // This is to clear the console
}

void newQuiz(vector<Question> &allQuestions, vector<int> &IDs) {
	bool game = true;
	int wrong = 0, right = 0;
	char answer, correctAnswer;
	int randQ, num = (IDs.size()) - 1;
	randQ = rand() % num + 0;
	int takenQ[5] = { randQ ,randQ ,randQ ,randQ ,randQ }; // Intializing all of the array with the 1st value

	for (int i = 1; i < 5; i++) {
		randQ = rand() % num + 0; // This will generate a random index for the vector IDs
		for (int j = 0; j < 5; j++) { // This loop ensures that the index hasn't been generated before
			if (takenQ[j] == randQ) {
				randQ = rand() % num + 0;
				j = 0;
			}
		}
		cout << "Question " << i << " :" << endl;
		correctAnswer = PrintQuestion(IDs[randQ], allQuestions, game);
		takenQ[i] = randQ;

		cout << endl << "Your answer: ";
		cin >> answer;
		if (answer == correctAnswer) {
			cout << endl << "Your answer is correct!" << endl << endl;
			right++;
		} else {
			cout << endl << "Incorrect! The correct answer is " << correctAnswer << endl << endl;
			wrong++;
		}
	}
	cout << endl << " ---------------------------------------" << endl;
	cout << "You got " << right << " questions right." << endl << "And " << wrong << " questions wrong." << endl << endl;
	system("pause"); // This will pause on the screen until the user presses any key
	system("CLS"); // This is to clear the console
}

int main()

{
	srand(time(NULL));
	vector<Question> allQuestions;	// Vector that includes objects that are the questions
	vector<int> IDs; // Vector the includes all the IDs
	int lastID = 0;		// To make it ascending order and avoid repetition
	string fileName = "exam_questions.txt";		// This is the file that has the questions
	loadQuestions(lastID, allQuestions, fileName, IDs);

Menu:
	int input;
	do {
		input = menu();
		switch (input) {
		case 1:
			adminMenu(lastID, allQuestions, fileName, IDs);
			break;
		case 2:
			updateName();
			break;
		case 3:
			newQuiz(allQuestions, IDs);
			break;
		case 4:
			break;
		}

	} while (input != 6);

}
