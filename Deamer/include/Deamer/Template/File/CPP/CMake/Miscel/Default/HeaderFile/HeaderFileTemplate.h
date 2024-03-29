#ifndef DEAMER_TEMPLATES_CMAKE_MISCEL_STANDARD_HEADERFILETEMPLATE_h
#define DEAMER_TEMPLATES_CMAKE_MISCEL_STANDARD_HEADERFILETEMPLATE_h

#include <string>
#include <variant>
#include <vector>

namespace deamer::templates::cmake::miscel::standard
{
	/*!	\class HeaderFileTemplate
	 *
	 *	\brief Generates code for "HeaderFileTemplate"
	 *
	 *	\details This is generated by DST.
	 *	For more information visit: https://github.com/Deruago/DeamerStringTemplate
	 */
	class HeaderFileTemplate
	{
	public:
		enum class Type
		{
			Unknown,
			Scope,

			// User defined types
			const_qualifier_,
			file_,
			header_guard_,
			languageName_,
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
			::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type enumerationValue)
		{
			switch (enumerationValue)
			{
			case ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
				const_qualifier_: {
				return "const_qualifier";
			}

			case ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::file_: {
				return "file";
			}

			case ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
				header_guard_: {
				return "header_guard";
			}

			case ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
				languageName_: {
				return "languageName";
			}

			case ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
				left_angle_bracket_: {
				return "left_angle_bracket";
			}

			case ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
				left_bracket_: {
				return "left_bracket";
			}

			case ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
				left_curly_bracket_: {
				return "left_curly_bracket";
			}

			case ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
				right_angle_bracket_: {
				return "right_angle_bracket";
			}

			case ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
				right_bracket_: {
				return "right_bracket";
			}

			case ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
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

			::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type type =
				::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::Unknown;

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
			::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::ScopeType scope_type =
				::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::ScopeType::
					Unknown;
			bool isReserved = false;

			VariableScope(
				::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::ScopeType
					scope_type_,
				bool isReserved_ = false)
				: VariableBase(),
				  scope_type(scope_type_),
				  isReserved(isReserved_)
			{
				type =
					::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::Scope;
			}

			VariableScope(
				const char* text,
				::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::ScopeType
					scope_type_,
				bool isReserved_ = false)
				: VariableBase(text),
				  scope_type(scope_type_),
				  isReserved(isReserved_)
			{
				type =
					::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::Scope;
			}

			VariableScope(
				std::vector<VariableBase*> variable,
				::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::ScopeType
					scope_type_,
				bool isReserved_ = false)
				: VariableBase(variable),
				  scope_type(scope_type_),
				  isReserved(isReserved_)
			{
				type =
					::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::Scope;
			}
		};

		struct Variable_ReservedScope_Upper : public VariableScope
		{
			VariableBase* base;
			Variable_ReservedScope_Upper(VariableBase* base_)
				: VariableScope(::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::
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
				: VariableScope(::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::
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
				: VariableScope(::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::
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
				: VariableScope(::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::
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
				: VariableScope(::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::
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
			VariableBase* default_ =
				new VariableScope(::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::
									  ScopeType::Default_,
								  true);
			VariableBase* upper_ = new Variable_ReservedScope_Upper(this);
			VariableBase* lower_ = new Variable_ReservedScope_Lower(this);

			VariableBase* snake_ = new Variable_ReservedScope_Snake(this);
			VariableBase* slash_ = new Variable_ReservedScope_Slash(this);
			VariableBase* double_colon_ = new Variable_ReservedScope_DoubleColon(this);

			VariableBase* variable_field_ =
				new VariableScope(::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::
									  ScopeType::Variable_Field_,
								  true);
			VariableBase* variable_field_separator_ =
				new VariableScope("\n",
								  ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::
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
		struct Variable_const_qualifier_ : public VariableScopes
		{
			static constexpr auto name = "const_qualifier_";

			Variable_const_qualifier_() : VariableScopes()
			{
				type = ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
					const_qualifier_;
			}

			virtual ~Variable_const_qualifier_() override = default;

			Variable_const_qualifier_(HeaderFileTemplate* headerfiletemplate_,
									  const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
					const_qualifier_;
			}

			Variable_const_qualifier_& operator=(const Variable_const_qualifier_& variable)
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
				type =
					::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::file_;
			}

			virtual ~Variable_file_() override = default;

			Variable_file_(HeaderFileTemplate* headerfiletemplate_,
						   const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type =
					::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::file_;
				*static_cast<VariableBase*>(Content_) = VariableBase(std::vector<VariableBase*>(
					{GenerateVariable("#ifndef "),
					 GenerateVariable(headerfiletemplate_->header_guard_->This()),
					 GenerateVariable("\n#define "),
					 GenerateVariable(headerfiletemplate_->header_guard_->This()),
					 GenerateVariable("\n\n// This is a generated file for the language: "),
					 GenerateVariable(headerfiletemplate_->languageName_->This()),
					 GenerateVariable("\n\nnamespace "),
					 GenerateVariable(headerfiletemplate_->languageName_->This()),
					 GenerateVariable("\n"), GenerateVariable("{"), GenerateVariable("\n"),
					 GenerateVariable("}"), GenerateVariable("\n\n#endif // "),
					 GenerateVariable(headerfiletemplate_->header_guard_->This())}));
				Content_->type =
					::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::Scope;

				*static_cast<VariableBase*>(Class_postfix_) =
					VariableBase(std::vector<VariableBase*>({}));
				Class_postfix_->type =
					::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::Scope;

				*static_cast<VariableBase*>(Extension_) =
					VariableBase(std::vector<VariableBase*>({GenerateVariable("h")}));
				Extension_->type =
					::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::Scope;

				*static_cast<VariableBase*>(File_name_) =
					VariableBase(std::vector<VariableBase*>({GenerateVariable("HeaderFile")}));
				File_name_->type =
					::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::Scope;

				*static_cast<VariableBase*>(Namespace_) = VariableBase(std::vector<VariableBase*>(
					{GenerateVariable("deamer::templates::cmake::miscel::standard")}));
				Namespace_->type =
					::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::Scope;

				*static_cast<VariableBase*>(Target_language_) =
					VariableBase(std::vector<VariableBase*>({GenerateVariable("C++")}));
				Target_language_->type =
					::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::Scope;
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
				type = ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
					header_guard_;
			}

			virtual ~Variable_header_guard_() override = default;

			Variable_header_guard_(HeaderFileTemplate* headerfiletemplate_,
								   const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
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

		struct Variable_languageName_ : public VariableScopes
		{
			static constexpr auto name = "languageName_";

			Variable_languageName_() : VariableScopes()
			{
				type = ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
					languageName_;
			}

			virtual ~Variable_languageName_() override = default;

			Variable_languageName_(HeaderFileTemplate* headerfiletemplate_,
								   const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
					languageName_;
			}

			Variable_languageName_& operator=(const Variable_languageName_& variable)
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
				type = ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
					left_angle_bracket_;
			}

			virtual ~Variable_left_angle_bracket_() override = default;

			Variable_left_angle_bracket_(HeaderFileTemplate* headerfiletemplate_,
										 const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
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
				type = ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
					left_bracket_;
			}

			virtual ~Variable_left_bracket_() override = default;

			Variable_left_bracket_(HeaderFileTemplate* headerfiletemplate_,
								   const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
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
				type = ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
					left_curly_bracket_;
			}

			virtual ~Variable_left_curly_bracket_() override = default;

			Variable_left_curly_bracket_(HeaderFileTemplate* headerfiletemplate_,
										 const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
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
				type = ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
					right_angle_bracket_;
			}

			virtual ~Variable_right_angle_bracket_() override = default;

			Variable_right_angle_bracket_(HeaderFileTemplate* headerfiletemplate_,
										  const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
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
				type = ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
					right_bracket_;
			}

			virtual ~Variable_right_bracket_() override = default;

			Variable_right_bracket_(HeaderFileTemplate* headerfiletemplate_,
									const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
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
				type = ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
					right_curly_bracket_;
			}

			virtual ~Variable_right_curly_bracket_() override = default;

			Variable_right_curly_bracket_(HeaderFileTemplate* headerfiletemplate_,
										  const std::vector<VariableBase*>& variables)
				: VariableScopes(variables)
			{
				type = ::deamer::templates::cmake::miscel::standard::HeaderFileTemplate::Type::
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
		// e.g. HeaderFileTemplate.member = "auto-generated";
		Variable_const_qualifier_* const_qualifier_ = new Variable_const_qualifier_();
		Variable_file_* file_ = new Variable_file_();
		Variable_header_guard_* header_guard_ = new Variable_header_guard_();
		Variable_languageName_* languageName_ = new Variable_languageName_();
		Variable_left_angle_bracket_* left_angle_bracket_ = new Variable_left_angle_bracket_();
		Variable_left_bracket_* left_bracket_ = new Variable_left_bracket_();
		Variable_left_curly_bracket_* left_curly_bracket_ = new Variable_left_curly_bracket_();
		Variable_right_angle_bracket_* right_angle_bracket_ = new Variable_right_angle_bracket_();
		Variable_right_bracket_* right_bracket_ = new Variable_right_bracket_();
		Variable_right_curly_bracket_* right_curly_bracket_ = new Variable_right_curly_bracket_();

	public:
		HeaderFileTemplate()
		{
			*const_qualifier_ = Variable_const_qualifier_(
				this, std::vector<VariableBase*>({GenerateVariable("const")}));
			*file_ = Variable_file_(this, std::vector<VariableBase*>({}));
			*header_guard_ = Variable_header_guard_(
				this, std::vector<VariableBase*>(
						  {GenerateVariable(languageName_->Upper()), GenerateVariable("_"),
						   GenerateVariable(languageName_->Upper()), GenerateVariable("_H")}));
			*languageName_ = Variable_languageName_(this, std::vector<VariableBase*>({}));
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

			variables_.emplace_back(const_qualifier_);
			variables_.emplace_back(file_);
			variables_.emplace_back(header_guard_);
			variables_.emplace_back(languageName_);
			variables_.emplace_back(left_angle_bracket_);
			variables_.emplace_back(left_bracket_);
			variables_.emplace_back(left_curly_bracket_);
			variables_.emplace_back(right_angle_bracket_);
			variables_.emplace_back(right_bracket_);
			variables_.emplace_back(right_curly_bracket_);
		}

		virtual ~HeaderFileTemplate()
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

#endif // DEAMER_TEMPLATES_CMAKE_MISCEL_STANDARD_HEADERFILETEMPLATE_h
