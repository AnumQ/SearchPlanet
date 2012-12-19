#pragma once

using namespace std;

class SearchInput
{
public:
	/* Functions */
	SearchInput();	
	string getSearch();
	void getSearchInput();
	vector <string> processSearchInput();
	void PrintWords( vector <string> & v );
	void setSearchType(string s);
	/* Attributes */

private:
	/* Functions */
	void setSearch( string s );
	/* Attributes */
	string Search;
	vector<string> SearchWords;
};


