//////////////////////////////////////////////////////////////////////////
// StandardInputParser.cpp:												//
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

#include "StandardInputParser.h"
#include "../Display/Display.h"
#include <regex>
#include <iostream>

StandardInputParser::StandardInputParser(Cataloger& cataloger) :_cataloger(cataloger)
{
}

//----< Untill empty input is provided prompt the user and get text search specifications >--------------------

void StandardInputParser::process()
{
	Display::showTextSpecificationInstructions();

	while (true)
	{
		Display::showUserPrompt();

		std::string input;
		std::getline(std::cin, input);
	
		if (input.empty())
			break;

		parseArguements(input);
		if (_patterns.empty())
		{
			_patterns.push_back("*.*");
		}
		_cataloger.FilesWithSearchText(_text, _patterns);
		_text.clear();
		_patterns.clear();
	}
}

//----< Given a string tokenize words and Quoted strings >--------------------

std::string  StandardInputParser::getNextArgument(std::string str)
{
	std::regex rgx("((\"([^\"]*)\")|(([^\" ]*)))"); // will capture "me too"

	std::regex_iterator<std::string::iterator> current(str.begin(), str.end(), rgx);
	std::regex_iterator<std::string::iterator> end;
	std::string arguement;
	if (current != end)
	{
		arguement = current->str();
	}
	return arguement;

}

//----< remove leading and trailing spaces from a string >--------------------

std::string StandardInputParser::trim(const std::string& str,
	const std::string& whitespace)
{
	const auto strBegin = str.find_first_not_of(whitespace);
	if (strBegin == std::string::npos)
		return ""; // no content

	const auto strEnd = str.find_last_not_of(whitespace);
	const auto strRange = strEnd - strBegin + 1;

	return str.substr(strBegin, strRange);
}

//----< If a quoted string, return the string with quotes removed >--------------------

std::string removeQuotesIfQuoted(std::string arg)
{
	
	if (arg.size() >= 2 && (arg.at(0) == ('\"')) && (arg.back() == ('\"')))
		arg = arg.substr(1, arg.length() - 2);
	return arg;
}

//----< Tokenize command line input in to search text and file patterns >--------------------

void  StandardInputParser::parseArguements(std::string searchText)
{
	
	bool firstArgumentFound = false;
	while (!searchText.empty())
	{
		searchText = trim(searchText);
		std::string arg = getNextArgument(searchText);
		searchText = searchText.substr(arg.size(), searchText.size());
		arg = removeQuotesIfQuoted(arg);
		if (!firstArgumentFound)
		{
			_text = arg;
			firstArgumentFound = true;
		}
		else
		{
			_patterns.push_back(arg);
		}	
	}
}

//----< returns the search text specified >--------------------

std::string StandardInputParser::text()
{
	return _text;
}

//----< returns the patterns of file names in the catalog which needs to be searched >--------------------

std::vector<std::string> StandardInputParser::patterns()
{
	return _patterns;
}

//----< returns whether to exit the program >--------------------

bool StandardInputParser::exit()
{
	return _input.empty();
}

#ifdef TEST_STANDARDINPUTPARSER
#include "../DataStore/DataStore.h"
#include <sstream>
#include <regex>

void main()
{
	DataStore store;
	Cataloger cataloger(store);
	StandardInputParser parser(cataloger);
	parser.parseArguements("\"Isira Samarasekera\"");

	std::cout << parser.text()<<std::endl;
	std::cout << Display::stringRepresentationofVector(parser.patterns()) << std::endl;
	
}
#endif