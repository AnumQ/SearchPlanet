#include "StdAfx.h"
#include "Search.h"
#include "Word.h"
#include "SearchInput.h"
#include "Line.h"

using namespace std;

Search::Search(void)
{
}

vector<Word> Search::SearchForMatch(vector<string> SearchValues)
{
	result = 0;

	for ( size_t x = 0; x < myWord.size(); x++ )
	{
		Word currentWord = myWord[x];
		string w = currentWord.getWord();
		for ( size_t k = 0; k < SearchValues.size(); k++ )
		{
			string h = SearchValues[k];
			if ( stricmp((w.c_str()), (h.c_str()) ) == 0 )
			{
				if( verbose)
				cout << "       Found the search '" << w << " at " << currentWord.getPosition() << endl;
				MatchedResults.push_back(currentWord);
				result++;
			}

		}

	}
	return MatchedResults;
}

void Search::SearchInWords(vector<Word> SplittedWords, vector<string> SearchValues, vector<Line> Sentences )
{
	result = 0;
	MatchedResults.clear();
	for ( size_t x = 0; x < SplittedWords.size(); x++ )
	{   
		Word currentWord = SplittedWords[x];
		string w = currentWord.getWord();
		for ( size_t k = 0; k < SearchValues.size(); k++ )
		{
			string h = SearchValues[k];
				
			if ( stricmp((w.c_str()), (h.c_str()) ) == 0 )
			{
				if ( verbose) 
				cout << "       Found the search '" << h << "' equal to " << w << endl;
				for ( size_t x = 0; x < Sentences.size(); x++ )
				{
					if( ( Sentences[x].getLineNo() == currentWord.getLine() ) 
						&& ( Sentences[x].getFileName() == currentWord.getFilename() ) )
					{
						//Sentences[x].displayLine();

					}
				}
				//cout << currentWord.getWord() << " " << currentWord.getLine() << " " << currentWord.getFilename() << endl;
				//addScore(currentWord);
				currentWord.addScore(1);
				MatchedResults.push_back(currentWord);
				result++;
			}	
		}
		string f = currentWord.getFilename();
		int pos = currentWord.getPosition();
		int l = currentWord.getLine();
		if ( verbose) 
		cout << "WordNo " << x << "; Position " << pos << " " << w << " (" << l << ") in " << f <<  endl;
	}
	
}

int Search::getResults()
{
	return result;
}

void Search::scoreByFrequency()
{
	if(verbose)
	cout << "MatchedResults " << MatchedResults.size() << endl; // how to compare the results between different files? what is another file shows higher score??
	for( size_t n = 0; n < MatchedResults.size(); n++ )
	{
		if ( n > 0 )
		{
			if ( MatchedResults[n].getLine() == MatchedResults[n-1].getLine() 
				&& MatchedResults[n].getFilename() == MatchedResults[n-1].getFilename() )
			{
				//MatchedResults[n-1].addScore(1);
				if(verbose)
				{
				cout << "MatchedResults[n-1].getLine() " << MatchedResults[n-1].getLine() << endl;
				cout << "MatchedResults[n].getLine() " << MatchedResults[n].getLine() << endl;
				cout << "	Adding score to " << MatchedResults[n].getPosition() << endl;
				}
				MatchedResults[n].addScore(MatchedResults[n-1].getScore() + 1); // is it necessary to add a score to each of the words found in the
				MatchedResults.erase(MatchedResults.begin() + (n-1));
				n = n - 1;
				if(verbose)
				cout << "MatchedResults2 " << MatchedResults.size() << endl;
			}
			
		}	
	}
	if(verbose)
	printScore();

}

void Search::printScore()
{
	for( size_t n = 0; n < MatchedResults.size(); n++ )
	{
	cout << MatchedResults[n].getWord() << " " << MatchedResults[n].getPosition() << " " << MatchedResults[n].getLine() << " score: " << MatchedResults[n].getScore() << endl;
	}
}


