//////////////////////////////////////////////////////////////////////////
// CLIManager.cpp -  Parse command line options							//
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

#include "CLIManager.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <regex>
#include "../Display/Display.h"

CLIManager::CLIManager() :_recursive(false), _findDuplicates(false)
{
}

//----< from the raw command line input, extract the arguments relavant for the application and return them as a vector>--------------

std::vector<std::string> CLIManager::extractRelavantCommandLineArguments(int argc, char** argv)
{
	std::vector<std::string> args;
	for (int i = 1; i < argc; i++)
	{
		args.push_back(argv[i]);
	}
	return args;
}

//----< Parse the vector of arguments. find path, patterns, and other options >-------------------------------------------

void CLIManager::understandCommandLineArguements(std::vector<std::string> args)
{
	Display::showCommandLineArguements(args);
	commands = args;
	for (unsigned int i = 0; i < commands.size(); i++)
	{
		std::string arguement = commands[i];
		if (!arguement.compare("/s")){
			_recursive = true;
		}

		else if (!arguement.compare("/d")){
			_findDuplicates = true;
		}

		else if (!arguement.compare(0, 2, "/f")){
			_searchText = arguement.substr(2, arguement.size());
		}

		else if (_path.empty()){
			_path = arguement;
		}
		else {
			_patterns.push_back(arguement);
		}
	}
	
}

//----< Parse raw commandline arguments >-----------------------------

void CLIManager::understandCommandLineArguements(int argc, char** argv)
{
	std::vector<std::string> args = extractRelavantCommandLineArguments(argc, argv);
	understandCommandLineArguements(args);
}


//----< returns whether recurse in to subdirectories >---------------

bool CLIManager::recursive()
{
	return _recursive;
}

//----< returns whether to find duplicates >-------------------

bool CLIManager::findDuplicates()
{
	return _findDuplicates;  
}

//----< returns the text which needs to be searched >---------

std::string CLIManager::searchText()
{
	return _searchText;
}

//----< returns file name patterns >--------------------------

std::vector<std::string> CLIManager::patterns()
{
	return _patterns;
}

//----< returns the directory path to be searched >---------------

std::string CLIManager::path()
{
	return _path;
}

#ifdef TEST_CLIMANAGER

std::string stringRepresentationofVector(std::vector<std::string> vector)
{
	std::string stringRepresentation;
	if (!vector.empty())
	{
		std::ostringstream oss;
		std::copy(vector.begin(), vector.end() - 1,
			std::ostream_iterator<std::string>(oss, " , "));
		oss << vector.back();
		stringRepresentation = oss.str();
	}

	return stringRepresentation;
}
void main()
{
	CLIManager manager;
	int argc = 6;
	char* argv[6];
	argv[0] = "climanager.exe";
	argv[1] = ".";
	argv[2] = "*.*";
	argv[3] = "/s";
	argv[4] = "/d";
	argv[5] = "/fDUplicates";

	manager.understandCommandLineArguements(argc,argv);
	std::cout << "Path: "<<manager.path()<< std::endl;
	std::cout << "Patterns: " << stringRepresentationofVector(manager.patterns()) << std::endl;
	std::cout << "Recursive: " <<manager.recursive() << std::endl;
	std::cout << "Find duplicates: " << manager.findDuplicates()<< std::endl;
	std::cout << "Search String: " << manager.searchText()<< std::endl;
	std::cout << std::endl;

	CLIManager _manager;
	std::vector<std::string> arguements = {".","*.h","/s","/d","/f\"DUplicate string search\""};
	_manager.understandCommandLineArguements(arguements);
	std::cout << "Path: " << _manager.path() << std::endl;
	std::cout << "Patterns: " << stringRepresentationofVector(_manager.patterns()) << std::endl;
	std::cout << "Recursive: " << _manager.recursive() << std::endl;
	std::cout << "Find duplicates: " << _manager.findDuplicates() << std::endl;
	std::cout << "Search String: " << _manager.searchText() << std::endl;

}
#endif