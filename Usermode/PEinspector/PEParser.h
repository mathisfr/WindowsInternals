#pragma once
#include <string>
#include <fstream>
#include "PEParserDosHeader.h"
#include "PEParserNTHeaders.h"


class PEParserNTHeaders;

class PEParser
{
private:
	std::string fileName;
	std::ifstream file;
	PEParser();

public:
	~PEParser();
	PEParser(std::string fileName);
	void printDump();

	PEParserDosHeader* peParserDosHeader;
	PEParserNTHeaders* peParserNTHeaders;

	bool b_error = false;
	bool b_is64 = false;

	static void printTitle(std::string str);
	static void printStandard(std::string strA, std::string strB);
	static void printStandardList(std::string strA, std::string strB);
};

