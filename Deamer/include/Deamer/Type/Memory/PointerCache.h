#ifndef DEAMER_TYPE_MEMORY_POINTERCACHE_H
#define DEAMER_TYPE_MEMORY_POINTERCACHE_H

#include "Deamer/Language/Type/Definition/Object/Type.h"
#include <map>
#include <set>

namespace deamer::type {

	/*! \class PointerCache
	 *
	 *  \brief PointerCache can be used to cache pointers based on enumerations.
	 */
    template<typename ElementBaseEnum, typename ElementBaseType, typename ConvertTypeToEnum>
    class PointerCache
    {
    private:
    public:
        std::map<ElementBaseEnum, std::set<ElementBaseType*>> Cache;

    	template<typename P>
        void Register(const P* const newElement) const noexcept
        {
            //Cache[ConvertTypeToEnum<P>()::value].insert(newElement);
        }

    };
}

#endif //DEAMER_TYPE_MEMORY_POINTERCACHE_H