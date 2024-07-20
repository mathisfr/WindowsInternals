#include "PEParserNTHeaders.h"
#include "PEParserDosHeader.h"
#include <iostream>
#include <sstream>
#include <ctime>

PEParserNTHeaders::PEParserNTHeaders() {
    ZeroMemory(&imageNtHeader, sizeof(imageNtHeader));
}

PEParserNTHeaders::PEParserNTHeaders(std::ifstream& file, PEParserDosHeader& peParserDosHeader, bool& is64Architecture) {
	file.seekg(peParserDosHeader.getNtHeadersOffset(), std::ios_base::beg);
    this->file = &file;
	file.read(reinterpret_cast<char*>(&imageNtHeader), sizeof(imageNtHeader));
	if (!file) {
		b_error = true;
	}
    this->imageDosHeader = &peParserDosHeader.getImageDosHeader();
    imageFileHeader = &imageNtHeader.FileHeader;
	is64Architecture = CHECK_ARCHITECTURE(file);
    peParserOptionalHeader64 = PEParserOptionalHeader64(imageNtHeader.FileHeader, imageNtHeader.OptionalHeader);

    // Init FileHeader variable
    std::string str_FileHeaderMachine = getMachine(imageFileHeader->Machine);
    std::string str_FileHeaderNumberOfSections = getNumberOfSections(imageFileHeader->NumberOfSections);
    std::string str_FileHeaderTimeDateStamp = getTimeDateStamp(imageFileHeader->TimeDateStamp);
    std::string str_FileHeaderPointerToSymbolTable = getPointerToSymbolTable(imageFileHeader->PointerToSymbolTable);
    std::string str_FileHeaderNumberOfSymbols = getNumberOfSymbols(imageFileHeader->NumberOfSymbols);
    std::string str_FileHeaderSizeOfOptionalHeader = getSizeOfOptionalHeader(imageFileHeader->SizeOfOptionalHeader);
    std::string str_FileHeaderCharacteristics = getCharacteristics(imageFileHeader->Characteristics);

    mapFileHeader.insert(std::pair<std::string, std::string>("Machine", str_FileHeaderMachine));
    mapFileHeader.insert(std::pair<std::string, std::string>("Number Of Sections", str_FileHeaderNumberOfSections));
    mapFileHeader.insert(std::pair<std::string, std::string>("Time Date Stamp", str_FileHeaderTimeDateStamp));
    mapFileHeader.insert(std::pair<std::string, std::string>("Pointer To SymbolTable", str_FileHeaderPointerToSymbolTable));
    mapFileHeader.insert(std::pair<std::string, std::string>("Number Of Symbols", str_FileHeaderNumberOfSymbols));
    mapFileHeader.insert(std::pair<std::string, std::string>("Size Of Optional Header", str_FileHeaderSizeOfOptionalHeader));
    mapFileHeader.insert(std::pair<std::string, std::string>("Characteristics", str_FileHeaderCharacteristics));

    // Section header
    sectionHeaders = new IMAGE_SECTION_HEADER[imageFileHeader->NumberOfSections];
    parseSectionHeaders();
}

PEParserNTHeaders::~PEParserNTHeaders() {
    if (sectionHeaders) {
        delete[] sectionHeaders;
    }
}

std::string PEParserNTHeaders::getSignature() {
    return std::string(reinterpret_cast<char*>(&imageNtHeader.Signature), sizeof(unsigned long));
}

bool PEParserNTHeaders::CHECK_ARCHITECTURE(std::ifstream& file) {
    std::string margicNumber = getOptionalHeaderMagicNumberFromNTHeaders();
    if (margicNumber == "PE32") {
        return false;
    }
    if (margicNumber == "PE32+") {
        return true;
    }
    b_error = true;
    return false;
}

std::string PEParserNTHeaders::getOptionalHeaderMagicNumberFromNTHeaders() {
    std::string magicString = PEPARSER_UNDEFINED_STRING;
    switch (imageNtHeader.OptionalHeader.Magic) {
    case IMAGE_NT_OPTIONAL_HDR32_MAGIC:
        magicString = "PE32";
        break;
    case IMAGE_NT_OPTIONAL_HDR64_MAGIC:
        magicString = "PE32+";
        break;
    case IMAGE_ROM_OPTIONAL_HDR_MAGIC:
        magicString = "ROM";
        break;
    }
    return magicString;
}

