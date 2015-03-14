#ifndef FILEMANAGER_H
#define FILEMANAGER_H

//////////////////////////////////////////////////////////////////////////
// FileManager.h -	Find files given directory path, patterns and to	//
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
/*
* Module Operations:
* ==================
* This module provides class FileManager.
* FileManager, search files in a path matching one or many file name patterns.
* If recursive is set true, then it will will recurse in to the subdirectories in order to find the files
* All the found file paths are saved in the datastore object.
*
* Public Interface:
* =================
*	DataStore store;
*	FileManager fileManager(path,patterns,recursive,store);
*	fileManager.search();
*
* Required Files:
* ===============
*	DataStore.h DataStore.cpp FileManager.h FileManager.cpp
*
* Build Command:
* ==============
* cl /EHa /DTEST_FILEMANAGER FileManager.cpp
*
* Maintenance History:
* ====================
* ver 1.0 : 09 Feb 15
* - first release
*/
#include <vector>
#include "../DataStore/DataStore.h"

class FileManager
{

public:
	FileManager(std::string path, std::vector<std::string> patterns, bool recursive,DataStore& store);
	void search();

private:
	void findFiles(std::string directory);
	std::string path_;
	std::vector<std::string> _patterns;
	std::vector<std::string> _files;
	bool _recursive;
	DataStore& _store;

};
#endif