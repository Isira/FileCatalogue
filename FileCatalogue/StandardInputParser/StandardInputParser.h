#ifndef STANDARDINPUTPARSER_H
#define STANDARDINPUTPARSER_H

//////////////////////////////////////////////////////////////////////////
// StandardInputParser.h:												//
//			Accept an string from the standard input,					//
//			parse it to get search text specification and file patterns,//
//          and search the text in the files stored in the catalog which//
//			are matching the pattern									//
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
* This module provides class StandardInputParser
* Parses a console input, to identify a text specification and one or more file name patterns.
* The files of which the file name match at least one of the patterns are searched for the text specification.
* The files with the search text is displayed.
* After that waits for a user input.
* To terminate, needs to give empty string as the input.
*
* Public Interface:
* =================
* StandardInputParser stdParser(cataloger);
* stdParser.process();
* stdParser.parseArguements("SearchText pattern1 pattern2");
* std::string searchText = stdParser.text(); //  "Searchtext"
* std::vector<std::string> patterns = stdParser.patterns(); // {"pattern1", "pattern2"}
* bool exitFalse = stdParser.exit(); //false
* stdParser.parseArguements("");
* bool exitTrue = stdParser.exit(); //false
*
* Required Files:
* ===============
*	StandardInputParser.h StandardInputParser.cpp Cataloger.h Cataloger.cpp
*
* Build Command:
* ==============
* cl /EHa /DTEST_STANDARDINPUTPARSER StandardInputParser.cpp
*
* Maintenance History:
* ====================
* ver 1.0 : 09 Feb 15
* - first release
*/

#include <string>
#include <vector>
#include "../Cataloger/Cataloger.h"

class StandardInputParser
{
	std::string  getNextArgument(std::string str);
	std::string trim(const std::string& str,
		const std::string& whitespace = " ");

	std::string _input;
	std::string _text;
	std::vector<std::string> _patterns;
	Cataloger& _cataloger;


public:
	StandardInputParser(Cataloger& _cataloger);
	void process();
	void  parseArguements(std::string searchText);
	std::string text();
	std::vector<std::string> patterns();
	bool exit();
};
#endif