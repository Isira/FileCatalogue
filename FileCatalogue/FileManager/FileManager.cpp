//////////////////////////////////////////////////////////////////////////
// FileManager.cpp -	Find files given directory path, patterns and to	//
//					recurse or not,and save each file in to a Datastore.//
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

#include "FileManager.h"
#include "FileSystem.h"
#include "../Display/Display.h"

FileManager::FileManager(std::string path, std::vector<std::string> patterns, bool recursive, DataStore& store) :
						path_(path), _patterns(patterns), _recursive(recursive), _store(store)
{
	if (_patterns.empty()){
		_patterns.push_back("*.*");
	}

	if (path_.empty()){
		path_ = ".";
	}

}

//----< find the files and display a brief summary >--------------------

void FileManager::search()
{
	findFiles(path_);
	Display::showBriefSummary(path_, _patterns,_recursive,_store);
}

//----< find the files for a directory and save in the datastore >--------------------

void FileManager::findFiles(std::string directory)
{
	for (auto it = _patterns.begin(); it < _patterns.end(); it++){
		std::string pattern = *it;
		std::vector<std::string> files = FileSystem::Directory::getFiles(directory, pattern);

		for (auto i = files.begin(); i < files.end(); i++)
		{
			std::string fileName = *i;
			_store.save(directory, fileName);
		}
	}
	if (_recursive)
	{
		std::vector<std::string> dirs = FileSystem::Directory::getDirectories(directory);
		for (auto it = dirs.begin(); it < dirs.end(); it++)
		{
			std::string relativeDirPath = *it;
			if (relativeDirPath.compare(".") && relativeDirPath.compare(".."))
			{
				std::string absoluteDirPath = FileSystem::Path::fileSpec(directory,relativeDirPath);
				findFiles(absoluteDirPath);
			}

		}
	}
}

#ifdef TEST_FILEMANAGER
#include <iostream>
int main()
{
	using namespace std;
	cout << "Recursive finding files" << endl;
	cout << "========================" << endl;
	cout << endl;
	{
		DataStore store;
		FileManager fm("..", { "*.h", "*.cpp" }, true, store);
		fm.search();
	}
	cout << "Non Recursive finding files" << endl;
	cout << "============================" << endl;
	cout << endl;
	{
		DataStore store;
		FileManager fm(".", { "*.h", "*.cpp" }, false, store);
		fm.search();
	}


}
#endif