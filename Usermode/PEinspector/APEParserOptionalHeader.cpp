#include "APEParserOptionalHeader.h"
#include <Windows.h>

APEParserOptionalHeader::~APEParserOptionalHeader() { }

std::string APEParserOptionalHeader::getOptionalHeaderMagic(unsigned short magicType) {
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

std::string APEParserOptionalHeader::getSubsystem(unsigned short subsystemType) {
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