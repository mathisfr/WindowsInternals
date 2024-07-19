#pragma once
#include "APEParserOptionalHeader.h"
#include <Windows.h>

class PEParserOptionalHeader64 : public APEParserOptionalHeader
{
public :
	IMAGE_OPTIONAL_HEADER64 OptionalHeader;
	PEParserOptionalHeader64();
	PEParserOptionalHeader64(IMAGE_OPTIONAL_HEADER64& imageOptionalHeader64);
};

