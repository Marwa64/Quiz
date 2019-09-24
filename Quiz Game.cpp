#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Question{
	public:
		//This is just the constructor that takes values by val and assigns them to private variables in the class
		Question(string question, string correctChoice, string choice2, string choice3, string choice4, int ID)
		: _question(question), _correctChoice(correctChoice), _choice2(choice2), _choice3(choice3), _choice4(choice4), _ID(ID)
		{

		}

		//This function takes a parameter and compares it to the correct solution of the question
		bool CheckAnswer(string answer) {
			if (answer == _correctChoice) {
				return true;
			}
			else {
				return false;
			}
		}

		//This function prints out the question and choices
		void PrintQuestion() {
			cout << _question << endl;
			cout << "   " << _correctChoice << "   " << _choice2 << "   " <<  _choice3 << "   " << _choice4 << endl;
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
void loadQuestions(int &lastID, vector<Question> &allQuestions, string filename) {
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
				Question newQuestion(question, correctC, c2, c3,c4, lastID);
				allQuestions.push_back(newQuestion);
				line = 0;
				break;
		}
		line++;
	}
	QFile.close();
}

void adminMenu() {

}

void uodateName() {

}


int main()
{
	vector<Question> allQuestions; //vector that includes objects that are the questions
	int lastID = 0; //to make it ascending order and avoid repetition
	string initFileName = "exam_questions.txt"; //This is the original file that has the questions
	loadQuestions(lastID, allQuestions, initFileName);
	return 0;
}

