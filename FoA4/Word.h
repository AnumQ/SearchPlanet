#pragma once

using namespace std;

class Word
{
public:
	/* Functions */
	Word( string w, int p, int l, string f );
	string getWord();
	int getPosition();
	int getLine();
	string getFilename();
	void addScore( int s );
	int getScore();
	void deductScore(int s);
	/* Attributes */

private:	
	/* Functions */
	void setWordData( string w, int p, int l, string f );
	/* Attributes */
	string word;
	int position;
	int line;
	string filename;	
	int score;
	
};

