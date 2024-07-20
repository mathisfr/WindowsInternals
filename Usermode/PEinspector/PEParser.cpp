#include "PEParser.h"
#include <map>
#include <iostream>

PEParser::PEParser(std::string fileName) {
	b_error = false;

	this->fileName = fileName;

	file.open(fileName, std::ios_base::binary);
	if (!file.is_open()) {
		std::cerr << "Ouverture du fichier echoue\n";
		b_error = true;
		return;
	}
	peParserDosHeader = PEParserDosHeader(file);
	if (peParserDosHeader.b_error) {
		std::cerr << "Erreur PEParserDosHeader\n";
		b_error = true;
		return;
	}
	peParserNTHeaders = PEParserNTHeaders(file, peParserDosHeader, b_is64);
	if (peParserNTHeaders.b_error) {
		std::cerr << "Erreur PEParserNTHeaders\n";
		b_error = true;
		return;
	}
}

void PEParser::printDump() {
	std::cout << "[PE inspector " << fileName << "]" << std::endl;
	printTitle("DosHeader");
	printStandard("Magic Number", peParserDosHeader.getMagicNumber());
	printTitle("NTHeaders");
	printTitle("FileHeader");
	for (std::map<std::string, std::string>::iterator it = peParserNTHeaders.mapFileHeader.begin(); it != peParserNTHeaders.mapFileHeader.end(); it++) {
		printStandard(it->first, it->second);
	}
	printTitle("OptionalHeader");
	for (std::map<std::string, std::string>::iterator it = peParserNTHeaders.peParserOptionalHeader64.mapOptionalHeader.begin(); it != peParserNTHeaders.peParserOptionalHeader64.mapOptionalHeader.end(); it++) {
		printStandard(it->first, it->second);
	}
	peParserNTHeaders.peParserOptionalHeader64.printSectionHeaders();
}

void PEParser::printTitle(std::string str) {
	std::cout << str << " : " << std::endl;
}

void PEParser::printStandard(std::string strA, std::string strB){
	std::cout << "\t- " << strA << ": " << strB << std::endl;
}