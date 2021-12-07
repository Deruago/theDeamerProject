#include "Deamer/Tool/Type/DeamerDefaultApplication/AstViewer/AstViewer.h"
#include "Deamer/Template/Tool/Type/DeamerDefaultApplication/AstViewer/AstViewerTemplate.h"

deamer::tool::type::deamerdefaultapplication::AstViewer::AstViewer(reference reference_)
	: Reference(reference_)
{
}

void deamer::tool::type::deamerdefaultapplication::AstViewer::Generate(
	::deamer::file::tool::Directory& output)
{
	auto astViewerTemplate =
		templates::tool::deamerdefaultapplication::astviewer::AstViewerTemplate();

	astViewerTemplate.language_name_->Set(
		Reference.GetDefinition<language::type::definition::property::Type::Identity>()
			.name->value);
	astViewerTemplate.parser_->Set("Bison");

	auto astViewerFile = file::tool::File("main", "cpp", astViewerTemplate.GetOutput());

	output.AddFile(astViewerFile);
}
