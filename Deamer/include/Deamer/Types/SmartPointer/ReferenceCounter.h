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

#ifndef DEAMER_TYPES_SMARTPOINTER_REFERENCECOUNTER_H
#define DEAMER_TYPES_SMARTPOINTER_REFERENCECOUNTER_H

 /*
  * ReferenceCounter is a simple class that can be used for reference counting.
  * It automatically adds and removes counts, based on the amount of copies there are.
  * Smart pointers such as SharedPtr use this reference counter.
  */

#include "Deamer/Types/SmartPointer/Exception/CountOutOfRange.h"
#include "Deamer/Types/Exception/NullpointerException.h"

namespace deamer
{
	class ReferenceCounter
	{
	private:
		unsigned* counter = nullptr;
	public:

		void Initialise()
		{
			CreateCounter();
		}
		
		ReferenceCounter() = default;

		ReferenceCounter(const ReferenceCounter& referenceCounter)
		{
			operator=(referenceCounter);
		}

		ReferenceCounter(ReferenceCounter&& referenceCounter) noexcept
		{
			operator=(referenceCounter);
		}

		ReferenceCounter& operator=(const ReferenceCounter& rhs)
		{
			if (this == &rhs)
				return *this;

			CopyCounter(rhs.counter);
			return *this;
		}

		ReferenceCounter& operator=(ReferenceCounter&& rhs) noexcept
		{
			if (this == &rhs)
				return *this;

			CopyCounter(rhs.counter);
			return *this;
		}

		bool IsLastReference() const
		{
			if (!CounterExists())
			{
				return false;
			}
			
			return (*this->counter == 1);
		}

		unsigned GetCounter() const
		{
			if (!CounterExists())
			{
				throw NullpointerException();
			}
			return *this->counter;
		}

		~ReferenceCounter()
		{
			DeleteCounter();
		}
		
	private:
		void IncreaseCounter() const
		{
			if (CounterExists())
			{
				(*counter) += 1;
			}
		}

		void DecreaseCounter() const
		{
			if (!CounterExists())
			{
				return;
			}

			if (*this->counter == 0)
			{
				throw CountOutOfRange();
			}
			
			(*counter) -= 1;
		}

		void DecreaseCounterNoexcept() const noexcept
		{
			if (!CounterExists())
			{
				return;
			}

			if (*this->counter == 0)
			{
				return;
			}

			(*counter) -= 1;
		}

		bool CounterExists() const
		{
			return (this->counter != nullptr);
		}
	private:
		void CreateCounter()
		{
			counter = new unsigned;
			*counter = 1;
		}

		void CopyCounter(unsigned* counter_)
		{
			this->counter = counter_;
			this->IncreaseCounter();
		}

		void DeleteCounter()
		{
			if (CounterExists() && IsLastReference())
			{
				delete counter;
				counter = nullptr;
			}
			else
			{
				DecreaseCounterNoexcept();
			}
		}
	};
}

#endif //DEAMER_TYPES_SMARTPOINTER_REFERENCECOUNTER_H