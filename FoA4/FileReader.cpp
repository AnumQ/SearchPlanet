#include "StdAfx.h"
#include "FileReader.h"
#include "Word.h"
#include "Line.h"
using namespace std;

FileReader::FileReader( string filepath )
{
	setFileName( filepath );
}

bool FileReader::open()
{
	fileInput.open(filename.c_str());
	if (!fileInput.is_open() )
	{
		cerr << "Error opening file: " << getFileName() << endl;
		return false;
	}
	else
	{
		if( verbose )
		{
			cout << "Opened file: " << getFileName() << endl;
		}
		return true;
	}
}

void FileReader::close()
{
	//cout << "Closing file.. " << getFileName() << endl;
	fileInput.close();
}

void FileReader::setFileName( string filepath )
{
	filename = filepath;
}

string FileReader::getFileName()
{
	return filename;
}

void FileReader::displayFileData() 
{
	ifstream& File = fileInput;
	string LINE;
	while ( !File.eof() )
	{
		getline( File, LINE );
		cout << LINE << endl;
	}
	File.clear();
}

void FileReader::clearFile()
{
	ifstream& File = fileInput;
	if ( verbose )
	{
		cout << "Clearing file .. " << getFileName() << endl;
	}
	fileInput.clear();
	fileInput.seekg( 0, ios::beg );
}

vector<string> FileReader::splitToParagraphs ()
{
	ifstream& File = fileInput;
	string LINE;
	vector<string> Paragraphs;
	while( !File.eof() )
	{
		getline( File, LINE );
		Paragraphs.push_back(LINE);
	}
	//PrintVector( Paragraphs );
	if ( verbose) 
	cout << "Counting the size of the paragraphs : " << Paragraphs.size() << endl;
	return Paragraphs;
}

vector<Line> FileReader::splitToLines()
{
	ifstream& File = fileInput;
	
	int linecount = 1;
	char c;	

	while( !File.eof() )
	{
		string LINE;
		while( File.get(c) )
		{
			if( c != '.')
			{
			     if ( c != '\n')
				 {
					LINE.push_back(c);
				 }
				 else
				 {
					 LINE.clear();
				 }				
			}
			else
			{
				if ( LINE[0] == ' ')
				{
					LINE.erase( LINE.begin(), (LINE.begin() + 1 ));
				}			
				//cout << "Line " << linecount << " --->" << LINE << "-" << endl;
				//Lines.push_back(LINE);
				Line currentLine( linecount, getFileName() );
				currentLine.setLine( LINE );
				LineVector.push_back( currentLine );
				LINE.clear();
				linecount++;				
			}
		}
	}
	if ( verbose) 
	cout << "Counting the size of the lines : " << LineVector.size() << endl;
	return LineVector;
}

int FileReader::getPosition( ifstream& File, string word )
{
	int position = ( File.tellg() );
	int l = word.size();
	position = position - l - 1; // setting the pointer to the beginning of the word
	return position;
}

vector<Word> FileReader::split(vector<string> SearchValues)
{
	ifstream& File = fileInput;
	int linecount1 = 1;
	int linecount2 = 1;
	char c;
	myWord.clear();
/*
	std::vector<Word*> WordVector;
	Word* currentWord;
	*/
	while ( !File.eof() )
	{
		string word; // 'word' is used as an array of chars to store a single word
		string LINE;
		while( File.get(c) )
		{
			if ( c != ' ' )
			{
				if ( c == '.' )
				{ 
					int pos = getPosition( File, word );
					
					Word currentWord(word, pos, linecount1, getFileName() );
					//currentWord = new Word( word, pos, linecount, getFileName() );
					WordVector.push_back( currentWord );
					//cout << "'" << currentWord.getWord() << "'";
					myWord.push_back( currentWord );
					word.clear(); //clear the 'word' array to store a new word
					
					linecount1++;
				}

				else if ( c == '\n')
				{	
					//word.clear(); 
					/* not too sure whether it's necessary to do something 
					here as a word is already being created if reached a dot. */
				}
				else if ( c == ',')
				{
					word.erase( word.end() );
				}
				else if ( c == '!')
				{
					word.erase( word.end() );
				}
				else if ( c == ';')
				{
					word.erase( word.end() );
				}
				else if ( c == '\'') 
				{
					word.erase( word.end() );
				}
				else
				{
					word.push_back(c);
				}
			}
			else
			{
				if ( !word.empty())
				{
					int pos = getPosition( File, word );
					Word currentWord(word, pos, linecount1, getFileName() );
					//currentWord = new Word( word, pos, linecount, getFileName() );
					WordVector.push_back( currentWord );
					//cout << "'" << currentWord.getWord() << "'";
					myWord.push_back( currentWord );
					word.clear();
				}
			}

			if( c != '.')
			{
			     if ( c != '\n')
				 {
					LINE.push_back(c);
				 }
				 else
				 {
					// LINE.clear();
				 }
				 if ( c == '\n')
				 { /*
					 if ( c+1 == '\n' )
					 {
					Line currentLine( linecount2, getFileName() );
					currentLine.setLine( LINE );
					cout << "		NEXT LINE HERE: " << LINE << endl;
					//LineVector.push_back( currentLine );
					myLine.push_back(currentLine);
					linecount2++;
						 LINE.clear();
					 } */
				 }
			}
			else
			{


				if ( LINE[0] == ' ')
				{
					LINE.erase( LINE.begin(), (LINE.begin() + 1 ));
				}
				//cout << "Line " << linecount << " --->" << LINE << "-" << endl;
				//Lines.push_back(LINE);

				Line currentLine( linecount2, getFileName() );
				currentLine.setLine( LINE );
				//cout << "		NEXT LINE HERE: " << LINE << endl;
				//LineVector.push_back( currentLine );
				myLine.push_back(currentLine);
				linecount2++;
				LINE.clear();
			}
		}
	if ( verbose) 
	cout << "Counting the size of WordVector : " << WordVector.size() << endl;
	return WordVector;
	}	
}

void FileReader::PrintVector( vector <string> & v )
{
	for ( size_t n = 0; n < v.size(); n++ )
    {
        cout << "-" << v[ n ] << "-\n";
        cout << endl;
    }
}