#include "Deamer/Tool/Type/DLDLConverter/DLDLConverter.h"
#include "Deamer/Tool/Type/DLDLConverter/Grammar/Grammar.h"
#include "Deamer/Tool/Type/DLDLConverter/Lexicon/Lexicon.h"

deamer::tool::type::dldlconverter::DLDLConverter::DLDLConverter(reference reference_)
	: Base(::deamer::tool::type::Tool::DLDLConverter),
	  Reference(reference_)
{
}

deamer::file::tool::Output deamer::tool::type::dldlconverter::DLDLConverter::Generate()
{
	const auto language_name =
		Reference.GetDefinition<language::type::definition::property::Type::Identity>().name->value;

	const auto generateAll =
		Reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsArgumentSet({Tool::DLDLConverter, "all"});
	const auto generateLexicon =
		Reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsArgumentSet({Tool::DLDLConverter, "lexicon"});
	const auto generateGrammar =
		Reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsArgumentSet({Tool::DLDLConverter, "grammar"});
	const auto generateGeneration =
		Reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsArgumentSet({Tool::DLDLConverter, "generation"});

	file::tool::Output output("DLDLConverter");

	if (Reference.IsDefinitionAvailable(language::type::definition::property::Type::Lexicon) &&
		(generateAll || generateLexicon))
		lexicon::Lexicon(Reference).Generate(output);

	if (Reference.IsDefinitionAvailable(language::type::definition::property::Type::Grammar) &&
		(generateAll || generateGrammar))
		grammar::Grammar(Reference).Generate(output);

	return output;
}
