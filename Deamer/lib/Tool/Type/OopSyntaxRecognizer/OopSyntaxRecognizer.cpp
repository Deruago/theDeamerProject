#include "Deamer/Tool/Type/OopSyntaxRecognizer/OopSyntaxRecognizer.h"
#include "Deamer/Language/Analyzer/Analyzer.h"
#include "Deamer/Language/Reference/LDO.h"
#include "Deamer/Language/Reference/ReverseLookup.h"
#include "Deamer/Language/Type/Definition/Object/Main/Grammar/NonTerminal.h"
#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/Terminal.h"
#include "Deamer/Language/Type/Definition/Object/Main/OOPSyntax/OopConceptLink.h"
#include "Deamer/Language/Type/Definition/Object/Main/OOPSyntax/OopLink.h"
#include "Deamer/Template/Tool/Type/OopSyntaxRecognizer/Recognizer/RecognizerTemplate.h"
#include <memory>

deamer::tool::type::oopsyntaxrecognizer::OopSyntaxRecognizer::OopSyntaxRecognizer(
	reference reference_)
	: Base(::deamer::tool::type::Tool::OopSyntaxRecognizer),
	  Reference(reference_)
{
}

deamer::file::tool::Output deamer::tool::type::oopsyntaxrecognizer::OopSyntaxRecognizer::Generate()
{
	file::tool::Output output("OopSyntaxRecognizer");

	const auto fileContent = GenerateRecognizer();
	const file::tool::File recognizer("OopSyntaxRecognizer", "h", fileContent);
	output.AddFileToInclude(recognizer);

	return output;
}

std::string deamer::tool::type::oopsyntaxrecognizer::OopSyntaxRecognizer::GenerateRecognizer()
{
	auto recognizerTemplate =
		std::make_unique<templates::oopsyntaxrecognizer::RecognizerTemplate>();
	recognizerTemplate->language_name_->Set(
		Reference.GetDefinition<language::type::definition::property::Type::Identity>()
			.GetName()
			->value);

	ImplementOopConceptScopes(recognizerTemplate);

	ImplementOopConceptLinks(recognizerTemplate);

	return recognizerTemplate->GetOutput();
}

void deamer::tool::type::oopsyntaxrecognizer::OopSyntaxRecognizer::ImplementOopConceptScopes(
	std::unique_ptr<deamer::templates::oopsyntaxrecognizer::RecognizerTemplate>& recognizerTemplate)
	const
{
	const auto& oopSyntaxLpd =
		Reference.GetDefinition<language::type::definition::property::Type::OOPSyntax>();

	for (language::reference::LDO<language::type::definition::object::main::OopEncapsulation, false>
			 oopEncapsulation : oopSyntaxLpd.OopEncapsulations)
	{
		recognizerTemplate->ast_node_->Set(oopEncapsulation->nonTerminal->Name);

		switch (oopEncapsulation->scope)
		{
		case language::type::definition::object::main::OopSyntaxScope::Struct: {
			recognizerTemplate->listen_struct_entry_->ExpandVariableField();
			recognizerTemplate->listen_struct_exit_->ExpandVariableField();
			break;
		}
		case language::type::definition::object::main::OopSyntaxScope::Interface: {
			recognizerTemplate->listen_interface_entry_->ExpandVariableField();
			recognizerTemplate->listen_interface_exit_->ExpandVariableField();
			break;
		}
		case language::type::definition::object::main::OopSyntaxScope::reserved_default_enum_option:
		case language::type::definition::object::main::OopSyntaxScope::Class: {
			recognizerTemplate->listen_class_entry_->ExpandVariableField();
			recognizerTemplate->listen_class_exit_->ExpandVariableField();
			break;
		}
		case language::type::definition::object::main::OopSyntaxScope::BaseTypes: {
			recognizerTemplate->listen_basetype_entry_->ExpandVariableField();
			recognizerTemplate->listen_basetype_exit_->ExpandVariableField();
			break;
		}
		case language::type::definition::object::main::OopSyntaxScope::Function: {
			recognizerTemplate->listen_function_entry_->ExpandVariableField();
			recognizerTemplate->listen_function_exit_->ExpandVariableField();
			break;
		}
		case language::type::definition::object::main::OopSyntaxScope::FunctionArguments: {
			recognizerTemplate->listen_functionargument_entry_->ExpandVariableField();
			recognizerTemplate->listen_functionargument_exit_->ExpandVariableField();
			break;
		}
		case language::type::definition::object::main::OopSyntaxScope::Property: {
			recognizerTemplate->listen_property_entry_->ExpandVariableField();
			recognizerTemplate->listen_property_exit_->ExpandVariableField();
			break;
		}
		case language::type::definition::object::main::OopSyntaxScope::Enum: {
			recognizerTemplate->listen_enumeration_entry_->ExpandVariableField();
			recognizerTemplate->listen_enumeration_exit_->ExpandVariableField();
			break;
		}
		case language::type::definition::object::main::OopSyntaxScope::Any: {
			// Nothing to do just inherit top flavor
			break;
		}
		}
	}
}

