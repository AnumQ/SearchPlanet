#pragma once
#include "Word.h"
#include "Line.h"
using namespace std;

class Search
{
public:
	/* Functions */
	Search(void);	
	void SearchInWords(vector<Word> SplittedWords, vector<string> SearchValues, vector<Line> Sentences );
	vector<Word> SearchForMatch(vector<string> SearchValues);
	int getResults();
	void addScore(Word word);
	void scoreByDistance();
	void DisplayTheResult( vector<Line> Sentences);
	bool SearchInVector ( vector<string> & v, vector<string> & search );
	void scoreByFrequency();
	void printScore();
	/* Attributes */

private:
	/* Attributes */
	int result;
	//vector<Word> SearchResults;
};

