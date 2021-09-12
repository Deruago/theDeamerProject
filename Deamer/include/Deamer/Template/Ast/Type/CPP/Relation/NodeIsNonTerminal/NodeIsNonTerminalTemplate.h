#ifndef DEAMER_TEMPLATES_AST_TYPE_CPP_NODEISNONTERMINALTEMPLATE_h
#define DEAMER_TEMPLATES_AST_TYPE_CPP_NODEISNONTERMINALTEMPLATE_h

#include <string>
#include <variant>
#include <vector>

namespace deamer::templates::ast::type::cpp
{
	/*!	\class NodeIsNonTerminalTemplate
	 *
	 *	\brief Generates code for "NodeIsNonTerminalTemplate"
	 *
	 *	\details This is generated by DST.
	 *	For more information visit: https://github.com/Deruago/DeamerStringTemplate
	 */
	class NodeIsNonTerminalTemplate
	{
	public:
		enum class Type
		{
			Unknown,
			Scope,

			// User defined types
			class_name_,
			file_,
			header_guard_,
			is_nonterminal_,
			language_name_,
			language_name_underscore_,
			left_angle_bracket_,
			left_bracket_,
			left_curly_bracket_,
			node_conversion_,
			node_enum_include_,
			node_enum_type_,
			node_enum_value_type_,
			node_name_,
			right_angle_bracket_,
			right_bracket_,
			right_curly_bracket_,

		};

		enum class ScopeType
		{
			Unknown,

			// Default
			Default_,
			Upper_,
			Lower_,

			Snake_,
			Slash_,
			BackSlash_,
			Colon_,
			DoubleColon_,

			Variable_Field_,
			Variable_Field_Separator_,
			Function_Field_,
			Function_Field_Separator_,

		};

		static constexpr const char* ConvertEnumToName(
			::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type enumerationValue)
		{
			switch (enumerationValue)
			{
			case ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
				class_name_: {
				return "class_name";
			}

			case ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::file_: {
				return "file";
			}

			case ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
				header_guard_: {
				return "header_guard";
			}

			case ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
				is_nonterminal_: {
				return "is_nonterminal";
			}

			case ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
				language_name_: {
				return "language_name";
			}

			case ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
				language_name_underscore_: {
				return "language_name_underscore";
			}

			case ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
				left_angle_bracket_: {
				return "left_angle_bracket";
			}

			case ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
				left_bracket_: {
				return "left_bracket";
			}

			case ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
				left_curly_bracket_: {
				return "left_curly_bracket";
			}

			case ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
				node_conversion_: {
				return "node_conversion";
			}

			case ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
				node_enum_include_: {
				return "node_enum_include";
			}

			case ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
				node_enum_type_: {
				return "node_enum_type";
			}

			case ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
				node_enum_value_type_: {
				return "node_enum_value_type";
			}

			case ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::node_name_: {
				return "node_name";
			}

			case ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
				right_angle_bracket_: {
				return "right_angle_bracket";
			}

			case ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
				right_bracket_: {
				return "right_bracket";
			}

			case ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
				right_curly_bracket_: {
				return "right_curly_bracket";
			}
			}

			return "";
		}

	public:
		struct VariableBase
		{
			// The value is either a string
			// or a vector of variables.
			std::variant<std::string, std::vector<VariableBase*>> value;
			bool isString = true;

			::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type type =
				::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::Unknown;

			VariableBase() : VariableBase(std::vector<VariableBase*>())
			{
			}

			virtual ~VariableBase() = default;

			VariableBase(const char* text)
			{
				isString = true;
				value = text;
			}

			VariableBase(const std::string& text)
			{
				isString = true;
				value = text;
			}

			VariableBase(std::vector<VariableBase*> variables)
			{
				isString = false;
				value = variables;
			}

			VariableBase* This()
			{
				return this;
			}

			virtual std::string GetValue()
			{
				if (isString)
				{
					return std::get<std::string>(value);
				}
				else
				{
					std::string output;
					auto& variables = std::get<std::vector<VariableBase*>>(value);
					for (auto* variable : variables)
					{
						output += variable->GetValue();
					}
					return output;
				}
			}

			std::string GetName()
			{
				return ConvertEnumToName(type);
			}

			VariableBase& operator=(const std::string& variable)
			{
				return Set(variable);
			}

