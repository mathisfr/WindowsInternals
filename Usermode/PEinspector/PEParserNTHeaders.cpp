#include "PEParserNTHeaders.h"
#include "PEParserDosHeader.h"
#include <iostream>
PEParserNTHeaders::PEParserNTHeaders() {
    ZeroMemory(&imageNtHeader, sizeof(imageNtHeader));
}

PEParserNTHeaders::PEParserNTHeaders(std::ifstream& file, PEParserDosHeader& peParserDosHeader, bool& is64Architecture) {
	file.seekg(peParserDosHeader.getNtHeadersOffset(), std::ios_base::beg);
	file.read(reinterpret_cast<char*>(&imageNtHeader), sizeof(imageNtHeader));
	if (!file) {
		b_error = true;
	}
	is64Architecture = CHECK_ARCHITECTURE(file);
    if (is64Architecture) {
        peParserOptionalHeader64 = PEParserOptionalHeader64(imageNtHeader.OptionalHeader);
    }
    else {

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
    std::string magicString = "Undefined";
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

std::string PEParserNTHeaders::getMachineTypes() {
    std::string machineTypeString = "Undefined";
    switch (imageNtHeader.FileHeader.Machine) {
    case IMAGE_FILE_MACHINE_UNKNOWN:
        machineTypeString = "Unknown";
        break;
    case IMAGE_FILE_MACHINE_TARGET_HOST:
        machineTypeString = "Target Host";
        break;
    case IMAGE_FILE_MACHINE_I386:
        machineTypeString = "Intel 386";
        break;
    case IMAGE_FILE_MACHINE_R3000:
        machineTypeString = "MIPS little-endian (R3000)";
        break;
    case IMAGE_FILE_MACHINE_R4000:
        machineTypeString = "MIPS little-endian (R4000)";
        break;
    case IMAGE_FILE_MACHINE_R10000:
        machineTypeString = "MIPS little-endian (R10000)";
        break;
    case IMAGE_FILE_MACHINE_WCEMIPSV2:
        machineTypeString = "MIPS little-endian WCE v2";
        break;
    case IMAGE_FILE_MACHINE_ALPHA:
        machineTypeString = "Alpha AXP";
        break;
    case IMAGE_FILE_MACHINE_SH3:
        machineTypeString = "SH3 little-endian";
        break;
    case IMAGE_FILE_MACHINE_SH3DSP:
        machineTypeString = "SH3DSP";
        break;
    case IMAGE_FILE_MACHINE_SH3E:
        machineTypeString = "SH3E little-endian";
        break;
    case IMAGE_FILE_MACHINE_SH4:
        machineTypeString = "SH4 little-endian";
        break;
    case IMAGE_FILE_MACHINE_SH5:
        machineTypeString = "SH5";
        break;
    case IMAGE_FILE_MACHINE_ARM:
        machineTypeString = "ARM Little-Endian";
        break;
    case IMAGE_FILE_MACHINE_THUMB:
        machineTypeString = "ARM Thumb/Thumb-2 Little-Endian";
        break;
    case IMAGE_FILE_MACHINE_ARMNT:
        machineTypeString = "ARM Thumb-2 Little-Endian";
        break;
    case IMAGE_FILE_MACHINE_AM33:
        machineTypeString = "AM33";
        break;
    case IMAGE_FILE_MACHINE_POWERPC:
        machineTypeString = "IBM PowerPC Little-Endian";
        break;
    case IMAGE_FILE_MACHINE_POWERPCFP:
        machineTypeString = "PowerPC with floating point support";
        break;
    case IMAGE_FILE_MACHINE_IA64:
        machineTypeString = "Intel 64";
        break;
    case IMAGE_FILE_MACHINE_MIPS16:
        machineTypeString = "MIPS16";
        break;
    case IMAGE_FILE_MACHINE_ALPHA64:
        machineTypeString = "Alpha64";
        break;
    case IMAGE_FILE_MACHINE_MIPSFPU:
        machineTypeString = "MIPS with FPU";
        break;
    case IMAGE_FILE_MACHINE_MIPSFPU16:
        machineTypeString = "MIPS16 with FPU";
        break;
    case IMAGE_FILE_MACHINE_TRICORE:
        machineTypeString = "Infineon";
        break;
    case IMAGE_FILE_MACHINE_CEF:
        machineTypeString = "CEF";
        break;
    case IMAGE_FILE_MACHINE_EBC:
        machineTypeString = "EFI Byte Code";
        break;
    case IMAGE_FILE_MACHINE_AMD64:
        machineTypeString = "AMD64 (K8)";
        break;
    case IMAGE_FILE_MACHINE_M32R:
        machineTypeString = "M32R little-endian";
        break;
    case IMAGE_FILE_MACHINE_ARM64:
        machineTypeString = "ARM64 Little-Endian";
        break;
    case IMAGE_FILE_MACHINE_CEE:
        machineTypeString = "CEE";
        break;
    default:
        machineTypeString = "Unknown machine type";
        break;
    }
    return machineTypeString;
}