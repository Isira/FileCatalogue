//////////////////////////////////////////////////////////////////////////
// Cataloger.cpp - Do operations on the Datastore.						//
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

#include "Cataloger.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>

#include "../FileManager/FileSystem.h"
#include "../Display/Display.h"


Cataloger::Cataloger(DataStore& store) :_store(store)
{
}

//----< Search and Display Duplicate files in the DataStore >----

void Cataloger::DuplicateFiles()
{
	DataStore _duplicateDataStore;

	for (auto it : _store)
	{
		DataStore::ListofRefs refs = it.second;
		if (refs.size() > 1)
		{
			std::string fileName = it.first;
			for (auto ref : refs)
			{
				std::string path = *ref;
				_duplicateDataStore.save(path,fileName);
			}
		}
	}
	Display::showDuplicateFiles(_duplicateDataStore);
}

//----< Search and Display files where the search text exist >------------------------------------------

void Cataloger::FilesWithSearchText(std::string searchText, std::vector<std::string> patterns)
{
	DataStore searchFileDataStore;
	for (auto it : _store)
	{
		DataStore::File file = it.first;
		if (matchesOneOfThePatterns(file, patterns))
		{
			DataStore::ListofRefs paths = it.second;
			for (auto i : paths)
			{
				std::string path = *i;
				std::string fullPath = FileSystem::Path::fileSpec(path, file);
				if (SearchTextInaFile(fullPath, searchText))
				{
					searchFileDataStore.save(path,file);
				}
			}
		}
	}

	Display::showSearchResults(searchText, patterns,searchFileDataStore);
}

//----< Check whether a file contains specified  text >-------------------------------

bool Cataloger::SearchTextInaFile(std::string filePath, std::string text)
{
 	bool found = false;
	std::ifstream in;
	in.open(filePath); 
	
	if (in.is_open()){
		std::string line;
		FileSystem::File file(filePath);
		while (std::getline(in, line))
		{
			std::istringstream iss(line);
			std::size_t position = line.find(text);
			if (position != std::string::npos)
			{
				found = true;
				break;
			}
		}
	}
	return found;
}

//----< check whether a fileName matches one of the patterns >-----------------------

bool Cataloger::matchesOneOfThePatterns(std::string fileName, std::vector<std::string> patterns)
{
	bool matching = false;
	for (std::string pattern : patterns)
	{
		if (isPatternMaching(fileName, pattern))
		{
			matching = true;
			break;
		}
	}
	return matching;
}

//----< check whether a fileName matches a specific pattern >------------------------------------------

bool Cataloger::isPatternMaching(std::string fileName, std::string pattern)
{
	std::string regexPattern = replaceWithWildcardRegex(pattern);
	return (std::regex_match(fileName, std::regex(regexPattern)));
}

//----< replace the wildcard character of a given string to match regex string >------------

std::string Cataloger::replaceWithWildcardRegex(std::string pattern)
{
	std::regex wildcardRegex("\\*");  
	std::string wildcardRegexString = "(.*)";
	std::string regexString = std::regex_replace(pattern, wildcardRegex, wildcardRegexString);
	return regexString;
}

//----< check whether a fileName matches a regex pattern 

bool Cataloger::matchWithRegex(const std::string& filename, const std::string& pattern)
{
	std::string regexPattern = replaceWithWildcardRegex(pattern);
	return (std::regex_match(filename, std::regex(regexPattern)));
}


#ifdef TEST_CATALOGER

void main()
{
	DataStore store;
	store.save(".","file1.txt");
	store.save(".", "file2.txt");
	store.save("folder", "file1.txt");
	store.save("folder", "file2.txt");

	Cataloger cataloger(store);
	cataloger.DuplicateFiles();

	store.save("../Cataloger","Cataloger.cpp");
	cataloger.FilesWithSearchText("DataStore");
	cataloger.FilesWithSearchText("DataStore", {"*.txt"});

}
#endif