			VariableBase& operator=(VariableBase* variable)
			{
				return Set(variable);
			}

			VariableBase& operator+=(VariableBase* variable)
			{
				return Add(variable);
			}

			VariableBase& operator+=(const std::string& variable)
			{
				return Add(variable);
			}

			VariableBase& Set(const std::string& variable)
			{
				value = variable;
				isString = true;

				return *this;
			}

			VariableBase& Set(VariableBase* variable)
			{
				if (variable == this)
				{
					return *this;
				}

				value = variable->value;
				isString = variable->isString;

				return *this;
			}

			VariableBase& Add(const std::string& variable)
			{
				if (isString)
				{
					auto& text = std::get<std::string>(value);
					text += variable;
					value = text;
				}
				else
				{
					auto& vector = std::get<std::vector<VariableBase*>>(value);
					vector.push_back(new VariableBase(variable));
					value = vector;
				}

				return *this;
			}

			VariableBase& Add(VariableBase* variable)
			{
				if (variable == this)
				{
					return *this;
				}

				if (isString)
				{
					// convert current -> variablebase
					// then create a vector.
					auto& currentValue = std::get<std::string>(value);
					auto* currentValueAsVariableBase = new VariableBase(currentValue);
					value = std::vector<VariableBase*>({currentValueAsVariableBase, variable});

					isString = false;
				}
				else
				{
					auto& vector = std::get<std::vector<VariableBase*>>(value);
					vector.push_back(variable);
					value = vector;
				}

				return *this;
			}

			void Clear()
			{
				if (isString)
				{
					value = "";
				}
				else
				{
					value = std::vector<VariableBase*>();
				}
			}

			void* operator new(size_t size)
			{
				void* newVariable = ::operator new(size);
				variables_to_delete.emplace_back(static_cast<VariableBase*>(newVariable));

				return newVariable;
			}
		};

		static VariableBase* GenerateVariable(VariableBase* variable)
		{
			return variable;
		}

		static VariableBase* GenerateVariable(const std::string& variable)
		{
			return new VariableBase(variable);
		}

		struct VariableScope : public VariableBase
		{
			::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::ScopeType scope_type =
				::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::ScopeType::Unknown;
			bool isReserved = false;

			VariableScope(::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::ScopeType
							  scope_type_,
						  bool isReserved_ = false)
				: VariableBase(),
				  scope_type(scope_type_),
				  isReserved(isReserved_)
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::Scope;
			}

			VariableScope(const char* text,
						  ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::ScopeType
							  scope_type_,
						  bool isReserved_ = false)
				: VariableBase(text),
				  scope_type(scope_type_),
				  isReserved(isReserved_)
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::Scope;
			}

