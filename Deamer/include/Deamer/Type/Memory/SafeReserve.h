#ifndef DEAMER_TYPE_MEMORY_SAFERESERVE_H
#define DEAMER_TYPE_MEMORY_SAFERESERVE_H

namespace deamer::type {

    /*! \class SafeReserve
     *
     *  \brief SafeReserve is a memory reserving class, used to reserve memory. It is a safe counterpart to Reserve.
     *
     *  \note The type requires a default constructor, to initialize the class with default values.
     *  The constructor may be private or protected, but remember to friend the SafeReserve class.
     *
     *  \warning Note it reserves memory. You need to manually delete this memory.
     */
    template<typename T>
    class SafeReserve
    {
    private:
        T* const t_Reserved = new T;
    public:
        constexpr static auto size = sizeof(T);

        using type = T;
        using pointer = T*;
        using reference = T&;

        SafeReserve() = default;

        explicit SafeReserve(const T& t) noexcept
        {
            Set(t);
        }

        explicit SafeReserve(const T* t) noexcept : SafeReserve(*t) {}

        explicit SafeReserve(T&& t) noexcept : SafeReserve(t) {}

        /*! \fn Set(const T& t)
         *
         *  \brief Set will copy the given variable into the reserved memory.
         *
         *  \note The destructor will be called if the variable is out of scope.
         */
        void Set(const T& t) const noexcept
        {
            *t_Reserved = T(t);
        }

        /*! \fn Set(const T* t)
         *
         *  \brief Set will copy the given pointer into the reserved memory.
         *
         *  \note The destructor will be called if the variable is out of scope.
         */
        void Set(const T* t) const noexcept
        {
            Set(*t);
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
            return t_Reserved;
        }
    	
        T* Pointer() noexcept
        {
            return t_Reserved;
        }

        ~SafeReserve() = default;

        SafeReserve& operator=(const SafeReserve& reserve) = delete;

        /*! \fn operator=
         *
         *  \brief Will assign the variable given to the reserved memory.
         *
         *  \note The destructor will be called if the variable is out of scope.
         *  \see Set
         */
        SafeReserve& operator=(const T& t) const noexcept
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

        /*! \fn operator->
         *
         *  \brief Returns a pointer to the reserved memory.
         */
        const T* operator->() const
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

#endif //DEAMER_TYPE_MEMORY_SAFERESERVE_H