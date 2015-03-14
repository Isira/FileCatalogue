//////////////////////////////////////////////////////////////////////////
// Cataloger.h - Do operations on the Datastore.						//
//			     i.e: FindDuplicates, Get files with search text		//
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
* This module acts as the Executive of the FileCatalogue project.
* It accepts commandline arguments and drives the application
* giving commands to other packages.
*
* Required Files:
* ===============
*	main.cpp	Cataloger.h Cataloger.cpp CLIManager.h CLIManager.cpp DataStore.h 
	DataStore.cpp Display.h Display.cpp FIleManager.h FileManager.cpp StandardInputParser.h StandardInputParser.cpp 
* 
*  Build Command:
* ==============
* cl /EHa main.cpp Cataloger.cpp CLIManager.cpp DataStore.cpp Display.cpp FileManager.cpp StandardInputParser.cpp 
*
* Maintenance History:
* ====================
* ver 1.0 : 09 Feb 15
* - first release
*/

#include "../FileManager/FileManager.h"
#include  "../Cataloger/Cataloger.h"
#include "../CLIManager/CLIManager.h"
#include "../StandardInputParser/StandardInputParser.h"
#include "../Display/Display.h"
#include "../DataStore/DataStore.h"
#include <string>
#include <vector>

//----< Store the files specified from the command line, in the data store >--------------------

void storeFilesSpecifiedInCommandLine(CLIManager& cli, DataStore& dat)
{
	std::vector<std::string> patterns = cli.patterns();
	bool recursive = cli.recursive();
	std::string path = cli.path();

	FileManager fm(path, patterns, recursive, dat);
	fm.search();
}

//----< If the option is enabled find duplicates >--------------------

void findDuplicatesIfSpecified(CLIManager& cli, Cataloger& cat)
{
	bool findDuplicates = cli.findDuplicates();
	if (findDuplicates)
		cat.DuplicateFiles();
	  
}

//----< If a text is provided to search, search the specified files >--------------------

void searhTextIfSpecified(CLIManager& cli, Cataloger& cat)
{
	std::string searchText = cli.searchText();
	if (!searchText.empty())
		cat.FilesWithSearchText(searchText);
}



int main(int argc, char** argv)
{
	CLIManager cli;
	DataStore dataStore;
	Cataloger cataloger(dataStore);
	StandardInputParser standardInputParser(cataloger);

	cli.understandCommandLineArguements(argc, argv);
	
	storeFilesSpecifiedInCommandLine(cli, dataStore);
	
	findDuplicatesIfSpecified(cli, cataloger);
	
	searhTextIfSpecified(cli, cataloger);
	
	standardInputParser.process();
	
	return 0;
}