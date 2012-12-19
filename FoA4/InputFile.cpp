#include "StdAfx.h"
#include <string>
#include <fstream>
#include <iostream>
#include "InputFile.h"

using namespace std;

InputFile::InputFile() :
	ifstream()
{
}

InputFile::InputFile( const char *filename )
{
}

void InputFile::open( const char *filename )
{
	this->filename = filename;
	ifstream::open(filename, ios::in);
	if( ifstream::fail() )
	{
		cerr << "Couldnt open " << endl;
		return;
	}
	else
	{
		cout << "Hurra!" << endl;
	}
}

void InputFile::close()
{
	ifstream::close();
}