void deamer::tool::type::oopsyntaxrecognizer::OopSyntaxRecognizer::ImplementOopConceptLinks(
	std::unique_ptr<deamer::templates::oopsyntaxrecognizer::RecognizerTemplate>& recognizerTemplate)
{
	const auto& oopSyntaxLpd =
		Reference.GetDefinition<language::type::definition::property::Type::OOPSyntax>();

	std::map<language::type::definition::object::Base*,
			 std::vector<std::tuple<
				 language::reference::LDO<language::type::definition::object::main::OopLink, false>,
				 language::reference::LDO<language::type::definition::object::main::OopConceptLink,
										  false>>>>
		MapBaseWithOopLinks;

	for (language::reference::LDO<language::type::definition::object::main::OopLink, false>
			 oopLink : oopSyntaxLpd.OopLinks)
	{
		for (language::reference::LDO<language::type::definition::object::main::OopConceptLink,
									  false>
				 oopConceptLink : oopLink->OopConceptLinks)
		{
			auto* basePtr = oopConceptLink->object;
			auto iter = MapBaseWithOopLinks.find(basePtr);
			if (iter == MapBaseWithOopLinks.end())
			{
				MapBaseWithOopLinks.insert({basePtr, {}});
			}

			MapBaseWithOopLinks.find(basePtr)->second.emplace_back(oopLink, oopConceptLink);
		}
	}

	for (auto [object, oopLinksAndOopConceptLinks] : MapBaseWithOopLinks)
	{
		recognizerTemplate->listen_property_assignment_impl_->variable_field_->Clear();
		recognizerTemplate->listen_property_assignment_impl_->variable_field_->Clear();

		bool first = true;
		for (auto [oopLink, oopConceptLink] : oopLinksAndOopConceptLinks)
		{
			recognizerTemplate->listen_property_assign_specific_production_rule_action_logic_
				->variable_field_->Clear();

			if (first)
			{
				recognizerTemplate->optional_parent_initializer_->Set(
					recognizerTemplate->parent_initializer_);
				recognizerTemplate->optional_parent_continuation_->Set(
					recognizerTemplate->parent_continuation_);
				first = false;
			}
			else
			{
				recognizerTemplate->optional_parent_initializer_->Set("");
				recognizerTemplate->optional_parent_continuation_->Set("");
			}

			const auto analyzer = language::analyzer::Analyzer<
				language::type::definition::object::main::ProductionRule>(&Reference,
																		  oopLink->productionRule);
			if (!analyzer->IsProductionRuleBelongToSomeNonTerminal())
			{
				// The LPD is ill-formed, associated Threat should be triggered
				// Skip for now
				continue;
			}

			const auto NonTerminal = analyzer->GetNonTerminal();
			const auto index = analyzer->GetProductionRuleId();

			if (oopConceptLink->object->Type_ == language::type::definition::object::Type::Terminal)
			{
				recognizerTemplate->ast_node_->Set(
					language::reference::LDO<language::type::definition::object::main::Terminal,
											 false>(oopConceptLink->object)
						->Name);
			}
			else if (oopConceptLink->object->Type_ ==
					 language::type::definition::object::Type::NonTerminal)
			{
				recognizerTemplate->ast_node_->Set(
					language::reference::LDO<language::type::definition::object::main::NonTerminal,
											 false>(oopConceptLink->object)
						->Name);
			}
			else
			{
				// Error OopSyntax LPD is ill-formed.
				continue;
			}

			recognizerTemplate->impl_extended_direct_access_specialization_->variable_field_
				->Clear();

			if (oopConceptLink->extendedObjectAccess.empty())
			{
				recognizerTemplate->direct_access_extension_call_->Set(
					recognizerTemplate->impl_simple_direct_access_);
			}
			else
			{
				recognizerTemplate->direct_access_extension_call_->Set(
					recognizerTemplate->impl_extended_direct_access_);

				for (auto* extendedObject : oopConceptLink->extendedObjectAccess)
				{
					if (extendedObject->Type_ == language::type::definition::object::Type::Terminal)
					{
						recognizerTemplate->extended_direct_access_specialization_name_->Set(
							language::reference::LDO<
								language::type::definition::object::main::Terminal, false>(
								extendedObject)
								->Name);
					}
					else if (extendedObject->Type_ ==
							 language::type::definition::object::Type::NonTerminal)
					{
						recognizerTemplate->extended_direct_access_specialization_name_->Set(
							language::reference::LDO<
								language::type::definition::object::main::NonTerminal, false>(
								extendedObject)
								->Name);
					}
					else
					{
						// Error OopSyntax LPD is ill-formed.
						continue;
					}

					recognizerTemplate->impl_extended_direct_access_specialization_
						->ExpandVariableField();
				}
			}

			recognizerTemplate->required_ast_node_->Set(NonTerminal->Name);
			recognizerTemplate->required_production_rule_index_->Set(std::to_string(index));

			switch (oopConceptLink->oopConceptMember->scope)
			{
			case language::type::definition::object::main::OopSyntaxScope::Struct: {
				if (oopConceptLink->oopConceptMember->member ==
					language::type::definition::object::main::OopConceptMemberType::Name)
				{
					recognizerTemplate
						->listen_property_assign_specific_production_rule_action_logic_->Set(
							recognizerTemplate->listen_property_assign_struct_name_);
				}
				break;
			}
			case language::type::definition::object::main::OopSyntaxScope::Interface: {
				if (oopConceptLink->oopConceptMember->member ==
					language::type::definition::object::main::OopConceptMemberType::Name)
				{
					recognizerTemplate
						->listen_property_assign_specific_production_rule_action_logic_->Set(
							recognizerTemplate->listen_property_assign_interface_name_);
				}
				break;
			}
			case language::type::definition::object::main::OopSyntaxScope::
				reserved_default_enum_option:
			case language::type::definition::object::main::OopSyntaxScope::Class: {
				if (oopConceptLink->oopConceptMember->member ==
					language::type::definition::object::main::OopConceptMemberType::Name)
				{
					recognizerTemplate
						->listen_property_assign_specific_production_rule_action_logic_->Set(
							recognizerTemplate->listen_property_assign_class_name_);
				}
				break;
			}
			case language::type::definition::object::main::OopSyntaxScope::BaseTypes: {
				if (oopConceptLink->oopConceptMember->member ==
					language::type::definition::object::main::OopConceptMemberType::Type)
				{
					recognizerTemplate
						->listen_property_assign_specific_production_rule_action_logic_->Set(
							recognizerTemplate->listen_property_assign_basetype_type_);
				}
				break;
			}
			case language::type::definition::object::main::OopSyntaxScope::Function: {
				if (oopConceptLink->oopConceptMember->member ==
					language::type::definition::object::main::OopConceptMemberType::Name)
				{
					recognizerTemplate
						->listen_property_assign_specific_production_rule_action_logic_->Set(
							recognizerTemplate->listen_property_assign_function_name_);
				}
				if (oopConceptLink->oopConceptMember->member ==
					language::type::definition::object::main::OopConceptMemberType::Type)
				{
					recognizerTemplate
						->listen_property_assign_specific_production_rule_action_logic_->Set(
							recognizerTemplate->listen_property_assign_function_returntype_);
				}
				break;
			}
			case language::type::definition::object::main::OopSyntaxScope::FunctionArguments: {
				if (oopConceptLink->oopConceptMember->member ==
					language::type::definition::object::main::OopConceptMemberType::Name)
				{
					recognizerTemplate
						->listen_property_assign_specific_production_rule_action_logic_->Set(
							recognizerTemplate->listen_property_assign_function_argument_name_);
				}
				if (oopConceptLink->oopConceptMember->member ==
					language::type::definition::object::main::OopConceptMemberType::Type)
				{
					recognizerTemplate
						->listen_property_assign_specific_production_rule_action_logic_->Set(
							recognizerTemplate->listen_property_assign_function_argument_type_);
				}
				break;
			}
			case language::type::definition::object::main::OopSyntaxScope::Property: {
				if (oopConceptLink->oopConceptMember->member ==
					language::type::definition::object::main::OopConceptMemberType::Name)
				{
					recognizerTemplate
						->listen_property_assign_specific_production_rule_action_logic_->Set(
							recognizerTemplate->listen_property_assign_property_name_);
				}
				if (oopConceptLink->oopConceptMember->member ==
					language::type::definition::object::main::OopConceptMemberType::Type)
				{
					recognizerTemplate
						->listen_property_assign_specific_production_rule_action_logic_->Set(
							recognizerTemplate->listen_property_assign_property_type_);
				}
				break;
			}
			case language::type::definition::object::main::OopSyntaxScope::Enum: {
				if (oopConceptLink->oopConceptMember->member ==
					language::type::definition::object::main::OopConceptMemberType::Name)
				{
					recognizerTemplate
						->listen_property_assign_specific_production_rule_action_logic_->Set(
							recognizerTemplate->listen_property_assign_enum_name_);
				}
				if (oopConceptLink->oopConceptMember->member ==
					language::type::definition::object::main::OopConceptMemberType::Member)
				{
					recognizerTemplate
						->listen_property_assign_specific_production_rule_action_logic_->Set(
							recognizerTemplate->listen_property_assign_enum_member_);
				}
				break;
			}
			}

			recognizerTemplate->listen_property_assign_specific_production_rule_action_logic_
				->ExpandVariableField();

			recognizerTemplate->listen_property_assignment_impl_->Set(
				recognizerTemplate->listen_property_assign_specific_production_rule_action_);

			recognizerTemplate->listen_property_assignment_impl_->ExpandVariableField();
		}

		recognizerTemplate->listen_property_assignment_->ExpandVariableField();
	}
}
