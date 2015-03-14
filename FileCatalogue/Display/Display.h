#ifndef DISPLAY_H
#define DISPLAY_H
//////////////////////////////////////////////////////////////////////////
// Display.h -  Class providing utillity functionalities to display		//
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
/*
* Module Operations:
* ==================
* This module provides class Display
*  Display class has the responsibility of showing results in the standard output.
* Public Interface:
* =================
* DataStore store;
* Display::showBriefSummary(path,patterns, recursive,store);
* DataStore duplicateFiles;
* Display::showDuplicateFiles(duplicateFiles);
* DataStore searchResults;
* Display::showSearchResults(searchText, patterns,searchResults);
* Display::stringRepresentationofVector({"Isira","Samarasekera"});
* Display::showCommandLineArguements(std::vector<std::string> args);
* Display::showTextSpecificationInstructions();
* Display::showUserPrompt();
* Display::showRequirementHeader(2);

* Required Files:
* ===============
* Display.h Display.cpp DataStore.h DataStore.cpp
* Build Command:
* ==============
* cl /EHa /DTEST_DISPLAY Display.cpp
*
* Maintenance History:
* ====================
* ver 1.0 : 09 Feb 15
* - first release
*/

#include "../DataStore/DataStore.h"

class Display
{

public :
	static void showBriefSummary(std::string path, std::vector<std::string> patterns, bool recursive,
								DataStore& store);
	static void showDuplicateFiles(DataStore& duplicateFiles);
	static void showSearchResults(std::string searchText, std::vector<std::string> patterns,DataStore& searchResults);
	static std::string stringRepresentationofVector(std::vector<std::string> vector, std::string delimiter=" , ");
	static void showCommandLineArguements(std::vector<std::string> args);
	static void showTextSpecificationInstructions(); 
	static void showUserPrompt();
	static void showRequirementHeader(int number);
};
#endif 