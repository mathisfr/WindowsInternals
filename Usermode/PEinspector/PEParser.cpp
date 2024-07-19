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

	std::map < std::string, std::string > peInfoOptionalHeader;
	std::string subsystem;
	std::string architecture;
	if (b_is64) {
		subsystem = PEParserOptionalHeader64::getSubsystem(peParserNTHeaders.peParserOptionalHeader64.OptionalHeader.Subsystem);
		peInfoOptionalHeader.insert(std::pair<std::string, std::string>(("Subsystem"), subsystem));

		architecture = PEParserOptionalHeader64::getOptionalHeaderMagic(peParserNTHeaders.peParserOptionalHeader64.OptionalHeader.Magic);
		peInfoOptionalHeader.insert(std::pair<std::string, std::string>(("Architecture"), architecture));
	}
	else {

	}

	std::cout << "[PE inspector " << fileName << "]" << std::endl;
	printTitle("DosHeader");
	printStandard("Magic Number", peParserDosHeader.getMagicNumber());
	printTitle("NTHeaders");
	printTitle("OptionalHeader");
	for (std::map<std::string, std::string>::iterator it = peInfoOptionalHeader.begin(); it != peInfoOptionalHeader.end(); it++) {
		printStandard(it->first, it->second);
	}
}

void PEParser::printTitle(std::string str) {
	std::cout << str << " : " << std::endl;
}

void PEParser::printStandard(std::string strA, std::string strB){
	std::cout << "\t- " << strA << ": " << strB << std::endl;
}