void Search::scoreByDistance()
{
	int lastpDifference = 0;
	int maxscore = 0;
	for( size_t n = 0; n < MatchedResults.size(); n++ )
	{
		if ( n > 0 )
		{
			int pDifference = 0;
			int p1 = MatchedResults[n].getPosition();
			int p2 = MatchedResults[n-1].getPosition();
			int l1 = MatchedResults[n].getLine();
			int l2 = MatchedResults[n-1].getLine();
			
			if ( strcmp( ((MatchedResults[n].getFilename()).c_str()), 
				((MatchedResults[n-1].getFilename()).c_str()) ) == 0 ) 
			{
				pDifference = p1 - p2;
				
				if (verbose)
				{
				cout << "   pDiff between positions " << p2 << " (" << l2 << ") and " << p1 << " (" << l1 << ") is: " << pDifference 
				<< " in " << MatchedResults[n].getFilename() << endl;
				}
				//need to score here, we have got 0, 1, 2 ==> 3 positions
				Word i = MatchedResults[n];
				MatchedResults[n].addScore(pDifference);
				i.addScore(pDifference);
				if (verbose)
				{
				//cout << "Getting the score " << i.getScore() << endl;
				cout << "       " << i.getWord() << " (" << i.getLine() << ") " << " was scored; Score is " << i.getScore() << endl;
				}
			/*	i = MatchedResults[n];
				i.addScore(pDifference);
				if (verbose)
				{
				cout << "Getting the score " << i.getScore() << endl;
				cout << "       " << i.getWord() << " (" << i.getLine() << ") " << " was scored; Score is " << i.getScore() << endl;
				}*/
			}

			if ( MatchedResults[n].getLine() == MatchedResults[n-1].getLine() 
				&& MatchedResults[n].getFilename() == MatchedResults[n-1].getFilename() ) 
			{
				if (verbose)
				cout << "Increasing importance where current score is " << MatchedResults[n].getScore() << endl;
				int x = ( ( MatchedResults[n].getScore() ) * 0.5 );
				MatchedResults[n].deductScore(x);
				if(verbose)
				cout << "New score is " << MatchedResults[n].getScore() << endl;
			}
		}
		if ( maxscore < MatchedResults[n].getScore() )
		{
			maxscore = MatchedResults[n].getScore();
		}
	}
		
	for( size_t n = 0; n < MatchedResults.size(); n++ )
	{
		if ( MatchedResults[n].getScore() == 0 ) //Scores that are initially zero must be put at the back of the list; therefore adding a score of maxscore + 100.
		{
			int s = maxscore + 100;
			if(verbose)
			{
			cout << "Pushing back the scores with " << s << endl;
			}
			MatchedResults[n].addScore(s);
		}
	}
		//cout << MatchedResults[n].getWord() << " " << MatchedResults[n].getLine() << " " << MatchedResults[n].getFilename() << endl;
		// checking the difference in the position
		/*if ( n > 0 )
		{
			int pDifference = 0;
			int p1 = MatchedResults[n].getPosition();
			int p2 = MatchedResults[n-1].getPosition();
			int l1 = MatchedResults[n].getLine();
			int l2 = MatchedResults[n-1].getLine();


			
			if ( strcmp( ((MatchedResults[n].getFilename()).c_str()), 
				((MatchedResults[n-1].getFilename()).c_str()) ) == 0 ) 
			{
				pDifference = p1 - p2;
				
				if (verbose)
				cout << "   pDiff between positions " << p1 << " (" << l1 << ") and " << p2 << " (" << l2 << ") is: " << pDifference 
				<< " in " << MatchedResults[n].getFilename() << endl;
			}

			if ( n > 1 )
			{
				if (verbose)
				cout << "  printing last difference: " << lastpDifference << " and the current: " << pDifference << endl;
				if ( pDifference < lastpDifference) 
				{
					//need to score here, we have got 0, 1, 2 ==> 3 positions
					Word i = MatchedResults[n-1];
					i.addScore(pDifference);
					if (verbose)
					{
					cout << "Getting the score " << i.getScore() << endl;
					cout << "       " << i.getWord() << " (" << i.getLine() << ") " << " was scored; Score is " << i.getScore() << endl;
					}
					i = MatchedResults[n];
					i.addScore(pDifference);
					if (verbose)
					{
					cout << "Getting the score " << i.getScore() << endl;
					cout << "       " << i.getWord() << " (" << i.getLine() << ") " << " was scored; Score is " << i.getScore() << endl;
					}
				}
				else
				{
					MatchedResults[n-2].addScore(lastpDifference);
					Word i = MatchedResults[n-2];
					if(verbose)
					{
					cout << "Getting the score " << i.getScore() << endl;
					cout << "       " << i.getWord() << " (" << i.getLine() << ") " << " was scored; Score is " << i.getScore() << endl;
					}
					MatchedResults[n-1].addScore(lastpDifference);
					i = MatchedResults[n-1];
					if(verbose)
					{
					cout << "Getting the score " << i.getScore() << endl;
					cout << "       " << i.getWord() << " (" << i.getLine() << ") " << " was scored; Score is " << i.getScore() << endl;
					}
				}
			}
			lastpDifference = pDifference;
		} */ 
}

void Search::addScore( Word word )
{
	Word i = word;
	i.addScore(2);
	string w = i.getWord();
	//if(verbose)
    cout << "       " << w << " (" << i.getLine() << ") " << " was scored; Score is " << i.getScore() << endl;
	
	//cout << "  Score is " << i.getScore() << endl;
	
}

void Search::DisplayTheResult( vector<Line> Sentences )
{
	for( size_t n = 0; n < MatchedResults.size(); n++ )
	{
		for ( size_t x = 0; x < Sentences.size(); x++ )
		{
			if ( ( Sentences[x].getLineNo() == MatchedResults[n].getLine() )
				&& ( Sentences[x].getFileName() == MatchedResults[n].getFilename() ) )
			{
				Sentences[x].displayLine();

			}

		}
		if(verbose)
		cout << "	Score: " << MatchedResults[n].getScore();
		cout << endl;

	}
}

bool Search::SearchInVector( vector <string> & v, vector <string> & search )
{
	for ( size_t n = 0; n < v.size(); n++ )
    {
		for ( size_t k = 0; k < search.size(); k++ )
		{
			if ( v[ n ] == search[k] )
			{
				cout << "Found a match of " << v[n] << "at position.. " << v[n].data()  << endl;
				return true;
			}
		}
    }
}