std::string PEParserNTHeaders::getMachine(WORD machine) {
    std::string machineType;
    switch (machine) {
    case IMAGE_FILE_MACHINE_UNKNOWN:
        machineType = "The content of this field is assumed to be applicable to any machine type";
        break;
    case IMAGE_FILE_MACHINE_ALPHA:
        machineType = "Alpha AXP, 32-bit address space";
        break;
    case IMAGE_FILE_MACHINE_ALPHA64:
        machineType = "Alpha 64, 64-bit address space";
        break;
    case IMAGE_FILE_MACHINE_AM33:
        machineType = "Matsushita AM33";
        break;
    case IMAGE_FILE_MACHINE_AMD64:
        machineType = "x64";
        break;
    case IMAGE_FILE_MACHINE_ARM:
        machineType = "ARM little endian";
        break;
    case IMAGE_FILE_MACHINE_ARM64:
        machineType = "ARM64 little endian";
        break;
    case IMAGE_FILE_MACHINE_ARMNT:
        machineType = "ARM Thumb-2 little endian";
        break;
    case IMAGE_FILE_MACHINE_EBC:
        machineType = "EFI byte code";
        break;
    case IMAGE_FILE_MACHINE_I386:
        machineType = "Intel 386 or later processors and compatible processors";
        break;
    case IMAGE_FILE_MACHINE_IA64:
        machineType = "Intel Itanium processor family";
        break;
    case 0x6232:
        machineType = "LoongArch 32-bit processor family";
        break;
    case 0x6264:
        machineType = "LoongArch 64-bit processor family";
        break;
    case IMAGE_FILE_MACHINE_M32R:
        machineType = "Mitsubishi M32R little endian";
        break;
    case IMAGE_FILE_MACHINE_MIPS16:
        machineType = "MIPS16";
        break;
    case IMAGE_FILE_MACHINE_MIPSFPU:
        machineType = "MIPS with FPU";
        break;
    case IMAGE_FILE_MACHINE_MIPSFPU16:
        machineType = "MIPS16 with FPU";
        break;
    case IMAGE_FILE_MACHINE_POWERPC:
        machineType = "Power PC little endian";
        break;
    case IMAGE_FILE_MACHINE_POWERPCFP:
        machineType = "Power PC with floating point support";
        break;
    case IMAGE_FILE_MACHINE_R4000:
        machineType = "MIPS little endian";
        break;
    case 0x5032:
        machineType = "RISC-V 32-bit address space";
        break;
    case 0x5064:
        machineType = "RISC-V 64-bit address space";
        break;
    case 0x5128:
        machineType = "RISC-V 128-bit address space";
        break;
    case IMAGE_FILE_MACHINE_SH3:
        machineType = "Hitachi SH3";
        break;
    case IMAGE_FILE_MACHINE_SH3DSP:
        machineType = "Hitachi SH3 DSP";
        break;
    case IMAGE_FILE_MACHINE_SH4:
        machineType = "Hitachi SH4";
        break;
    case IMAGE_FILE_MACHINE_SH5:
        machineType = "Hitachi SH5";
        break;
    case IMAGE_FILE_MACHINE_THUMB:
        machineType = "Thumb";
        break;
    case IMAGE_FILE_MACHINE_WCEMIPSV2:
        machineType = "MIPS little-endian WCE v2";
        break;
    default:
        machineType = PEPARSER_UNDEFINED_STRING;
        break;
    }
    return machineType;
}

std::string PEParserNTHeaders::getNumberOfSections(WORD numberofsection){
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << static_cast<int>(numberofsection);
    return ss.str();
}

std::string PEParserNTHeaders::getTimeDateStamp(DWORD timedatestamp){
    time_t timestamp = static_cast<time_t>(timedatestamp);
    struct tm* timeinfo = localtime(&timestamp);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return std::string(buffer);
}

std::string PEParserNTHeaders::getPointerToSymbolTable(DWORD pointertosymboltable) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << pointertosymboltable;
    return ss.str();
}

std::string PEParserNTHeaders::getNumberOfSymbols(DWORD numberofsymbols) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << numberofsymbols;
    return ss.str();
}

std::string PEParserNTHeaders::getSizeOfOptionalHeader(WORD sizeofoptionalheader) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << static_cast<int>(sizeofoptionalheader);
    return ss.str();
}

