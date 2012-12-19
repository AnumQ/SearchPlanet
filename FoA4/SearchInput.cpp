#include "StdAfx.h"
#include "SearchInput.h"

using namespace std;

SearchInput::SearchInput()
{
	SearchInput::getSearchInput();
	SearchInput::setSearch( Search );
}

void SearchInput::setSearch( string s )
{
	Search = s;
}

string SearchInput::getSearch()
{
	return Search;
}

void SearchInput::getSearchInput()
{
	cout << "Please enter your search query: " << endl;
	getline( cin, Search );
}
void SearchInput::setSearchType(string s)
{
	searchType = s;
	if(verbose)
	cout << "Setting the searchType to: " << searchType << endl;
}

vector <string> SearchInput::processSearchInput()
{
	string search = getSearch();
	string and = "and ";
	string or = "or ";
	int word1 = search.find( and );
	int word2 = search.find( or );
	
	if ( ( word1 != string::npos) || ( word2 != string::npos ) ) 
	{
		string newstr;
		//cout << "\nSplitting string.." << endl;
		if ( word1 != string::npos )
		{

		    newstr = search.erase(int(word1), and.length());// erase the word 'and' before splitting 
			setSearchType("and");
		}
		if ( word2 != string::npos )
		{
			newstr = search.erase(int(word2), or.length());	// erase the word 'or' before splitting	
			setSearchType("or");
		}

		char *c_line, *p;
		c_line = new char[ newstr.size() + 1]; 
		strcpy( c_line, newstr.c_str() );  // c_line now contains a c-string copy of newstr
		p = strtok ( c_line, " " );
		SearchWords.clear();
		while ( p != NULL )
		{
			SearchWords.push_back( p );
			p = strtok( NULL, " " );

		}		
		if(verbose)
		PrintWords(SearchWords);
	}
	else
	{
		SearchWords.clear();
		SearchWords.push_back(search);
	}
	return SearchWords;

}

void SearchInput::PrintWords( vector <string> & v )
{
    for ( size_t n = 0; n < v.size(); n++ )
    {
        cout << "'" << v[ n ] << "'\n";
        cout << endl;
    }
}
	