#include "StdAfx.h"
#include "DirExplorer.h"
#include "FileReader.h"

using namespace std;

DirExplorer::DirExplorer(void)
{
	
	DirExplorer::enterDir();
	DirExplorer::setDir( directory );
	if ( DirExplorer::openDirectory( getDir() ) != true )
	{
		DirExplorer::DirExplorer();
	} 
}

void DirExplorer::setDir( string d )
{
	directory = d;
}

string DirExplorer::getDir()
{
	return directory;
}

void DirExplorer::enterDir()
{
	cout << "Enter a directory path to open (or enter nothing to exit):\n" << flush;
	cin >> directory;
	//directory = "D:/Search/";
}
/*
void DirExplorer::openFile( string filepath )
{
	ifstream File;	
	// Endeavor to read a single number from the file and display it
	File.open( filepath.c_str() );

		if (!File.is_open() )
		{
			cerr << "Error opening file: " << filepath << endl;
		}
		else
		{
			cout << "Opened file: " << filepath << endl;
			cout << endl;
		}
}
*/
vector<string> DirExplorer::getFilePaths()
{
	string dir = DirExplorer::getDir();
	DIR *folder = dp;
	filepaths.clear();

	while ((dirp = readdir( folder )))
	{
		filepath = dir + "/" + dirp->d_name;
		// If the file is a directory (or is in some way invalid), skip it
		if (stat( filepath.c_str(), &filestat )) 
			continue;
		if (S_ISDIR( filestat.st_mode ))         
			continue;
		filepaths.push_back(filepath);
		//openFile( filepath );					
	}
	return filepaths;
}

bool DirExplorer::openDirectory( string d )
{
	string dir = d;
	int num = 0;
	
	if ( dir == "" )
	{
		exit(1);
	}
	else
	{
		dp = opendir(dir.c_str() );

		if ( dp != NULL )
		{
			if ( verbose) 
			{
				cout << "Opened directory: " << dir << endl;
			}
			return true;
		}
		else
		{
			cerr << "Error opening directory: " << dir << endl;
			return false;
		}
	}
}

void DirExplorer::closeDir()
{
	cout << "Closing directory: " << getDir() << endl;
	closedir(dp);
}

