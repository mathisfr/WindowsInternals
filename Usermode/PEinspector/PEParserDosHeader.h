#pragma once
#include <fstream>
#include <Windows.h>
class PEParserDosHeader
{
private:
	IMAGE_DOS_HEADER imageDosHeader;
public:
	PEParserDosHeader();
	PEParserDosHeader(std::ifstream& file);

	bool b_error = false;
	long getNtHeadersOffset();

	std::string getMagicNumber();
	IMAGE_DOS_HEADER& getImageDosHeader();
};

