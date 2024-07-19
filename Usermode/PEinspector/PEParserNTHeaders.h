#pragma once
#include "PEParserOptionalHeader64.h"
#include "PEParserDosHeader.h"
#include <map>

#define PEPARSER_UNDEFINED_STRING "Undefined"
#define PEPARSER_IOMANIP_HEX std::hex << std::setw(1) << std::setfill('0')

class PEParserNTHeaders
{
private:
	IMAGE_NT_HEADERS64 imageNtHeader;
	IMAGE_FILE_HEADER imageFileHeader;

	bool CHECK_ARCHITECTURE(std::ifstream& file);

public:
	PEParserNTHeaders();
	PEParserNTHeaders(std::ifstream& file, PEParserDosHeader& peParserDosHeader, bool& is64Architecture);

	bool b_error = false;

	PEParserOptionalHeader64 peParserOptionalHeader64;

	std::string getOptionalHeaderMagicNumberFromNTHeaders();
	std::string getSignature();


	// IMAGE_FILE_HEADER FileHeader
	std::map<std::string, std::string> mapFileHeader;

	std::string str_FileHeaderMachine;
	std::string str_FileHeaderNumberOfSections;
	std::string str_FileHeaderTimeDateStamp;
	std::string str_FileHeaderPointerToSymbolTable;
	std::string str_FileHeaderNumberOfSymbols;
	std::string str_FileHeaderSizeOfOptionalHeader;
	std::string str_FileHeaderCharacteristics;

	std::string getMachine(WORD machine);
	std::string getNumberOfSections(WORD numberofsection);
	std::string getTimeDateStamp(DWORD timedatestamp);
	std::string getPointerToSymbolTable(DWORD pointertosymboltable);
	std::string getNumberOfSymbols(DWORD numberofsymbols);
	std::string getSizeOfOptionalHeader(WORD sizeofoptionalheader);
	std::string getCharacteristics(WORD characteristics);
};

