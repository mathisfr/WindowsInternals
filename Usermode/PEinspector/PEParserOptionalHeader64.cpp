#include "PEParserOptionalHeader64.h"
#include <Windows.h>
#include <sstream>
#include <fstream>
#include <iostream>

PEParserOptionalHeader64::PEParserOptionalHeader64(){
    ZeroMemory(&imageOptionalHeader, sizeof(imageOptionalHeader)); 
}

PEParserOptionalHeader64::PEParserOptionalHeader64(std::ifstream& file, IMAGE_DOS_HEADER& imageDosHeader, IMAGE_FILE_HEADER& imageFileHeader, IMAGE_OPTIONAL_HEADER64& imageOptionalHeader64) {
    imageOptionalHeader = imageOptionalHeader64;
    this->imageDosHeader = &imageDosHeader;
    this->imageFileHeader = &imageFileHeader;
    this->file = &file;
    str_architecture = PEParserOptionalHeader64::getOptionalHeaderMagic(imageOptionalHeader.Magic);
    str_majorLinkerVersion = PEParserOptionalHeader64::getMajorLinkerVersion(imageOptionalHeader.MajorLinkerVersion);
    str_minorLinkerVersion = PEParserOptionalHeader64::getMinorLinkerVersion(imageOptionalHeader.MinorLinkerVersion);
    str_sizeOfCode = PEParserOptionalHeader64::getSizeOfCode(imageOptionalHeader.SizeOfCode);
    str_sizeOfInitializedData = PEParserOptionalHeader64::getSizeOfInitializedData(imageOptionalHeader.SizeOfInitializedData);
    str_sizeOfUninitializedData = PEParserOptionalHeader64::getSizeOfUninitializedData(imageOptionalHeader.SizeOfUninitializedData);
    str_addressOfEntryPoint = PEParserOptionalHeader64::getAddressOfEntryPoint(imageOptionalHeader.AddressOfEntryPoint);
    str_baseOfCode = PEParserOptionalHeader64::getBaseOfCode(imageOptionalHeader.BaseOfCode);
    str_imageBase = PEParserOptionalHeader64::getImageBase(imageOptionalHeader.ImageBase);
    str_sectionAlignment = PEParserOptionalHeader64::getSectionAlignment(imageOptionalHeader.SectionAlignment);
    str_fileAlignment = PEParserOptionalHeader64::getFileAlignment(imageOptionalHeader.FileAlignment);
    str_majorOperatingSystemVersion = PEParserOptionalHeader64::getMajorOperatingSystemVersion(imageOptionalHeader.MajorOperatingSystemVersion);
    str_minorOperatingSystemVersion = PEParserOptionalHeader64::getMinorOperatingSystemVersion(imageOptionalHeader.MinorOperatingSystemVersion);
    str_majorImageVersion = PEParserOptionalHeader64::getMajorImageVersion(imageOptionalHeader.MajorImageVersion);
    str_minorImageVersion = PEParserOptionalHeader64::getMinorImageVersion(imageOptionalHeader.MinorImageVersion);
    str_majorSubsystemVersion = PEParserOptionalHeader64::getMajorSubsystemVersion(imageOptionalHeader.MajorSubsystemVersion);
    str_minorSubsystemVersion = PEParserOptionalHeader64::getMinorSubsystemVersion(imageOptionalHeader.MinorSubsystemVersion);
    str_win32VersionValue = PEParserOptionalHeader64::getWin32VersionValue(imageOptionalHeader.Win32VersionValue);
    str_sizeOfImage = PEParserOptionalHeader64::getSizeOfImage(imageOptionalHeader.SizeOfImage);
    str_sizeOfHeaders = PEParserOptionalHeader64::getSizeOfHeaders(imageOptionalHeader.SizeOfHeaders);
    str_checkSum = PEParserOptionalHeader64::getCheckSum(imageOptionalHeader.CheckSum);
    str_subsystem = PEParserOptionalHeader64::getSubsystem(imageOptionalHeader.Subsystem);
    str_dllCharacteristics = PEParserOptionalHeader64::getDllCharacteristics(imageOptionalHeader.DllCharacteristics);
    str_sizeOfStackReserve = PEParserOptionalHeader64::getSizeOfStackReserve(imageOptionalHeader.SizeOfStackReserve);
    str_sizeOfStackCommit = PEParserOptionalHeader64::getSizeOfStackCommit(imageOptionalHeader.SizeOfStackCommit);
    str_sizeOfHeapReserve = PEParserOptionalHeader64::getSizeOfHeapReserve(imageOptionalHeader.SizeOfHeapReserve);
    str_sizeOfHeapCommit = PEParserOptionalHeader64::getSizeOfHeapCommit(imageOptionalHeader.SizeOfHeapCommit);
    str_loaderFlags = PEParserOptionalHeader64::getLoaderFlags(imageOptionalHeader.LoaderFlags);
    str_numberOfRvaAndSizes = PEParserOptionalHeader64::getNumberOfRvaAndSizes(imageOptionalHeader.NumberOfRvaAndSizes);

    mapOptionalHeader.insert(std::pair<std::string, std::string>("Architecture", str_architecture));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Major Linker Version", str_majorLinkerVersion));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Minor Linker Version", str_minorLinkerVersion));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Size Of Code", str_sizeOfCode));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Size Of Initialized Data", str_sizeOfInitializedData));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Size Of Uninitialized Data", str_sizeOfUninitializedData));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Address Of Entry Point", str_addressOfEntryPoint));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Base Of Code", str_baseOfCode));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Image Base", str_imageBase));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Section Alignment", str_sectionAlignment));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("File Alignment", str_fileAlignment));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Major Operating System Version", str_majorOperatingSystemVersion));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Minor Operating System Version", str_minorOperatingSystemVersion));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Major Image Version", str_majorImageVersion));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Minor Image Version", str_minorImageVersion));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Major Subsystem Version", str_majorSubsystemVersion));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Minor Subsystem Version", str_minorSubsystemVersion));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Win32 Version Value", str_win32VersionValue));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Size Of Image", str_sizeOfImage));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Size Of Headers", str_sizeOfHeaders));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Check Sum", str_checkSum));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Subsystem", str_subsystem));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("DLL Characteristics", str_dllCharacteristics));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Size Of Stack Reserve", str_sizeOfStackReserve));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Size Of Stack Commit", str_sizeOfStackCommit));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Size Of Heap Reserve", str_sizeOfHeapReserve));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Size Of Heap Commit", str_sizeOfHeapCommit));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Loader Flags", str_loaderFlags));
    mapOptionalHeader.insert(std::pair<std::string, std::string>("Number Of RVA And Sizes", str_numberOfRvaAndSizes));

    sectionHeaders = new IMAGE_SECTION_HEADER[imageFileHeader.NumberOfSections];
    parseSectionHeaders();
}

