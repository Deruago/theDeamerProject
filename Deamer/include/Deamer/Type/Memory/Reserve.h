#ifndef DEAMER_TYPE_MEMORY_RESERVE_H
#define DEAMER_TYPE_MEMORY_RESERVE_H

#include <cstring>

namespace deamer::type {

    /*! \class Reserve
     *
     *  \brief Reserve is a memory reserving class, used to reserve memory.
     *
     *  \details Reserve reserves memory for a type T, it can be used whenever you need a specific address to point to, but that address cannot be initialized immediately.
     *  This feature of initializing later, is used in Language generation classes.
     *
     *  \warning The reserved memory is allocated in the heap, and not deleted in this class. You are required to ask the Pointer and delete the pointer yourself.
     *
     *  \tparam T the type Reserve will reserve memory for.
     */
    template<typename T>
    class Reserve
    {
    private:
        char* const t_Reserved = static_cast<char*>(::operator new(size));
    public:
        constexpr static auto size = sizeof(T);

        using type = T;
        using pointer = T*;
        using reference = T&;

        Reserve() = default;

        explicit Reserve(const T& t) noexcept
        {
            Set(t);
        }

        explicit Reserve(const T* t) noexcept : Reserve(*t) {}

        explicit Reserve(T&& t) noexcept : Reserve(t) {}

        /*! \fn Set(const T& t)
         *
         *  \brief Set will copy the given variable into the reserved memory.
         *
         *  \note The destructor will be called if the variable is out of scope.
         */
        void Set(const T& t) const noexcept
        {
            std::memcpy(t_Reserved, &t, size);
        }

        /*! \fn Set(const T* t)
         *
         *  \brief Set will copy the given pointer into the reserved memory.
         *
         *  \note The destructor will be called if the variable is out of scope.
         */
        void Set(const T* t) const noexcept
        {
            std::memcpy(t_Reserved, t, size);
        }

        /*! \fn Get
         *
         *  \brief Returns a reference to the reserved memory.
         */
        T& Get() const noexcept
        {
            return *Pointer();
        }

        /*! \fn Pointer
         *
         *  \brief Returns a Pointer to the reserved memory.
         */
        T* Pointer() const noexcept
        {
            return (pointer)t_Reserved;
        }

        ~Reserve() = default;

        Reserve& operator=(const Reserve& reserve) = delete;

        /*! \fn operator=
         *
         *  \brief Will assign the variable given to the reserved memory.
         *
         *  \note The destructor will be called if the variable is out of scope.
         *  \see Set
         */
        Reserve& operator=(const T& t) const noexcept
        {
            if (&t == Pointer())
            {
                return *this;
            }

            Set(t);
            return *this;
        }

        /*! \fn operator->
         *
         *  \brief Returns a pointer to the reserved memory.
         */
        T* operator->()
        {
            return Pointer();
        }

        void operator()(const T& t) const noexcept
        {
            Set(t);
        }

        void operator()(const T* t) const noexcept
        {
            Set(t);
        }
    };
}

#endif //DEAMER_TYPE_MEMORY_RESERVE_H