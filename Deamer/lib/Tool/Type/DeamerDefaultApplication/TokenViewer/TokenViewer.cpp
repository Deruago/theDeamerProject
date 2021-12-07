#include "Deamer/Tool/Type/DeamerDefaultApplication/TokenViewer/TokenViewer.h"
#include "Deamer/Template/Tool/Type/DeamerDefaultApplication/TokenViewer/TokenViewerTemplate.h"

deamer::tool::type::deamerdefaultapplication::TokenViewer::TokenViewer(reference reference_)
	: Reference(reference_)
{
}

void deamer::tool::type::deamerdefaultapplication::TokenViewer::Generate(
	::deamer::file::tool::Directory& output)
{
	auto tokenViewerTemplate =
		templates::tool::deamerdefaultapplication::tokenviewer::TokenViewerTemplate();

	tokenViewerTemplate.language_name_->Set(
		Reference.GetDefinition<language::type::definition::property::Type::Identity>()
			.name->value);
	tokenViewerTemplate.lexer_->Set("Flex");

	auto tokenViewerFile = file::tool::File("main", "cpp", tokenViewerTemplate.GetOutput());

	output.AddFile(tokenViewerFile);
}
