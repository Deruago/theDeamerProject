/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
/*
 * Part of the DeamerProject.
 * For more information go to: https://github.com/Deruago/theDeamerProject
 */

#ifndef DEAMER_LANGUAGE_REFERENCE_REVERSELOOKUPRESULT_H
#define DEAMER_LANGUAGE_REFERENCE_REVERSELOOKUPRESULT_H

#include "Deamer/Language/Reference/LDO.h"
#include <utility>

namespace deamer::language::reference
{
	/*!	\enum CacheLocation
	 *
	 *	\brief Used to specify where the result has been found.
	 */
	enum class CacheLocation
	{
		Unknown = 0,
		None,
		Primary,
		Secondary,
	};

	template<typename T_lookup>
	class ReverseLookupResult
	{
	private:
		bool reverseLookupSuccess;
		CacheLocation cacheLocation;
		std::vector<LDO<T_lookup>> results;

	public:
		ReverseLookupResult(bool reverseLookupSuccess_, CacheLocation cacheLocation_,
							std::vector<LDO<T_lookup>> results_)
			: reverseLookupSuccess(reverseLookupSuccess_),
			  cacheLocation(cacheLocation_),
			  results(std::move(results_))
		{
		}

		ReverseLookupResult(bool reverseLookupSuccess_, CacheLocation cacheLocation_)
			: reverseLookupSuccess(reverseLookupSuccess_),
			  cacheLocation(cacheLocation_)
		{
		}

		ReverseLookupResult(const ReverseLookupResult& rhs)
		{
			reverseLookupSuccess = rhs.reverseLookupSuccess;
			cacheLocation = rhs.cacheLocation;
			results = rhs.results;
		}
		ReverseLookupResult(ReverseLookupResult&& rhs) noexcept
		{
			reverseLookupSuccess = rhs.reverseLookupSuccess;
			cacheLocation = rhs.cacheLocation;
			results = std::move(rhs.results);
		}

		~ReverseLookupResult() = default;

	public:
		bool Success() const
		{
			return reverseLookupSuccess;
		}

		bool Fail() const
		{
			return !Success();
		}

		bool IsEmpty() const noexcept
		{
			return results.empty();
		}

		LDO<T_lookup> GetObject() const noexcept
		{
			return results[0];
		}

		const std::vector<LDO<T_lookup>>& GetObjects() const noexcept
		{
			return results;
		}

		size_t Size() const
		{
			return results.size();
		}

		bool IsPrimaryCache() const
		{
			return cacheLocation == CacheLocation::Primary;
		}

		bool IsSecondaryCache() const
		{
			return cacheLocation == CacheLocation::Secondary;
		}

		CacheLocation GetCacheLocation() const
		{
			return cacheLocation;
		}
	};
}

#endif // DEAMER_LANGUAGE_REFERENCE_REVERSELOOKUPRESULT_H
