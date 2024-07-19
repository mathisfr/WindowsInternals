#pragma once
#include "PEParserOptionalHeader64.h"
#include "PEParserDosHeader.h"
class PEParserNTHeaders
{
private:
#ifdef _WIN64
	IMAGE_NT_HEADERS64 imageNtHeader;
#else
	IMAGE_NT_HEADERS32 imageNtHeader;
#endif

	bool CHECK_ARCHITECTURE(std::ifstream& file);

public:
	PEParserNTHeaders();
	PEParserNTHeaders(std::ifstream& file, PEParserDosHeader& peParserDosHeader, bool& is64Architecture);

	bool b_error = false;

	PEParserOptionalHeader64 peParserOptionalHeader64;

	std::string getMachineTypes();
	std::string getOptionalHeaderMagicNumberFromNTHeaders();
	std::string getSignature();
};

