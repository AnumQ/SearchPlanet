#pragma once

using namespace std;

class InputFile : public std::ifstream
{
public:
	InputFile();
	InputFile( const char * );
	void open( const char * );
	void close();

private:
	InputFile( const InputFile &copy );
	string filename;
};

