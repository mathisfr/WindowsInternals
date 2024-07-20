#pragma once
#include "PEParserOptionalHeader64.h"
#include "PEParserDosHeader.h"
#include <map>
#include <unordered_map>
#include "PEParser.h"

#define PEPARSER_UNDEFINED_STRING "Undefined"
#define PEPARSER_IOMANIP_HEX std::hex << std::setw(1) << std::setfill('0')

class PEParse;

class PEParserNTHeaders
{
private:
	std::ifstream* file = nullptr;

	// FILE HEADER
	IMAGE_NT_HEADERS64 imageNtHeader;
	IMAGE_FILE_HEADER* imageFileHeader = nullptr;
	IMAGE_DOS_HEADER* imageDosHeader = nullptr;

	bool CHECK_ARCHITECTURE(std::ifstream& file);

	// SECTION HEADER
	DWORD getOffsetToSectionHeadersFromIndex(unsigned int index);
	void parseSectionHeaders();

public:
	PEParserNTHeaders();
	~PEParserNTHeaders();
	PEParserNTHeaders(std::ifstream& file, PEParserDosHeader& peParserDosHeader, bool& is64Architecture);
	bool b_error = false;

	// FILE HEADER
	PEParserOptionalHeader64 peParserOptionalHeader64;

	std::string getOptionalHeaderMagicNumberFromNTHeaders();
	std::string getSignature();

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

	// IMAGE_SECTION_HEADER 
	void printSectionHeaders();

	IMAGE_SECTION_HEADER* sectionHeaders = nullptr;

	std::unordered_map<std::string, std::string> mapSectionHeader;

	std::string getSectionHeaderName(int index);
	int getSectionHeaderNumberOfLinenumbers(int index);
};

