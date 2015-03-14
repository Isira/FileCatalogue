//////////////////////////////////////////////////////////////////////////
// Display.cpp -  Class providing utillity functionalities to display		//
//				in the standard output									//
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

#include "Display.h"
#include <iostream>
#include <string>
#include <sstream>
#include "../FileManager/FileSystem.h"

//----< Display set of files with duplicate names, with their paths >--------------------

void Display::showDuplicateFiles(DataStore& duplicateFiles)
{
	if (duplicateFiles.empty())
		std::cout << "No Duplicate Files Found" << std::endl << std::endl;

	else
	{
		std::cout << "Displaying Duplicate Files" << std::endl;
		std::cout << "=========================" << std::endl;
		std::cout << std::endl;

		for (auto it : duplicateFiles)
		{
			std::string fileName = it.first;
			std::cout << "\"" << fileName << "\"" <<  " found in paths:" << std::endl;
			DataStore::ListofRefs refs = it.second;
			for (auto ref : refs)
			{
				std::string path = *ref;
				std::cout << "\t" << path << std::endl;
			}
			std::cout << std::endl;
		}
	}

}

//----< Show brief summary of overall execution >--------------------

void Display::showBriefSummary(std::string path, std::vector<std::string> patterns, bool recursive,
								DataStore& store)
{
	std::cout << "Path\t\t: " << path << std::endl;
	std::cout << "Patterns\t: " << stringRepresentationofVector(patterns) << std::endl;
	std::cout << "Recursive\t: " << (recursive ? "True" : "False") << std::endl;
	std::cout << std::endl;
	std::cout << store.fileSize() << " files found in "<< store.pathSize()<< " Directories." <<std::endl;
	std::cout << std::endl;

}

//----< Assemble a vector of strings in to a string using a delimiter >-------------------------------

std::string Display::stringRepresentationofVector(std::vector<std::string> vector, std::string delimiter)
{
	std::string stringRepresentation;
	if (!vector.empty())
	{
		std::ostringstream oss;
		std::copy(vector.begin(), vector.end() - 1,
			std::ostream_iterator<std::string>(oss, delimiter.c_str()));
		oss << vector.back();
		stringRepresentation = oss.str();
	}
	
	return stringRepresentation;
}

//----< Display the results of the Search >--------------------

void Display::showSearchResults(std::string searchText, std::vector<std::string> patterns,DataStore& searchResults)
{
	std::cout << std::endl;
	std::cout << "Displaying Files With Search Result" << std::endl;
	std::cout << "====================================" << std::endl;
	std::cout << std::endl;

	std::cout << "Search Text\t: " << searchText << std::endl;
	std::cout << std::endl;

	if (searchResults.empty())
		std::cout << "No search Results Were Found" << std::endl << std::endl;

	else
	{

		for (auto it : searchResults)
		{
			std::string fileName = it.first;
			DataStore::ListofRefs refs = it.second;
			for (auto ref : refs)
			{
				std::string path = *ref;
				std::string absolutePath = FileSystem::Path::fileSpec(path, fileName);
				std::cout << "\t"<<absolutePath << std::endl;
			}
		}
	}
}

//----< Show command line arguments as one string >--------------------

void Display::showCommandLineArguements(std::vector<std::string> args)
{
	if (args.empty()){
		std::cout << "No command line arguments are provided " << std::endl;
	}
	else{
		std::cout << "Command line arguments: " << stringRepresentationofVector(args, " ") << std::endl;
	}
	std::cout << std::endl;
}

//----< Show Instructions for the user about how to input the text search specification >--------------------

void Display::showTextSpecificationInstructions()
{
	std::cout << std::endl;
	std::cout << "Search Text in catalogue," << std::endl;
	std::cout << "Input : <searchText> <file_pattern1> <file_pattern2> ..... " << std::endl;
	std::cout << "Press Enter To Exit" << std::endl;
}

//----< Show User > sign to indicate that application waiting for input >--------------------

void Display::showUserPrompt()
{
	std::cout <<std::endl;
	std::cout << ">";
}



//----< Display header for demonstarting requirement #number >--------------------

void Display::showRequirementHeader(int number)
{
	std::cout << std::endl;
	std::cout << "============================================" << std::endl;
	std::cout << "         Demonstrating Requirment " << number <<std::endl;
	std::cout << "=============================================" << std::endl;
	std::cout << std::endl;
}


#ifdef TEST_DISPLAY
void main()
{
	std::cout << "Testing vector concating:" << std::endl;
	std::vector<std::string> names = {"Jim" ,"Fawcett","Isira"};
	std::string namesString = Display::stringRepresentationofVector(names);
	std::cout << namesString << std::endl;
	Display::showTextSpecificationInstructions(); 
	Display::showUserPrompt();
	Display::showRequirementHeader(4);
}
#endif