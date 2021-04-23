#ifndef DEAMER_TESTS_LANGUAGE_VALIDATOR_GENERATION_GETFIRSTDEFAULTGENERATORINGENERATORS_H
#define DEAMER_TESTS_LANGUAGE_VALIDATOR_GENERATION_GETFIRSTDEFAULTGENERATORINGENERATORS_H

#include <Deamer/Language/Validator/Generator/GetFirstDefaultGeneratorInGenerators.h>
#include "Deamer/Language/Generator/Definition/Language.h"
#include "Deamer/Language/Generator/Definition/Property/User/Main/Lexicon.h"
#include "Deamer/Language/Generator/Definition/Property/User/Main/Grammar.h"
#include "Deamer/Language/Generator/Definition/Property/Standard/Main/Precedence.h"

using namespace deamer::language::validator::generator;
using namespace deamer::language::generator::definition;
using namespace deamer::language::generator::definition::property;
using namespace deamer::language::generator::definition::property::standard;
using namespace deamer::language::generator::definition::property::user;

class DerivedLanguage;

class DerivedLexicon : public Lexicon<DerivedLanguage>
{
public:
	DerivedLexicon(DerivedLanguage* lang) : Lexicon<DerivedLanguage>(lang) {}
};
class DerivedGrammar : public Grammar<DerivedLanguage>
{
public:
	DerivedGrammar(DerivedLanguage* lang) : Grammar<DerivedLanguage>(lang) {}
};
class DerivedPrecedence : public Precedence<DerivedLanguage>
{
public:
	DerivedPrecedence(DerivedLanguage* lang) : Precedence<DerivedLanguage>(lang) {}
};
class DerivedPrecedence1 : public Precedence<DerivedLanguage>
{
public:
	DerivedPrecedence1(DerivedLanguage* lang) : Precedence<DerivedLanguage>(lang) {}
};

class DerivedLanguage : public Language<DerivedLanguage, DerivedLexicon, DerivedGrammar, DerivedPrecedence>, public DerivedLexicon, public DerivedGrammar, public DerivedPrecedence
{
public:
	DerivedLanguage() : DerivedLexicon(this), DerivedGrammar(this), DerivedPrecedence(this)
	{
	}
	
	~DerivedLanguage() = default;
};


#endif //DEAMER_TESTS_LANGUAGE_VALIDATOR_GENERATION_GETFIRSTDEFAULTGENERATORINGENERATORS_H