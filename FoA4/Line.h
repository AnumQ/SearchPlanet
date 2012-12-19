#pragma once

using namespace std;
class Line
{
public:
	/* Functions */
	Line(int LineNumber, string FileName );	
	void displayLine();
	void setLine( string l );
	int getLineNo();
	string getLine();
	string getFileName();
	/* Attributes */

private:
	/* Functions */
	void setLineData( int l, string f );
	/* Attributes */
	int lineNo;
	string line;
	string filename;
};

