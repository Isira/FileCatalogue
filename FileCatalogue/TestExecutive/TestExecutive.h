#ifndef TESTEXECUTIVE_H
#define TESTEXECUTIVE_H

//////////////////////////////////////////////////////////////////////////
// TestExecutive.h -	Demonstrate Requirements						//
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
* This module provides class TestExecutive.
* Responsibility of the TestExecutive class is to demonstrate that the requirements are met. 
*
* Public Interface:
* =================
* TestExecutive executive;
* executive.DemonstrateRequirement3();
* executive.DemonstrateRequirement5();
* executive.DemonstrateRequirement6();
* executive.DemonstrateRequirement7();
* executive.DemonstrateRequirement8();
*
* Required Files:
* ===============
*	TestExecutive.h TestExecutive.cpp
* Build Command:
* ==============
* cl /EHa /DTEST_TESTEXECUTIVE TestExecutive.cpp
*
* Maintenance History:
* ====================
* ver 1.0 : 09 Feb 15
* - first release
*/

#include "../DataStore/DataStore.h"

class TestExecutive
{
	
private:
	void prepareDataStore(std::vector<std::string> arguments,DataStore& store);
	void loadDataStore(std::string path, std::vector<std::string> patterns, bool recurse, DataStore& store);
	void DemonstrateRequirement3_NonRecursive();
	void DemonstrateRequirement3_Recursive();
	void DemonstrateRequirement7_NonRecursive();
	void DemonstrateRequirement7_Recursive();

public:
	TestExecutive();
	void DemonstrateRequirement3();
	void DemonstrateRequirement5();
	void DemonstrateRequirement6();
	void DemonstrateRequirement7();
	void DemonstrateRequirement8();
};
#endif