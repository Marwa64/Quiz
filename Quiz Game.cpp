#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


class Question{
	public:
		Question(string question, string correctChoice, string choice2, string choice3, string choice4, int ID)
		: _question(question), _correctChoice(correctChoice), _choice2(choice2), _choice3(choice3), _choice4(choice4), _ID(ID)
		{

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
void loadQuestions(int &lastID) {

}

void adminMenu() {

}

void uodateName() {

}


int main()
{
	vector<Question> allQuestions; //vector that includes objects that are questions
	int lastID = 0; //to make it ascending order and avoid repetition
	loadQuestions(lastID);

	return 0;
}

