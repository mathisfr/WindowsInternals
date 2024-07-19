#pragma once
#include <string>
#include <fstream>
#include "PEParserDosHeader.h"
#include "PEParserNTHeaders.h"

class PEParser
{
private:
	std::string fileName;
	std::ifstream file;
	PEParser();

	void printTitle(std::string str);
	void printStandard(std::string strA, std::string strB);
public:
	PEParser(std::string fileName);
	void printDump();

	PEParserDosHeader peParserDosHeader;
	PEParserNTHeaders peParserNTHeaders;

	bool b_error = false;
	bool b_is64 = false;
};

