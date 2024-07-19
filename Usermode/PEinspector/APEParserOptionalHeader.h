#pragma once
#include <string>
class APEParserOptionalHeader
{
public:
	virtual ~APEParserOptionalHeader() = 0;

	static std::string getSubsystem(unsigned short subsystemType);
	static std::string getOptionalHeaderMagic(unsigned short magicType);
};

