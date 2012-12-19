#include "StdAfx.h"
#include "Word.h"

using namespace std;

Word::Word(string w, int p, int l, string f )
{
	setWordData( w, p, l, f );
	score = 0;
}

void Word::setWordData( string Word, int Pos, int Line, string FN )
{
	word = Word;
	position = Pos;
	line = Line;
	filename = FN;
}

void Word::addScore( int s )
{
	/*int currentscore = getScore();
	int newscore = currentscore + s;
	score = newscore; */
	score = score + s;
}

void Word::deductScore( int s )
{
	score = score - s;
}

int Word::getScore()
{
	return score;
}

string Word::getWord()
{
	return word;
}

int Word::getPosition()
{
	return position;
}

int Word::getLine()
{
	return line;
}

string Word::getFilename()
{
	return filename;
}
