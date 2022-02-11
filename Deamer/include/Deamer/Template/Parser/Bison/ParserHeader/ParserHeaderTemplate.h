#ifndef DEAMER_TEMPLATES_BISON_PARSER_PARSERHEADERTEMPLATE_h
#define DEAMER_TEMPLATES_BISON_PARSER_PARSERHEADERTEMPLATE_h

#include <string>
#include <variant>
#include <vector>

namespace deamer::templates::bison::parser
{
	/*!	\class ParserHeaderTemplate
	 *
	 *	\brief Generates code for "ParserHeaderTemplate"
	 *
	 *	\details This is generated by DST.
	 *	For more information visit: https://github.com/Deruago/DeamerStringTemplate
	 */
	class ParserHeaderTemplate
	{
	public:
		enum class Type
		{
			Unknown,
			Scope,

			// User defined types
			file_,
			header_guard_,
			language_name_,
			left_angle_bracket_,
			left_bracket_,
			left_curly_bracket_,
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
			::deamer::templates::bison::parser::ParserHeaderTemplate::Type enumerationValue)
		{
			switch (enumerationValue)
			{
			case ::deamer::templates::bison::parser::ParserHeaderTemplate::Type::file_: {
				return "file";
			}

			case ::deamer::templates::bison::parser::ParserHeaderTemplate::Type::header_guard_: {
				return "header_guard";
			}

			case ::deamer::templates::bison::parser::ParserHeaderTemplate::Type::language_name_: {
				return "language_name";
			}

			case ::deamer::templates::bison::parser::ParserHeaderTemplate::Type::
				left_angle_bracket_: {
				return "left_angle_bracket";
			}

			case ::deamer::templates::bison::parser::ParserHeaderTemplate::Type::left_bracket_: {
				return "left_bracket";
			}

			case ::deamer::templates::bison::parser::ParserHeaderTemplate::Type::
				left_curly_bracket_: {
				return "left_curly_bracket";
			}

			case ::deamer::templates::bison::parser::ParserHeaderTemplate::Type::
				right_angle_bracket_: {
				return "right_angle_bracket";
			}

			case ::deamer::templates::bison::parser::ParserHeaderTemplate::Type::right_bracket_: {
				return "right_bracket";
			}

			case ::deamer::templates::bison::parser::ParserHeaderTemplate::Type::
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

			::deamer::templates::bison::parser::ParserHeaderTemplate::Type type =
				::deamer::templates::bison::parser::ParserHeaderTemplate::Type::Unknown;

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
			::deamer::templates::bison::parser::ParserHeaderTemplate::ScopeType scope_type =
				::deamer::templates::bison::parser::ParserHeaderTemplate::ScopeType::Unknown;
			bool isReserved = false;

			VariableScope(
				::deamer::templates::bison::parser::ParserHeaderTemplate::ScopeType scope_type_,
				bool isReserved_ = false)
				: VariableBase(),
				  scope_type(scope_type_),
				  isReserved(isReserved_)
			{
				type = ::deamer::templates::bison::parser::ParserHeaderTemplate::Type::Scope;
			}

			VariableScope(
				const char* text,
				::deamer::templates::bison::parser::ParserHeaderTemplate::ScopeType scope_type_,
				bool isReserved_ = false)
				: VariableBase(text),
				  scope_type(scope_type_),
				  isReserved(isReserved_)
			{
				type = ::deamer::templates::bison::parser::ParserHeaderTemplate::Type::Scope;
			}

			VariableScope(
				std::vector<VariableBase*> variable,
				::deamer::templates::bison::parser::ParserHeaderTemplate::ScopeType scope_type_,
				bool isReserved_ = false)
				: VariableBase(variable),
				  scope_type(scope_type_),
				  isReserved(isReserved_)
			{
				type = ::deamer::templates::bison::parser::ParserHeaderTemplate::Type::Scope;
			}
		};

		struct Variable_ReservedScope_Upper : public VariableScope
		{
			VariableBase* base;
			Variable_ReservedScope_Upper(VariableBase* base_)
				: VariableScope(
					  ::deamer::templates::bison::parser::ParserHeaderTemplate::ScopeType::Upper_,
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
				: VariableScope(
					  ::deamer::templates::bison::parser::ParserHeaderTemplate::ScopeType::Lower_,
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
				: VariableScope(
					  ::deamer::templates::bison::parser::ParserHeaderTemplate::ScopeType::Snake_,
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
				: VariableScope(
					  ::deamer::templates::bison::parser::ParserHeaderTemplate::ScopeType::Slash_,
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
				: VariableScope(::deamer::templates::bison::parser::ParserHeaderTemplate::
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
				::deamer::templates::bison::parser::ParserHeaderTemplate::ScopeType::Default_,
				true);
			VariableBase* upper_ = new Variable_ReservedScope_Upper(this);
			VariableBase* lower_ = new Variable_ReservedScope_Lower(this);

			VariableBase* snake_ = new Variable_ReservedScope_Snake(this);
			VariableBase* slash_ = new Variable_ReservedScope_Slash(this);
			VariableBase* double_colon_ = new Variable_ReservedScope_DoubleColon(this);

			VariableBase* variable_field_ =
				new VariableScope(::deamer::templates::bison::parser::ParserHeaderTemplate::
									  ScopeType::Variable_Field_,
								  true);
			VariableBase* variable_field_separator_ =
				new VariableScope("\n",
								  ::deamer::templates::bison::parser::ParserHeaderTemplate::
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
				type = ::deamer::templates::bison::parser::ParserHeaderTemplate::Type::file_;
			}

			virtual ~Variable_file_() override = default;

			Variable_file_(ParserHeaderTemplate* parserheadertemplate_,
						   const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::bison::parser::ParserHeaderTemplate::Type::file_;
				*static_cast<VariableBase*>(Content_) = VariableBase(std::vector<VariableBase*>(
					{GenerateVariable("#ifndef "),
					 GenerateVariable(parserheadertemplate_->header_guard_->This()),
					 GenerateVariable("\n#define "),
					 GenerateVariable(parserheadertemplate_->header_guard_->This()),
					 GenerateVariable("\n\n#include <Deamer/External/Cpp/Parser/Interface/Parser"),
					 GenerateVariable("."),
					 GenerateVariable("h>\n\nnamespace "),
					 GenerateVariable(parserheadertemplate_->language_name_->This()),
					 GenerateVariable(" "),
					 GenerateVariable("{"),
					 GenerateVariable(" namespace parser "),
					 GenerateVariable("{"),
					 GenerateVariable("\n\n    class Parser : public "
									  "deamer::external::cpp::parser::Parser\n    "),
					 GenerateVariable("{"),
					 GenerateVariable(
						 "\n    public:\n        Parser() = default;\n        ~Parser() override = "
						 "default;\n\n    public:\n        deamer::external::cpp::ast::Tree* "
						 "Parse(const std::string& text) const override;\n    "),
					 GenerateVariable("}"),
					 GenerateVariable(";\n\n"),
					 GenerateVariable("}}"),
					 GenerateVariable("\n\n#endif // "),
					 GenerateVariable(parserheadertemplate_->header_guard_->This()),
					 GenerateVariable("\n")}));
				Content_->type =
					::deamer::templates::bison::parser::ParserHeaderTemplate::Type::Scope;

				*static_cast<VariableBase*>(Class_postfix_) =
					VariableBase(std::vector<VariableBase*>({}));
				Class_postfix_->type =
					::deamer::templates::bison::parser::ParserHeaderTemplate::Type::Scope;

				*static_cast<VariableBase*>(Extension_) =
					VariableBase(std::vector<VariableBase*>({GenerateVariable("h")}));
				Extension_->type =
					::deamer::templates::bison::parser::ParserHeaderTemplate::Type::Scope;

				*static_cast<VariableBase*>(File_name_) =
					VariableBase(std::vector<VariableBase*>({GenerateVariable("ParserHeader")}));
				File_name_->type =
					::deamer::templates::bison::parser::ParserHeaderTemplate::Type::Scope;

				*static_cast<VariableBase*>(Namespace_) = VariableBase(std::vector<VariableBase*>(
					{GenerateVariable("deamer::templates::bison::parser")}));
				Namespace_->type =
					::deamer::templates::bison::parser::ParserHeaderTemplate::Type::Scope;

				*static_cast<VariableBase*>(Target_language_) =
					VariableBase(std::vector<VariableBase*>({GenerateVariable("C++")}));
				Target_language_->type =
					::deamer::templates::bison::parser::ParserHeaderTemplate::Type::Scope;
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
				type =
					::deamer::templates::bison::parser::ParserHeaderTemplate::Type::header_guard_;
			}

			virtual ~Variable_header_guard_() override = default;

			Variable_header_guard_(ParserHeaderTemplate* parserheadertemplate_,
								   const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type =
					::deamer::templates::bison::parser::ParserHeaderTemplate::Type::header_guard_;
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

		struct Variable_language_name_ : public VariableScopes
		{
			static constexpr auto name = "language_name_";

			Variable_language_name_() : VariableScopes()
			{
				type =
					::deamer::templates::bison::parser::ParserHeaderTemplate::Type::language_name_;
			}

			virtual ~Variable_language_name_() override = default;

			Variable_language_name_(ParserHeaderTemplate* parserheadertemplate_,
									const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type =
					::deamer::templates::bison::parser::ParserHeaderTemplate::Type::language_name_;
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

		struct Variable_left_angle_bracket_ : public VariableScopes
		{
			static constexpr auto name = "left_angle_bracket_";

			Variable_left_angle_bracket_() : VariableScopes()
			{
				type = ::deamer::templates::bison::parser::ParserHeaderTemplate::Type::
					left_angle_bracket_;
			}

			virtual ~Variable_left_angle_bracket_() override = default;

			Variable_left_angle_bracket_(ParserHeaderTemplate* parserheadertemplate_,
										 const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::bison::parser::ParserHeaderTemplate::Type::
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
				type =
					::deamer::templates::bison::parser::ParserHeaderTemplate::Type::left_bracket_;
			}

			virtual ~Variable_left_bracket_() override = default;

			Variable_left_bracket_(ParserHeaderTemplate* parserheadertemplate_,
								   const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type =
					::deamer::templates::bison::parser::ParserHeaderTemplate::Type::left_bracket_;
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
				type = ::deamer::templates::bison::parser::ParserHeaderTemplate::Type::
					left_curly_bracket_;
			}

			virtual ~Variable_left_curly_bracket_() override = default;

			Variable_left_curly_bracket_(ParserHeaderTemplate* parserheadertemplate_,
										 const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::bison::parser::ParserHeaderTemplate::Type::
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

		struct Variable_right_angle_bracket_ : public VariableScopes
		{
			static constexpr auto name = "right_angle_bracket_";

			Variable_right_angle_bracket_() : VariableScopes()
			{
				type = ::deamer::templates::bison::parser::ParserHeaderTemplate::Type::
					right_angle_bracket_;
			}

			virtual ~Variable_right_angle_bracket_() override = default;

			Variable_right_angle_bracket_(ParserHeaderTemplate* parserheadertemplate_,
										  const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::bison::parser::ParserHeaderTemplate::Type::
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
				type =
					::deamer::templates::bison::parser::ParserHeaderTemplate::Type::right_bracket_;
			}

			virtual ~Variable_right_bracket_() override = default;

			Variable_right_bracket_(ParserHeaderTemplate* parserheadertemplate_,
									const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type =
					::deamer::templates::bison::parser::ParserHeaderTemplate::Type::right_bracket_;
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
				type = ::deamer::templates::bison::parser::ParserHeaderTemplate::Type::
					right_curly_bracket_;
			}

			virtual ~Variable_right_curly_bracket_() override = default;

			Variable_right_curly_bracket_(ParserHeaderTemplate* parserheadertemplate_,
										  const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::bison::parser::ParserHeaderTemplate::Type::
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
		// e.g. ParserHeaderTemplate.member = "auto-generated";
		Variable_file_* file_ = new Variable_file_();
		Variable_header_guard_* header_guard_ = new Variable_header_guard_();
		Variable_language_name_* language_name_ = new Variable_language_name_();
		Variable_left_angle_bracket_* left_angle_bracket_ = new Variable_left_angle_bracket_();
		Variable_left_bracket_* left_bracket_ = new Variable_left_bracket_();
		Variable_left_curly_bracket_* left_curly_bracket_ = new Variable_left_curly_bracket_();
		Variable_right_angle_bracket_* right_angle_bracket_ = new Variable_right_angle_bracket_();
		Variable_right_bracket_* right_bracket_ = new Variable_right_bracket_();
		Variable_right_curly_bracket_* right_curly_bracket_ = new Variable_right_curly_bracket_();

	public:
		ParserHeaderTemplate()
		{
			*file_ = Variable_file_(this, std::vector<VariableBase*>({}));
			*header_guard_ = Variable_header_guard_(
				this, std::vector<VariableBase*>({GenerateVariable(language_name_->This()),
												  GenerateVariable("_BISON_PARSER_H")}));
			*language_name_ = Variable_language_name_(this, std::vector<VariableBase*>({}));
			*left_angle_bracket_ = Variable_left_angle_bracket_(
				this, std::vector<VariableBase*>({GenerateVariable("<")}));
			*left_bracket_ =
				Variable_left_bracket_(this, std::vector<VariableBase*>({GenerateVariable("{")}));
			*left_curly_bracket_ = Variable_left_curly_bracket_(
				this, std::vector<VariableBase*>({GenerateVariable("(")}));
			*right_angle_bracket_ = Variable_right_angle_bracket_(
				this, std::vector<VariableBase*>({GenerateVariable(">")}));
			*right_bracket_ =
				Variable_right_bracket_(this, std::vector<VariableBase*>({GenerateVariable("}")}));
			*right_curly_bracket_ = Variable_right_curly_bracket_(
				this, std::vector<VariableBase*>({GenerateVariable(")")}));

			variables_.emplace_back(file_);
			variables_.emplace_back(header_guard_);
			variables_.emplace_back(language_name_);
			variables_.emplace_back(left_angle_bracket_);
			variables_.emplace_back(left_bracket_);
			variables_.emplace_back(left_curly_bracket_);
			variables_.emplace_back(right_angle_bracket_);
			variables_.emplace_back(right_bracket_);
			variables_.emplace_back(right_curly_bracket_);
		}

		virtual ~ParserHeaderTemplate()
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

#endif // DEAMER_TEMPLATES_BISON_PARSER_PARSERHEADERTEMPLATE_h
