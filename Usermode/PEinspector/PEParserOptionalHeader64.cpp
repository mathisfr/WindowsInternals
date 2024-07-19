#include "PEParserOptionalHeader64.h"
#include <Windows.h>

PEParserOptionalHeader64::PEParserOptionalHeader64(){
    ZeroMemory(&OptionalHeader, sizeof(OptionalHeader));
}

PEParserOptionalHeader64::PEParserOptionalHeader64(IMAGE_OPTIONAL_HEADER64& imageOptionalHeader64) {
    OptionalHeader = imageOptionalHeader64;
}