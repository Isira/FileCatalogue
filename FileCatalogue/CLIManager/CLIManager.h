#ifndef CLIMANAGER_H
#define CLIMANAGER_H
//////////////////////////////////////////////////////////////////////////
// CLIManager.h -  Parse command line options							//
// ver 1.0																//
// ---------------------------------------------------------------------//
// copyright © Isira Samarasekera, 2015									//
// All rights granted provided that this notice is retained				//
// ---------------------------------------------------------------------//
// Language:    Visual C++, Visual Studio Ultimate 2013                 //
// Platform:    Mac Book Pro, Core i5, Windows 8.1						//
// Application: Project #1 – File Catalogue,2015						//
// Author:      Isira Samarasekera, Syracuse University					//
//              issamara@syr.edu										//
//////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* ==================
* This module provides class CLIManager,
* CLIManager is able to parse a set or arguments provided in the command line,
* to find out the path, patterns and options.
* options are to recurse, find duplicates, and search for text.
* Arguments can be given as a char** or a std::vector<std::string>

* Public Interface:
* =================
*	int argc = 2;	
*	char* argv[2];
*	arg[0] = "Executive.exe"; arg[1] = "."
*   CLIManager manager;
*	manager.understandCommandLineArguements(argc,argv);
*
*	std::vector<std::string> commands ={"."};
*	CLIManager _manager;
*	_manager.understandCommandLineArguements(commands);
*
* bool recurse = _manager.recursive();
* bool findDuplicates = _manager.findDuplicates();
* std::string searchText = _manager..searchText();
* std::vector<std::string> patterns = _manager.patterns();
* std::string path = _manager.path();
*    
* Required Files:
* ===============
*	CLIManager.h	CLIManager.cpp
* Build Command:
* ==============
* cl /EHa /DTEST_CLIMANAGER CLIManager.cpp
*
* Maintenance History:
* ====================
* ver 1.0 : 09 Feb 15
* - first release
*/

#include <vector>

class CLIManager
{
	bool _recursive;
	bool _findDuplicates;
	std::string _searchText;
	std::vector<std::string> _patterns;
	std::string _path;
	std::string _command;
	std::vector<std::string> commands;
	std::vector<std::string> extractRelavantCommandLineArguments(int argc, char** argv);


public:
	CLIManager();
	void understandCommandLineArguements(int argc, char** argv);
	void understandCommandLineArguements(std::vector<std::string> args);
	bool recursive();
	bool findDuplicates();
	std::string searchText();
	std::vector<std::string> patterns();
	std::string path();

};
#endif