#include "StdAfx.h"
#include "Line.h"

using namespace std;

Line::Line( int LineNumber, string FileName )
{
	setLineData( LineNumber, FileName );
}

void Line::setLineData( int l, string f )
{
	lineNo = l;
	filename = f;
}

void Line::setLine( string l )
{
	line = l;
}
int Line::getLineNo()
{
	return lineNo;
}

string Line::getLine()
{
	return line;
}

string Line::getFileName()
{
	return filename;
}


void Line::displayLine()
{
	int a = getLineNo();
	string b = getLine();
	string c = getFileName();
	//if (verbose)
	cout << b << " (" << a << ") in " << c << endl;
	//else
	//cout << b << " (" << a << ") " << endl;
}