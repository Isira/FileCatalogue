//////////////////////////////////////////////////////////////////////////
// TestExecutive.cpp -	Demonstrate Requirements						//
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

#include "TestExecutive.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "../CLIManager/CLIManager.h"
#include "../FileManager/FileManager.h"
#include "../Cataloger/Cataloger.h"
#include "../StandardInputParser/StandardInputParser.h"
#include "../Display/Display.h"

TestExecutive::TestExecutive()
{

}

//----< Load files in to a datastore according to path, patterns and recurse >--------------------

void TestExecutive::loadDataStore(std::string path,std::vector<std::string> patterns,bool recurse, DataStore& store)
{
	FileManager fm(path, patterns, recurse, store);
	fm.search();
}

//----< Load files in to a datastore according specifications given as a vector command line arguments >--------------------

void TestExecutive::prepareDataStore(std::vector<std::string> arguments, DataStore& store)
{
	CLIManager cli;
	cli.understandCommandLineArguements(arguments);
	loadDataStore(cli.path(), cli.patterns(), cli.recursive(),store);

}

//----< Demo Requirement 3: Show the brief summary for a non recursive file search >--------------------

void TestExecutive::DemonstrateRequirement3_NonRecursive()
{

	std::vector<std::string> options = { ".", "*.*" };
	DataStore store;
	prepareDataStore(options, store);
}

//----< Demo Requirement 3:Show the brief summary for a recursive file search >--------------------

void TestExecutive::DemonstrateRequirement3_Recursive()
{
	std::vector<std::string> arguments = { ".", "*.*", "/s" };
	DataStore store;
	prepareDataStore(arguments, store);
}

//----< Demo Requirement 3: Proper working of file search when , path, pattern and /s options provided>--------------------

void TestExecutive::DemonstrateRequirement3()
{
	Display::showRequirementHeader(3);
	DemonstrateRequirement3_NonRecursive();
	DemonstrateRequirement3_Recursive();
}

//----< Demo Requirement 5 :Show duplicate files in the datastore >--------------------

void TestExecutive::DemonstrateRequirement5()
{

	Display::showRequirementHeader(5);
	std::vector<std::string> options = { "..", "*.*" ,"/s","/d"};

	DataStore store;
	prepareDataStore(options, store);;
	Cataloger cataloger(store);
	cataloger.DuplicateFiles();
	
}

//----< Demo Requirement 6 : Search files for a given text >--------------------
void TestExecutive::DemonstrateRequirement6()
{
	Display::showRequirementHeader(6);
	std::vector<std::string> options = { "..", "*.cpp", "*.h", "/s", "/fDemonstrating" };

	DataStore store;
	CLIManager cli;
	cli.understandCommandLineArguements(options);
	loadDataStore(cli.path(), cli.patterns(), cli.recursive(), store);
	
	Cataloger cataloger(store);

	std::string searchText = cli.searchText();
	cataloger.FilesWithSearchText(searchText);
}

//----< Demo Requirement 7 : Show brief description when no option provided (without /s)>--------------------

void TestExecutive::DemonstrateRequirement7_NonRecursive()
{
	std::vector<std::string> options = { "..", "*.cpp", "*.h" };

	DataStore store;
	prepareDataStore(options, store);
}

//----< Demo Requirement 7 : Show brief description when no option provided (with /s)>--------------------

void TestExecutive::DemonstrateRequirement7_Recursive()
{
	std::vector<std::string> options = { "..", "*.cpp", "*.h", "/s" };

	DataStore store;
	prepareDataStore(options, store);
}

//----< Demo Requirement 7 : Show brief description when no option provided >--------------------

void TestExecutive::DemonstrateRequirement7()
{
	Display::showRequirementHeader(7);
	DemonstrateRequirement7_NonRecursive();
	DemonstrateRequirement7_Recursive();
}

//----< Demo Requirement  8: Prompt user to search in the catalog files for a text specification and show results>--------------------

void TestExecutive::DemonstrateRequirement8()
{
	Display::showRequirementHeader(8);
	std::vector<std::string> options = { "..", "*.cpp" ,"/s"};

	DataStore store;
	prepareDataStore(options, store);

	Cataloger cataloger(store);
	StandardInputParser standardInputParser(cataloger);
	standardInputParser.process();
}

#ifdef TEST_TESTEXECUTIVE

int main(int argc, char** argv)
{
	TestExecutive executive;
	executive.DemonstrateRequirement3();
	executive.DemonstrateRequirement5();
	executive.DemonstrateRequirement6();
	executive.DemonstrateRequirement7();
	executive.DemonstrateRequirement8();
}

#endif