std::string PEParserNTHeaders::getCharacteristics(WORD characteristics){
    std::stringstream ss;
    std::string listDecorator("\t\t * ");
    ss << '\n';
    if (characteristics & IMAGE_FILE_RELOCS_STRIPPED) {
        ss << listDecorator << "Image only, Windows CE, and Microsoft Windows NT and later. This indicates that the file does not contain base relocations and must therefore be loaded at its preferred base address. If the base address is not available, the loader reports an error. The default behavior of the linker is to strip base relocations from executable (EXE) files." << std::endl;
    }
    if (characteristics & IMAGE_FILE_EXECUTABLE_IMAGE) {
        ss << listDecorator << "Image only. This indicates that the image file is valid and can be run. If this flag is not set, it indicates a linker error." << std::endl;
    }
    if (characteristics & IMAGE_FILE_LINE_NUMS_STRIPPED) {
        ss << listDecorator << "COFF line numbers have been removed. This flag is deprecated and should be zero." << std::endl;
    }
    if (characteristics & IMAGE_FILE_LOCAL_SYMS_STRIPPED) {
        ss << listDecorator << "COFF symbol table entries for local symbols have been removed. This flag is deprecated and should be zero." << std::endl;
    }
    if (characteristics & 0x0010) {
        ss << listDecorator << "Obsolete. Aggressively trim working set. This flag is deprecated for Windows 2000 and later and must be zero." << std::endl;
    }
    if (characteristics & IMAGE_FILE_LARGE_ADDRESS_AWARE) {
        ss << listDecorator << "Application can handle > 2-GB addresses." << std::endl;
    }
    if (characteristics & 0x0040) {
        ss << listDecorator << "This flag is reserved for future use." << std::endl;
    }
    if (characteristics & IMAGE_FILE_BYTES_REVERSED_LO) {
        ss << listDecorator << "Little endian: the least significant bit (LSB) precedes the most significant bit (MSB) in memory. This flag is deprecated and should be zero." << std::endl;
    }
    if (characteristics & IMAGE_FILE_32BIT_MACHINE) {
        ss << listDecorator << "Machine is based on a 32-bit-word architecture." << std::endl;
    }
    if (characteristics & IMAGE_FILE_DEBUG_STRIPPED) {
        ss << listDecorator << "Debugging information is removed from the image file." << std::endl;
    }
    if (characteristics & IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP) {
        ss << listDecorator << "If the image is on removable media, fully load it and copy it to the swap file." << std::endl;
    }
    if (characteristics & IMAGE_FILE_NET_RUN_FROM_SWAP) {
        ss << listDecorator << "If the image is on network media, fully load it and copy it to the swap file." << std::endl;
    }
    if (characteristics & IMAGE_FILE_SYSTEM) {
        ss << listDecorator << "The image file is a system file, not a user program." << std::endl;
    }
    if (characteristics & IMAGE_FILE_DLL) {
        ss << listDecorator << "The image file is a dynamic-link library (DLL). Such files are considered executable files for almost all purposes, although they cannot be directly run." << std::endl;
    }
    if (characteristics & IMAGE_FILE_UP_SYSTEM_ONLY) {
        ss << listDecorator << "The file should be run only on a uniprocessor machine." << std::endl;
    }
    if (characteristics & IMAGE_FILE_BYTES_REVERSED_HI) {
        ss << listDecorator << "Big endian: the MSB precedes the LSB in memory. This flag is deprecated and should be zero." << std::endl;
    }

    return ss.str();
}

// Section Header

void PEParserNTHeaders::printSectionHeaders() {
    PEParser::printTitle("Section Headers");
    //std::string decoratorList("\t\t* ");
    for (unsigned int i = 0; i < imageFileHeader->NumberOfSections; i++) {
        mapSectionHeader.insert(std::pair<std::string, std::string>("Section", getSectionHeaderName(i)));
        mapSectionHeader.insert(std::pair<std::string, std::string>("Number Of Linenumbers", std::to_string(getSectionHeaderNumberOfLinenumbers(i))));

        for (std::unordered_map<std::string, std::string>::iterator it = mapSectionHeader.begin(); it != mapSectionHeader.end(); it++) {
            if (it->first == "Section"){
                PEParser::printStandard(it->first, it->second);
            }
            else {
                PEParser::printStandardList(it->first, it->second);
            }
        }
    }
}

void PEParserNTHeaders::parseSectionHeaders() {
    if (sectionHeaders) {
        for (unsigned int i = 0; i < imageFileHeader->NumberOfSections; i++) {
            DWORD offsetToSectionHeader = getOffsetToSectionHeadersFromIndex(i);
            file->seekg(offsetToSectionHeader, std::ios_base::beg);
            file->read(reinterpret_cast<char*>(&sectionHeaders[i]), IMAGE_SIZEOF_SECTION_HEADER);
        }
    }
}

DWORD PEParserNTHeaders::getOffsetToSectionHeadersFromIndex(unsigned int index) {
    return static_cast<DWORD>(imageDosHeader->e_lfanew) + sizeof(IMAGE_NT_HEADERS) + (IMAGE_SIZEOF_SECTION_HEADER * index);
}

std::string PEParserNTHeaders::getSectionHeaderName(int index) {
    return std::string(reinterpret_cast<char*>(&sectionHeaders[index].Name));
}

int PEParserNTHeaders::getSectionHeaderNumberOfLinenumbers(int index) {
    return static_cast<int>(sectionHeaders[index].NumberOfLinenumbers);
}