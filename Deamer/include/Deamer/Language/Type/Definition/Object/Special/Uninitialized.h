#ifndef DEAMER_LANGUAGE_TYPE_DEFINITION_SPECIAL_UNINITIALIZED_H
#define DEAMER_LANGUAGE_TYPE_DEFINITION_SPECIAL_UNINITIALIZED_H

#include "Deamer/Language/Type/Definition/Object/Base.h"
#include <string>
#include <type_traits>

namespace deamer::language::type::definition::object::special
{
	/*!	\class Uninitialized
	 *
	 *	\brief Uninitialized is a special LDO to specify uninitialized LDO's
	 *
	 *	\tparam Base_T The LDO that is uninitialized.
	 *
	 *	\details An Uninitialized LDO can be used for varies situations.
	 *	It can serve as a pure virtual LDO, that one needs to replace (override) when inheriting
	 *	from a given language.
	 *
	 *	The other use case is for when you forgot to specify a definition for a given LDO. This use
	 *	case is most often used by DLDL. The threat analyzer can give meaningful error messages,
	 *	without the compiler throwing errors.
	 *
	 *	Example:
	 *	```c++
	 *	SafeReserve<Uninitialized<Terminal>> VAR;
	 *
	 *	void GenerateObjects()
	 *	{
	 *		VAR.Set(Uninitialized<Terminal>("Terminal", "VAR", "There is no definition for VAR!"));
	 *	}
	 *	```
	 *
	 *	\note
	 *	- The given base parameter must be an LDO
	 *	- The given base parameter must be default constructable.
	 */
	template<typename Base_T,
			 std::enable_if_t<
				 std::is_base_of_v<::deamer::language::type::definition::object::Base, Base_T>,
				 bool> = true>
	class Uninitialized : public Base_T
	{
	private:
		std::string supposedType;
		std::string supposedName;
		std::string reasonForBeingUnInitialized;

	public:
		Uninitialized(std::string supposedType_ = "unknown", std::string supposedName_ = "unknown",
					  std::string reasonForBeingUnInitialized_ = "unknown")
			: Base_T(),
			  supposedType(supposedType_),
			  supposedName(supposedName_),
			  reasonForBeingUnInitialized(reasonForBeingUnInitialized_)
		{
			this->SetAsUninitialized();
		}

		void Set(std::string supposedType_ = "unknown", std::string supposedName_ = "unknown",
				 std::string reasonForBeingUnInitialized_ = "unknown")
		{
			supposedType = supposedType_;
			supposedName = supposedName_;
			reasonForBeingUnInitialized = reasonForBeingUnInitialized_;
		}
	};
}

#endif // DEAMER_LANGUAGE_TYPE_DEFINITION_SPECIAL_UNINITIALIZED_H
