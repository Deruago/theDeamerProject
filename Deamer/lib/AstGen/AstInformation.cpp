#include "Deamer/AstGen/AstInformation.h"

AstInformation::AstInformation(unsigned int lineNumber, unsigned int charNumber, std::string valueName)
{
    AstInformation::LineNumber = lineNumber;
    AstInformation::CharNumber = charNumber;
    AstInformation::ValueName = valueName;
}