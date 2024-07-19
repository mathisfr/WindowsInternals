#pragma once
#include <Windows.h>
#include <iomanip>
#include <map>

#define PEPARSER_UNDEFINED_STRING "Undefined"
#define PEPARSER_IOMANIP_HEX std::hex << std::setw(1) << std::setfill('0')

class PEParserOptionalHeader64
{
public :
	IMAGE_OPTIONAL_HEADER64 OptionalHeader;
	PEParserOptionalHeader64();
	PEParserOptionalHeader64(IMAGE_OPTIONAL_HEADER64& imageOptionalHeader64);

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

    static std::string getOptionalHeaderMagic(WORD MagicType);
    static std::string getMajorLinkerVersion(BYTE MajorLinkerVersion);
    static std::string getMinorLinkerVersion(BYTE MinorLinkerVersion);
    static std::string getSizeOfCode(DWORD SizeOfCode);
    static std::string getSizeOfInitializedData(DWORD SizeOfInitializedData);
    static std::string getSizeOfUninitializedData(DWORD SizeOfUninitializedData);
    static std::string getAddressOfEntryPoint(DWORD AddressOfEntryPoint);
    static std::string getBaseOfCode(DWORD BaseOfCode);
    static std::string getImageBase(ULONGLONG ImageBase);
    static std::string getSectionAlignment(DWORD SectionAlignment);
    static std::string getFileAlignment(DWORD FileAlignment);
    static std::string getMajorOperatingSystemVersion(WORD MajorOperatingSystemVersion);
    static std::string getMinorOperatingSystemVersion(WORD MinorOperatingSystemVersion);
    static std::string getMajorImageVersion(WORD MajorImageVersion);
    static std::string getMinorImageVersion(WORD MinorImageVersion);
    static std::string getMajorSubsystemVersion(WORD MajorSubsystemVersion);
    static std::string getMinorSubsystemVersion(WORD MinorSubsystemVersion);
    static std::string getWin32VersionValue(DWORD Win32VersionValue);
    static std::string getSizeOfImage(DWORD SizeOfImage);
    static std::string getSizeOfHeaders(DWORD SizeOfHeaders);
    static std::string getCheckSum(DWORD CheckSum);
    static std::string getSubsystem(WORD SubsystemType);
    static std::string getDllCharacteristics(WORD DllCharacteristics);
    static std::string getSizeOfStackReserve(ULONGLONG SizeOfStackReserve);
    static std::string getSizeOfStackCommit(ULONGLONG SizeOfStackCommit);
    static std::string getSizeOfHeapReserve(ULONGLONG SizeOfHeapReserve);
    static std::string getSizeOfHeapCommit(ULONGLONG SizeOfHeapCommit);
    static std::string getLoaderFlags(DWORD LoaderFlags);
    static std::string getNumberOfRvaAndSizes(DWORD NumberOfRvaAndSizes);
};