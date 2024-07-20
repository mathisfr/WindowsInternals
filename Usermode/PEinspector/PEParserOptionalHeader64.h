#pragma once
#include <Windows.h>
#include <iomanip>
#include <map>
#include <vector>

#define PEPARSER_UNDEFINED_STRING "Undefined"
#define PEPARSER_IOMANIP_HEX std::hex << std::setw(1) << std::setfill('0')

class PEParserOptionalHeader64
{
private:
    IMAGE_FILE_HEADER* imageFileHeader = nullptr;

public :
	IMAGE_OPTIONAL_HEADER64 imageOptionalHeader;
	PEParserOptionalHeader64();
    PEParserOptionalHeader64(IMAGE_FILE_HEADER& imageFileHeader, IMAGE_OPTIONAL_HEADER64& imageOptionalHeader64);

    std::map <std::string, std::string> mapOptionalHeader;

    std::string str_architecture;
    std::string str_majorLinkerVersion;
    std::string str_minorLinkerVersion;
    std::string str_sizeOfCode;
    std::string str_sizeOfInitializedData;
    std::string str_sizeOfUninitializedData;
    std::string str_addressOfEntryPoint;
    std::string str_baseOfCode;
    std::string str_imageBase;
    std::string str_sectionAlignment;
    std::string str_fileAlignment;
    std::string str_majorOperatingSystemVersion;
    std::string str_minorOperatingSystemVersion;
    std::string str_majorImageVersion;
    std::string str_minorImageVersion;
    std::string str_majorSubsystemVersion;
    std::string str_minorSubsystemVersion;
    std::string str_win32VersionValue;
    std::string str_sizeOfImage;
    std::string str_sizeOfHeaders;
    std::string str_checkSum;
    std::string str_subsystem;
    std::string str_dllCharacteristics;
    std::string str_sizeOfStackReserve;
    std::string str_sizeOfStackCommit;
    std::string str_sizeOfHeapReserve;
    std::string str_sizeOfHeapCommit;
    std::string str_loaderFlags;
    std::string str_numberOfRvaAndSizes;

    std::string getOptionalHeaderMagic();
    std::string getMajorLinkerVersion();
    std::string getMinorLinkerVersion();
    std::string getSizeOfCode();
    std::string getSizeOfInitializedData();
    std::string getSizeOfUninitializedData();
    std::string getAddressOfEntryPoint();
    std::string getBaseOfCode();
    std::string getImageBase();
    std::string getSectionAlignment();
    std::string getFileAlignment();
    std::string getMajorOperatingSystemVersion();
    std::string getMinorOperatingSystemVersion();
    std::string getMajorImageVersion();
    std::string getMinorImageVersion();
    std::string getMajorSubsystemVersion();
    std::string getMinorSubsystemVersion();
    std::string getWin32VersionValue();
    std::string getSizeOfImage();
    std::string getSizeOfHeaders();
    std::string getCheckSum();
    std::string getSubsystem();
    std::string getDllCharacteristics();
    std::string getSizeOfStackReserve();
    std::string getSizeOfStackCommit();
    std::string getSizeOfHeapReserve();
    std::string getSizeOfHeapCommit();
    std::string getLoaderFlags();
    std::string getNumberOfRvaAndSizes();
};