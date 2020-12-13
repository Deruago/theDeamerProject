/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
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