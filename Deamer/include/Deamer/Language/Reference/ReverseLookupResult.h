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

#include <utility>

namespace deamer::language::reference
{
	template<typename T_lookup>
	class ReverseLookupResult
	{
	private:
		bool reverseLookupSuccess;
		std::vector<const T_lookup*> results;

	public:
		ReverseLookupResult(bool reverseLookupSuccess_, std::vector<const T_lookup*> results_)
			: reverseLookupSuccess(reverseLookupSuccess_),
			  results(std::move(results_))
		{
		}

		ReverseLookupResult(bool reverseLookupSuccess_)
			: reverseLookupSuccess(reverseLookupSuccess_)
		{
		}

		ReverseLookupResult(const ReverseLookupResult& rhs)
		{
			reverseLookupSuccess = rhs.reverseLookupSuccess;
			results = rhs.results;
		}
		ReverseLookupResult(ReverseLookupResult&& rhs) noexcept
		{
			reverseLookupSuccess = rhs.reverseLookupSuccess;
			results = std::move(rhs.results);
		}

		~ReverseLookupResult() = default;

	public:
		bool Success() const
		{
			return reverseLookupSuccess;
		}

		bool IsEmpty() const noexcept
		{
			return results.empty();
		}

		const T_lookup* GetObject() const noexcept
		{
			return results[0];
		}

		const std::vector<const T_lookup*>& GetObjects() const noexcept
		{
			return results;
		}

		size_t Size() const
		{
			return results.size();
		}
	};
}

#endif // DEAMER_LANGUAGE_REFERENCE_REVERSELOOKUPRESULT_H
