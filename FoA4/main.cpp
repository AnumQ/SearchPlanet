// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SearchInput.h"
#include "DirExplorer.h"
#include "FileReader.h"
#include "Search.h"
#include "MergeSort.h"

bool verbose = false; /* declaring a global variable 'verbose'. Verbose sets a flag to show/hide 
					  additional information while running the program. Personally, I find it easier
					  to debug this way. */
vector<Word> myWord;
vector<Line> myLine;
vector<Word> MatchedResults;
string searchType;
using namespace std;

void Print( vector <string> & v )
{
    for ( size_t n = 0; n < v.size(); n++ )
    {
        cout << "'" << v[ n ] << "'\n";
        cout << endl;
    }
}

void welcomeMessage()
{
	cout << "*************************************************************************\n"
		    "*                         WELCOME TO SEARCHPLANET!                      *\n"
			"*                                                                       *\n"
			"* Module: Foundations of Algorithms                                     *\n"
			"* Assignment: Search Problem                                            *\n" 
			"* Lecturer: Paolo Remagnino                                             *\n" 
			"* Kingston University London                                            *\n" 
			"*                                                                       *\n" 
			"* Copyright (c) 2012 Anum Qudsia, K0913234                              *\n" 
			"*************************************************************************\n"
			<< endl;
}

void setVerbose()
{
	char answer;
	cout << "\nPlease set the Verbose to display/hide the details of the program: (Y/N)" << endl;
	cin >> answer;
	if ( ( answer == 'Y' ) || ( answer == 'y' ) )
	{
		verbose = true;
		cout << "/**                           Verbose is true.                          **/\n"
			    "/**    Comprehensive details about this program will be displayed.      **/\n";
	}
	else if ( ( answer == 'N' ) || ( answer == 'n' ) )
	{
		verbose = false;
		cout << "/**                          Verbose is false.                          **/\n"
			    "/**        Summary will be displayed while running this program.        **/\n";
	}
	else
	{
		verbose = false;
		cout << "/**                       Verbose is set to false.                       **/\n"
			    "/**        Summary will be displayed while running this program.         **/\n";

	}
}
void display( int i )
{
	string tempLine;
	for ( size_t n = 0; n < myLine.size(); n++ )
		{
			if( myLine[n].getLineNo() == MatchedResults[i].getLine() 
				&& myLine[n].getFileName() == MatchedResults[i].getFilename() )
			{	
				
				if ( i < (MatchedResults.size() - 1))
				{
					if ( ( MatchedResults[i].getLine() == MatchedResults[i+1].getLine() ) 
						&& MatchedResults[i].getFilename() == MatchedResults[i+1].getFilename() )
					{
						//don't diplay the line.
					}
					else
					{
					cout << "    '" << myLine[n].getLine() << "'\n - Score: " << MatchedResults[i].getScore() << " - Position " 
						<< MatchedResults[i].getPosition() << " Line (" <<  MatchedResults[i].getLine() << ") File: " << MatchedResults[i].getFilename() << endl;
					cout << endl;
					}
				}
				else
				{
					cout << "    '" << myLine[n].getLine() << "'\n - Score: " << MatchedResults[i].getScore() << " - Position " 
						<< MatchedResults[i].getPosition() << " Line (" <<  MatchedResults[i].getLine() << ") File: " << MatchedResults[i].getFilename() << endl;
					cout << endl;
				}
			}
		}
		tempLine = MatchedResults[i].getLine();
}
void displayResults1()
{
	for ( int i = (MatchedResults.size() - 1); i >= 0; --i )
	{
		display(i);
	}
}