			VariableScope(std::vector<VariableBase*> variable,
						  ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::ScopeType
							  scope_type_,
						  bool isReserved_ = false)
				: VariableBase(variable),
				  scope_type(scope_type_),
				  isReserved(isReserved_)
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::Scope;
			}
		};

		struct Variable_ReservedScope_Upper : public VariableScope
		{
			VariableBase* base;
			Variable_ReservedScope_Upper(VariableBase* base_)
				: VariableScope(::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::
									ScopeType::Upper_,
								true),
				  base(base_)
			{
			}

			virtual std::string GetValue() override
			{
				std::string upperVariant;
				std::string currentValue = base->GetValue();

				for (const auto character : currentValue)
				{
					upperVariant += std::toupper(character);
				}

				return upperVariant;
			}
		};

		struct Variable_ReservedScope_Lower : public VariableScope
		{
			VariableBase* base;
			Variable_ReservedScope_Lower(VariableBase* base_)
				: VariableScope(::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::
									ScopeType::Lower_,
								true),
				  base(base_)
			{
			}

			virtual std::string GetValue() override
			{
				std::string lowerVariant;
				std::string currentValue = base->GetValue();

				for (const auto character : currentValue)
				{
					lowerVariant += std::tolower(character);
				}

				return lowerVariant;
			}
		};

		struct Variable_ReservedScope_Snake : public VariableScope
		{
			VariableBase* base;
			Variable_ReservedScope_Snake(VariableBase* base_)
				: VariableScope(::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::
									ScopeType::Snake_,
								true),
				  base(base_)
			{
			}

			virtual std::string GetValue() override
			{
				std::string snakeVariant;
				std::string currentValue = base->GetValue();

				bool lastWasNonAlpha = true;
				for (const auto character : currentValue)
				{
					if (std::isalpha(character))
					{
						snakeVariant += character;
						lastWasNonAlpha = false;
					}
					else
					{
						if (lastWasNonAlpha)
						{
							continue;
						}

						snakeVariant += '_';
						lastWasNonAlpha = true;
					}
				}

				// If it contains text
				// remove the tail
				if (!snakeVariant.empty() && lastWasNonAlpha)
				{
					snakeVariant.pop_back();
				}

				return snakeVariant;
			}
		};

		struct Variable_ReservedScope_Slash : public VariableScope
		{
			VariableBase* base;
			Variable_ReservedScope_Slash(VariableBase* base_)
				: VariableScope(::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::
									ScopeType::Slash_,
								true),
				  base(base_)
			{
			}

			virtual std::string GetValue() override
			{
				std::string slashVariant;
				std::string currentValue = base->GetValue();

				bool lastWasNonAlpha = true;
				for (const auto character : currentValue)
				{
					if (std::isalpha(character))
					{
						slashVariant += character;
						lastWasNonAlpha = false;
					}
					else
					{
						if (lastWasNonAlpha)
						{
							continue;
						}

						slashVariant += '/';
						lastWasNonAlpha = true;
					}
				}

				// If it contains text
				// remove the tail
				if (!slashVariant.empty() && lastWasNonAlpha)
				{
					slashVariant.pop_back();
				}

				return slashVariant;
			}
		};

		struct Variable_ReservedScope_DoubleColon : public VariableScope
		{
			VariableBase* base;
			Variable_ReservedScope_DoubleColon(VariableBase* base_)
				: VariableScope(::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::
									ScopeType::DoubleColon_,
								true),
				  base(base_)
			{
			}

			virtual std::string GetValue() override
			{
				std::string doubleColonVariant;
				std::string currentValue = base->GetValue();

				bool lastWasNonAlpha = true;
				for (const auto character : currentValue)
				{
					if (std::isalpha(character))
					{
						doubleColonVariant += character;
						lastWasNonAlpha = false;
					}
					else
					{
						if (lastWasNonAlpha)
						{
							continue;
						}

						doubleColonVariant += "::";
						lastWasNonAlpha = true;
					}
				}

				// If it contains text
				// remove the tail
				if (!doubleColonVariant.empty() && lastWasNonAlpha)
				{
					doubleColonVariant.pop_back();
					doubleColonVariant.pop_back();
				}

				return doubleColonVariant;
			}
		};

		struct VariableScopes : public VariableBase
		{
			// Default scopes
			VariableBase* default_ = new VariableScope(
				::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::ScopeType::Default_,
				true);
			VariableBase* upper_ = new Variable_ReservedScope_Upper(this);
			VariableBase* lower_ = new Variable_ReservedScope_Lower(this);

			VariableBase* snake_ = new Variable_ReservedScope_Snake(this);
			VariableBase* slash_ = new Variable_ReservedScope_Slash(this);
			VariableBase* double_colon_ = new Variable_ReservedScope_DoubleColon(this);

			VariableBase* variable_field_ =
				new VariableScope(::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::
									  ScopeType::Variable_Field_,
								  true);
			VariableBase* variable_field_separator_ =
				new VariableScope("\n",
								  ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::
									  ScopeType::Variable_Field_Separator_,
								  true);

			// Ctor
			VariableScopes() : VariableBase()
			{
			}

			VariableScopes(const char* text) : VariableBase(text)
			{
			}

			VariableScopes(const std::string& text) : VariableBase(text)
			{
			}

			VariableScopes(std::vector<VariableBase*> variables) : VariableBase(variables)
			{
			}

			// Dtor
			virtual ~VariableScopes() override = default;

			// Calls
			VariableBase* Default()
			{
				return default_;
			}
			VariableBase* Upper()
			{
				return upper_;
			}

			VariableBase* Lower()
			{
				return lower_;
			}

			VariableBase* Underscore()
			{
				return snake_;
			}

			VariableBase* Snake()
			{
				return snake_;
			}

			VariableBase* Slash()
			{
				return slash_;
			}

			VariableBase* DoubleColon()
			{
				return double_colon_;
			}

			VariableBase* Variable_Field()
			{
				return variable_field_;
			}

			VariableBase* Variable_Field_Separator()
			{
				return variable_field_separator_;
			}

			void ExpandVariableField()
			{
				// currentvalue + separator
				const auto currentValue = GetValue() + Variable_Field_Separator()->GetValue();
				*Variable_Field() += currentValue;
			}
		};

	public:
		struct Variable_class_name_ : public VariableScopes
		{
			static constexpr auto name = "class_name_";

			Variable_class_name_() : VariableScopes()
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					class_name_;
			}

			virtual ~Variable_class_name_() override = default;

			Variable_class_name_(NodeIsNonTerminalTemplate* nodeisnonterminaltemplate_,
								 const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					class_name_;
			}

			Variable_class_name_& operator=(const Variable_class_name_& variable)
			{
				if (&variable == this)
				{
					return *this;
				}

				value = variable.value;
				isString = variable.isString;

				return *this;
			}
		};

		struct Variable_file_ : public VariableScopes
		{
			static constexpr auto name = "file_";

			VariableBase* Content_ = GenerateVariable("");
			VariableBase* Class_postfix_ = GenerateVariable("");
			VariableBase* Extension_ = GenerateVariable("");
			VariableBase* File_name_ = GenerateVariable("");
			VariableBase* Namespace_ = GenerateVariable("");
			VariableBase* Target_language_ = GenerateVariable("");

			Variable_file_() : VariableScopes()
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::file_;
			}

			virtual ~Variable_file_() override = default;

			Variable_file_(NodeIsNonTerminalTemplate* nodeisnonterminaltemplate_,
						   const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::file_;
				*static_cast<VariableBase*>(Content_) = VariableBase(std::vector<VariableBase*>(
					{GenerateVariable("#ifndef "),
					 GenerateVariable(nodeisnonterminaltemplate_->header_guard_->This()),
					 GenerateVariable("\n#define "),
					 GenerateVariable(nodeisnonterminaltemplate_->header_guard_->This()),
					 GenerateVariable("\n\n"),
					 GenerateVariable(nodeisnonterminaltemplate_->node_enum_include_->This()),
					 GenerateVariable("\n\nnamespace "),
					 GenerateVariable(nodeisnonterminaltemplate_->language_name_->This()),
					 GenerateVariable(" "),
					 GenerateVariable("{"),
					 GenerateVariable(" namespace ast "),
					 GenerateVariable("{"),
					 GenerateVariable(" namespace relation "),
					 GenerateVariable("{"),
					 GenerateVariable(" \n\n\tconstexpr static bool "),
					 GenerateVariable(nodeisnonterminaltemplate_->class_name_->This()),
					 GenerateVariable("("),
					 GenerateVariable(nodeisnonterminaltemplate_->node_enum_type_->This()),
					 GenerateVariable(" t)\n\t"),
					 GenerateVariable("{"),
					 GenerateVariable("\n\t\t"),
					 GenerateVariable(
						 nodeisnonterminaltemplate_->node_conversion_->Variable_Field()),
					 GenerateVariable("\n\n\t\treturn false;\n\t"),
					 GenerateVariable("}"),
					 GenerateVariable("\n\n\n"),
					 GenerateVariable("}}"),
					 GenerateVariable("}"),
					 GenerateVariable("\n\n#endif // "),
					 GenerateVariable(nodeisnonterminaltemplate_->header_guard_->This())}));
				Content_->type =
					::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::Scope;

				*static_cast<VariableBase*>(Class_postfix_) =
					VariableBase(std::vector<VariableBase*>({}));
				Class_postfix_->type =
					::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::Scope;

				*static_cast<VariableBase*>(Extension_) =
					VariableBase(std::vector<VariableBase*>({GenerateVariable("h")}));
				Extension_->type =
					::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::Scope;

				*static_cast<VariableBase*>(File_name_) = VariableBase(std::vector<VariableBase*>(
					{GenerateVariable(nodeisnonterminaltemplate_->class_name_->This())}));
				File_name_->type =
					::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::Scope;

				*static_cast<VariableBase*>(Namespace_) = VariableBase(std::vector<VariableBase*>(
					{GenerateVariable("deamer::templates::ast::type::cpp")}));
				Namespace_->type =
					::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::Scope;

				*static_cast<VariableBase*>(Target_language_) =
					VariableBase(std::vector<VariableBase*>({GenerateVariable("C++")}));
				Target_language_->type =
					::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::Scope;
			}

			VariableBase* Content() const
			{
				return Content_;
			}

			VariableBase* Class_postfix() const
			{
				return Class_postfix_;
			}

			VariableBase* Extension() const
			{
				return Extension_;
			}

			VariableBase* File_name() const
			{
				return File_name_;
			}

			VariableBase* Namespace() const
			{
				return Namespace_;
			}

			VariableBase* Target_language() const
			{
				return Target_language_;
			}

			Variable_file_& operator=(const Variable_file_& variable)
			{
				if (&variable == this)
				{
					return *this;
				}

				value = variable.value;
				isString = variable.isString;

				*Content_ = *variable.Content_;
				*Class_postfix_ = *variable.Class_postfix_;
				*Extension_ = *variable.Extension_;
				*File_name_ = *variable.File_name_;
				*Namespace_ = *variable.Namespace_;
				*Target_language_ = *variable.Target_language_;

				return *this;
			}
		};

		struct Variable_header_guard_ : public VariableScopes
		{
			static constexpr auto name = "header_guard_";

			Variable_header_guard_() : VariableScopes()
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					header_guard_;
			}

			virtual ~Variable_header_guard_() override = default;

			Variable_header_guard_(NodeIsNonTerminalTemplate* nodeisnonterminaltemplate_,
								   const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					header_guard_;
			}

			Variable_header_guard_& operator=(const Variable_header_guard_& variable)
			{
				if (&variable == this)
				{
					return *this;
				}

				value = variable.value;
				isString = variable.isString;

				return *this;
			}
		};

		struct Variable_is_nonterminal_ : public VariableScopes
		{
			static constexpr auto name = "is_nonterminal_";

			Variable_is_nonterminal_() : VariableScopes()
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					is_nonterminal_;
			}

			virtual ~Variable_is_nonterminal_() override = default;

			Variable_is_nonterminal_(NodeIsNonTerminalTemplate* nodeisnonterminaltemplate_,
									 const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					is_nonterminal_;
			}

			Variable_is_nonterminal_& operator=(const Variable_is_nonterminal_& variable)
			{
				if (&variable == this)
				{
					return *this;
				}

				value = variable.value;
				isString = variable.isString;

				return *this;
			}
		};

		struct Variable_language_name_ : public VariableScopes
		{
			static constexpr auto name = "language_name_";

			Variable_language_name_() : VariableScopes()
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					language_name_;
			}

			virtual ~Variable_language_name_() override = default;

			Variable_language_name_(NodeIsNonTerminalTemplate* nodeisnonterminaltemplate_,
									const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					language_name_;
			}

			Variable_language_name_& operator=(const Variable_language_name_& variable)
			{
				if (&variable == this)
				{
					return *this;
				}

				value = variable.value;
				isString = variable.isString;

				return *this;
			}
		};

		struct Variable_language_name_underscore_ : public VariableScopes
		{
			static constexpr auto name = "language_name_underscore_";

			Variable_language_name_underscore_() : VariableScopes()
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					language_name_underscore_;
			}

			virtual ~Variable_language_name_underscore_() override = default;

			Variable_language_name_underscore_(
				NodeIsNonTerminalTemplate* nodeisnonterminaltemplate_,
				const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					language_name_underscore_;
			}

			Variable_language_name_underscore_&
			operator=(const Variable_language_name_underscore_& variable)
			{
				if (&variable == this)
				{
					return *this;
				}

				value = variable.value;
				isString = variable.isString;

				return *this;
			}
		};

		struct Variable_left_angle_bracket_ : public VariableScopes
		{
			static constexpr auto name = "left_angle_bracket_";

			Variable_left_angle_bracket_() : VariableScopes()
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					left_angle_bracket_;
			}

			virtual ~Variable_left_angle_bracket_() override = default;

			Variable_left_angle_bracket_(NodeIsNonTerminalTemplate* nodeisnonterminaltemplate_,
										 const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					left_angle_bracket_;
			}

			Variable_left_angle_bracket_& operator=(const Variable_left_angle_bracket_& variable)
			{
				if (&variable == this)
				{
					return *this;
				}

				value = variable.value;
				isString = variable.isString;

				return *this;
			}
		};

		struct Variable_left_bracket_ : public VariableScopes
		{
			static constexpr auto name = "left_bracket_";

			Variable_left_bracket_() : VariableScopes()
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					left_bracket_;
			}

			virtual ~Variable_left_bracket_() override = default;

			Variable_left_bracket_(NodeIsNonTerminalTemplate* nodeisnonterminaltemplate_,
								   const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					left_bracket_;
			}

			Variable_left_bracket_& operator=(const Variable_left_bracket_& variable)
			{
				if (&variable == this)
				{
					return *this;
				}

				value = variable.value;
				isString = variable.isString;

				return *this;
			}
		};

		struct Variable_left_curly_bracket_ : public VariableScopes
		{
			static constexpr auto name = "left_curly_bracket_";

			Variable_left_curly_bracket_() : VariableScopes()
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					left_curly_bracket_;
			}

			virtual ~Variable_left_curly_bracket_() override = default;

			Variable_left_curly_bracket_(NodeIsNonTerminalTemplate* nodeisnonterminaltemplate_,
										 const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					left_curly_bracket_;
			}

			Variable_left_curly_bracket_& operator=(const Variable_left_curly_bracket_& variable)
			{
				if (&variable == this)
				{
					return *this;
				}

				value = variable.value;
				isString = variable.isString;

				return *this;
			}
		};

		struct Variable_node_conversion_ : public VariableScopes
		{
			static constexpr auto name = "node_conversion_";

			Variable_node_conversion_() : VariableScopes()
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					node_conversion_;
			}

			virtual ~Variable_node_conversion_() override = default;

			Variable_node_conversion_(NodeIsNonTerminalTemplate* nodeisnonterminaltemplate_,
									  const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					node_conversion_;
			}

			Variable_node_conversion_& operator=(const Variable_node_conversion_& variable)
			{
				if (&variable == this)
				{
					return *this;
				}

				value = variable.value;
				isString = variable.isString;

				return *this;
			}
		};

		struct Variable_node_enum_include_ : public VariableScopes
		{
			static constexpr auto name = "node_enum_include_";

			Variable_node_enum_include_() : VariableScopes()
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					node_enum_include_;
			}

			virtual ~Variable_node_enum_include_() override = default;

			Variable_node_enum_include_(NodeIsNonTerminalTemplate* nodeisnonterminaltemplate_,
										const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					node_enum_include_;
			}

			Variable_node_enum_include_& operator=(const Variable_node_enum_include_& variable)
			{
				if (&variable == this)
				{
					return *this;
				}

				value = variable.value;
				isString = variable.isString;

				return *this;
			}
		};

		struct Variable_node_enum_type_ : public VariableScopes
		{
			static constexpr auto name = "node_enum_type_";

			Variable_node_enum_type_() : VariableScopes()
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					node_enum_type_;
			}

			virtual ~Variable_node_enum_type_() override = default;

			Variable_node_enum_type_(NodeIsNonTerminalTemplate* nodeisnonterminaltemplate_,
									 const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					node_enum_type_;
			}

			Variable_node_enum_type_& operator=(const Variable_node_enum_type_& variable)
			{
				if (&variable == this)
				{
					return *this;
				}

				value = variable.value;
				isString = variable.isString;

				return *this;
			}
		};

		struct Variable_node_enum_value_type_ : public VariableScopes
		{
			static constexpr auto name = "node_enum_value_type_";

			Variable_node_enum_value_type_() : VariableScopes()
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					node_enum_value_type_;
			}

			virtual ~Variable_node_enum_value_type_() override = default;

			Variable_node_enum_value_type_(NodeIsNonTerminalTemplate* nodeisnonterminaltemplate_,
										   const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					node_enum_value_type_;
			}

			Variable_node_enum_value_type_&
			operator=(const Variable_node_enum_value_type_& variable)
			{
				if (&variable == this)
				{
					return *this;
				}

				value = variable.value;
				isString = variable.isString;

				return *this;
			}
		};

		struct Variable_node_name_ : public VariableScopes
		{
			static constexpr auto name = "node_name_";

			Variable_node_name_() : VariableScopes()
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					node_name_;
			}

			virtual ~Variable_node_name_() override = default;

			Variable_node_name_(NodeIsNonTerminalTemplate* nodeisnonterminaltemplate_,
								const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					node_name_;
			}

			Variable_node_name_& operator=(const Variable_node_name_& variable)
			{
				if (&variable == this)
				{
					return *this;
				}

				value = variable.value;
				isString = variable.isString;

				return *this;
			}
		};

		struct Variable_right_angle_bracket_ : public VariableScopes
		{
			static constexpr auto name = "right_angle_bracket_";

			Variable_right_angle_bracket_() : VariableScopes()
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					right_angle_bracket_;
			}

			virtual ~Variable_right_angle_bracket_() override = default;

			Variable_right_angle_bracket_(NodeIsNonTerminalTemplate* nodeisnonterminaltemplate_,
										  const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					right_angle_bracket_;
			}

			Variable_right_angle_bracket_& operator=(const Variable_right_angle_bracket_& variable)
			{
				if (&variable == this)
				{
					return *this;
				}

				value = variable.value;
				isString = variable.isString;

				return *this;
			}
		};

		struct Variable_right_bracket_ : public VariableScopes
		{
			static constexpr auto name = "right_bracket_";

			Variable_right_bracket_() : VariableScopes()
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					right_bracket_;
			}

			virtual ~Variable_right_bracket_() override = default;

			Variable_right_bracket_(NodeIsNonTerminalTemplate* nodeisnonterminaltemplate_,
									const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					right_bracket_;
			}

			Variable_right_bracket_& operator=(const Variable_right_bracket_& variable)
			{
				if (&variable == this)
				{
					return *this;
				}

				value = variable.value;
				isString = variable.isString;

				return *this;
			}
		};

		struct Variable_right_curly_bracket_ : public VariableScopes
		{
			static constexpr auto name = "right_curly_bracket_";

			Variable_right_curly_bracket_() : VariableScopes()
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					right_curly_bracket_;
			}

			virtual ~Variable_right_curly_bracket_() override = default;

			Variable_right_curly_bracket_(NodeIsNonTerminalTemplate* nodeisnonterminaltemplate_,
										  const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate::Type::
					right_curly_bracket_;
			}

			Variable_right_curly_bracket_& operator=(const Variable_right_curly_bracket_& variable)
			{
				if (&variable == this)
				{
					return *this;
				}

				value = variable.value;
				isString = variable.isString;

				return *this;
			}
		};

	public:
		inline static std::vector<VariableBase*> variables_to_delete = std::vector<VariableBase*>();

	public:
		std::vector<VariableBase*> variables_;

	public:
		// Members that one can directly access.
		// e.g. NodeIsNonTerminalTemplate.member = "auto-generated";
		Variable_class_name_* class_name_ = new Variable_class_name_();
		Variable_file_* file_ = new Variable_file_();
		Variable_header_guard_* header_guard_ = new Variable_header_guard_();
		Variable_is_nonterminal_* is_nonterminal_ = new Variable_is_nonterminal_();
		Variable_language_name_* language_name_ = new Variable_language_name_();
		Variable_language_name_underscore_* language_name_underscore_ =
			new Variable_language_name_underscore_();
		Variable_left_angle_bracket_* left_angle_bracket_ = new Variable_left_angle_bracket_();
		Variable_left_bracket_* left_bracket_ = new Variable_left_bracket_();
		Variable_left_curly_bracket_* left_curly_bracket_ = new Variable_left_curly_bracket_();
		Variable_node_conversion_* node_conversion_ = new Variable_node_conversion_();
		Variable_node_enum_include_* node_enum_include_ = new Variable_node_enum_include_();
		Variable_node_enum_type_* node_enum_type_ = new Variable_node_enum_type_();
		Variable_node_enum_value_type_* node_enum_value_type_ =
			new Variable_node_enum_value_type_();
		Variable_node_name_* node_name_ = new Variable_node_name_();
		Variable_right_angle_bracket_* right_angle_bracket_ = new Variable_right_angle_bracket_();
		Variable_right_bracket_* right_bracket_ = new Variable_right_bracket_();
		Variable_right_curly_bracket_* right_curly_bracket_ = new Variable_right_curly_bracket_();

	public:
		NodeIsNonTerminalTemplate()
		{
			*class_name_ = Variable_class_name_(
				this, std::vector<VariableBase*>({GenerateVariable("NodeIsNonTerminal")}));
			*file_ = Variable_file_(this, std::vector<VariableBase*>({}));
			*header_guard_ = Variable_header_guard_(
				this, std::vector<VariableBase*>(
						  {GenerateVariable(language_name_underscore_->Upper()),
						   GenerateVariable("_AST_RELATION_"),
						   GenerateVariable(class_name_->Upper()), GenerateVariable("_H")}));
			*is_nonterminal_ = Variable_is_nonterminal_(this, std::vector<VariableBase*>({}));
			*language_name_ = Variable_language_name_(this, std::vector<VariableBase*>({}));
			*language_name_underscore_ = Variable_language_name_underscore_(
				this, std::vector<VariableBase*>({GenerateVariable(language_name_->Underscore())}));
			*left_angle_bracket_ = Variable_left_angle_bracket_(
				this, std::vector<VariableBase*>({GenerateVariable("<")}));
			*left_bracket_ =
				Variable_left_bracket_(this, std::vector<VariableBase*>({GenerateVariable("{")}));
			*left_curly_bracket_ = Variable_left_curly_bracket_(
				this, std::vector<VariableBase*>({GenerateVariable("(")}));
			*node_conversion_ = Variable_node_conversion_(
				this,
				std::vector<VariableBase*>({GenerateVariable("\n\t\tif (t == "),
											GenerateVariable(node_enum_value_type_->This()),
											GenerateVariable(")\n\t\t"), GenerateVariable("{"),
											GenerateVariable("\n\t\t\treturn "),
											GenerateVariable(is_nonterminal_->This()),
											GenerateVariable(";\n\t\t"), GenerateVariable("}")}));
			*node_enum_include_ = Variable_node_enum_include_(
				this, std::vector<VariableBase*>({GenerateVariable("#include \""),
												  GenerateVariable(language_name_->This()),
												  GenerateVariable("/Ast/Enum/Type"),
												  GenerateVariable("."), GenerateVariable("h\"")}));
			*node_enum_type_ = Variable_node_enum_type_(
				this, std::vector<VariableBase*>({GenerateVariable("::"),
												  GenerateVariable(language_name_->This()),
												  GenerateVariable("::ast::Type")}));
			*node_enum_value_type_ = Variable_node_enum_value_type_(
				this, std::vector<VariableBase*>({GenerateVariable(node_enum_type_->This()),
												  GenerateVariable("::"),
												  GenerateVariable(node_name_->This())}));
			*node_name_ = Variable_node_name_(this, std::vector<VariableBase*>({}));
			*right_angle_bracket_ = Variable_right_angle_bracket_(
				this, std::vector<VariableBase*>({GenerateVariable(">")}));
			*right_bracket_ =
				Variable_right_bracket_(this, std::vector<VariableBase*>({GenerateVariable("}")}));
			*right_curly_bracket_ = Variable_right_curly_bracket_(
				this, std::vector<VariableBase*>({GenerateVariable(")")}));

			variables_.emplace_back(class_name_);
			variables_.emplace_back(file_);
			variables_.emplace_back(header_guard_);
			variables_.emplace_back(is_nonterminal_);
			variables_.emplace_back(language_name_);
			variables_.emplace_back(language_name_underscore_);
			variables_.emplace_back(left_angle_bracket_);
			variables_.emplace_back(left_bracket_);
			variables_.emplace_back(left_curly_bracket_);
			variables_.emplace_back(node_conversion_);
			variables_.emplace_back(node_enum_include_);
			variables_.emplace_back(node_enum_type_);
			variables_.emplace_back(node_enum_value_type_);
			variables_.emplace_back(node_name_);
			variables_.emplace_back(right_angle_bracket_);
			variables_.emplace_back(right_bracket_);
			variables_.emplace_back(right_curly_bracket_);
		}

		virtual ~NodeIsNonTerminalTemplate()
		{
			for (auto* variable : variables_to_delete)
			{
				delete variable;
			}

			variables_to_delete.clear();
		}

	public:
		// Default DST functions

		/*!	\fn GetOutput
		 *
		 *	\brief returns the output with the given the current state.
		 */
		std::string GetOutput()
		{
			return file_->Content()->GetValue();
		}

		/*!	\fn GetVariables
		 *
		 *	\brief Returns all top level variables known in this template.
		 */
		std::vector<VariableBase*> GetVariables()
		{
			return variables_;
		}

	public:
	};
}

#endif // DEAMER_TEMPLATES_AST_TYPE_CPP_NODEISNONTERMINALTEMPLATE_h
