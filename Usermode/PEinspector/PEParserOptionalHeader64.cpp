#include "PEParserOptionalHeader64.h"
#include <Windows.h>
#include <sstream>
#include <fstream>
#include <iostream>

PEParserOptionalHeader64::PEParserOptionalHeader64(){
    imageFileHeader = nullptr;
    ZeroMemory(&imageOptionalHeader, sizeof(imageOptionalHeader)); 
}

PEParserOptionalHeader64::PEParserOptionalHeader64(IMAGE_FILE_HEADER& imageFileHeader, IMAGE_OPTIONAL_HEADER64& imageOptionalHeader64) {
    imageOptionalHeader = imageOptionalHeader64;
    this->imageFileHeader = &imageFileHeader;
    str_architecture = PEParserOptionalHeader64::getOptionalHeaderMagic();
    str_majorLinkerVersion = PEParserOptionalHeader64::getMajorLinkerVersion();
    str_minorLinkerVersion = PEParserOptionalHeader64::getMinorLinkerVersion();
    str_sizeOfCode = PEParserOptionalHeader64::getSizeOfCode();
    str_sizeOfInitializedData = PEParserOptionalHeader64::getSizeOfInitializedData();
    str_sizeOfUninitializedData = PEParserOptionalHeader64::getSizeOfUninitializedData();
    str_addressOfEntryPoint = PEParserOptionalHeader64::getAddressOfEntryPoint();
    str_baseOfCode = PEParserOptionalHeader64::getBaseOfCode();
    str_imageBase = PEParserOptionalHeader64::getImageBase();
    str_sectionAlignment = PEParserOptionalHeader64::getSectionAlignment();
    str_fileAlignment = PEParserOptionalHeader64::getFileAlignment();
    str_majorOperatingSystemVersion = PEParserOptionalHeader64::getMajorOperatingSystemVersion();
    str_minorOperatingSystemVersion = PEParserOptionalHeader64::getMinorOperatingSystemVersion();
    str_majorImageVersion = PEParserOptionalHeader64::getMajorImageVersion();
    str_minorImageVersion = PEParserOptionalHeader64::getMinorImageVersion();
    str_majorSubsystemVersion = PEParserOptionalHeader64::getMajorSubsystemVersion();
    str_minorSubsystemVersion = PEParserOptionalHeader64::getMinorSubsystemVersion();
    str_win32VersionValue = PEParserOptionalHeader64::getWin32VersionValue();
    str_sizeOfImage = PEParserOptionalHeader64::getSizeOfImage();
    str_sizeOfHeaders = PEParserOptionalHeader64::getSizeOfHeaders();
    str_checkSum = PEParserOptionalHeader64::getCheckSum();
    str_subsystem = PEParserOptionalHeader64::getSubsystem();
    str_dllCharacteristics = PEParserOptionalHeader64::getDllCharacteristics();
    str_sizeOfStackReserve = PEParserOptionalHeader64::getSizeOfStackReserve();
    str_sizeOfStackCommit = PEParserOptionalHeader64::getSizeOfStackCommit();
    str_sizeOfHeapReserve = PEParserOptionalHeader64::getSizeOfHeapReserve();
    str_sizeOfHeapCommit = PEParserOptionalHeader64::getSizeOfHeapCommit();
    str_loaderFlags = PEParserOptionalHeader64::getLoaderFlags();
    str_numberOfRvaAndSizes = PEParserOptionalHeader64::getNumberOfRvaAndSizes();

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

}

