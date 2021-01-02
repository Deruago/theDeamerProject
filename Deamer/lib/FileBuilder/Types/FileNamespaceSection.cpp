/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
 /*
  * Part of the DeamerProject.
  * For more information go to: https://github.com/Deruago/theDeamerProject
  */

#include "Deamer/FileBuilder/Types/FileNamespaceSection.h"
#include "Deamer/StringBuilder/StringBuilder.h"
#include <string>

deamer::FileNamespaceSection::FileNamespaceSection(std::string namespaceName)
{
	_namespaceName = namespaceName;
}

deamer::FileNamespaceSection::FileNamespaceSection(FileNamespaceSection* baseNamespace, std::string namespaceName) : FileNamespaceSection(namespaceName)
{
	_baseNamespace = baseNamespace;
}

std::string deamer::FileNamespaceSection::GetOutput()
{
	StringBuilder beginDeclaration;
	StringBuilder midDeclaration;
	StringBuilder endDeclaration;
	unsigned depth = 0;
	unsigned indentSize = 4;
	AddNamespaceDeclaration(&beginDeclaration, &endDeclaration, &depth, indentSize, true);
	AddFileSectionOutputToStringBuilder(&midDeclaration);
	return beginDeclaration.GetOutput() + midDeclaration.GetOutput() + endDeclaration.GetOutput();
}

std::string deamer::FileNamespaceSection::GetOutputType() const
{
	StringBuilder stringBuilder;
	unsigned depth = 0;
	AddNamespaceTypeToStringBuilder(&stringBuilder, &depth, true);
	return stringBuilder.GetOutputIgnoreNewLine();
}

std::string deamer::FileNamespaceSection::GetNamespaceName() const
{
	return _namespaceName;
}

std::string deamer::FileNamespaceSection::EmbedThisString(std::string string_that_needs_to_be_embedded) const
{
	StringBuilder beginDeclaration;
	StringBuilder midDeclaration;
	StringBuilder endDeclaration;
	unsigned depth = 0;
	unsigned indentSize = 4;
	AddNamespaceDeclaration(&beginDeclaration, &endDeclaration, &depth, indentSize, true);
	const std::string tmpReformattedString = midDeclaration.IndentEachLineInString(string_that_needs_to_be_embedded, indentSize, depth);
	midDeclaration.Add(tmpReformattedString);

	return beginDeclaration.GetOutput() + midDeclaration.GetOutput() + endDeclaration.GetOutput();
}

//std::string deamer::FileNamespaceSection::GetOutputUsingNamespace() const
//{
//	StringBuilder stringBuilder;
//	stringBuilder.Add("using ");
//	unsigned depth = 0;
//	GetNamespaceUsing(&stringBuilder, &depth);
//	return "";
//}

std::string deamer::FileNamespaceSection::GetThisNamespaceDeclarationWithoutNestedBaseNamespaceDeclarations() const
{
	StringBuilder stringBuilder;
	stringBuilder.Add("namespace ");
	stringBuilder.Add(_namespaceName);
	return stringBuilder.GetOutputIgnoreNewLine();
}

void deamer::FileNamespaceSection::AddNamespaceTypeToStringBuilder(StringBuilder* stringBuilder, unsigned* depth, bool firstNamespace) const
{
	if (_baseNamespace != nullptr)
	{
		_baseNamespace->AddNamespaceTypeToStringBuilder(stringBuilder, depth, false);
	}
	
	stringBuilder->Add(_namespaceName);
	if (!firstNamespace)
	{
		stringBuilder->Add("::");
	}
	(*depth)++;
}

void deamer::FileNamespaceSection::AddFileSectionOutputToStringBuilder(StringBuilder* string_builder)
{
	for(FileSection* file_section : FileSections)
	{
		string_builder->Add(file_section->GetOutput());
	}
}

void deamer::FileNamespaceSection::AddNamespaceDeclaration(StringBuilder* beginDeclarations,
                                                           StringBuilder* endDeclarations, unsigned* depth, unsigned indent, bool firstNamespace) const
{	
	if(_baseNamespace != nullptr)
	{
		_baseNamespace->AddNamespaceDeclaration(beginDeclarations, endDeclarations, depth, indent, false);
	}

	beginDeclarations->Add(GetThisNamespaceDeclarationWithoutNestedBaseNamespaceDeclarations(), *depth, indent);
	beginDeclarations->Add("{", *depth, indent);

	if (firstNamespace)
	{
		AddEndingNamespaceDeclaration(endDeclarations, indent, *depth);
	}
	(*depth)++;
}

void deamer::FileNamespaceSection::AddEndingNamespaceDeclaration(StringBuilder* endDeclarations, unsigned indentSize, unsigned depth) const
{
	for(int i = depth; i > -1; i--)
	{
		endDeclarations->Add("}", indentSize, i);
	}
}
