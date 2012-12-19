#pragma once
#include "Word.h"
#include "Line.h"

using namespace std;

class FileReader
{
public:
	/* Functions */
	FileReader( string filepath );
	bool open();
	void close();
	string getFileName();
	void displayFileData();
	void clearFile(); // clears the flags such as EOF
	vector<Word> split(vector<string> SearchValues);
	vector<Line> splitToLines();
	vector<string> splitToParagraphs();
	void PrintVector ( vector<string> &v );	
	/* Attributes */	

private:
	/* Functions */
	void setFileName( string filepath );
	int getPosition( ifstream& File, string word );
	/* Attributes */
	string filename;
	ifstream fileInput;
	vector<string> Paragraphs;
	vector<Word> WordVector;
	vector<Line> LineVector;
	
	
};