std::string PEParserOptionalHeader64::getOptionalHeaderMagic() {
    std::string magicString = PEPARSER_UNDEFINED_STRING;
    switch (imageOptionalHeader.Magic) {
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

std::string PEParserOptionalHeader64::getSubsystem() {
    std::string subsystemString = PEPARSER_UNDEFINED_STRING;
    switch (imageOptionalHeader.Subsystem) {
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

std::string PEParserOptionalHeader64::getMajorLinkerVersion() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << static_cast<int>(imageOptionalHeader.MajorLinkerVersion);
    return ss.str();
}
std::string PEParserOptionalHeader64::getMinorLinkerVersion() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << static_cast<int>(imageOptionalHeader.MinorLinkerVersion);
    return ss.str();
}
std::string PEParserOptionalHeader64::getSizeOfCode() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << imageOptionalHeader.SizeOfCode;
    return ss.str();
}
std::string PEParserOptionalHeader64::getSizeOfInitializedData() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << imageOptionalHeader.SizeOfInitializedData;
    return ss.str();
}
std::string PEParserOptionalHeader64::getSizeOfUninitializedData() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << imageOptionalHeader.SizeOfUninitializedData;
    return ss.str();
}
std::string PEParserOptionalHeader64::getAddressOfEntryPoint() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << imageOptionalHeader.AddressOfEntryPoint;
    return ss.str();
}
std::string PEParserOptionalHeader64::getBaseOfCode() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << imageOptionalHeader.BaseOfCode;
    return ss.str();
}
std::string PEParserOptionalHeader64::getImageBase() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << imageOptionalHeader.ImageBase;
    return ss.str();
}
std::string PEParserOptionalHeader64::getSectionAlignment() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << imageOptionalHeader.SectionAlignment;
    return ss.str();
}
std::string PEParserOptionalHeader64::getFileAlignment() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << imageOptionalHeader.FileAlignment;
    return ss.str();
}
std::string PEParserOptionalHeader64::getMajorOperatingSystemVersion() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << static_cast<int>(imageOptionalHeader.MajorOperatingSystemVersion);
    return ss.str();
}
std::string PEParserOptionalHeader64::getMinorOperatingSystemVersion() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << static_cast<int>(imageOptionalHeader.MinorOperatingSystemVersion);
    return ss.str();
}
std::string PEParserOptionalHeader64::getMajorImageVersion() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << static_cast<int>(imageOptionalHeader.MajorImageVersion);
    return ss.str();
}
std::string PEParserOptionalHeader64::getMinorImageVersion() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << static_cast<int>(imageOptionalHeader.MinorImageVersion);
    return ss.str();
}
std::string PEParserOptionalHeader64::getMajorSubsystemVersion() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << static_cast<int>(imageOptionalHeader.MajorSubsystemVersion);
    return ss.str();
}
std::string PEParserOptionalHeader64::getMinorSubsystemVersion() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << static_cast<int>(imageOptionalHeader.MinorSubsystemVersion);
    return ss.str();
}
std::string PEParserOptionalHeader64::getWin32VersionValue() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << imageOptionalHeader.Win32VersionValue;
    return ss.str();
}
std::string PEParserOptionalHeader64::getSizeOfImage() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << imageOptionalHeader.SizeOfImage;
    return ss.str();
}
std::string PEParserOptionalHeader64::getSizeOfHeaders() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << imageOptionalHeader.SizeOfHeaders;
    return ss.str();
}
std::string PEParserOptionalHeader64::getCheckSum() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << imageOptionalHeader.CheckSum;
    return ss.str();
}
std::string PEParserOptionalHeader64::getDllCharacteristics() {
    std::stringstream ss;
    std::string listDecorator("\t\t* ");
    ss << '\n';
    if (imageOptionalHeader.DllCharacteristics & 0x0020) {
        ss << listDecorator << "Image can handle a high entropy 64 - bit virtual address space." << std::endl;
    }
    if (imageOptionalHeader.DllCharacteristics & 0x0040) {
        ss << listDecorator << "DLL can be relocated at load time." << std::endl;
    }
    if (imageOptionalHeader.DllCharacteristics & 0x0080) {
        ss << listDecorator << "Code Integrity checks are enforced." << std::endl;
    }
    if (imageOptionalHeader.DllCharacteristics & 0x0100) {
        ss << listDecorator << "Image is NX compatible." << std::endl;
    }
    if (imageOptionalHeader.DllCharacteristics & 0x0200) {
        ss << listDecorator << "Isolation aware, but do not isolate the image." << std::endl;
    }
    if (imageOptionalHeader.DllCharacteristics & 0x0400) {
        ss << listDecorator << "Does not use structured exception (SE) handling. No SE handler may be called in this image." << std::endl;
    }
    if (imageOptionalHeader.DllCharacteristics & 0x0800) {
        ss << listDecorator << "Do not bind the image." << std::endl;
    }
    if (imageOptionalHeader.DllCharacteristics & 0x1000) {
        ss << listDecorator << "Image must execute in an AppContainer." << std::endl;
    }
    if (imageOptionalHeader.DllCharacteristics & 0x2000) {
        ss << listDecorator << "A WDM driver." << std::endl;
    }
    if (imageOptionalHeader.DllCharacteristics & 0x4000) {
        ss << listDecorator << "Image supports Control Flow Guard." << std::endl;
    }
    if (imageOptionalHeader.DllCharacteristics & 0x8000) {
        ss << listDecorator << "Terminal Server aware." << std::endl;
    }
    return ss.str();
}
std::string PEParserOptionalHeader64::getSizeOfStackReserve() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << imageOptionalHeader.SizeOfStackReserve;
    return ss.str();
}
std::string PEParserOptionalHeader64::getSizeOfStackCommit() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << imageOptionalHeader.SizeOfStackCommit;
    return ss.str();
}
std::string PEParserOptionalHeader64::getSizeOfHeapReserve() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << imageOptionalHeader.SizeOfHeapReserve;
    return ss.str();
}
std::string PEParserOptionalHeader64::getSizeOfHeapCommit() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << imageOptionalHeader.SizeOfHeapCommit;
    return ss.str();
}
std::string PEParserOptionalHeader64::getLoaderFlags() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << imageOptionalHeader.LoaderFlags;
    return ss.str();
}
std::string PEParserOptionalHeader64::getNumberOfRvaAndSizes() {
    std::stringstream ss;
    ss << "0x" << PEPARSER_IOMANIP_HEX << imageOptionalHeader.NumberOfRvaAndSizes;
    return ss.str();
}