void displayResults2()
{
	for ( size_t i = 0; i < MatchedResults.size(); ++i )
	{
		for ( size_t n = 0; n < myLine.size(); n++ )
		{
			if( myLine[n].getLineNo() == MatchedResults[i].getLine() 
				&& myLine[n].getFileName() == MatchedResults[i].getFilename() )
			{	
				
				if ( i > 0)
				{
					if ( ( MatchedResults[i].getLine() == MatchedResults[i-1].getLine() ) 
						&& MatchedResults[i].getFilename() == MatchedResults[i-1].getFilename() )
					{
						//don't diplay the line.
					}
					else
					{
					cout << "    '" << myLine[n].getLine() << "'\n - Score: " << MatchedResults[i].getScore() << " - Position " 
						<< MatchedResults[i].getPosition() << " Line (" <<  MatchedResults[i].getLine() << ") File: " << MatchedResults[i].getFilename() << endl;
					cout << endl;
					}
				}
				else
				{
					cout << "    '" << myLine[n].getLine() << "'\n - Score: " << MatchedResults[i].getScore() << " - Position " 
						<< MatchedResults[i].getPosition() << " Line (" <<  MatchedResults[i].getLine() << ") File: " << MatchedResults[i].getFilename() << endl;
					cout << endl;
				}
			}
		}
	}
}
void sortData()
{
		cout << "\n SORTING...\n" << endl;
		MergeSort sortVector;
		//cout << "Unsorted vector:" << endl;
		sortVector.displayElements(); // print unsorted vector
		//cout << endl << endl;
		sortVector.sort(); // sort vector
		//cout << "Sorted vector:" << endl;
		sortVector.displayElements(); // print sorted vector
		cout << endl;
	if(verbose)
	cout << "Done with sorting! " << endl;
}
int _tmain(int argc, _TCHAR* argv[])
{ 
	welcomeMessage();
	
	SearchInput SearchObject;
	vector <string> SearchValues = SearchObject.processSearchInput();

	setVerbose();
	cout << endl;

	DirExplorer explore; // Open the directory
	cout << endl;
	cout << " Opening the directory... " << endl;
	vector<string> FileList = explore.getFilePaths(); // Get the names of the files from the directory 
	if (verbose) // Verbose used to indicate whether to show the next piece of code or not 
	{
		cout << "Printing the list of files found.. " << endl;
		Print(FileList);
	}

	std::vector<FileReader*> p; 
	FileReader* file;
	vector<Word> SplittedWords;
	vector<Word*> Results; 
	vector<Line> Sentences;
	Search mySearch;
	myLine.clear();
	MatchedResults.clear();
	int results = 0;
	int totalresult = 0;
	cout << " Reading and storing the matching results... " << endl;
	for ( size_t n = 0; n < FileList.size(); n++ ) // loop through the list of files in the directory 
    {
		string filename = FileList[ n ]; 
		file = new FileReader(filename);
		if ( (file->open()) != true ) // open a single file 
		{
			return false;
		}
		else
		{
			file->split(SearchValues); // split the file's content into words and store in a vector of objects 
			file->clearFile(); // clear the file's EOF flag once done with reading 
		}

	   // create Search object
		
		mySearch.SearchForMatch(SearchValues);
		results = mySearch.getResults();
		totalresult = totalresult + results;

	   p.push_back( file );		
    }
		
	if( SearchValues.size() == 1 ) // simple query
	{
		cout << " Scoring.. " << endl;
		mySearch.scoreByFrequency();
		sortData();
		cout << "/**                               RESULTS                               **/\n";
		cout << "/*----------------------------------------------------------------------**/\n";
		cout << "  Total Results: " << totalresult << "\n" << endl;
		displayResults1(); //Display the sorted array
	}
	else // composed query
	{
		cout << " Scoring.. " << endl;
		string st1 = "and";
		string st2 = "or";
		string stype = searchType;
		if ( st1.compare(stype) == 0 )
		{
			if(verbose)
			cout << "Search is of type AND" << endl;
			mySearch.scoreByDistance();
			sortData();
			cout << "/**                               RESULTS                               **/\n";
			cout << "/*----------------------------------------------------------------------**/\n";
			cout << "/**  Total Results: " << totalresult << "\n" << endl;
			displayResults2(); 
		}
		if ( st2.compare(stype) == 0 )
		{
			if(verbose)
			cout << "Search is of type OR" << endl;

			mySearch.scoreByFrequency();
			sortData();
			cout << "/**                               RESULTS                               **/\n";
			cout << "/*----------------------------------------------------------------------**/\n";
			cout << "  Total Results: " << totalresult << "\n" << endl;
			displayResults1(); //Display the sorted array
		}
		//score by frequency plus distance
	}
	

	MatchedResults.clear();
	/* Close all files */
	for ( size_t i = 0; i < p.size(); i++ )
    {
		p[i]->close();
    }
	/* Close the directory */
	cout << endl;
	explore.closeDir();


    _getch();
	return 0;
}

void DefineScope()
{
	//define search scope
	cout << "Refine your search (or enter nothing for default selection):" << endl;
	cout << "1. Search by words" << endl;
	cout << "2. Search by lines" << endl;
	cout << "3. Search by paragraph" << endl;
	cout << "4. Search by document" << endl;
 	char DefineScope;
	cin >> DefineScope;

	switch ( DefineScope )
	{
		case '1':
		// within all words
			cout << "You chose 1" << endl;
			//
			break;
		case '2':
			//within all lines
			cout << "You chose 2" << endl;
			break;
		case '3':
			//within paragraphs
			cout << "You chose 3" << endl;
			break;
		case '4':
			// within each document
			cout << "You chose 4" << endl;
			break;
		case ' \n':
			cout << "Choosing default " << endl;
		default:
			// within all words
			cout << "Choosing default " << endl;
	} 
}

