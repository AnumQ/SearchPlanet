// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#define MAXLINE 5000 
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <istream>
#include <memory>

#include <tchar.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include "Word.h"
#include "Line.h"

#include "targetver.h"
#include "conio.h"

extern bool verbose; // extern tells the compiler this variable 'verbose' is declared elsewhere
extern vector<Word> myWord;
extern vector<Line> myLine;
extern vector<Word> MatchedResults;
extern string searchType;

// TODO: reference additional headers your program requires here