DWORD PEParserOptionalHeader64::getOffsetToSectionHeadersFromIndex(unsigned int index) {
    return static_cast<DWORD>(imageDosHeader->e_lfanew) + sizeof(IMAGE_NT_HEADERS) + (IMAGE_SIZEOF_SECTION_HEADER * index);
}

void PEParserOptionalHeader64::parseSectionHeaders() {
    for (unsigned int i = 0; i < imageFileHeader->NumberOfSections; i++) {
        DWORD offsetToSectionHeader = getOffsetToSectionHeadersFromIndex(i);
        file->seekg(offsetToSectionHeader, std::ios_base::beg);
        file->read(reinterpret_cast<char*>(&sectionHeaders[i]), IMAGE_SIZEOF_SECTION_HEADER);
    }
}

void PEParserOptionalHeader64::printSectionHeaders() {
    std::cout << "Section Headers : " << std::endl;
    std::string decoratorList("\t\t* ");
    for (unsigned int i = 0; i < imageFileHeader->NumberOfSections; i++) {
        std::cout << "\t- " << sectionHeaders[i].Name << std::endl;
    }
}

std::string PEParserOptionalHeader64::getOptionalHeaderMagic(WORD magicType) {
    std::string magicString = PEPARSER_UNDEFINED_STRING;
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

std::string PEParserOptionalHeader64::getSubsystem(WORD subsystemType) {
    std::string subsystemString = PEPARSER_UNDEFINED_STRING;
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

std::string PEParserOptionalHeader64::getMajorLinkerVersion(BYTE MajorLinkerVersion) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << static_cast<int>(MajorLinkerVersion);
    return ss.str();
}
std::string PEParserOptionalHeader64::getMinorLinkerVersion(BYTE MinorLinkerVersion) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << static_cast<int>(MinorLinkerVersion);
    return ss.str();
}
std::string PEParserOptionalHeader64::getSizeOfCode(DWORD SizeOfCode) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << SizeOfCode;
    return ss.str();
}
std::string PEParserOptionalHeader64::getSizeOfInitializedData(DWORD SizeOfInitializedData) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << SizeOfInitializedData;
    return ss.str();
}
std::string PEParserOptionalHeader64::getSizeOfUninitializedData(DWORD SizeOfUninitializedData) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << SizeOfUninitializedData;
    return ss.str();
}
std::string PEParserOptionalHeader64::getAddressOfEntryPoint(DWORD AddressOfEntryPoint) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << AddressOfEntryPoint;
    return ss.str();
}
std::string PEParserOptionalHeader64::getBaseOfCode(DWORD BaseOfCode) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << BaseOfCode;
    return ss.str();
}
std::string PEParserOptionalHeader64::getImageBase(ULONGLONG ImageBase) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << ImageBase;
    return ss.str();
}
std::string PEParserOptionalHeader64::getSectionAlignment(DWORD SectionAlignment) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << SectionAlignment;
    return ss.str();
}
std::string PEParserOptionalHeader64::getFileAlignment(DWORD FileAlignment) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << FileAlignment;
    return ss.str();
}
std::string PEParserOptionalHeader64::getMajorOperatingSystemVersion(WORD MajorOperatingSystemVersion) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << static_cast<int>(MajorOperatingSystemVersion);
    return ss.str();
}
std::string PEParserOptionalHeader64::getMinorOperatingSystemVersion(WORD MinorOperatingSystemVersion) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << static_cast<int>(MinorOperatingSystemVersion);
    return ss.str();
}
std::string PEParserOptionalHeader64::getMajorImageVersion(WORD MajorImageVersion) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << static_cast<int>(MajorImageVersion);
    return ss.str();
}
std::string PEParserOptionalHeader64::getMinorImageVersion(WORD MinorImageVersion) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << static_cast<int>(MinorImageVersion);
    return ss.str();
}
std::string PEParserOptionalHeader64::getMajorSubsystemVersion(WORD MajorSubsystemVersion) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << static_cast<int>(MajorSubsystemVersion);
    return ss.str();
}
std::string PEParserOptionalHeader64::getMinorSubsystemVersion(WORD MinorSubsystemVersion) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << static_cast<int>(MinorSubsystemVersion);
    return ss.str();
}
std::string PEParserOptionalHeader64::getWin32VersionValue(DWORD Win32VersionValue) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << Win32VersionValue;
    return ss.str();
}
std::string PEParserOptionalHeader64::getSizeOfImage(DWORD SizeOfImage) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << SizeOfImage;
    return ss.str();
}
std::string PEParserOptionalHeader64::getSizeOfHeaders(DWORD SizeOfHeaders) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << SizeOfHeaders;
    return ss.str();
}
std::string PEParserOptionalHeader64::getCheckSum(DWORD CheckSum) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << CheckSum;
    return ss.str();
}
std::string PEParserOptionalHeader64::getDllCharacteristics(WORD DllCharacteristics) {
    std::stringstream ss;
    std::string listDecorator("\t\t * ");
    ss << '\n';
    if (DllCharacteristics & 0x0020) {
        ss << listDecorator << "Image can handle a high entropy 64 - bit virtual address space." << std::endl;
    }
    if (DllCharacteristics & 0x0040) {
        ss << listDecorator << "DLL can be relocated at load time." << std::endl;
    }
    if (DllCharacteristics & 0x0080) {
        ss << listDecorator << "Code Integrity checks are enforced." << std::endl;
    }
    if (DllCharacteristics & 0x0100) {
        ss << listDecorator << "Image is NX compatible." << std::endl;
    }
    if (DllCharacteristics & 0x0200) {
        ss << listDecorator << "Isolation aware, but do not isolate the image." << std::endl;
    }
    if (DllCharacteristics & 0x0400) {
        ss << listDecorator << "Does not use structured exception (SE) handling. No SE handler may be called in this image." << std::endl;
    }
    if (DllCharacteristics & 0x0800) {
        ss << listDecorator << "Do not bind the image." << std::endl;
    }
    if (DllCharacteristics & 0x1000) {
        ss << listDecorator << "Image must execute in an AppContainer." << std::endl;
    }
    if (DllCharacteristics & 0x2000) {
        ss << listDecorator << "A WDM driver." << std::endl;
    }
    if (DllCharacteristics & 0x4000) {
        ss << listDecorator << "Image supports Control Flow Guard." << std::endl;
    }
    if (DllCharacteristics & 0x8000) {
        ss << listDecorator << "Terminal Server aware." << std::endl;
    }
    return ss.str();
}
std::string PEParserOptionalHeader64::getSizeOfStackReserve(ULONGLONG SizeOfStackReserve) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << SizeOfStackReserve;
    return ss.str();
}
std::string PEParserOptionalHeader64::getSizeOfStackCommit(ULONGLONG SizeOfStackCommit) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << SizeOfStackCommit;
    return ss.str();
}
std::string PEParserOptionalHeader64::getSizeOfHeapReserve(ULONGLONG SizeOfHeapReserve) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << SizeOfHeapReserve;
    return ss.str();
}
std::string PEParserOptionalHeader64::getSizeOfHeapCommit(ULONGLONG SizeOfHeapCommit) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << SizeOfHeapCommit;
    return ss.str();
}
std::string PEParserOptionalHeader64::getLoaderFlags(DWORD LoaderFlags) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << LoaderFlags;
    return ss.str();
}
std::string PEParserOptionalHeader64::getNumberOfRvaAndSizes(DWORD NumberOfRvaAndSizes) {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << NumberOfRvaAndSizes;
    return ss.str();
}