#include "PEParserDosHeader.h"
#include <iostream>

PEParserDosHeader::PEParserDosHeader() {
	ZeroMemory(&imageDosHeader, sizeof(imageDosHeader));
}

PEParserDosHeader::PEParserDosHeader(std::ifstream& file) {
	file.read(reinterpret_cast<char*>(&imageDosHeader), sizeof(IMAGE_DOS_HEADER));
	if (!file) {
		b_error = true;
	}
}

long PEParserDosHeader::getNtHeadersOffset() {
	return this->imageDosHeader.e_lfanew;
}


std::string PEParserDosHeader::getMagicNumber() {
	return std::string(reinterpret_cast<char*>(&imageDosHeader.e_magic), sizeof(unsigned short));
}
