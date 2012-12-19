#pragma once

using namespace std;

class DirExplorer 
{
public:
	/* Functions */	
	DirExplorer(void);	
	void enterDir();	
	string getDir();
	vector<string> getFilePaths();	
	void closeDir();	
	/* Attributes */

private: 
	/* Functions */
	void setDir( string d );
	bool openDirectory( string d );
	// void openFile( string ); // is this necessary here?
	/* Attributes */
	string directory;
	DIR *dp;
	struct dirent *dirp;
	struct stat filestat;	
	string filepath;
	vector<string> filepaths;
};

