#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Question {
public:
	// This is just the constructor that takes values by val and assigns them to private variables in the class
	Question(string question, string correctChoice, string choice2, string choice3, string choice4, int ID)
		: _question(question), _correctChoice(correctChoice), _choice2(choice2), _choice3(choice3), _choice4(choice4), _ID(ID)
	{

	}

	// This function takes a parameter and compares it to the correct solution of the question
	bool CheckAnswer(string answer) {
		if (answer == _correctChoice) {
			return true;
		}
		else {
			return false;
		}
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

// This function reads the text file, makes the questions and its choices into objects, then addes them to the vector
void loadQuestions(int& lastID, vector<Question>& allQuestions, string filename) {
	string temp, question, correctC, c2, c3, c4;
	int line = 1;

	ifstream QFile;
	QFile.open(filename);

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
			allQuestions.push_back(newQuestion);
			line = 0;
			break;
		}
		line++;
	}
	QFile.close();
}

// Prints a question with the choices in a random order, can be used both to view all questions and in game
void PrintQuestion(int ID, vector<Question> allQuestions) {

	bool done, choices[4];
	int num;

	cout << endl << "[" << allQuestions[ID].GetID() << "] ";
	allQuestions[ID].PrintQuestion();

	done = false;
	for (int x = 0; x < 4; x++) {
		choices[x] = false;
	}

	while (done == false) {
		num = rand() % 4 + 1;
		if (choices[num - 1] == false) {
			allQuestions[ID].PrintChoices(num);
			cout << "   ";
			choices[num - 1] = true; // minus 1 here because of the index
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
}

// This function will delete a question from the vector
void DeleteQuestion(vector<Question>& allQuestions) {
	int ID;
	cout << "Enter the question number: ";
	cin >> ID;
	allQuestions.erase(allQuestions.begin() + ID - 1); // begin() gets the 1st value in the vector 
	cout << endl << "Question " << ID << " has been deleted" << endl;
}

// This function will add a new question to the vector
void AddQuestion(int& lastID, vector<Question>& allQuestions) {
	string question, c1, c2, c3, c4;
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
	allQuestions.push_back(newQuestion);

	ofstream questionFile; // Adds the question to the file
	questionFile.open("exam_questions.txt", fstream::app);
	questionFile << endl << question << endl;
	questionFile << c1 << endl;
	questionFile << c2 << endl;
	questionFile << c3 << endl;
	questionFile << c4;
	questionFile.close();
}

void adminMenu(int &lastID, vector<Question> &allQuestions) {
	int choice;
	string nameEntered, fileName;
	char input;
	cout << "Welcome to the administration menu, please choose from the following options:" << endl;
	cout << "[1] View all questions" << endl << "[2] Add new question" << endl;
	cout << "[3] Load questions from file" << endl << "[4] Go back to main menu" << endl;
	cout << "Your choice: ";
	cin >> choice;
	switch (choice) {
	case 1:
		for (unsigned int i = 0; i < allQuestions.size(); i++) {
			PrintQuestion(i, allQuestions);
		}
		cout << endl << " ---------------------------------------";
		cout << endl << "Enter d to delete a question and b to go back to the main menu: ";
		cin >> input;
		switch (input) {
		case 'D':
		case 'd':
			DeleteQuestion(allQuestions);
			cout << " ---------------------------------------" << endl;
			for (unsigned int i = 0; i < allQuestions.size(); i++) {
				PrintQuestion(i, allQuestions);
			}
			break;

		case 'B':
		case 'b':
			break;
		}
		break;
	case 2:
		AddQuestion(lastID, allQuestions);
		break;
	case 3:
		cout << "Enter the name of the file: ";
		cin >> nameEntered;
		fileName = nameEntered + ".txt";
		loadQuestions(lastID, allQuestions, fileName);
		break;
	case 4:
		break;
	}
}

void updateName() {

}


int main()
{
	srand(time(NULL)); 

	vector<Question> allQuestions;	// vector that includes objects that are the questions
	int lastID = 0;		// To make it ascending order and avoid repetition
	string initFileName = "exam_questions.txt";		// This is the initial file that has the questions

	loadQuestions(lastID, allQuestions, initFileName);

	adminMenu(lastID, allQuestions);

	return 0;
}
