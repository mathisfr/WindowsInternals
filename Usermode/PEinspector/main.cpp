//	Header used for PE struct
#include <iostream>
#include <string>
<<<<<<< HEAD
#include "PEParser.h"
=======

/*
*   Oui le code est horrible pour le moment, mais je decouvre :)
*   Je cleanerai plus tard avec des class e.t.c...
*   
*   Si vous voulez tester dans l'etat, compiler le projet suivant l'executable à analyser,
*   si c'est 32 compiler en 32 sinon 64.
*/

#ifdef _WIN64
typedef _IMAGE_NT_HEADERS64	IMAGE_NT_HEADERS;
typedef _IMAGE_OPTIONAL_HEADER64 OPTIONAL_HEADER;
#else
typedef _IMAGE_NT_HEADERS IMAGE_NT_HEADERS;
typedef _IMAGE_OPTIONAL_HEADER OPTIONAL_HEADER;
#endif

/*
*   La vous pouvez mettre le chemin de l'executable que vous voulez analyser
*/
#define FILE_NAME ""

std::string getOptionalHeaderMagicNumber(WORD& magicType) {
    std::string magicString = "Undefined";
    switch (magicType) {
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

std::string getMachineTypes(WORD machineType) {
    std::string machineTypeString = "Undefined";
    switch (machineType) {
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

std::string getSubsystem(WORD subsystemType) {
    std::string subsystemString = "Undefined";
    switch (subsystemType) {
    case IMAGE_SUBSYSTEM_UNKNOWN:
        subsystemString = "Unknown";
        break;
    case IMAGE_SUBSYSTEM_NATIVE:
        subsystemString = "Native";
        break;
    case IMAGE_SUBSYSTEM_WINDOWS_GUI:
        subsystemString = "Windows GUI";
        break;
    case IMAGE_SUBSYSTEM_WINDOWS_CUI:
        subsystemString = "Windows CUI";
        break;
    case IMAGE_SUBSYSTEM_OS2_CUI:
        subsystemString = "OS/2 CUI";
        break;
    case IMAGE_SUBSYSTEM_POSIX_CUI:
        subsystemString = "POSIX CUI";
        break;
    case IMAGE_SUBSYSTEM_NATIVE_WINDOWS:
        subsystemString = "Native Windows";
        break;
    case IMAGE_SUBSYSTEM_WINDOWS_CE_GUI:
        subsystemString = "Windows CE GUI";
        break;
    case IMAGE_SUBSYSTEM_EFI_APPLICATION:
        subsystemString = "EFI Application";
        break;
    case IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER:
        subsystemString = "EFI Boot Service Driver";
        break;
    case IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER:
        subsystemString = "EFI Runtime Driver";
        break;
    case IMAGE_SUBSYSTEM_EFI_ROM:
        subsystemString = "EFI ROM";
        break;
    case IMAGE_SUBSYSTEM_XBOX:
        subsystemString = "Xbox";
        break;
    case IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION:
        subsystemString = "Windows Boot Application";
        break;
    case IMAGE_SUBSYSTEM_XBOX_CODE_CATALOG:
        subsystemString = "Xbox Code Catalog";
        break;
    }
    return subsystemString;
}

int getLenghtOfFile(std::ifstream& file) {
	file.seekg(0, file.end);
	int length = file.tellg();
	file.seekg(0, file.beg);
	return length;
}

int getNewHeaderOffset(_IMAGE_DOS_HEADER& imageDosHeader) {
	return imageDosHeader.e_lfanew;
}

std::string getSignature(IMAGE_NT_HEADERS& ntHeader) {
	return std::string(reinterpret_cast<char*>(&ntHeader.Signature), sizeof(DWORD));
}

std::string getMagicNumber(WORD& magic) {
    return std::string(reinterpret_cast<char*>(&magic), sizeof(WORD));
}

bool hasFileError(std::ifstream &file) {
	if (!file) {
		std::cerr << "Erreur de lecture du fichier\n";
		return true;
	}
	return false;
}
>>>>>>> 76b3f339e293401e11664a92842b8fbfa9533805

int main() {
	PEParser peParser("C:\\Program Files\\Recuva\\recuva64.exe");
	if (peParser.b_error) {
		std::cerr << "Une erreur est survenue pendant l'inspection..." << std::endl;
	}
	return 0;
}
