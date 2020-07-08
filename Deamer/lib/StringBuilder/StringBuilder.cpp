/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/StringBuilder/StringBuilder.h"

void deamer::StringBuilder::Add(std::string newLine)
{
	Output.push_back(newLine);
}

void deamer::StringBuilder::AddUpper(std::string newLine)
{
	Output.push_back(makeLineUpperCase(newLine));
}

std::string deamer::StringBuilder::makeLineLowerCase(const std::string line)
{
	std::string newLine;
	for (char c : line)
	{
		newLine += ::tolower(c);
	}
	return newLine;
}

std::string deamer::StringBuilder::makeLineUpperCase(const std::string line)
{
	std::string newLine;
	for (char c : line)
	{
		newLine += ::toupper(c);
	}
	return newLine;
}

void deamer::StringBuilder::AddLower(std::string newLine)
{
	Output.push_back(makeLineLowerCase(newLine));
}

bool deamer::StringBuilder::doesOutputContainAmountLines(unsigned int position) const
{
	return Output.size() <= position;
}

std::string deamer::StringBuilder::GetLine(unsigned position)
{
	if(doesOutputContainAmountLines(position))
	{
		return Output[position];
	}
	return "";
}

void deamer::StringBuilder::SetLine(unsigned position, std::string newLine)
{
	if(doesOutputContainAmountLines(position))
	{
		Output[position] = newLine;
	}
}

void deamer::StringBuilder::CompressLinesIgnoreNewLines(unsigned int beginPosition, unsigned int endPosition)
{
	std::string newLine;
	for(int i = beginPosition; i <= endPosition; i++)
	{
		newLine += Output[i];
	}
	Output[beginPosition] = newLine;
}

void deamer::StringBuilder::AddLinesFromStringBuilderToOwnOutput(const StringBuilder string_builder)
{
	for(std::string line : string_builder.Output)
	{
		Add(line);
	}
}

void deamer::StringBuilder::CompressLines(unsigned int beginPosition, unsigned int endPosition)
{
	std::string newLine;
	for (int i = beginPosition; i <= endPosition; i++)
	{
		newLine += Output[i] + '\n';
	}
	Output[beginPosition] = newLine;
}

void deamer::StringBuilder::Compress(bool ignoreNewLine)
{
	Compress(0, Output.size(), ignoreNewLine);
}

void deamer::StringBuilder::CapPositionToOutputLineSize(unsigned* position) const
{
	if (*position > Output.size())
		*position = Output.size();
}

void deamer::StringBuilder::CapPositionToOutputLineSize(unsigned* begin_postion, unsigned* end_position) const
{
	CapPositionToOutputLineSize(begin_postion);
	CapPositionToOutputLineSize(end_position);
}

void deamer::StringBuilder::RemoveExtraLines(unsigned begin_postion, unsigned end_position)
{
	Output.erase(Output.begin() + begin_postion + 1, Output.begin() + end_position);
}

void deamer::StringBuilder::Compress(unsigned beginPostion, unsigned endPosition, bool ignoreNewLine)
{
	CapPositionToOutputLineSize(&beginPostion, &endPosition);
	if (ignoreNewLine)
		CompressLinesIgnoreNewLines(beginPostion, endPosition);
	else
		CompressLines(beginPostion, endPosition);
	RemoveExtraLines(beginPostion, endPosition);
}

void deamer::StringBuilder::CompressFrom(unsigned beginPostion, bool ignoreNewLine)
{
	Compress(beginPostion, Output.size(), ignoreNewLine);
}

void deamer::StringBuilder::CompressTill(unsigned endPostion, bool ignoreNewLine)
{
	Compress(0, endPostion, ignoreNewLine);
}

void deamer::StringBuilder::CombineStringBuilders(std::vector<StringBuilder> stringBuilders)
{
	for(StringBuilder stringBuilder : stringBuilders)
	{
		AddLinesFromStringBuilderToOwnOutput(stringBuilder);
	}
}

std::string deamer::StringBuilder::GetOutput()
{
	std::string builtOutput;
	for(std::string line : Output)
	{
		builtOutput += line + '\n';
	}
	return  builtOutput;
}

std::string deamer::StringBuilder::GetOutputIgnoreNewLine()
{
	std::string builtOutput;
	for (std::string line : Output)
	{
		builtOutput += line;
	}
	return  builtOutput;
}
